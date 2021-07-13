#include "TableWidget.h"
#include "CommonConstants.h"

#include <QHeaderView>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QSpinBox>

TableWidget::TableWidget(QWidget* parent) :
	QTableWidget(parent),
	m_rowsCount(0),
	m_colsCount(0),
	m_lastSelectedRow(-1),
	m_lastSelectedCol(-1)
{
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

TableWidget::~TableWidget()
{

}

void TableWidget::setColumnsCount(int columnsCount)
{
	m_colsCount = columnsCount + 1;
	setColumnCount(m_colsCount);
}

void TableWidget::setHeaders(const QStringList& headers)
{
	auto additionalButtonHeaders = headers;
	additionalButtonHeaders.append(QString(" "));
	m_columnHeaders = additionalButtonHeaders;
	setHorizontalHeaderLabels(m_columnHeaders);
}

void TableWidget::createMembers()
{

}

void TableWidget::initializeMembers()
{
	verticalHeader()->setVisible(false);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TableWidget::makeConnections()
{
	QObject::connect(this, &QTableWidget::cellChanged, this, &TableWidget::onCellEdited);
	QObject::connect(this, &QTableWidget::currentCellChanged, this, &TableWidget::onCurrentCellChanged);
}

void TableWidget::setupLayouts()
{

}

void TableWidget::removeRow(int row)
{
	for (auto& [_, buttons] : m_stringToButtonsMapping) {
		buttons.erase(buttons.begin() + row);
	}
	m_cellValues.erase(m_cellValues.begin() + row);
	m_rowsCount--;
	QTableWidget::removeRow(row);
}



void TableWidget::onCellEdited(int row, int col)
{
	if (col >= m_colsCount - 1) {
		return;
	}
	if (m_lastSelectedCol == col && m_lastSelectedRow == row) {
		m_changedRows.at(row) = isRowChanged(row);
		configureSave(row);
	}
}

bool TableWidget::isRowChanged(int row)
{
	bool changed = false;
	for (auto i = 0; i < m_colsCount - 1; ++i) {
		if (m_columnWidgetType[i] == "Item" || 
			m_columnWidgetType[i] == "TimeItem" || 
			m_columnWidgetType[i] == "DateItem") {
			QString value = item(row, i)->text();
			changed |= (m_cellValues[row][i] != value);
		}
		else if (m_columnWidgetType[i] == "ComboBox") {
			QString value = m_rowToComboBoxMapping[row]->currentText();
			changed |= (m_cellValues[row][i] != m_rowToComboBoxMapping[row]->currentText());
		}
	}
	return changed;
}

bool TableWidget::isRowChanged()
{
	if (m_changedRows.size() == 0) {
		return false;
	}
	return std::any_of(m_changedRows.begin(), m_changedRows.end(), [](bool v) { return v; });
}

int TableWidget::getButtonRowIndex(QToolButton* clickedButton, const QString& groupName)
{
	auto group = m_stringToButtonsMapping[groupName];
	for (auto i = 0; i < group.size(); ++i) {
		if (clickedButton == group.at(i)) {
			return i;
		}
	}
	return -1;
}

void TableWidget::initializeColRowValues(int size)
{
	clear();

	m_rowsCount = 0;
	m_stringToButtonsMapping.clear();
	m_rowToComboBoxMapping.clear();

	m_changedRows.resize(size);
	m_changedRows.assign(size, false);
	
	m_cellValues.resize(size);
	m_cellValues.assign(size, std::vector<QString>(m_colsCount, ""));

	setHorizontalHeaderLabels(m_columnHeaders);
}

void TableWidget::configureSave(int row)
{
	if (!m_changedRows[row]) {
		m_stringToButtonsMapping["Save"][row]->setDisabled(true);
		m_stringToButtonsMapping["Cancel"][row]->setDisabled(true);
	}
	else {
		m_stringToButtonsMapping["Save"][row]->setDisabled(false);
		m_stringToButtonsMapping["Cancel"][row]->setDisabled(false);
	}
}

void TableWidget::onCellClicked(int row, int col)
{
	m_lastSelectedRow = row;
	m_lastSelectedCol = col;
}

void TableWidget::onCurrentCellChanged(int row, int col, int prevRow, int prevCol)
{
	m_lastSelectedCol = col;
	m_lastSelectedRow = row;
}

void TableWidget::addItem(int row, int col, bool isEditable, const QString& value)
{
	QTableWidgetItem* item = new QTableWidgetItem(value);
	if (!isEditable) {
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	}
	setItem(row, col, item);
	if (row < m_cellValues.size() && col < m_cellValues.front().size()) {
		m_cellValues[row][col] = value;
	}
	m_columnWidgetType[col] = "Item";
}

void TableWidget::addTimeItem(int row, int col, bool isEditable, int value) {
	QString initialValue = QString::asprintf(Constants::Formats::timeFormat, value / 60, value % 60);
	QTableWidgetItem* item = new QTableWidgetItem(initialValue);
	if (!isEditable) {
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	}
	setItem(row, col, item);
	if (row < m_cellValues.size() && col < m_cellValues.front().size()) {
		m_cellValues[row][col] = initialValue;
	};
	m_columnWidgetType[col] = "TimeItem";
}

void TableWidget::addDateItem(int row, int col, bool isEditable, const QDate& date) {
	QString initialValue = date.toString(Constants::Formats::dateFormat);
	QTableWidgetItem* item = new QTableWidgetItem(initialValue);
	if (!isEditable) {
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	}
	setItem(row, col, item);
	if (row < m_cellValues.size() && col < m_cellValues.front().size()) {
		m_cellValues[row][col] = initialValue;
	};
	m_columnWidgetType[col] = "DateItem";
}

void TableWidget::addComboBox(int row, int col, const QString& state, const QStringList& states)
{
	QWidget* pWidget = new QWidget();
	QComboBox* box = new QComboBox();
	box->addItems(states);
	box->setCurrentText(state);

	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(box);
	pLayout->setAlignment(Qt::AlignCenter);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pWidget->setLayout(pLayout);

	setCellWidget(row, col, pWidget);

	m_cellValues[row][col] = state;
	m_rowToComboBoxMapping[row] = box;
	m_columnWidgetType[col] = "ComboBox";

	QObject::connect(box, &QComboBox::currentTextChanged, this, [this, row, col](const QString& text) {
		m_changedRows.at(row) = isRowChanged(row);
		configureSave(row);
	});
}

void TableWidget::addSpinBox(int row, int col, int minValue, int maxValue, int value, bool disabled) {
	QWidget* pWidget = new QWidget();
	QSpinBox* box = new QSpinBox();
	box->setMinimum(minValue);
	box->setMaximum(maxValue);
	box->setValue(value);

	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(box);
	pLayout->setAlignment(Qt::AlignCenter);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pWidget->setLayout(pLayout);

	setCellWidget(row, col, pWidget);

	m_cellValues[row][col] = QString::number(value);
	m_columnWidgetType[col] = "SpinBox";
	
	if (disabled) {
		box->setDisabled(true);
	}

	QObject::connect(box, qOverload<const QString &>(&QSpinBox::valueChanged), this, [this, row, col](const QString& text) {
		m_changedRows.at(row) = isRowChanged(row);
		configureSave(row);
	});
}

void TableWidget::addButtons(int row, int col)
{
	QWidget* pWidget = new QWidget();
	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	
	QToolButton* saveButton = new QToolButton();
	QToolButton* deleteButton = new QToolButton();
	QToolButton* cancelButton = new QToolButton();
	
	saveButton->setToolTip("Save Changes");
	deleteButton->setToolTip("Delete Row");
	cancelButton->setToolTip("Discard Changes");

	pLayout->addWidget(saveButton);
	pLayout->addWidget(cancelButton);
	pLayout->addWidget(deleteButton);

	pLayout->setAlignment(Qt::AlignCenter);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pWidget->setLayout(pLayout);
	setCellWidget(row, col, pWidget);

	saveButton->setDisabled(true);
	cancelButton->setDisabled(true);

	QIcon iconSave(":/qrc/save.png");
	saveButton->setIcon(iconSave);
	saveButton->setAccessibleName("SingleSave");

	QIcon iconCancel(":/qrc/cancel.png");
	cancelButton->setIcon(iconCancel);
	cancelButton->setAccessibleName("SingleCancel");

	QIcon iconDelete(":/qrc/delete.png");
	deleteButton->setIcon(iconDelete);
	deleteButton->setAccessibleName("SingleDelete");

	QObject::connect(saveButton, &QToolButton::clicked, this, [this, row, cancelButton, saveButton]() {
		auto rowIndex = getButtonRowIndex(saveButton, "Save");
		onSaveItem(rowIndex, m_cellValues[rowIndex].front().toInt());
		//saveButton->setDisabled(true);
		//cancelButton->setDisabled(true);
	});

	QObject::connect(deleteButton, &QToolButton::clicked, this, [this, row, deleteButton]() {
		auto rowIndex = getButtonRowIndex(deleteButton, "Delete");
		onDeleteItem(rowIndex, m_cellValues[rowIndex].front().toInt());
	});

	QObject::connect(cancelButton, &QToolButton::clicked, this, [this, row, saveButton, cancelButton]() {
		auto rowIndex = getButtonRowIndex(cancelButton, "Cancel");
		saveButton->setDisabled(true);
		cancelButton->setDisabled(true);
		onCancelItem(rowIndex, m_cellValues[rowIndex].front().toInt());
	});

	m_stringToButtonsMapping["Save"].push_back(saveButton);
	m_stringToButtonsMapping["Delete"].push_back(deleteButton);
	m_stringToButtonsMapping["Cancel"].push_back(cancelButton);
}

void TableWidget::saveAll()
{
	for (auto i = 0; i < m_changedRows.size(); ++i) {
		if (m_changedRows.at(i)) {
			onSaveItem(i, m_cellValues[i].front().toInt());
			configureSave(i);
		}
	}
}

void TableWidget::discardAll()
{
	for (auto i = 0; i < m_changedRows.size(); ++i) {
		if (m_changedRows.at(i)) {
			onCancelItem(i, m_cellValues[i].front().toInt());
			configureSave(i);
		}
	}
}

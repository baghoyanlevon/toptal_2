#include "UsersTableWidget.h"

#include "CommonConstants.h"
#include "User.h"
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>

UsersTableWidget::UsersTableWidget(QWidget* parent) :
	TableWidget(parent), m_usersModel(new UsersModel)
{
	setColumnsCount(Constants::Users::columnsCount);
	setHeaders(Constants::Users::columnNames);
}

UsersTableWidget::~UsersTableWidget()
{

}

void UsersTableWidget::setUsersModel(UsersModel* usersModel)
{
	m_usersModel = usersModel;
}

void UsersTableWidget::setupValues()
{
	initializeColRowValues(m_usersModel->models.size());
	setRowCount(m_usersModel->models.size());
	for (auto i = 0; i < m_usersModel->models.size(); ++i) {
		auto userModel = m_usersModel->models.at(i);
		addNewUserRow(userModel);
	}
}

std::map<QString, int> UsersTableWidget::getUsersWithId()
{
	std::map<QString, int> res;
	for (auto const& user : m_usersModel->models) {
		res[user.email] = user.id;
	}
	return res;
}

void UsersTableWidget::onDeleteItem(int row, int id)
{
	QMessageBox msgBox;
	msgBox.setText("Are you sure you want to delete this user?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes) {
		emit(clickedOnDelete(id));
		QTableWidget::removeRow(row);
	}
}

void UsersTableWidget::onCancelItem(int row, int id)
{
	for (auto i = 0; i < columnCount() - 1; ++i) {
		if (m_columnWidgetType[i] == "Item") {
			item(row, i)->setText(m_cellValues[row][i]);
		}
		else if (m_columnWidgetType[i] == "ComboBox") {
			m_rowToComboBoxMapping[row]->setCurrentText(m_cellValues[row][i]);
		}
	}
	m_changedRows.at(row) = false;
	configureSave(row);
}

void UsersTableWidget::onSaveItem(int row, int id)
{
	QJsonObject object;

	object.insert(Constants::Users::memberNames[0], item(row, 0)->text().toInt());
	object.insert(Constants::Users::memberNames[1], item(row, 1)->text());
	object.insert(Constants::Users::memberNames[2], item(row, 2)->text());
	object.insert(Constants::Users::memberNames[3], m_rowToComboBoxMapping[row]->currentText());

	//m_cellValues[row][0] = item(row, 0)->text();
	//m_cellValues[row][1] = item(row, 1)->text();
	//m_cellValues[row][2] = item(row, 2)->text();
	//m_cellValues[row][3] = m_rowToComboBoxMapping[row]->currentText();

	//m_changedRows[row] = false;

	emit(clickedOnSave(id, object));
}

void UsersTableWidget::addNewUserRow(const UserModel& userModel)
{
	int i = m_rowsCount;
	int j = 0;

	addItem(i, j++, false, QString::number(userModel.id));
	addItem(i, j++, true, userModel.fullName);
	addItem(i, j++, true, userModel.email);
	addComboBox(i, j++, userModel.role, { "client", "realtor" });
	addButtons(i, j++);

	m_rowsCount++;
}

std::vector<int> UsersTableWidget::getAllUserIds()
{
	std::vector<int> res;
	for (auto i = 0; i < rowCount(); ++i) {
		res.push_back(item(i, 0)->text().toInt());
	}
	return res;
}

std::vector<std::pair<int, QJsonObject>> UsersTableWidget::getAllUserData()
{
	std::vector<std::pair<int, QJsonObject>> res;
	for (auto i = 0; i < rowCount(); ++i) {
		QJsonObject object;

		object.insert(Constants::Users::memberNames[0], item(i, 0)->text().toInt());
		object.insert(Constants::Users::memberNames[1], item(i, 1)->text());
		object.insert(Constants::Users::memberNames[2], item(i, 2)->text());
		object.insert(Constants::Users::memberNames[3], m_rowToComboBoxMapping[i]->currentText());

		res.push_back({ item(i, 0)->text().toInt(),object });
	}
	return res;
}

void UsersTableWidget::initializeValues(UsersModel* model)
{
	setUsersModel(model);
	setupValues();
}

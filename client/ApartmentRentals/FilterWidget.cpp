#include "FilterWidget.h"

#include <QVBoxLayout>
#include <QDateEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDate>
#include <QSpinBox>

FilterWidget::FilterWidget(QWidget* parent) : QWidget(parent)
{
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

FilterWidget::~FilterWidget()
{

}

void FilterWidget::onFilter()
{
	QString res ="?";
	res += "size_min=" + QString::number(m_sizeMinSpinBox->value())+ "&";
	res += "size_max=" + QString::number(m_sizeMaxSpinBox->value()) + "&";
	res += "price_min=" + QString::number(m_priceMinSpinBox->value()) + "&";
	res += "price_max=" + QString::number(m_priceMaxSpinBox->value()) + "&";
	res += "number_of_rooms_min=" + QString::number(m_numberOfRoomsMinSpinBox->value()) + "&";
	res += "number_of_rooms_max=" + QString::number(m_numberOfRoomsMaxSpinBox->value()) + "&";
	emit(filter(res));
}
 
void FilterWidget::clearValues()
{
	m_priceMinSpinBox->blockSignals(true);
	m_sizeMinSpinBox->blockSignals(true);
	m_numberOfRoomsMinSpinBox->blockSignals(true);
	m_priceMaxSpinBox->blockSignals(true);
	m_sizeMaxSpinBox->blockSignals(true);
	m_numberOfRoomsMaxSpinBox->blockSignals(true);

	m_priceMinSpinBox->setValue(0);
	m_sizeMinSpinBox->setValue(0);
	m_numberOfRoomsMinSpinBox->setValue(0);

	m_priceMaxSpinBox->setValue(10000);
	m_sizeMaxSpinBox->setValue(10000);
	m_numberOfRoomsMaxSpinBox->setValue(100);
	emit(reset());
	m_priceMinSpinBox->blockSignals(false);
	m_sizeMinSpinBox->blockSignals(false);
	m_numberOfRoomsMinSpinBox->blockSignals(false);
	m_priceMaxSpinBox->blockSignals(false);
	m_sizeMaxSpinBox->blockSignals(false);
	m_numberOfRoomsMaxSpinBox->blockSignals(false);
}

void FilterWidget::createMembers()
{
	m_numberOfRoomsMinLabel = new QLabel;
	m_numberOfRoomsMaxLabel = new QLabel;
	m_priceMinLabel = new QLabel;
	m_priceMaxLabel = new QLabel;
	m_sizeMinLabel = new QLabel;
	m_sizeMaxLabel = new QLabel;

	m_numberOfRoomsMinSpinBox = new QSpinBox;
	m_numberOfRoomsMaxSpinBox = new QSpinBox;
	m_priceMinSpinBox = new QDoubleSpinBox;
	m_priceMaxSpinBox = new QDoubleSpinBox;
	m_sizeMinSpinBox = new QDoubleSpinBox;
	m_sizeMaxSpinBox = new QDoubleSpinBox;

}
void FilterWidget::initializeMembers()
{
	m_numberOfRoomsMinLabel->setText("Number of rooms min:");
	m_numberOfRoomsMaxLabel->setText("Number of rooms max:");
	m_priceMinLabel->setText("Price min:");
	m_priceMaxLabel->setText("Price max:");
	m_sizeMinLabel->setText("Size min:");
	m_sizeMaxLabel->setText("Size max:");

	m_priceMaxSpinBox->setMinimum(0);
	m_priceMaxSpinBox->setMaximum(10000);

	m_priceMinSpinBox->setMinimum(0);
	m_priceMinSpinBox->setMaximum(10000);
	
	m_sizeMinSpinBox->setMinimum(0);
	m_sizeMinSpinBox->setMaximum(10000);

	m_sizeMaxSpinBox->setMinimum(0);
	m_sizeMaxSpinBox->setMaximum(10000);

	m_numberOfRoomsMaxSpinBox->setMinimum(0);
	m_numberOfRoomsMaxSpinBox->setMaximum(100);

	m_numberOfRoomsMinSpinBox->setMinimum(0);
	m_numberOfRoomsMinSpinBox->setMaximum(100);
	 
	m_priceMinSpinBox->setValue(0);
	m_sizeMinSpinBox->setValue(0);
	m_numberOfRoomsMinSpinBox->setValue(0);

	m_priceMaxSpinBox->setValue(10000);
	m_sizeMaxSpinBox->setValue(10000);
	m_numberOfRoomsMaxSpinBox->setValue(100);
}

void FilterWidget::setupLayouts()
{
	QHBoxLayout* widgetLayout = new QHBoxLayout(this);
	QSpacerItem inner(2, 2, QSizePolicy::Fixed, QSizePolicy::Fixed);
	QSpacerItem outer(5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed);


	// ------------------ price -------------------------------
	QVBoxLayout* priceLayout = new QVBoxLayout;

	QHBoxLayout* priceMinLayout = new QHBoxLayout;
	priceMinLayout->addWidget(m_priceMinLabel, 0, Qt::AlignLeft);
	priceMinLayout->addSpacerItem(new QSpacerItem(inner));
	priceMinLayout->addWidget(m_priceMinSpinBox, 0, Qt::AlignRight);

	QHBoxLayout* priceMaxLayout = new QHBoxLayout;
	priceMaxLayout->addWidget(m_priceMaxLabel, 0, Qt::AlignLeft);
	priceMaxLayout->addSpacerItem(new QSpacerItem(inner));
	priceMaxLayout->addWidget(m_priceMaxSpinBox, 0, Qt::AlignRight);

	priceLayout->addLayout(priceMinLayout);
	priceLayout->addLayout(priceMaxLayout);

	// ------------------ size -------------------------------
	QVBoxLayout* sizeLayout = new QVBoxLayout;

	QHBoxLayout* sizeMinLayout = new QHBoxLayout;
	sizeMinLayout->addWidget(m_sizeMinLabel, 0, Qt::AlignLeft);
	sizeMinLayout->addSpacerItem(new QSpacerItem(inner));
	sizeMinLayout->addWidget(m_sizeMinSpinBox, 0, Qt::AlignRight);

	QHBoxLayout* sizeMaxLayout = new QHBoxLayout;
	sizeMaxLayout->addWidget(m_sizeMaxLabel, 0, Qt::AlignLeft);
	sizeMaxLayout->addSpacerItem(new QSpacerItem(inner));
	sizeMaxLayout->addWidget(m_sizeMaxSpinBox, 0, Qt::AlignRight);

	sizeLayout->addLayout(sizeMinLayout);
	sizeLayout->addLayout(sizeMaxLayout);

	// ------------------ numberOfRooms -------------------------------
	QVBoxLayout* numberOfRoomsLayout = new QVBoxLayout;

	QHBoxLayout* numberOfRoomsMinLayout = new QHBoxLayout;
	numberOfRoomsMinLayout->addWidget(m_numberOfRoomsMinLabel, 0, Qt::AlignLeft);
	numberOfRoomsMinLayout->addSpacerItem(new QSpacerItem(inner));
	numberOfRoomsMinLayout->addWidget(m_numberOfRoomsMinSpinBox, 0, Qt::AlignRight);

	QHBoxLayout* numberOfRoomsMaxLayout = new QHBoxLayout;
	numberOfRoomsMaxLayout->addWidget(m_numberOfRoomsMaxLabel, 0, Qt::AlignLeft);
	numberOfRoomsMaxLayout->addSpacerItem(new QSpacerItem(inner));
	numberOfRoomsMaxLayout->addWidget(m_numberOfRoomsMaxSpinBox, 0, Qt::AlignRight);

	numberOfRoomsLayout->addLayout(numberOfRoomsMinLayout);
	numberOfRoomsLayout->addLayout(numberOfRoomsMaxLayout);

	QPushButton* resetBtn = new QPushButton("Reset");

	widgetLayout->addLayout(priceLayout);
	widgetLayout->addSpacerItem(new QSpacerItem(outer));
	widgetLayout->addLayout(sizeLayout);
	widgetLayout->addSpacerItem(new QSpacerItem(outer));
	widgetLayout->addLayout(numberOfRoomsLayout);
	widgetLayout->addSpacerItem(new QSpacerItem(outer));
	widgetLayout->addWidget(resetBtn, 0, Qt::AlignRight);
	connect(resetBtn, &QPushButton::clicked, this, &FilterWidget::clearValues);
}

void FilterWidget::makeConnections()
{
	QObject::connect(m_numberOfRoomsMaxSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &FilterWidget::onFilter);
	QObject::connect(m_numberOfRoomsMinSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &FilterWidget::onFilter);
	QObject::connect(m_sizeMaxSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FilterWidget::onFilter);
	QObject::connect(m_sizeMinSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FilterWidget::onFilter);
	QObject::connect(m_priceMaxSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FilterWidget::onFilter);
	QObject::connect(m_priceMinSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FilterWidget::onFilter);
}

void FilterWidget::checkAndCorrectValuse()
{
}

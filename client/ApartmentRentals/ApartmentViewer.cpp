
#include "ApartmentViewer.h"

#include <QLabel>
#include <QLineEdit>
#include <QToolTip>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QEvent>
#include <QMessageBox>
#include <QComboBox>

#include "Realtor.h"
#include "RequestManager.h"
#include "User.h"
static const QString btnStyle =

"QPushButton { font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(27,64,93), stop:1 rgb(127,164,193));}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(27,64,93), stop:1 rgb(0, 255, 255)); }"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgb(27,64,93), stop:1 rgb(127,164,193)); }";


static const QString labelSty = "background-color: transparent;  font: %1pt;  color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x2:0 y1:0, x1:1 y2:0,  stop:0 rgb(255, 255, 255), stop:1  rgb(27,64,93));"
"border-top: 0px;"
"border-right: 0px dotted rgb(27,64,93);"
"border-left: 0px;"
"QToolTip { color: rgb(0,0,0); background-color: rgb(255,255,255); border: 1px solid qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); }";
static const QString labelStyActive = "QLabel {background-color: transparent;  font: %1pt; color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x2:0 y1:0, x1:1 y2:0,  stop:0 rgb(255, 255, 255), stop:1  rgb(255,0,0));"
"border-top: 0px;"
"border: none;"
"border-right: 0px dotted rgb(27,64,93);"
"border-left: 0px;}"
"QToolTip { color: rgb(0,0,0); background-color: rgb(255,255,255); border: 1px solid qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); }";
ApartmentViewer::ApartmentViewer(const Apartment& apartment, bool isCreationDialog, bool isEditable, QWidget* parent)
	: QWidget(parent)
	, m_isCreationDialog(isCreationDialog)
	, m_isEditable(isEditable)
	, m_isActive(false)
{
	createMembers();
	setupLayout();
	setupMembers();
	makeConnections();
	setApartment(apartment);
	setActive(false);
	setFixedWidth(300);
	setValidations();
	configureEditability();

}

void ApartmentViewer::setApartment(const Apartment& apartment)
{
	m_apartment = apartment;

	m_locLatitude->setText(QString::number(m_apartment.getLocLatitude(),'f',4));
	m_locLongitude->setText(QString::number(m_apartment.getLocLongitude(), 'f', 4));

	m_locLatitude->setToolTip(m_locLatitude->text());
	m_locLongitude->setToolTip(m_locLongitude->text());

	if (!m_isCreationDialog) {
		m_infoLab->setText(m_apartment.getName());
		if (ActiveUser->isAdmin()) {
			m_realtorName->setCurrentText(QString("%1").arg(apartment.getRealtor().first));
		}
		m_isRented->setCurrentText(m_apartment.getRented() == true ? "Yes" : "No");
		m_name->setText(m_apartment.getName());
		m_description->setText(m_apartment.getDescription());
		m_floorSize->setText(QString::number(m_apartment.getFloorSize()));
		m_price->setText(QString::number(m_apartment.getPrice()));
		m_roomsNum->setText(QString::number(m_apartment.getRoomsNum()));
		m_dateAdded->setDate(m_apartment.getDateAdded());

		if (ActiveUser->isAdmin()) {
			m_realtorName->setToolTip(QString("%1").arg(apartment.getRealtor().first));
		}
		m_isRented->setToolTip(m_isRented->currentText());
		m_name->setToolTip(m_name->text());
		m_description->setToolTip(m_description->text());
		m_floorSize->setToolTip(m_floorSize->text());
		m_price->setToolTip(m_price->text());
		m_roomsNum->setToolTip(m_roomsNum->text());
		m_dateAdded->setToolTip(m_dateAdded->text());
	}

	if (ActiveUser->isAdmin()) {
		setupRealtors();
	}
}

void ApartmentViewer::setActive(bool isActive)
{
	m_isActive = isActive;
	m_widget->setVisible(isActive);
	if (isActive) {
		m_widget->setStyleSheet(labelStyActive.arg(QString::number(10)));
		m_infoLab->setStyleSheet(labelStyActive.arg(QString::number(13)));

	}
	else {
		m_widget->setStyleSheet(labelSty.arg(QString::number(10)));
		m_infoLab->setStyleSheet(labelSty.arg(QString::number(13)));
	}
}

bool ApartmentViewer::getActiveState() const
{
	return m_isActive;
}

void ApartmentViewer::createMembers()
{
	m_infoLab = new QLabel(this);
	m_infoLab->installEventFilter(this);
	m_isRented = new QComboBox(this);

	m_name = new QLineEdit(this);
	m_description = new QLineEdit(this);
	m_floorSize = new QLineEdit(this);
	m_price = new QLineEdit(this);
	m_roomsNum = new QLineEdit(this);
	m_locLatitude = new QLineEdit(this);
	m_locLongitude = new QLineEdit(this);
	m_dateAdded = new QDateEdit(this);
	if (ActiveUser->isAdmin()) {
		m_realtorName = new QComboBox(this);
	}
	if (ActiveUser->getRole() != User::Role::eClient) {
		if (!m_isCreationDialog) {
			m_updateBtn = new QPushButton("Update", this);
			m_removeBtn = new QPushButton("Remove", this);
			m_discardBtn = new QPushButton("Discard", this);
		}
		else {
			m_updateBtn = new QPushButton("Save", this);
			m_removeBtn = new QPushButton("Cancel", this);
		}
	}
	m_isRented->addItem("Yes");
	m_isRented->addItem("No");

	m_widget = new QWidget(this);

}

void ApartmentViewer::setupLayout()
{
	QVBoxLayout* vlay1 = new QVBoxLayout;
	{
		if (ActiveUser->isAdmin()) {
			vlay1->addWidget(new QLabel("Realtor:"), 0, Qt::AlignLeft);
		}
		vlay1->addWidget(new QLabel("Rented:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Name:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Description:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Floor Size:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Price:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Rooms Num:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Latitude:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Longitude:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Date Added:"), 0, Qt::AlignLeft);
	}

	QVBoxLayout* vlay2 = new QVBoxLayout;
	{
		if (ActiveUser->isAdmin()) {
			vlay2->addWidget(m_realtorName, 0, Qt::AlignLeft);
		}
		vlay2->addWidget(m_isRented, 0, Qt::AlignLeft);
		vlay2->addWidget(m_name, 0, Qt::AlignLeft);
		vlay2->addWidget(m_description, 0, Qt::AlignLeft);
		vlay2->addWidget(m_floorSize, 0, Qt::AlignLeft);
		vlay2->addWidget(m_price, 0, Qt::AlignLeft);
		vlay2->addWidget(m_roomsNum, 0, Qt::AlignLeft);
		vlay2->addWidget(m_locLatitude, 0, Qt::AlignLeft);
		vlay2->addWidget(m_locLongitude, 0, Qt::AlignLeft);
		vlay2->addWidget(m_dateAdded, 0, Qt::AlignLeft);

	}



	QHBoxLayout* hlay = new QHBoxLayout;
	{
		hlay->addLayout(vlay1);
		hlay->addLayout(vlay2);
	}
	QVBoxLayout* vlay = new QVBoxLayout;
	vlay->addLayout(hlay);

	if (ActiveUser->getRole() != User::Role::eClient) {
		QHBoxLayout* hlay1 = new QHBoxLayout;
		{
			hlay1->addWidget(m_updateBtn);
			if (!m_isCreationDialog) {
				hlay1->addWidget(m_discardBtn);
			}
			hlay1->addWidget(m_removeBtn);
		}

		vlay->addLayout(hlay1);
	}


	m_widget->setLayout(vlay);

	QVBoxLayout* mainLay = new QVBoxLayout;
	mainLay->addWidget(m_infoLab);
	mainLay->addWidget(m_widget);
	mainLay->setSpacing(0);

	setLayout(mainLay);
}

void ApartmentViewer::setupMembers()
{
	if (ActiveUser->getRole() != User::Role::eClient) {
		if (!m_isCreationDialog) {
			m_discardBtn->setFixedSize(70, 20);
		}
		m_updateBtn->setFixedSize(70, 20);
		m_removeBtn->setFixedSize(70, 20);
	}
	if (ActiveUser->isAdmin()) {
		m_realtorName->setFixedWidth(180);
	}

	m_isRented->setFixedWidth(180);
	m_name->setFixedWidth(180);
	m_description->setFixedWidth(180);
	m_floorSize->setFixedWidth(180);
	m_price->setFixedWidth(180);
	m_roomsNum->setFixedWidth(180);
	m_locLatitude->setFixedWidth(180);
	m_locLongitude->setFixedWidth(180);
	m_dateAdded->setFixedWidth(180);

}

void ApartmentViewer::makeConnections()
{
	if (ActiveUser->getRole() != User::Role::eClient) {
		if (!m_isCreationDialog) {
			connect(m_discardBtn, &QPushButton::clicked, this, &ApartmentViewer::onDiscard);
			connect(m_removeBtn, &QPushButton::clicked, this, &ApartmentViewer::onRemove);
			connect(m_updateBtn, &QPushButton::clicked, this, &ApartmentViewer::onSave);
		}
		else {
			connect(m_updateBtn, &QPushButton::clicked, [this]()
			{
				if (updateValues()) {
					emit(clicked(-1));
				}
			});
			connect(m_removeBtn, &QPushButton::clicked, this, &ApartmentViewer::unclicked);
		}
		connect(m_name, &QLineEdit::textChanged, [this](const QString& text) {
			m_infoLab->setText(text);
		});
	}
}

void ApartmentViewer::setValidations()
{
	m_price->setValidator(new QIntValidator(this));
	m_floorSize->setValidator(new QDoubleValidator(this));
	m_locLatitude->setValidator(new QDoubleValidator(this));
	m_locLongitude->setValidator(new QDoubleValidator(this));
	m_roomsNum->setValidator(new QIntValidator(this));
}

bool ApartmentViewer::updateValues()
{
	bool ok;
	m_apartment.setDateAdded(m_dateAdded->date());
	m_apartment.setName(m_name->text());
	if (m_name->text().isEmpty()) {
		QMessageBox::warning(this, "Name", "Name must be filled out");
		return false;
	}

	m_apartment.setDescription(m_description->text());
	if (m_description->text().isEmpty()) {
		QMessageBox::warning(this, "Description", "Description must be filled out");
		return false;
	}

	m_apartment.setFloorSize(m_floorSize->text().toDouble(&ok));
	if (!ok) {
		QMessageBox::warning(this, "Floor size", "Floor size must be valid number");
		return false;
	}
	if (ActiveUser->isAdmin()) {
		m_apartment.setUserId(m_realtorToIdMapping[m_realtorName->currentText()]);
	}
	m_apartment.setLocLatitude(m_locLatitude->text().toDouble(&ok));
	if (!ok) {
		QMessageBox::warning(this, "Latitude", "Latitude must be valid number");
		return false;
	}
	m_apartment.setLocLongitude(m_locLongitude->text().toDouble(&ok));
	if (!ok) {
		QMessageBox::warning(this, "Longitude", "Longitude must be valid number");
		return false;
	}

	m_apartment.setPrice(m_price->text().toInt(&ok));
	if (!ok) {
		QMessageBox::warning(this, "Price", "Price must be valid number");
		return false;
	}
	m_apartment.setRented(m_isRented->currentText() == "Yes");
	m_apartment.setRoomsNum(m_roomsNum->text().toInt(&ok));
	if (!ok) {
		QMessageBox::warning(this, "Number of rooms", "Number of rooms must be valid number");
		return false;
	}
	return true;
}

void ApartmentViewer::setupRealtors()
{
	if (ActiveUser->isAdmin()) {
		m_realtorName->clear();
		auto realtors = ActiveUser->getRealtors();
		for (auto const& r : realtors.models) {
			m_realtorToIdMapping[r.email] = r.id;
			m_realtorName->addItem(r.email);
			if (m_apartment.getUserId() == r.id) {
				m_realtorName->setCurrentText(r.email);
			}
		}
	}
}

void ApartmentViewer::configureEditability()
{
	if (ActiveUser->isAdmin()) {
		m_realtorName->setEnabled(m_isEditable);
	}
	m_isRented->setEnabled(m_isEditable);
	m_name->setEnabled(m_isEditable);
	m_description->setEnabled(m_isEditable);
	m_floorSize->setEnabled(m_isEditable);
	m_price->setEnabled(m_isEditable);
	m_roomsNum->setEnabled(m_isEditable);
	m_locLatitude->setEnabled(m_isEditable);
	m_locLongitude->setEnabled(m_isEditable);
	m_dateAdded->setEnabled(m_isEditable);
}

bool ApartmentViewer::eventFilter(QObject* obj, QEvent* event)
{
	if ((obj) == m_infoLab && event->type() == QEvent::MouseButtonPress)
	{
		if (m_isActive) {
			setActive(false);
			emit(unclicked(m_apartment.getId()));
		}
		else {
			emit(clicked(m_apartment.getId()));
			setActive(true);
		}
	}
	return false;
}

Apartment ApartmentViewer::getApartment() const
{
	return m_apartment;
}

void ApartmentViewer::onSave()
{
	auto updated = updateValues();
	if (updated) {
		RequestManager::getInstance()->updateApartment(m_apartment.getId(), m_apartment.toJson());
		emit(saved());
	}
}

void ApartmentViewer::onRemove()
{
	RequestManager::getInstance()->deleteApartment(m_apartment.getId());
	emit(removed());
}

void ApartmentViewer::onDiscard()
{
	setApartment(m_apartment);
	emit(discarded());
}


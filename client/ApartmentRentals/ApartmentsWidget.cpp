#include "ApartmentsWidget.h"
#include "MarkerData.h"
#include "Realtor.h"
#include "ApartmentViewer.h"
#include "RequestManager.h"
#include "User.h"
#include "CommonConstants.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
ApartmentsWidget::ApartmentsWidget(QWidget* parent)
	:QWidget(parent)
	,m_lastSelectedId(-1)
{
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

ApartmentsWidget::~ApartmentsWidget()
{
}

void ApartmentsWidget::setRealtors(const UsersModel& realtors)
{
	m_realtors = realtors;
}

void ApartmentsWidget::initializeValues(const QJsonArray& arr)
{
	clearValues();
	m_apartments.initializeFromJson(arr);
	for (auto const& a : m_apartments.models) {
		MarkerData data;
		data.setId(a.getId());
		data.setLatitude(a.getLocLatitude());
		data.setLongitude(a.getLocLongitude());
		data.setName(a.getName());
		data.setRented(a.getRented());
		m_mapsView->onAddMarker(data);
	}
	ActiveUser->setApartments(m_apartments);
	m_apartmentViewersContainer->setApartmentsData(m_apartments);
	if (m_lastSelectedId != -1) {
		m_mapsView->focusOnMarker(m_lastSelectedId);
		m_apartmentViewersContainer->setActiveById(m_lastSelectedId);
	}
}

void ApartmentsWidget::clearValues()
{
	m_apartmentViewersContainer->clearValues();
	m_mapsView->removeMarkers();
	m_realtors.models.clear();
	m_apartments.models.clear();
}

void ApartmentsWidget::updateWidget()
{
	RequestManager::getInstance()->getAllApartments(m_filterParams);
}

void ApartmentsWidget::onFilter(const QString& filterParams)
{
	m_filterParams = filterParams;
	updateWidget();
}

void ApartmentsWidget::onReset()
{
	RequestManager::getInstance()->resetFilter();
	m_filterParams.clear();
	updateWidget();
}

void ApartmentsWidget::onAddApartment()
{
	m_mapsView->selectLocation();
	m_addToolButton->setDisabled(true);
}

void ApartmentsWidget::onApartmentClick(int id)
{
	m_lastSelectedId = id;
	m_mapsView->focusOnMarker(id);
}

void ApartmentsWidget::onApartmentUnclick(int id)
{
	m_lastSelectedId = -1;
	m_mapsView->setIcons();
}

void ApartmentsWidget::onCreateNewApartment(double lat, double lng)
{
	Apartment creationApartment;
	creationApartment.setLocLatitude(lat);
	creationApartment.setLocLongitude(lng);
	ApartmentViewer* creationWidget = new ApartmentViewer(creationApartment, true, ActiveUser->getRole() != User::Role::eClient, this);
	creationWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	creationWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
	creationWidget->setActive(true);
	creationWidget->show();
	creationWidget->hide();
	creationWidget->move(mapToGlobal(m_mapsView->geometry().center()) - creationWidget->rect().center());
	creationWidget->show();

	connect(creationWidget, &ApartmentViewer::clicked, [this,creationWidget]() {
		bool added = RequestManager::getInstance()->addApartment(creationWidget->getApartment().toJson());
		if (added) {
			m_mapsView->cancelSelectingLocation();
			m_addToolButton->setDisabled(false);
			RequestManager::getInstance()->getAllApartments();
			creationWidget->hide();
		}
	});
	connect(creationWidget, &ApartmentViewer::unclicked, [this,creationWidget]() {
		creationWidget->hide();
	});

}

void ApartmentsWidget::createMembers()
{
	m_mapsView = new MapsView;
	m_apartmentViewersContainer = new ApartmentViewersContainter;
	m_filterWidget = new FilterWidget;

	if (ActiveUser->getRole() != User::Role::eClient) {
		m_addToolButton = new QToolButton;
		m_saveAllButton = new QToolButton;
		m_discardAllButton = new QToolButton;
		m_deleteAllButton = new QToolButton;
	}

	
}

void ApartmentsWidget::initializeMembers()
{

	if (ActiveUser->getRole() != User::Role::eClient) {
		m_addToolButton->setIconSize(Constants::UIElements::iconsSize);
		m_saveAllButton->setIconSize(Constants::UIElements::iconsSize);
		m_discardAllButton->setIconSize(Constants::UIElements::iconsSize);
		m_deleteAllButton->setIconSize(Constants::UIElements::iconsSize);
		QIcon iconAdd(":/qrc/add.png");
		m_addToolButton->setIcon(iconAdd);
		m_addToolButton->setToolTip("Add New Apartment");
		m_addToolButton->setAccessibleName("ApartmentAddToolButton");
		QIcon iconSave(":/qrc/save.png");
		m_saveAllButton->setIcon(iconSave);
		m_saveAllButton->setToolTip("Save All Unsaved Changes");
		m_saveAllButton->setAccessibleName("ApartmentSaveAllToolButton");
		
		QIcon iconDelete(":/qrc/delete.png");
		m_deleteAllButton->setIcon(iconDelete);
		m_deleteAllButton->setToolTip("Delete All Shown Apartments");
		m_deleteAllButton->setAccessibleName("ApartmentDeleteAllToolButton");

		QIcon iconDiscard(":/qrc/cancel.png");
		m_discardAllButton->setIcon(iconDiscard);
		m_discardAllButton->setToolTip("Discard All Unsaved Changes");
		m_discardAllButton->setAccessibleName("ApartmentDiscardAllToolButton");
	}
}

void ApartmentsWidget::setupLayouts()
{
	QVBoxLayout* widgetLayout = new QVBoxLayout(this);
	QHBoxLayout* mapInfoLayout = new QHBoxLayout;

	mapInfoLayout->addWidget(m_apartmentViewersContainer);
	mapInfoLayout->addWidget(m_mapsView);

	widgetLayout->addWidget(m_filterWidget);
	widgetLayout->addLayout(mapInfoLayout);

	if (ActiveUser->getRole() != User::Role::eClient) {
		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(m_addToolButton, 1, Qt::AlignRight);
		buttonsLayout->addWidget(m_saveAllButton, 0, Qt::AlignRight);
		buttonsLayout->addWidget(m_discardAllButton, 0, Qt::AlignRight);
		buttonsLayout->addWidget(m_deleteAllButton, 0, Qt::AlignRight);

		widgetLayout->addLayout(buttonsLayout);
	}
}
void ApartmentsWidget::makeConnections()
{
	if (ActiveUser->getRole() != User::Role::eClient) {
		connect(m_addToolButton, &QToolButton::clicked, this, &ApartmentsWidget::onAddApartment);
		connect(m_saveAllButton, &QToolButton::clicked, m_apartmentViewersContainer, &ApartmentViewersContainter::saveAllChanges);
		connect(m_discardAllButton, &QToolButton::clicked, m_apartmentViewersContainer, &ApartmentViewersContainter::discardAllChanges);
		connect(m_deleteAllButton, &QToolButton::clicked, m_apartmentViewersContainer, &ApartmentViewersContainter::deleteAllApartments);
	}
	connect(m_filterWidget, &FilterWidget::filter, this, &ApartmentsWidget::onFilter);
	connect(m_filterWidget, &FilterWidget::reset, this, &ApartmentsWidget::onReset);
	connect(RequestManager::getInstance(), &RequestManager::apartmentRecordsReady, this, &ApartmentsWidget::initializeValues);
	connect(m_mapsView, &MapsView::loadingFinished, this, &ApartmentsWidget::updateWidget);
	connect(m_mapsView, &MapsView::canceledSelectingLocation, [this]() {
		m_addToolButton->setDisabled(false);
	});
	connect(m_mapsView, &MapsView::locationPicked, [this](double latitude, double longitude) {
		static int k = 0; 
		MarkerData markerData;
		markerData.setId(k);
		markerData.setLatitude(latitude);
		markerData.setLongitude(longitude);
		markerData.setName("Apartment" + QString::number(k));
		//m_mapsView->onAddMarker(markerData);
		Apartment ap;
		auto re = std::make_shared<UserModel>();
		ap.setRealtor(re->email,re->id);
		//QMessageBox::information(this, "Picked", QString("Location Selected: %1 %2").arg(latitude).arg(longitude), QMessageBox::Ok);
		k++;
	});
	connect(m_mapsView, &MapsView::markerClicked, [this](const MarkerData & data) {
		m_lastSelectedId = data.getId();
		m_apartmentViewersContainer->setActiveById(data.getId());
		//QMessageBox::information(this, "Picked", QString("Location Selected: %1 name: %2").arg(data.getId()).arg(data.getName()), QMessageBox::Ok);
	});
	connect(m_mapsView, &MapsView::newMarkerAdded, this, &ApartmentsWidget::onCreateNewApartment);
	//connect(m_mapsView, &MapsView::newMarkerAdded, [this](double latitude, double longitude) {
	//	Apartment ap;
	//	auto re = std::make_shared<UserModel>();
	//	ap.setLocLatitude(latitude);
	//	ap.setLocLongitude(longitude);
	//	ApartmentViewer* apartmentViewer = new ApartmentViewer(ap, true, ActiveUser->getRole() != User::Role::eClient, this);
	//	apartmentViewer->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	//	apartmentViewer->setActive(true);
	//	apartmentViewer->show();
	//	apartmentViewer->hide();
	//	apartmentViewer->move(mapToGlobal(m_mapsView->geometry().center()) - apartmentViewer->rect().center());
	//	apartmentViewer->show();
	//	//if (apartmentViewer->exec() == QDialog::Accepted) {
	//	//	qDebug() << "Accepted ";
	//	//	//m_apartmentViewersContainer->addApartmentData(apartmentViewer->getApartment().getId(), apartmentViewer->getApartment());
	//	//	RequestManager::getInstance()->addApartment(apartmentViewer->getApartment().toJson());
	//	//	saveApartment(apartmentViewer->getApartment().toJson());
	//	//	m_mapsView->cancelSelectingLocation();
	//	//	RequestManager::getInstance()->getAllApartments();
	//	//}
	//});


	connect(m_apartmentViewersContainer, &ApartmentViewersContainter::clicked,this, &ApartmentsWidget::onApartmentClick);
	connect(m_apartmentViewersContainer, &ApartmentViewersContainter::unclicked,this, &ApartmentsWidget::onApartmentUnclick);
}

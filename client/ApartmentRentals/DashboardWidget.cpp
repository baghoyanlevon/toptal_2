#include "DashboardWidget.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMessageBox>

#include "CommonConstants.h"

DashboardWidget::DashboardWidget(QWidget* parent) : QWidget(parent)
{
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

DashboardWidget::~DashboardWidget()
{

}

void DashboardWidget::createMembers()
{
	m_anyAuthorized = false;

	m_userWidget = new UserWidget;
	m_tabWidget = new QTabWidget;

	m_apartmentsWidget = new ApartmentsWidget;

	m_clientsManagementWidget = new UsersManagementWidget(User::Role::eClient);
	m_realtorsManagementWidget = new UsersManagementWidget(User::Role::eRealtor);
}

void DashboardWidget::initializeMembers()
{
	if (ActiveUser->getRole() == User::Role::eRealtor ||
		ActiveUser->getRole() == User::Role::eAdmin) {
	}
	if (ActiveUser->getRole() == User::Role::eClient ||
		ActiveUser->getRole() == User::Role::eAdmin) {
		//TODO 
	}
	
}

void DashboardWidget::setupLayouts()
{
	QHBoxLayout* layout = new QHBoxLayout(this);

	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addWidget(m_userWidget, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(m_tabWidget);
	layout->addLayout(leftLayout);
	setMinimumWidth(Constants::UIElements::dashboardWidgetMinimumWidth);
}

void DashboardWidget::makeConnections()
{
	QObject::connect(m_userWidget, &UserWidget::signOut, this, &DashboardWidget::signOut);
	QObject::connect(m_userWidget, &UserWidget::refresh, this, &DashboardWidget::onRefresh);
	QObject::connect(m_tabWidget, &QTabWidget::currentChanged, this, &DashboardWidget::onTabSwitched);
	QObject::connect(m_realtorsManagementWidget, &UsersManagementWidget::availableUsersReady, this, &DashboardWidget::onAvailableRealtors);
	QObject::connect(m_realtorsManagementWidget, &UsersManagementWidget::userDataChanged, this, &DashboardWidget::updateApartments);
	QObject::connect(m_clientsManagementWidget, &UsersManagementWidget::userDataChanged, this, &DashboardWidget::updateApartments);
}

void DashboardWidget::updateApartments()
{
	RequestManager::getInstance()->getAllApartments();
}

void DashboardWidget::onTabSwitched(int id)
{
	m_tabWidget->blockSignals(true);

	//if (id == 0) {
	//	if (!m_timeRecordsTableWidget->warnAboutEditedRows(false)) {
	//		m_tabWidget->setCurrentIndex(1);
	//	}
	//	else {
	//		m_usersTableWidget->updateTable();
	//	}
	//}
	//else {
	//	if (!m_usersTableWidget->warnAboutEditedRows(false)) {
	//		m_tabWidget->setCurrentIndex(0);
	//	}
	//	else {
	//		m_timeRecordsTableWidget->updateTable();
	//	}
	//}

	m_tabWidget->blockSignals(false);
}

void DashboardWidget::onRefresh()
{
	m_tabWidget->blockSignals(true);

	int currentTabId = m_tabWidget->currentIndex();
	m_tabWidget->clear();

	m_tabWidget->addTab(m_apartmentsWidget, "Apartments");
	m_apartmentsWidget->clearValues();
	if (ActiveUser->getRole() == User::Role::eAdmin) {
		m_tabWidget->addTab(m_clientsManagementWidget, "Clients");
		m_clientsManagementWidget->clearValues();
		m_tabWidget->addTab(m_realtorsManagementWidget, "Realtors");
		m_realtorsManagementWidget->clearValues();

	}
	
	m_tabWidget->setCurrentIndex(currentTabId);

	if (ActiveUser->getRole() == User::Role::eAdmin) {
		RequestManager::getInstance()->getAllClients();
		RequestManager::getInstance()->getAllRealtors();
	}
	RequestManager::getInstance()->getAllApartments();
	m_tabWidget->blockSignals(ActiveUser->getRole() != User::Role::eAdmin);
	m_anyAuthorized = true;
}

void DashboardWidget::onError(const QString& error)
{
	if (!m_anyAuthorized) return;
	QMessageBox msgBox;
	msgBox.setText(error);
	msgBox.exec();
}

void DashboardWidget::onAuthorizationError()
{
	if (!m_anyAuthorized) return;
	
	m_anyAuthorized = false;
	QMessageBox msgBox;
	msgBox.setText("You are not allowed to do this action. Please sign in again");
	msgBox.exec();
	emit(signOut());
}

void DashboardWidget::onAvailableRealtors(const UsersModel& realtors)
{
	m_apartmentsWidget->setRealtors(realtors);
}

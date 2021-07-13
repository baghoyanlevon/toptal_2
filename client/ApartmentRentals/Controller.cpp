#include "Controller.h"

#include "SignInWidget.h"
#include "SignUpWidget.h"

Controller::Controller()
	: m_signInUpWidget(new SignInUpWidget)
	, m_dashboardWidget(nullptr)
{
	m_signInUpWidget->setAccessibleName("sign_in_up_widget");
	QObject::connect(m_signInUpWidget, &SignInUpWidget::successfullySignedIn, this, &Controller::onSignedInSuccessfully);
}

void Controller::run()
{
	m_signInUpWidget->show();
}

void Controller::makeConnections()
{
	QObject::connect(m_dashboardWidget, &DashboardWidget::signOut, this, &Controller::onSignout);
	QObject::connect(RequestManager::getInstance(), &RequestManager::responseError, m_dashboardWidget, &DashboardWidget::onError);
	QObject::connect(RequestManager::getInstance(), &RequestManager::unauthorizedOperation, m_dashboardWidget, &DashboardWidget::onAuthorizationError);
}

void Controller::makeDisconnections()
{
	QObject::disconnect(m_dashboardWidget, &DashboardWidget::signOut, this, &Controller::onSignout);
	QObject::disconnect(RequestManager::getInstance(), &RequestManager::responseError, m_dashboardWidget, &DashboardWidget::onError);
	QObject::disconnect(RequestManager::getInstance(), &RequestManager::unauthorizedOperation, m_dashboardWidget, &DashboardWidget::onAuthorizationError);
}

void Controller::onSignout()
{
	m_dashboardWidget->hide();
	m_signInUpWidget->show();
}

void Controller::onSignedInSuccessfully()
{
	m_signInUpWidget->hide();
	if (m_dashboardWidget != nullptr) {
		makeDisconnections();
		m_dashboardWidget->deleteLater();
	}
	m_dashboardWidget = new DashboardWidget;
	makeConnections();
	m_dashboardWidget->onRefresh();
	m_dashboardWidget->show();
}



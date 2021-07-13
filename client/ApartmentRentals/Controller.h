#pragma once

#include <QObject>

#include "SignInUpWidget.h"
#include "RequestManager.h"
#include "DashboardWidget.h"

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller();
	void run();

public slots:
	void onSignedInSuccessfully();
	void onSignout();

private:
	void makeConnections();
	void makeDisconnections();
private:
	SignInUpWidget* m_signInUpWidget;
	DashboardWidget* m_dashboardWidget;
};


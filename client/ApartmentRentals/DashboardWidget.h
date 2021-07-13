#pragma once

#include <QWidget>

#include "UsersManagementWidget.h"
#include "UserWidget.h"
#include "ApartmentsWidget.h"
#include "User.h"

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    DashboardWidget(QWidget* parent = nullptr);
    ~DashboardWidget();

private:
    void createMembers();
    void initializeMembers();
    void setupLayouts();
    void makeConnections();

public slots:
    void onRefresh();
    void updateApartments();
    void onTabSwitched(int id);
    void onError(const QString& error);
    void onAuthorizationError();
    void onAvailableRealtors(const UsersModel& realtors);
signals:
    void signOut();

private:
    bool m_anyAuthorized;
    UsersManagementWidget* m_clientsManagementWidget;
    UsersManagementWidget* m_realtorsManagementWidget;
    ApartmentsWidget* m_apartmentsWidget; 
    UserWidget* m_userWidget;
    QTabWidget* m_tabWidget;
};


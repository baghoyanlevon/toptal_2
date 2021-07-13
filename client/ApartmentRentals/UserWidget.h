#pragma once

#include <QWidget>
#include "RequestManager.h"

class QLabel;
class QPushButton;
class QSpinBox;
class QJsonObject;
class QToolButton;

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    UserWidget(QWidget* parent = nullptr);

public slots:
    void updateUserWidget();
private:
    void createMembers();
    void initializeMembers();
    void setupLayouts();
    void makeConnections();

signals:
    void signOut();
    void refresh();

private:
    QToolButton* m_refreshButton;
    QToolButton* m_signOutButton;

    QLabel* m_userFullNameLabel;
    QLabel* m_userFullNameValueLabel;

    QLabel* m_userRoleLabel;
    QLabel* m_userRoleValueLabel;

    QLabel* m_userEmailLabel;
    QLabel* m_userEmailValueLabel;

};


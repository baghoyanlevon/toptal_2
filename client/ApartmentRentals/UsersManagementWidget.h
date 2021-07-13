#pragma once

#include "IManagementWidget.h"
#include "UsersTableWidget.h"
#include "SignUpWidget.h"
#include "RequestManager.h"
#include "User.h"

class QToolButton;

class UsersManagementWidget : public IManagementWidget
{
	Q_OBJECT

public:
	UsersManagementWidget(const User::Role& role, QWidget* parent=nullptr);
	~UsersManagementWidget();

	void initializeValues(const QJsonArray& arr);
	bool warnAboutEditedRows(bool update = true);

private:
	void createMembers();
	void initializeMembers();
	void setupLayouts();
	void makeConnections();

public slots:
	void addNewUser();

	void updateTable();

	void onAddUser(const QJsonObject& object);

	void onDeleteUser(int userId);
	void onSaveUser(int userId, const QJsonObject& object);

	void onDeleteAll();

	void clearValues();

signals:
	void userDataChanged();
	void availableUsersReady(const UsersModel& data);

private:
	User::Role m_role;

	UsersTableWidget* m_usersTableWidget;
	SignUpWidget* m_addUserWidget;
	QToolButton* m_addToolButton;
	QToolButton* m_saveAllButton;
	QToolButton* m_discardAllButton;
	QToolButton* m_deleteAllButton;
};

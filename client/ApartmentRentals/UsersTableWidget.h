#pragma once

#include "Models.h"
#include "TableWidget.h"

class UsersTableWidget : public TableWidget
{
	Q_OBJECT

public:
	UsersTableWidget(QWidget* parent = nullptr);
	~UsersTableWidget();

	std::map<QString, int> getUsersWithId();
private:
	void setUsersModel(UsersModel* model);
	void setupValues();

public slots:
	void initializeValues(UsersModel* model);
	void onDeleteItem(int row, int id);
	void onSaveItem(int row, int id);
	void onCancelItem(int row, int id);
	void addNewUserRow(const UserModel& user);
	std::vector<int> getAllUserIds();
	std::vector<std::pair<int, QJsonObject>> getAllUserData();

private:
	UsersModel* m_usersModel;
};

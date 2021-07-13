#include "DataManager.h"

User* DataManager::s_activeUser = nullptr;
UsersModel* DataManager::s_clientUsersModel = nullptr;
UsersModel* DataManager::s_realtorUsersModel = nullptr;
ApartmentsModel* DataManager::s_apartmentsModel = nullptr;

UsersModel* DataManager::getClientsModel()
{
	if (s_clientUsersModel == nullptr) {
		s_clientUsersModel = new UsersModel;
	}
	return s_clientUsersModel;
}

UsersModel* DataManager::getRealtorsModel()
{
	if (s_realtorUsersModel == nullptr) {
		s_realtorUsersModel = new UsersModel;
	}
	return s_realtorUsersModel;
}

ApartmentsModel* DataManager::getApartmentsModel()
{
	if (s_apartmentsModel == nullptr) {
		s_apartmentsModel = new ApartmentsModel;
	}
	return s_apartmentsModel;
}

User* DataManager::getActiveUser()
{
	if (s_activeUser == nullptr) {
		s_activeUser = new User;
	}
	return s_activeUser;
}

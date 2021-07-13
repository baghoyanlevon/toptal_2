#pragma once
#include "Models.h"
#include "Apartment.h"
#include "User.h"

class DataManager
{
public:
	static UsersModel* getClientsModel();
	static UsersModel* getRealtorsModel();
	static ApartmentsModel* getApartmentsModel();
	static User* getActiveUser();
private:
	static UsersModel* s_clientUsersModel;
	static UsersModel* s_realtorUsersModel;
	static User* s_activeUser;
	static ApartmentsModel* s_apartmentsModel;
};
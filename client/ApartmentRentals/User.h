#pragma once

#include <QString>

#include "Apartment.h"
#include "Models.h"

class User;
using UserPtr = User*;

class User
{
public:
	enum class Role { eClient, eRealtor, eAdmin };
public:
	User();
	static UserPtr getInstance();

	int getId() const;
	void setId(const int& id);
	QString getFullName() const;
	void setFullName(const QString& fullName);
	QString getEmail() const;
	void setEmail(const QString& email);
	QString getToken() const;
	void setToken(const QString& token);
	Role getRole() const;
	void setRole(const Role& role);
	
	ApartmentsModel getApartments() const;
	void setApartments(const ApartmentsModel& model);

	UsersModel getClients() const;
	void setClients(const UsersModel& model);

	UsersModel getRealtors() const;
	void setRealtors(const UsersModel& model);

	bool isAdmin() const;
private:
	static UserPtr s_instance;

	int m_id;
	QString m_fullName;
	QString m_email;
	QString m_token;
	Role m_role;
	int m_preferredWorkingHours;

	ApartmentsModel m_apartmentsModel;
	UsersModel m_clientsModel;
	UsersModel m_realtorsModel;
};

#define ActiveUser User::getInstance()

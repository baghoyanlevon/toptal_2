#include "User.h"

UserPtr User::s_instance = nullptr;

UserPtr User::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new User;
    }
    return s_instance;
}

int User::getId() const
{
    return m_id;
}

void User::setId(const int& id)
{
    m_id = id;
}

QString User::getFullName() const
{
    return m_fullName;
}

void User::setFullName(const QString& fullName)
{
    m_fullName = fullName;
}

QString User::getEmail() const
{
    return m_email;
}

void User::setEmail(const QString& email)
{
    m_email = email;
}

QString User::getToken() const
{
    return m_token;
}

void User::setToken(const QString& token)
{
    m_token = token;
}

User::Role User::getRole() const
{
    return m_role;
}

void User::setRole(const User::Role& role)
{
    m_role = role;
}

ApartmentsModel User::getApartments() const
{
    return m_apartmentsModel;
}

void User::setApartments(const ApartmentsModel& model)
{
    m_apartmentsModel = model;
}

UsersModel User::getClients() const
{
    return m_clientsModel;
}

void User::setClients(const UsersModel& model)
{
    m_clientsModel = model;
}

UsersModel User::getRealtors() const
{
    return m_realtorsModel;
}

void User::setRealtors(const UsersModel& model)
{
    m_realtorsModel = model;
}



bool User::isAdmin() const
{
    return m_role == User::Role::eAdmin;
}

User::User()
{
    
}

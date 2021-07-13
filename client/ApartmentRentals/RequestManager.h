#pragma once

#include <QObject>

#include "RequestDispatcher.h"

class RequestManager : public QObject
{
    Q_OBJECT

public:
    static RequestManager* getInstance();

    void getAllUsers();

    void getAllClients();
    void getAllRealtors();

    void deleteUser(int userId);
    bool updateUser(int userId, const QJsonObject& object);
    bool addUser(const QJsonObject& object);

    bool updateActiveUser(const QJsonObject& object);
    bool getActiveUser();

    void getAllApartments(const QString& params = "");
    bool addApartment(const QJsonObject& object);
    bool updateApartment(int id, const QJsonObject& object);
    void deleteApartment(int id);

    void resetFilter();
signals:
    void allUsersDataReady(const QJsonArray& arr);
    void allClientsDataReady(const QJsonArray& arr);
    void allRealtorsDataReady(const QJsonArray& arr);
    void userDeleted(bool state);
    void userUpdated(bool state);
    void userAdded(const QJsonObject& object);

    void filteredReport(const QJsonObject& object);

    void apartmentRecordsReady(const QJsonArray& arr);
    void apartmentDeleted(bool state);
    void apartmentUpdated(bool state);

    void responseError(const QString& err);
    void unauthorizedOperation();
private:
    RequestManager(QObject* parent = nullptr);
    static RequestManager* s_instance;

    RequestDispatcher* m_requestDispatcher;
    QString m_apartmentParams;
};

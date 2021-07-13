#include "RequestManager.h"

RequestManager* RequestManager::s_instance = nullptr;

RequestManager* RequestManager::getInstance() {
	if (s_instance == nullptr) {
		s_instance = new RequestManager;
		QObject::connect(
			s_instance->m_requestDispatcher, &RequestDispatcher::unauthorizedOperation, 
			s_instance, &RequestManager::unauthorizedOperation);
	}
	return s_instance;
}

RequestManager::RequestManager(QObject* parent) : 
	QObject(parent), m_requestDispatcher(new RequestDispatcher)
{

}

void RequestManager::getAllUsers()
{
	QJsonArray arr = m_requestDispatcher->getAllUsers(QString());
	emit(allUsersDataReady(arr));
}

void RequestManager::getAllClients()
{
	QJsonArray arr = m_requestDispatcher->getAllUsers("client");
	emit(allClientsDataReady(arr));
}

void RequestManager::getAllRealtors()
{
	QJsonArray arr = m_requestDispatcher->getAllUsers("realtor");
	emit(allRealtorsDataReady(arr));
}

void RequestManager::deleteUser(int userId)
{
	bool deleted = m_requestDispatcher->deleteUser(userId);
	emit(userDeleted(deleted));
}

bool RequestManager::updateUser(int userId, const QJsonObject& object)
{
	QString answer = m_requestDispatcher->updateUser(userId, object);
	if (answer.isEmpty()) {
		emit(userUpdated(true));
	}
	else {
		emit(responseError(answer));
	}
	return answer.isEmpty();
}

bool RequestManager::updateActiveUser(const QJsonObject& object)
{
	QString answer = m_requestDispatcher->updateActiveUser(object);
	if (answer.isEmpty()) {
		emit(userUpdated(true));
	}
	else {
		emit(responseError(answer));
	}
	return answer.isEmpty();
}

bool RequestManager::getActiveUser()
{
	return m_requestDispatcher->getActiveUser();
}

void RequestManager::getAllApartments(const QString& params)
{
	if (!params.isEmpty()) {
		m_apartmentParams = params;
	}
	QJsonArray arr = m_requestDispatcher->getAllApartments(m_apartmentParams);
	
	emit(apartmentRecordsReady(arr));

}

bool RequestManager::addApartment(const QJsonObject& object)
{
	QJsonObject responseDate;
	QString answer = m_requestDispatcher->addApartment(object, responseDate);
	if (answer.isEmpty()) {
		emit(apartmentUpdated(true));
	}
	else {
		emit(responseError(answer));
	}
	return answer.isEmpty();

}

bool RequestManager::updateApartment(int id, const QJsonObject& object)
{
	QString answer = m_requestDispatcher->updateApartment(id, object);
	if (answer.isEmpty()) {
		emit(apartmentUpdated(true));
	}
	else {
		emit(responseError(answer));
	}
	return answer.isEmpty(); 
}

void RequestManager::deleteApartment(int id)
{
	bool deleted = m_requestDispatcher->deleteApartment(id);
	emit(apartmentDeleted(deleted));
}

void RequestManager::resetFilter()
{
	m_apartmentParams.clear();
}

bool RequestManager::addUser(const QJsonObject& object)
{
	QJsonObject responseData;
	QString answer = m_requestDispatcher->addUser(object, responseData);
	if (answer.isEmpty()) {
		emit(userAdded(responseData));
	}
	else {
		emit(responseError(answer));
	}
	return answer.isEmpty();
}

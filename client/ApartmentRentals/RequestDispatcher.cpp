#include "RequestDispatcher.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "CommonConstants.h"
#include "User.h"

RequestDispatcher::RequestDispatcher(QObject* parent) : QObject(parent)
{
	m_APIPrefixPath = Constants::APIPaths::apiPrefix;
	m_requestSender = new RequestSender;
}

std::pair<QString, bool> RequestDispatcher::signIn(const QString& email, const QString& password)
{
	QString url = getAPIFullPath(Constants::APIPaths::signIn);
	QJsonObject signInObject;
	signInObject["email"] = email;
	signInObject["password"] = password;
	QString bytes = objectToBytes(signInObject);
	RequestOptions requestOptions;
	requestOptions.m_authorization = false;
	QByteArray answerBytes = m_requestSender->post(url, bytes.toUtf8(), ActiveUser->getToken(), requestOptions);

	QJsonObject answer = bytesToObject(answerBytes);

	if (!(requestOptions.m_httpStatusCode >= 200 && requestOptions.m_httpStatusCode < 300)) {
		if (answer.size() > 0) {
			return std::pair<QString, bool>(parseError(answer), false);
		}
		else {
			return std::pair<QString, bool>("Login failed\n\nInvalid credentials.\nPlease recheck your credentials.", false);
		}
	}

	ActiveUser->setEmail(answer["email"].toString());
	ActiveUser->setFullName(answer["name"].toString());
	ActiveUser->setToken(answer["token"].toString());
	ActiveUser->setId(answer["id"].toInt());

	auto role = answer["role"].toString();
	if (role == "client") {
		ActiveUser->setRole(User::Role::eClient);
	}
	else if (role == "realtor") {
		ActiveUser->setRole(User::Role::eRealtor);
	}
	else if (role == "admin") {
		ActiveUser->setRole(User::Role::eAdmin);
	}

	return std::pair<QString, bool>(QString(), true);
}

std::pair<QString, bool> RequestDispatcher::signUp(const QString& email, const QString& password, const QString& fullName, const QString& role)
{
	QString url = getAPIFullPath(Constants::APIPaths::signUp);
	QJsonObject signUpObject;
	signUpObject["email"] = email;
	signUpObject["password"] = password;
	signUpObject["name"] = fullName;
	signUpObject["role"] = role;
	QString bytes = objectToBytes(signUpObject);
	RequestOptions requestOptions;
	requestOptions.m_authorization = false;
	QByteArray answerBytes = m_requestSender->post(url, bytes.toUtf8(), ActiveUser->getToken(), requestOptions);

	QJsonObject answer = bytesToObject(answerBytes);

	if (!(requestOptions.m_httpStatusCode >= 200 && requestOptions.m_httpStatusCode < 300)) {
		if (answer.size() > 0) {
			return std::pair<QString, bool>(parseError(answer), false);
		}
		else {
			return std::pair<QString, bool>("Something went wrong", false);
		}
	}

	bool res = (email == answer["email"].toString() && fullName == answer["name"].toString());
	return std::pair<QString, bool>(QString(), res);
}

// ====================================== User operations ======================================
QJsonArray RequestDispatcher::getAllUsers(const QString& role)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiUsers);
	if (!role.isEmpty()) {
		url += "?role=" + role;
	}
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->get(url, ActiveUser->getToken(), requestOptions);
	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}
	return bytesToArray(answerBytes);
}

QString RequestDispatcher::addUser(const QJsonObject& object, QJsonObject& responseData)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiUsers);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->post(url, objectToBytes(object), ActiveUser->getToken(), requestOptions);
	responseData = bytesToObject(answerBytes);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QString res;
	if (requestOptions.m_httpStatusCode != 201) {
		res = parseError(responseData);
	}
	return res;
}

bool RequestDispatcher::deleteUser(int userId)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiUsers) + QString::number(userId) + "/";
	QJsonObject signInObject;
	QString bytes = objectToBytes(signInObject);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->deleteResource(url, ActiveUser->getToken(), requestOptions);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	return requestOptions.m_httpStatusCode == 204;
}

QString RequestDispatcher::updateUser(int id, const QJsonObject& object)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiUsers) + QString::number(id) + "/";
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->patch(url, objectToBytes(object), ActiveUser->getToken(), requestOptions);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	if (!(requestOptions.m_httpStatusCode >= 200 && requestOptions.m_httpStatusCode < 300)) {
		return parseError(answer);
	}
	return QString();
}
QJsonArray RequestDispatcher::getAllApartments(const QString & params)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiApartments);
	if (!params.isEmpty()) {
		url += params + "/";
	}
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->get(url, ActiveUser->getToken(), requestOptions);
	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}
	return bytesToArray(answerBytes);
}
QString RequestDispatcher::addApartment(const QJsonObject& object, QJsonObject& responseData)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiApartments);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->post(url, objectToBytes(object), ActiveUser->getToken(), requestOptions);
	responseData = bytesToObject(answerBytes);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QString res;
	if (requestOptions.m_httpStatusCode != 201) {
		res = parseError(responseData);
	}
	return res;
}
bool RequestDispatcher::deleteApartment(int apartmentId)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiApartments) + QString::number(apartmentId) + "/";
	QJsonObject signInObject;
	QString bytes = objectToBytes(signInObject);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->deleteResource(url, ActiveUser->getToken(), requestOptions);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	return requestOptions.m_httpStatusCode == 204;
}
QString RequestDispatcher::updateApartment(int id, const QJsonObject& object)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiApartments) + QString::number(id) + "/";
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->patch(url, objectToBytes(object), ActiveUser->getToken(), requestOptions);
	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	if (!(requestOptions.m_httpStatusCode >= 200 && requestOptions.m_httpStatusCode < 300)) {
		return parseError(answer);
	}
	return QString();
}
// =============================================================================================

// ================================== Active User operations ===================================
QString RequestDispatcher::updateActiveUser(const QJsonObject& object)
{
	QString url = getAPIFullPath(Constants::APIPaths::apiMe);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->patch(url, objectToBytes(object), ActiveUser->getToken(), requestOptions);

	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	if (!(requestOptions.m_httpStatusCode >= 200 && requestOptions.m_httpStatusCode < 300)) {
		return parseError(answer);
	}
	return QString();
}

bool RequestDispatcher::getActiveUser()
{
	QString url = getAPIFullPath(Constants::APIPaths::apiMe);
	RequestOptions requestOptions;
	requestOptions.m_authorization = true;
	QByteArray answerBytes = m_requestSender->get(url, ActiveUser->getToken(), requestOptions);
	
	if (requestOptions.m_httpStatusCode == 401) {
		emit(unauthorizedOperation());
	}

	QJsonObject answer = bytesToObject(answerBytes);
	if (ActiveUser->getEmail() != answer["email"].toString()) {
		return false;
	}
	auto role = answer["role"].toString();
	if (role == "client") {
		ActiveUser->setRole(User::Role::eClient);
	}
	else if (role == "realtor") {
		ActiveUser->setRole(User::Role::eRealtor);
	}
	else if (role == "admin") {
		ActiveUser->setRole(User::Role::eAdmin);
	}
	return true;
}
// =============================================================================================

RequestDispatcher::~RequestDispatcher() {  }

QString RequestDispatcher::getAPIFullPath(const QString& path)
{
	return m_APIPrefixPath + "/" + path + "/";
}

QJsonObject RequestDispatcher::bytesToObject(const QByteArray& str)
{
	QJsonObject obj;

	QJsonDocument doc = QJsonDocument::fromJson(str);

	if (!doc.isNull()) {
		if (doc.isObject()) {
			obj = doc.object();
		}
		else {
			return QJsonObject();
		}
	}
	else {
		return QJsonObject();
	}
	return obj;
}

QJsonArray RequestDispatcher::bytesToArray(const QByteArray& str)
{
	QJsonArray arr;

	QJsonDocument doc = QJsonDocument::fromJson(str);

	if (!doc.isNull()) {
		if (doc.isArray()) {
			arr = doc.array();
		}
		else {
			return QJsonArray();
		}
	}
	else {
		return QJsonArray();
	}
	return arr;
}

QByteArray RequestDispatcher::objectToBytes(const QJsonObject& obj)
{
	QByteArray arr;

	QJsonDocument doc(obj);

	if (!doc.isNull()) {
		arr = doc.toJson();
	}
	else {
		return QByteArray();
	}
	return arr;
}

QString RequestDispatcher::parseError(const QJsonObject& obj)
{
	QString res;
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		res += it.key() + " - ";
		auto jsonArray = it.value().toArray();
		for (auto i = 0; i < jsonArray.size(); ++i) {
			res += jsonArray[i].toString();
			if (i != jsonArray.size() - 1) {
				res += ", ";
			}
		}
		res += "\n";
	}
	return res;
}


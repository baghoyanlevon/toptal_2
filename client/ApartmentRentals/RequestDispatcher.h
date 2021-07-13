#pragma once

#include "RequestSender.h"

#include <QJsonArray>
#include <QJsonObject>

class RequestDispatcher : public QObject
{
	Q_OBJECT

public:
	RequestDispatcher(QObject* parent=nullptr);
	~RequestDispatcher();

signals:
	void unauthorizedOperation();

public slots:
	std::pair<QString, bool> signIn(const QString& email, const QString& password);
	std::pair<QString, bool> signUp(const QString& email, const QString& password, const QString& name, const QString& role);

	QJsonArray getAllUsers(const QString & type);
	QString addUser(const QJsonObject& object, QJsonObject& responseData);
	bool deleteUser(int userId);
	QString updateUser(int id, const QJsonObject& object);

	QJsonArray getAllApartments(const QString& params);
	QString addApartment(const QJsonObject& object, QJsonObject& responseData);
	bool deleteApartment(int apartmentId);
	QString updateApartment(int id, const QJsonObject& object);


	QString updateActiveUser(const QJsonObject& object);
	bool getActiveUser();

private:
	QString getAPIFullPath(const QString& path);

	QJsonObject bytesToObject(const QByteArray& str);
	QJsonArray bytesToArray(const QByteArray& str);
	QByteArray objectToBytes(const QJsonObject& obj);

	QString parseError(const QJsonObject& obj);
private:
	QString m_APIPrefixPath;
	RequestSender* m_requestSender;
};


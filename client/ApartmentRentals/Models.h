#pragma once

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

struct UserModel
{
	int id;
	QString email;
	QString fullName;
	QString role;
	void initializeFromJson(const QJsonObject& object);

};

struct Model
{
	virtual void initializeFromJson(const QJsonArray& jsonArray) = 0;
};

struct UsersModel :public Model
{
	QVector<UserModel> models;
	void initializeFromJson(const QJsonArray& jsonArray);
};




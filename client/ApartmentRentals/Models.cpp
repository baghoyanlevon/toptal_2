#include "Models.h"

void UserModel::initializeFromJson(const QJsonObject& object)
{
	id = object["id"].toInt();
	email = object["email"].toString();
	fullName = object["name"].toString();
	role = object["role"].toString();
}

void UsersModel::initializeFromJson(const QJsonArray& jsonArray)
{
	for (auto const& item : jsonArray) {
		UserModel currentUser;
		currentUser.initializeFromJson(item.toObject());
		models.push_back(currentUser);
	}
}



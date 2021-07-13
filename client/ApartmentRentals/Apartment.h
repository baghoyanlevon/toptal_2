#pragma once
#include <QString>
#include <QJsonObject>
#include <QDate>
#include <memory>
#include <memory>

#include "Models.h"
class Apartment
{
public:
	int getId() const;
	void setId(int val);

	int getUserId() const;
	void setUserId(int val);

	QString getName() const;
	void setName(QString val);

	QString getDescription() const;
	void setDescription(QString val);

	float getFloorSize() const;
	void setFloorSize(float val);

	int getPrice() const;
	void setPrice(int val);

	int getRoomsNum() const;
	void setRoomsNum(int val);

	double getLocLatitude() const;
	void setLocLatitude(double val);

	double getLocLongitude() const;
	void setLocLongitude(double val);

	QDate getDateAdded() const;
	void setDateAdded(const QDate& val);

	std::pair<QString, int> getRealtor() const;
	void setRealtor(const QString& realtorEmail , int id);

	bool getRented() const;
	void setRented(bool val);

	QJsonObject toJson();
	void initializeFromJson(const QJsonObject& object);
private:
	int id;
	int user_id;
	bool m_isRented;
	QString m_name;
	QString m_description;
	float m_floorSize;
	int m_price;
	int m_roomsNum;
	double m_locLatitude;
	double m_locLongitude;
	QDate m_dateAdded;
	std::pair<QString, int> m_realtor;
};

struct ApartmentsModel :public Model
{
	QVector<Apartment> models;
	void initializeFromJson(const QJsonArray& jsonArray);
};
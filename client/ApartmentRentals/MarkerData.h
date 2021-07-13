#pragma once
#include <QMetaType>
#include <QString>
class MarkerData
{
public:
	int getId() const { return id; }
	void setId(int val) { id = val; }
	double getLatitude() const { return m_latitude; }
	void setLatitude(double val) { m_latitude = val; }
	double getLongitude() const { return m_longitude; }
	void setLongitude(double val) { m_longitude = val; }
	QString getName() const { return m_name; }
	void setName(QString val) { m_name = val; }
	bool getRented() const { return m_isRented; }
	void setRented(bool val) { m_isRented = val; }
private:
	int id;
	QString m_name;
	double m_latitude;
	double m_longitude;	
	bool m_isRented=false;
};
Q_DECLARE_METATYPE(MarkerData)


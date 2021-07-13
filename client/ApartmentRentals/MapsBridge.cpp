#include "MapsBridge.h"

#include <QDebug>

#include "MarkerData.h"

MapsBridge::MapsBridge(QObject  *parent) :QObject(parent)
{
}


MapsBridge::~MapsBridge()
{
}
void MapsBridge::onLocationPick(QString lat, QString lng)
{
	bool ok1, ok2;
	double longitude = lng.toDouble(&ok1);
	double latitude = lat.toDouble(&ok2);
	if (ok1 && ok2) {
		emit locationPicked(latitude, longitude);
	}
	else {
		qDebug() << "[FAIL] : Failed to convert arguments" << lat << lng;
	}
}
void MapsBridge::onNewMarkerAdded(QString lat, QString lng)
{
	bool ok1, ok2;
	double longitude = lng.toDouble(&ok1);
	double latitude = lat.toDouble(&ok2);
	if (ok1 && ok2) {
		emit newMarkerAdded(latitude, longitude);
	}
	else {
		qDebug() << "[FAIL] : Failed to convert arguments" << lat << lng;
	}
}
void MapsBridge::onCreateNewApartment(QString lat, QString lng)
{

	bool ok1, ok2;
	double longitude = lng.toDouble(&ok1);
	double latitude = lat.toDouble(&ok2);
	if (ok1 && ok2) {
		emit createNewApartment(latitude, longitude);
	}
	else {
		qDebug() << "[FAIL] : Failed to convert arguments" << lat << lng;
	}
}
void MapsBridge::onCancelSelectingLocation()
{
	emit(cancelSelectingLocation());
}
void MapsBridge::onMarkerClicked(QString idStr, QString latitudeStr, QString longitudeStr)
{
	bool ok1, ok2, ok3;
	int id = idStr.toInt(&ok1);
	double longitude = longitudeStr.toDouble(&ok2);
	double latitude = latitudeStr.toDouble(&ok3);
	if (ok1 && ok2 && ok3) {
		MarkerData data;
		data.setId(id);
		data.setLatitude(latitude);
		data.setLongitude(longitude);
		emit markerClicked(data);
	}
	else {
		qDebug() << "[FAIL] : Failed to convert arguments" << idStr << longitudeStr << latitudeStr;
	}
}
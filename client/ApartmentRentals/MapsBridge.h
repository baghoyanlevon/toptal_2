#pragma once

#include <QObject>
#include <QString>

class MarkerData;

class MapsBridge :	public QObject
{
	Q_OBJECT
public:
	MapsBridge(QObject  *parent=nullptr);
	~MapsBridge();
signals:
	void markerClicked(const MarkerData& data);
	void locationPicked(double lat, double lng);
	void newMarkerAdded(double lat, double lng);
	void createNewApartment(double lat, double lng);
	void cancelSelectingLocation();
public slots:
	void onMarkerClicked(QString idStr, QString latitudeStr, QString longitudeStr);
	void onLocationPick(QString lat, QString lng);
	void onNewMarkerAdded(QString lat, QString lng);
	void onCreateNewApartment(QString lat, QString lng);
	void onCancelSelectingLocation();
};


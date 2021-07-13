#pragma once
#include <QWidget>

class QWebEngineView;
class QWebChannel;
class MapsBridge;
class MarkerData;

class MapsView :public QWidget
{
	Q_OBJECT

public:
	MapsView(QWidget *parent=nullptr);
	~MapsView();
public slots:
	void onAddMarker(const MarkerData& data);
	void focusOnMarker(int id);
	void removeMarker(int id);
	void removeMarkers();
	void setIcons();
	void selectLocation();
	void cancelSelectingLocation();
signals:
	void markerClicked(const MarkerData& data);
	void locationPicked(double latitude, double longitude);
	void newMarkerAdded(double lat, double lng);
	void canceledSelectingLocation();
	void loadingFinished();
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();

private:
	QWebEngineView *m_webView;
	QWebChannel *m_webChannel;
	MapsBridge *m_mapBridge;
};


#include "MapsView.h"

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWebChannel>
#include <QFile>
#include <QString>
#include <QBoxLayout>

#include "MapsBridge.h"
#include "MarkerData.h"

#include <sstream>


static QString readFile(const QString& path) {
	QFile f(path);
	QString res;
	if (f.open(QIODevice::ReadOnly)) {
		res = f.readAll();
	}
	return res;
}
MapsView::MapsView(QWidget *parent) :QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}

MapsView::~MapsView()
{
}

void MapsView::focusOnMarker(int id)
{
	this->m_webView->page()->runJavaScript(QString("focusOnMarker(%1)").arg(id));
}

void MapsView::removeMarker(int id)
{
	this->m_webView->page()->runJavaScript(QString("removeMarker(%1)").arg(id));
}
void MapsView::removeMarkers()
{
	this->m_webView->page()->runJavaScript("removeMarkers();");
}

void MapsView::setIcons()
{
	this->m_webView->page()->runJavaScript("setIcons();");
}

void MapsView::selectLocation()
{
	this->m_webView->page()->runJavaScript("selectLocation();");
}

void MapsView::cancelSelectingLocation()
{
	this->m_webView->page()->runJavaScript("cancelSelectingLocation();");
}

void MapsView::createMembers()
{
	m_webView = new QWebEngineView;	
	m_mapBridge = new MapsBridge();
	m_webChannel = new QWebChannel(this);
}

void MapsView::setupMembers()
{
	const QString html = readFile(":/Resources/map.html");
	m_webView->setHtml(html, QUrl("qrc:/Resources/"));
	m_webChannel->registerObject("mapsBridge", m_mapBridge);
	m_webView->page()->setWebChannel(m_webChannel);
}

void MapsView::setupLayout()
{
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(m_webView);
	setLayout(hlay);
}

void MapsView::makeConnections()
{
	connect(m_webView->page(), &QWebEnginePage::loadFinished, this, &MapsView::loadingFinished);
	connect(m_mapBridge, &MapsBridge::markerClicked, this, &MapsView::markerClicked);
	connect(m_mapBridge, &MapsBridge::locationPicked, this, &MapsView::locationPicked);
	connect(m_mapBridge, &MapsBridge::newMarkerAdded, this, &MapsView::newMarkerAdded);
	connect(m_mapBridge, &MapsBridge::createNewApartment, this, &MapsView::newMarkerAdded);
	connect(m_mapBridge, &MapsBridge::cancelSelectingLocation, this, &MapsView::canceledSelectingLocation);

}


void MapsView::onAddMarker(const MarkerData& data)
{
	//%1 lat
	//%2 long
	//%3 name
	//%4 id
	QString ss("addMarker(%1, %2, \"%3\", %4, %5);");
	QString parsedCmd = ss.arg(QString::number(data.getLatitude()), QString::number(data.getLongitude()), data.getName(), QString::number(data.getId()), QString::number(data.getRented()%2));
	this->m_webView->page()->runJavaScript(parsedCmd);
}

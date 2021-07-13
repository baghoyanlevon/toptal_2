#include "RequestSender.h"


#include <QTimer>
#include <QBuffer>
#include <QEventLoop>

RequestSender::RequestSender(QObject* parent) : QObject(parent) { }

RequestSender::~RequestSender() { }

QByteArray RequestSender::post(const QString& url, const QByteArray& data, const QString& token, RequestOptions& options)
{
	if (url.isEmpty()) {
		return QByteArray();
	}

	QNetworkRequest networkRequest = createAndGetNetworkRequest(url, token, options);
	QNetworkAccessManager* networkManager = new QNetworkAccessManager();
	QNetworkReply* reply = networkManager->post(networkRequest, data);
	QByteArray answer = waitForResponse(reply, options);

	networkManager->deleteLater();
	reply->deleteLater();
	return answer;
}

QByteArray RequestSender::put(const QString& url, const QByteArray& data, const QString& token, RequestOptions& options)
{
	if (url.isEmpty()) {
		return QByteArray();
	}

	QNetworkRequest networkRequest = createAndGetNetworkRequest(url, token, options);
	QNetworkAccessManager* networkManager = new QNetworkAccessManager();
	QNetworkReply* reply = networkManager->put(networkRequest, data);
	QByteArray answer = waitForResponse(reply, options);

	networkManager->deleteLater();
	reply->deleteLater();
	return answer;
}

QByteArray RequestSender::get(const QString& url, const QString& token, RequestOptions& options)
{
	if (url.isEmpty()) {
		return QByteArray();
	}

	QNetworkRequest networkRequest = createAndGetNetworkRequest(url, token, options);
	QNetworkAccessManager* networkManager = new QNetworkAccessManager();
	QNetworkReply* reply = networkManager->get(networkRequest);
	QByteArray answer = waitForResponse(reply, options);

	networkManager->deleteLater();
	reply->deleteLater();
	return answer;
}

QByteArray RequestSender::deleteResource(const QString& url, const QString& token, RequestOptions& options)
{
	if (url.isEmpty()) {
		return QByteArray();
	}

	QNetworkRequest networkRequest = createAndGetNetworkRequest(url, token, options);
	QNetworkAccessManager* networkManager = new QNetworkAccessManager();
	QNetworkReply* reply = networkManager->deleteResource(networkRequest);
	QByteArray answer = waitForResponse(reply, options);

	networkManager->deleteLater();
	reply->deleteLater();
	return answer;
}

QByteArray RequestSender::patch(const QString& url, const QByteArray& data, const QString& token, RequestOptions& options)
{
	if (url.isEmpty()) {
		return QByteArray();
	}

	QNetworkRequest networkRequest = createAndGetNetworkRequest(url, token, options);
	QNetworkAccessManager* networkManager = new QNetworkAccessManager();
	QBuffer* buffer = new QBuffer();
	buffer->open((QBuffer::ReadWrite));
	buffer->write(data);
	buffer->seek(0);
	QNetworkReply* reply = networkManager->sendCustomRequest(networkRequest, "PATCH", buffer);
	QByteArray answer = waitForResponse(reply, options);

	networkManager->deleteLater();
	reply->deleteLater();
	return answer;
}

QByteArray RequestSender::waitForResponse(QNetworkReply*& reply, RequestOptions& options)
{
	QEventLoop loop;
	QTimer timer;
	
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

	options.m_isOk = (reply->error() == QNetworkReply::NetworkError::NoError);
	timer.start(5000);
	loop.exec();

	QByteArray answer;
	if (timer.isActive()) {
		timer.stop();
		if (reply->error() > 0) {
			options.m_networkReply = reply->error();
			int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
			options.m_httpStatusCode = v;
			answer = reply->readAll();
		}
		else {
			int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
			options.m_httpStatusCode = v;
			if (v >= 200 && v < 300) {
				answer = reply->readAll();
			}
		}
	}
	else {
		QObject::disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		reply->abort();
		answer = "{}";
	}
	return answer;
}

QNetworkRequest RequestSender::createAndGetNetworkRequest(const QString& url, const QString& token, RequestOptions& options)
{
	QNetworkRequest networkRequest;
	networkRequest.setUrl(QUrl(url));
	networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	if (options.m_authorization && !token.isEmpty()) {
		networkRequest.setRawHeader("Authorization", QByteArray("Token " + token.toUtf8()));
	}
	return networkRequest;
}

#pragma once

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

struct RequestOptions {
    bool m_isOk;
    bool m_authorization;
    QString m_url;
    QByteArray m_answer;
    QNetworkReply::NetworkError m_networkReply;
    int m_httpStatusCode;
};

class RequestSender : public QObject
{
    Q_OBJECT

public:
    explicit RequestSender(QObject* parent=nullptr);
    ~RequestSender();

    QByteArray post(const QString& url, const QByteArray& send, const QString& token, RequestOptions& options);
    QByteArray put(const QString& url, const QByteArray& send, const QString& token, RequestOptions& options);
    QByteArray get(const QString& url, const QString& token, RequestOptions& options);
    QByteArray deleteResource(const QString& url, const QString& token, RequestOptions& options);
    QByteArray patch(const QString& url, const QByteArray& send, const QString& token, RequestOptions& options);
private:
    QNetworkRequest createAndGetNetworkRequest(const QString& url, const QString& token, RequestOptions& options);
    QByteArray waitForResponse(QNetworkReply*& reply, RequestOptions& options);
};

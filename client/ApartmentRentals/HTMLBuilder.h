#pragma once

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class HTMLBuilder
{
public:
    static HTMLBuilder* getInstance();

	QString getReportHTML(const QJsonObject& object);
private:
    HTMLBuilder();
    static HTMLBuilder* s_instance;
    
    QString m_htmlTemplate;
    QString m_generateBlock(int indent, const QString& date, const QJsonObject& object);
};


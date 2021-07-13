#include "HTMLBuilder.h"
#include "CommonConstants.h"

HTMLBuilder* HTMLBuilder::s_instance = nullptr;

HTMLBuilder* HTMLBuilder::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new HTMLBuilder;
	}
	return s_instance;
}

HTMLBuilder::HTMLBuilder() {
	m_htmlTemplate = \
		"<!DOCTYPE html>\n"
		"<html lang=\"en\">\n"
		"    <head>\n"
		"        <meta charset=\"UTF-8\">\n"
		"        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
		"        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
		"        <title>Report</title>\n"
		"    </head>\n"
		"    <body style=\"font-size: 30px\">\n"
		"{ placeholder }"
		"    </body>\n"
		"</html>\n"
		"";
}


QString HTMLBuilder::m_generateBlock(int tabs, const QString& date, const QJsonObject& object)
{
	int totalTimeMinutes = object["total_time"].toInt();
	QString totalTime = QString::asprintf(Constants::Formats::timeFormatReport, totalTimeMinutes / 60, totalTimeMinutes % 60);
	QJsonArray titles = object["titles"].toArray();
	QJsonArray comments = object["comments"].toArray();
	QStringList elements;

	QString indent = QString(tabs * 4, ' ');
	QString indentPlus = QString((tabs + 1) * 4, ' ');

	elements.append(indent + QString("<h3>Date: %1</h3>").arg(date));
	elements.append(indent + QString("<b>Total Time: %1</b><br>").arg(totalTime));
	elements.append(indent + QString("<em>Notes:</em>"));
	elements.append(indent + "<ul>");
	for (int j = 0; j < titles.size(); j++) {
		elements.append(indentPlus + QString("<li>") + titles.at(j).toString() + QString(" : ") + comments.at(j).toString() + QString("</li>"));
	}
	elements.append(indent + "</ul>");
	elements.append("");

	return elements.join("\n");
}

QString HTMLBuilder::getReportHTML(const QJsonObject& object)
{
	QStringList bodyElements;
	for (int i = 0; i < object.keys().size(); i++) {
		bodyElements.append(m_generateBlock(2, object.keys().at(i), object[object.keys().at(i)].toObject()));
	}
	QString separator = QString(8, ' ') + "<hr>\n";
	QString htmlCode = m_htmlTemplate;
	htmlCode.replace("{ placeholder }", bodyElements.join(separator));
	return htmlCode;
}

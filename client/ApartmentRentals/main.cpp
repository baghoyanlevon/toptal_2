#include <QtWidgets/QApplication>
#include <QFile>
#include "Controller.h"

static void initStyleSheets()
{
    QFile file(":/qrc/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

#include "ApartmentsWidget.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	initStyleSheets();

	Controller c;
	c.run();
	return a.exec();
}

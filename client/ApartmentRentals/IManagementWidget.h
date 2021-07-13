#pragma once

#include <QWidget>

#include "TableWidget.h"
#include "Models.h"

class QJsonObject;
class QToolButton;

class IManagementWidget : public QWidget
{
	Q_OBJECT

public:
	IManagementWidget(QWidget* parent) : QWidget(parent) {}
	virtual ~IManagementWidget() {}

protected:
	virtual void createMembers() = 0;
	virtual void initializeMembers() = 0;
	virtual void setupLayouts() = 0;
	virtual void makeConnections() = 0;

signals:
	void clickedOnDelete(int id);
	void clickedOnSave(int id, QJsonObject object);
	void addItem(const QJsonObject& object);
	void printReport();
	void deleteAll(const std::vector<int>& timeRecords);
};


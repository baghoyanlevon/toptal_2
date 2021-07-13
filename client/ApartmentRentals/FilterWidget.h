#pragma once

#include <QWidget>
#include <QDate>
#include <QString>

class QLabel;
class QLineEdit;
class QDateEdit;
class QSpinBox;
class QDoubleSpinBox;

class FilterWidget : public QWidget
{
	Q_OBJECT

public:
	FilterWidget(QWidget* parent = nullptr);
	~FilterWidget();

public slots:
	void onFilter();
	void clearValues();
private:
	void createMembers();
	void initializeMembers();
	void setupLayouts();
	void makeConnections();

	void checkAndCorrectValuse();
signals:
	void reset();
	void filterApplied();
	void filter(const QString& filterParams);
private:
	QLabel* m_sizeMinLabel;
	QLabel* m_sizeMaxLabel;
	QLabel* m_priceMinLabel;
	QLabel* m_priceMaxLabel;
	QLabel* m_numberOfRoomsMinLabel;
	QLabel* m_numberOfRoomsMaxLabel;

	QDoubleSpinBox* m_sizeMinSpinBox;
	QDoubleSpinBox* m_sizeMaxSpinBox;
	QDoubleSpinBox* m_priceMinSpinBox;
	QDoubleSpinBox* m_priceMaxSpinBox;
	QSpinBox* m_numberOfRoomsMinSpinBox;
	QSpinBox* m_numberOfRoomsMaxSpinBox;

	bool m_isActivated;
};

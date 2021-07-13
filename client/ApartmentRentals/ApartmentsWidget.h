#pragma once

#include <QWidget>
#include <QToolButton>

#include "MapsView.h"
#include "ApartmentViewersContainter.h"
#include "FilterWidget.h"
class ApartmentsWidget : public QWidget
{
    Q_OBJECT

public:
    ApartmentsWidget(QWidget* parent = nullptr);
    ~ApartmentsWidget();
    void setRealtors(const UsersModel & realtors);
    void initializeValues(const QJsonArray& arr);
    void clearValues();
    void updateWidget();

public slots:
    void onFilter(const QString& filterParams);
    void onReset();
    void onAddApartment();
    void onApartmentClick(int id);
    void onApartmentUnclick(int id);
    void onCreateNewApartment(double lat, double lng);
private:
    void createMembers();
    void initializeMembers();
    void setupLayouts();
    void makeConnections();

signals:
    void saveApartment(const QJsonObject& data);
private:
    FilterWidget* m_filterWidget;
    MapsView* m_mapsView;
    ApartmentViewersContainter* m_apartmentViewersContainer;
    UsersModel m_realtors;
    ApartmentsModel m_apartments;

    QString m_filterParams;
    int m_lastSelectedId;

    QToolButton* m_addToolButton;
    QToolButton* m_saveAllButton;
    QToolButton* m_discardAllButton;
    QToolButton* m_deleteAllButton;
};

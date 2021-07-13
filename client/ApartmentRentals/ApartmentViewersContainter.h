#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>

#include "Apartment.h"


class ApartmentViewer;
class QScrollArea;

class ApartmentViewersContainter : public QWidget
{
    Q_OBJECT

public:
	ApartmentViewersContainter(QWidget *parent = nullptr);
    ~ApartmentViewersContainter();
    void setApartmentsData(ApartmentsModel model);
    void clearValues();
    void setActiveById(int id);

public slots:
    void saveAllChanges();
    void discardAllChanges();
    void deleteAllApartments();
    void updateWidget();
private:
    void deactivateAll();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
signals:
    bool clicked(int id);
    bool unclicked(int id);
private:
	QVector<ApartmentViewer*> m_apartmentViewers;
    QScrollArea* m_area;
    UsersModel m_realtorsModel;
    QVBoxLayout* m_vLayout;
    bool m_isActive = true;
};

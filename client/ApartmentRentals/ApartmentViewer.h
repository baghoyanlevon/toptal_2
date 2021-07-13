#pragma once

#include <QWidget>
#include <QDialog>
#include <QMap>

#include "Apartment.h"
class QLabel;
class QPushButton;
class QLineEdit;
class QDateEdit;
class QComboBox;

class ApartmentViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ApartmentViewer(const Apartment& apartment,bool isCreationDialog =false, bool isEditable = true, QWidget *parent = nullptr);
    void setApartment(const Apartment& apartment);
    void setActive(bool isActive);
    bool getActiveState()const;
    Apartment getApartment()const;
public slots:
    void onSave();
    void onRemove();
    void onDiscard();
signals:
    void saved();
    void removed();
    void discarded();

    void clicked(int id);
    void unclicked(int id);
private:
    void createMembers();
    void setupLayout();
    void setupMembers();
    void makeConnections();
    void setValidations();
    bool updateValues();
    void setupRealtors();
    void configureEditability();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
    QLabel* m_infoLab;
	QComboBox* m_realtorName;
    QComboBox* m_isRented;

    QLineEdit* m_name;
    QLineEdit* m_description;
    QLineEdit* m_floorSize;
    QLineEdit* m_price;
    QLineEdit* m_roomsNum;
    QLineEdit* m_locLatitude;
    QLineEdit* m_locLongitude;
    QDateEdit* m_dateAdded;

    std::map<QString, int> m_realtorToIdMapping;

    QPushButton* m_updateBtn;
    QPushButton* m_removeBtn;
    QPushButton* m_discardBtn;

    Apartment m_apartment;
    bool m_isActive;
    QWidget* m_widget;

    bool m_isEditable;
    bool m_isCreationDialog;
};

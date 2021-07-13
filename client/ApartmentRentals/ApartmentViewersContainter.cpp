#include "ApartmentViewersContainter.h"
#include "ApartmentViewer.h"
#include "RequestManager.h"
#include "User.h"

#include <QScrollArea>
#include <QEvent>
#include <QLabel>

ApartmentViewersContainter::ApartmentViewersContainter(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(350);
    m_vLayout = new QVBoxLayout;
    m_vLayout->addStretch();
    QWidget* widget = new QWidget(this);
    widget->setLayout(m_vLayout);
    widget->setFixedWidth(300);

    m_area = new QScrollArea(this);
    m_area->setWidgetResizable(true);
    m_area->setWidget(widget);
    m_area->setStyleSheet("border: none;");
    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(m_area);
    setLayout(vlay);
}

ApartmentViewersContainter::~ApartmentViewersContainter()
{

}

void ApartmentViewersContainter::setApartmentsData(ApartmentsModel model)
{
	for (auto const& m : model.models) {
		ApartmentViewer* apartmentViewer = new ApartmentViewer(m,false,ActiveUser->getRole() != User::Role::eClient, this);
		m_apartmentViewers.push_back(apartmentViewer);

		connect(apartmentViewer, &ApartmentViewer::removed, this, &ApartmentViewersContainter::updateWidget);
		connect(apartmentViewer, &ApartmentViewer::saved, this, &ApartmentViewersContainter::updateWidget);
		connect(apartmentViewer, &ApartmentViewer::clicked, this, &ApartmentViewersContainter::clicked);
		connect(apartmentViewer, &ApartmentViewer::unclicked, this, &ApartmentViewersContainter::unclicked);

		m_vLayout->insertWidget(0, m_apartmentViewers.back());
	}
}

void ApartmentViewersContainter::clearValues()
{
	for (auto const& a : m_apartmentViewers) {
		a->deleteLater();
	}
	m_realtorsModel.models.clear();
	m_apartmentViewers.clear();
}

void ApartmentViewersContainter::setActiveById(int id)
{
	for (auto const& ap : m_apartmentViewers) {
		ap->setActive(ap->getApartment().getId() == id);
	}
}

void ApartmentViewersContainter::saveAllChanges()
{
	for (auto& ap : m_apartmentViewers) {
		ap->blockSignals(true);
		ap->onSave();
		ap->blockSignals(false);
	}
	updateWidget();
}

void ApartmentViewersContainter::discardAllChanges()
{
	for (auto& ap : m_apartmentViewers) {
		ap->blockSignals(true);
		ap->onDiscard();
		ap->blockSignals(false);
	}
}

void ApartmentViewersContainter::deleteAllApartments()
{
	for (auto& ap : m_apartmentViewers) {
		ap->blockSignals(true);
		ap->onRemove();
		ap->blockSignals(false);
	}
	updateWidget();
}

void ApartmentViewersContainter::updateWidget()
{
	RequestManager::getInstance()->getAllApartments();
}

void ApartmentViewersContainter::deactivateAll()
{
	for (auto const& a : m_apartmentViewers) {
		a->setActive(false);
	}
}

bool ApartmentViewersContainter::eventFilter(QObject *obj, QEvent *event)
{
	return false;
	for (int i = 0; i < m_apartmentViewers.size(); ++i) {
		if ((obj) == reinterpret_cast<QObject*>(m_apartmentViewers[i]) && event->type() == QEvent::MouseButtonPress)
		{
			if (m_apartmentViewers[i]->getActiveState()) {
				m_apartmentViewers[i]->setActive(false);
				emit(unclicked(m_apartmentViewers[i]->getApartment().getId()));
			}
			else {
				emit(clicked(m_apartmentViewers[i]->getApartment().getId()));
				deactivateAll();
				m_apartmentViewers[i]->setActive(true);
			}
		}
	}
    return  false;
}

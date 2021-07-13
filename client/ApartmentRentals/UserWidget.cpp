#include "UserWidget.h"

#include <QLabel>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QJsonObject>

#include "CommonConstants.h"
#include "User.h"

UserWidget::UserWidget(QWidget* parent) : QWidget(parent)
{
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

void UserWidget::createMembers()
{
	m_refreshButton = new QToolButton;
	m_signOutButton = new QToolButton;

	m_userFullNameLabel = new QLabel;
	m_userFullNameValueLabel = new QLabel;

	m_userRoleLabel = new QLabel;
	m_userRoleValueLabel = new QLabel;

	m_userEmailLabel = new QLabel;
	m_userEmailValueLabel = new QLabel;

}

void UserWidget::initializeMembers()
{
	this->setContentsMargins(0, 0, 0, 0);
	m_refreshButton->setIconSize(Constants::UIElements::iconsSize);
	m_signOutButton->setIconSize(Constants::UIElements::iconsSize);

	QIcon iconRefresh(":/qrc/refresh.png");
	m_refreshButton->setIcon(iconRefresh);
	m_refreshButton->setToolTip("Refresh Page\n"
		"*All unsaved edits will be discarded");
	m_refreshButton->setAccessibleName("RefreshButton");

	QIcon iconSignOut(":/qrc/sign-out.png");
	m_signOutButton->setIcon(iconSignOut);
	m_signOutButton->setToolTip("Sign Out");
	m_signOutButton->setAccessibleName("SignOutButton");

	m_userFullNameLabel->setText("Full Name");
	m_userEmailLabel->setText("Email");
	m_userRoleLabel->setText("Role");

	m_userFullNameLabel->setFixedWidth(Constants::UIElements::userWidgetLabelsFixedWidth);
	m_userEmailLabel->setFixedWidth(Constants::UIElements::userWidgetLabelsFixedWidth);
	m_userRoleLabel->setFixedWidth(Constants::UIElements::userWidgetLabelsFixedWidth);

	m_userFullNameValueLabel->setObjectName("ValueLabels");
	m_userRoleValueLabel->setObjectName("ValueLabels");
	m_userEmailValueLabel->setObjectName("ValueLabels");

	updateUserWidget();
}

void UserWidget::setupLayouts()
{
	QVBoxLayout* widgetLayout = new QVBoxLayout(this);

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(m_refreshButton, 1, Qt::AlignRight);
	buttonsLayout->addWidget(m_signOutButton, 0, Qt::AlignRight);

	QHBoxLayout* userNameLayout = new QHBoxLayout;
	userNameLayout->addWidget(m_userFullNameLabel);
	userNameLayout->addWidget(m_userFullNameValueLabel);

	QHBoxLayout* userRoleLayout = new QHBoxLayout;
	userRoleLayout->addWidget(m_userRoleLabel);
	userRoleLayout->addWidget(m_userRoleValueLabel);

	QHBoxLayout* userEmailLayout = new QHBoxLayout;
	userEmailLayout->addWidget(m_userEmailLabel);
	userEmailLayout->addWidget(m_userEmailValueLabel);

	widgetLayout->addSpacing(Constants::UIElements::iconsSize.height());
	widgetLayout->addLayout(userEmailLayout);
	widgetLayout->addLayout(userNameLayout);
	widgetLayout->addLayout(userRoleLayout);
	widgetLayout->addLayout(buttonsLayout);
}

void UserWidget::makeConnections()
{
	QObject::connect(m_signOutButton, &QToolButton::clicked, this, &UserWidget::signOut);
	QObject::connect(m_refreshButton, &QToolButton::clicked, this, &UserWidget::refresh);
}


void UserWidget::updateUserWidget()
{
	m_userFullNameValueLabel->setText(ActiveUser->getFullName());
	m_userEmailValueLabel->setText(ActiveUser->getEmail());

	if (ActiveUser->getRole() == User::Role::eAdmin) {
		m_userRoleValueLabel->setText("Admin");
	}
	else if (ActiveUser->getRole() == User::Role::eClient) {
		m_userRoleValueLabel->setText("Client");
	}
	else {
		m_userRoleValueLabel->setText("Realtor");
	}
}

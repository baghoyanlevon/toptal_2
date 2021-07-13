#include "SignInUpWidget.h"

#include <QPushButton>
#include <QStackedWidget>
#include <QBoxLayout>

#include "SignUpWidget.h"
#include "SignInWidget.h"
#include "CommonConstants.h"

SignInUpWidget::SignInUpWidget(QWidget* parent) : QWidget(parent)
{
	createMembers();
	initializeMembers();
	makeConnections();
	setupLayouts();
}

SignInUpWidget::~SignInUpWidget()
{
}

void SignInUpWidget::createMembers()
{
	m_signInTabButton = new QPushButton;
	m_signInTabButton->setObjectName("sign_in_button");
	m_signUpTabButton = new QPushButton;
	m_signInTabButton->setObjectName("sign_up_button");

	m_signUpWidget = new SignUpWidget(false);
	m_signInWidget = new SignInWidget;

	m_stackedWidget = new QStackedWidget;
}

void SignInUpWidget::initializeMembers()
{
	m_signInTabButton->setText("Sign In");
	m_signInTabButton->setObjectName("SignInTabButton");
	m_signUpTabButton->setText("Sign Up");
	m_signUpTabButton->setObjectName("SignUpTabButton");

	m_stackedWidget->addWidget(m_signInWidget);
	m_stackedWidget->addWidget(m_signUpWidget);
}

void SignInUpWidget::makeConnections()
{
	connect(m_signInTabButton, &QPushButton::clicked, this, &SignInUpWidget::onSignInTabButtonPressed);
	connect(m_signUpTabButton, &QPushButton::clicked, this, &SignInUpWidget::onSignUpTabButtonPressed);
	connect(m_signInWidget, &SignInWidget::successfullySignedIn, this, &SignInUpWidget::successfullySignedIn);
	connect(m_signUpWidget, &SignUpWidget::successfullySignedUp, this, &SignInUpWidget::onSignInTabButtonPressed);
}

void SignInUpWidget::setupLayouts()
{
	QVBoxLayout* mainL = new QVBoxLayout(this);
	QHBoxLayout* buttonL = new QHBoxLayout;
	QHBoxLayout* widgetL = new QHBoxLayout;
	QVBoxLayout* signInTabButtonL = new QVBoxLayout;
	QVBoxLayout* signUpTabButtonL = new QVBoxLayout;

	signInTabButtonL->setSpacing(0);
	signInTabButtonL->addWidget(m_signInTabButton, 0, Qt::AlignTop);

	signUpTabButtonL->setSpacing(0);
	signUpTabButtonL->addWidget(m_signUpTabButton, 0, Qt::AlignTop);

	buttonL->setSpacing(0);
	buttonL->addLayout(signInTabButtonL);
	buttonL->addLayout(signUpTabButtonL);

	mainL->addLayout(buttonL);
	mainL->addWidget(m_stackedWidget, 0, Qt::AlignCenter);
	m_signInTabButton->setStyleSheet(Constants::UIElements::tabActiveStyle);
	m_signUpTabButton->setStyleSheet(Constants::UIElements::tabPassiveStyle);

	setFixedSize(Constants::UIElements::signInUpWidgetFixedWidth, Constants::UIElements::signInUpWidgetFixedHeight);
}

void SignInUpWidget::onSignInTabButtonPressed()
{
	m_stackedWidget->setCurrentWidget(m_signInWidget);
	m_signInTabButton->setStyleSheet(Constants::UIElements::tabActiveStyle);
	m_signUpTabButton->setStyleSheet(Constants::UIElements::tabPassiveStyle);
}

void SignInUpWidget::onSignUpTabButtonPressed()
{
	m_stackedWidget->setCurrentWidget(m_signUpWidget);
	m_signUpTabButton->setStyleSheet(Constants::UIElements::tabActiveStyle);
	m_signInTabButton->setStyleSheet(Constants::UIElements::tabPassiveStyle);
}

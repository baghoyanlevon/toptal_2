#include "SignInWidget.h"

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QMessageBox>

#include "CommonConstants.h"
#include "RequestManager.h"

SignInWidget::SignInWidget(QWidget* parent) : QWidget(parent)
{
	createMembers();
	initializeMembers();
	makeConnections();
	setupLayouts();
}

SignInWidget::~SignInWidget()
{
	m_passwordLineEdit->deleteLater();
	m_signInButton->deleteLater();
	m_emailLabel->deleteLater();
	m_passwordLabel->deleteLater();
}

void SignInWidget::createMembers()
{
	m_signInButton = new QPushButton;
	m_emailLineEdit = new QLineEdit;
	m_emailLineEdit->setAccessibleName("sign_in_email_field");
	m_passwordLineEdit = new QLineEdit;
	m_passwordLineEdit->setAccessibleName("password_field");
	m_emailLabel = new QLabel;
	m_passwordLabel = new QLabel;
}

void SignInWidget::initializeMembers()
{
	m_passwordLineEdit->setEchoMode(QLineEdit::Password);
	m_signInButton->setText("Sign In");
	m_emailLabel->setText("Email");
	m_passwordLabel->setText("Password");
}

void SignInWidget::setupLayouts()
{
	QHBoxLayout* mainHorizontalLayout = new QHBoxLayout(this);
	QVBoxLayout* widgetLayout = new QVBoxLayout;

	QHBoxLayout* emailLayout = new QHBoxLayout;
	emailLayout->addWidget(m_emailLabel, 0, Qt::AlignLeft);
	emailLayout->addWidget(m_emailLineEdit, 0, Qt::AlignRight);

	QHBoxLayout* passwordLayout = new QHBoxLayout;
	passwordLayout->addWidget(m_passwordLabel, 0, Qt::AlignLeft);
	passwordLayout->addWidget(m_passwordLineEdit, 0, Qt::AlignRight);


	widgetLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
	widgetLayout->addLayout(emailLayout);
	widgetLayout->addLayout(passwordLayout);
	widgetLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
	widgetLayout->addWidget(m_signInButton, 0, Qt::AlignHCenter);
	widgetLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	mainHorizontalLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
	mainHorizontalLayout->addLayout(widgetLayout);
	mainHorizontalLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	setFixedSize(Constants::UIElements::signInWidgetFixedWidth, Constants::UIElements::signInWidgetFixedHeight);

	//m_emailLineEdit->setText("levon@admin.com");
	//m_passwordLineEdit->setText("adminadmin");
}

void SignInWidget::makeConnections()
{
	QObject::connect(m_signInButton, &QPushButton::clicked, this, &SignInWidget::onSignInAction);
}

void SignInWidget::onSignInAction()
{
	RequestDispatcher requestDispatcher;

	std::pair<QString, bool> response = requestDispatcher.signIn(m_emailLineEdit->text(), m_passwordLineEdit->text());
	if (!response.second) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText(response.first);
		msgBox.exec();
	}
	else {
		emit(successfullySignedIn());
	}
}
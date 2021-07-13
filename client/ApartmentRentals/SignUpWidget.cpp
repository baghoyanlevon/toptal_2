#include "SignUpWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QSpinBox>

#include "CommonConstants.h"
#include "RequestManager.h"
#include "User.h"

SignUpWidget::SignUpWidget(bool addWidget, QWidget* parent) : 
	QWidget(parent), m_isAddWidget(addWidget)
{
	createMembers();
	initializeMembers();
	makeConnections();
	setupLayouts();
}

SignUpWidget::~SignUpWidget()
{

}

void SignUpWidget::onSignUp()
{
	RequestDispatcher requestDispatcher;

	QString fullName = m_fullNameLineEdit->text();
	QString email = m_emailLineEdit->text();
	QString password = m_passwordLineEdit->text();
	QString confirmPassword = m_confirmPasswordLineEdit->text();
	QString role = m_roleComboBox->currentText();

	if (fullName.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Full Name may not be empty");
		msgBox.exec();
		return;
	}

	if (email.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Email may not be empty");
		msgBox.exec();
		return;
	}

	if (password.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Password may not be empty");
		msgBox.exec();
		return;
	}

	if (password != confirmPassword) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Password and confirm password don't match");
		msgBox.exec();
		return;
	}

	auto response = requestDispatcher.signUp(email, password, fullName, role);
	QMessageBox msgBox;
	msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	if (!response.second) {
		msgBox.setText(response.first);
		msgBox.exec();
	}
	else {
		msgBox.setText("You successfully signed up");
		msgBox.exec();
		emit(successfullySignedUp());
		clearValues();
	}
}

void SignUpWidget::onAdd()
{
	QString fullName = m_fullNameLineEdit->text();
	QString email = m_emailLineEdit->text();
	QString password = m_passwordLineEdit->text();
	QString confirmPassword = m_confirmPasswordLineEdit->text();
	QString role = m_roleComboBox->currentText();

	if (fullName.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Full Name may not be empty");
		msgBox.exec();
		return;
	}

	if (email.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Email may not be empty");
		msgBox.exec();
		return;
	}

	if (password.isEmpty()) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Password may not be empty");
		msgBox.exec();
		return;
	}

	if (password != confirmPassword) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msgBox.setText("Password and confirm password don't match");
		msgBox.exec();
		return;
	}

	QJsonObject object;
	object["email"] = email;
	object["password"] = password;
	object["name"] = fullName;
	object["role"] = role;
	emit(addUser(object));
}

void SignUpWidget::onRoleChange(const QString& role)
{
}

void SignUpWidget::createMembers()
{
	m_fullNameLineEdit = new QLineEdit;
	m_fullNameLineEdit->setAccessibleName("sign_up_name_line_edit");
	m_emailLineEdit = new QLineEdit;
	m_passwordLineEdit = new QLineEdit;
	m_confirmPasswordLineEdit = new QLineEdit;
	m_roleComboBox = new QComboBox;

	m_fullNameLabel = new QLabel;
	m_emailLabel = new QLabel;
	m_passwordLabel = new QLabel;
	m_confirmPasswordLabel = new QLabel;
	m_roleLabel = new QLabel;

	m_saveButton = new QPushButton;
	if (m_isAddWidget) {
		m_cancelButton = new QPushButton;
	}
}

void SignUpWidget::initializeMembers()
{
	m_fullNameLabel->setText("Full Name");
	m_emailLabel->setText("Email");
	m_passwordLabel->setText("Password");
	m_confirmPasswordLabel->setText("Confirm Password");
	m_roleLabel->setText("Role");

	m_passwordLineEdit->setEchoMode(QLineEdit::Password);
	m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

	if (m_isAddWidget) {
		m_saveButton->setText("Save");
		m_cancelButton->setText("Cancel");

		if (ActiveUser->isAdmin()) {
			m_roleComboBox->addItems(Constants::Roles::standardRoles);
		}
		else {
			m_roleComboBox->addItems(Constants::Roles::standardRolesForManager);
		}
	}
	else {
		m_saveButton->setText("Sign Up");
		m_roleComboBox->addItems(Constants::Roles::standardRolesSignUp);
	}
}

void SignUpWidget::setupLayouts()
{
	QHBoxLayout* mainHorizontalLayout = new QHBoxLayout(this);
	QVBoxLayout* widgetLayout = new QVBoxLayout;

	QHBoxLayout* fullNameLayout = new QHBoxLayout;
	fullNameLayout->addWidget(m_fullNameLabel, 0, Qt::AlignLeft);
	fullNameLayout->addWidget(m_fullNameLineEdit, 0, Qt::AlignRight);

	QHBoxLayout* emailLayout = new QHBoxLayout;
	emailLayout->addWidget(m_emailLabel, 0, Qt::AlignLeft);
	emailLayout->addWidget(m_emailLineEdit, 0, Qt::AlignRight);

	QHBoxLayout* passwordLayout = new QHBoxLayout;
	passwordLayout->addWidget(m_passwordLabel, 0, Qt::AlignLeft);
	passwordLayout->addWidget(m_passwordLineEdit, 0, Qt::AlignRight);

	QHBoxLayout* confirmPasswordLayout = new QHBoxLayout;
	confirmPasswordLayout->addWidget(m_confirmPasswordLabel, 0, Qt::AlignLeft);
	confirmPasswordLayout->addWidget(m_confirmPasswordLineEdit, 0, Qt::AlignRight);

	QHBoxLayout* roleLayout = new QHBoxLayout;
	roleLayout->addWidget(m_roleLabel, 0, Qt::AlignLeft);
	roleLayout->addWidget(m_roleComboBox, 0, Qt::AlignRight);

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	if (m_isAddWidget) {
		buttonLayout->addWidget(m_saveButton, 1, Qt::AlignRight);
		buttonLayout->addWidget(m_cancelButton, 0, Qt::AlignRight);
	}
	else {
		buttonLayout->addWidget(m_saveButton, 0, Qt::AlignCenter);
	}
	widgetLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	widgetLayout->addLayout(fullNameLayout);
	widgetLayout->addLayout(emailLayout);
	widgetLayout->addLayout(passwordLayout);
	widgetLayout->addLayout(confirmPasswordLayout);
	if (m_isAddWidget) {
		widgetLayout->addLayout(roleLayout);
	}

	widgetLayout->addSpacerItem(new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));

	widgetLayout->addLayout(buttonLayout);
	
	widgetLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	mainHorizontalLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
	mainHorizontalLayout->addLayout(widgetLayout);
	mainHorizontalLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	setFixedSize(Constants::UIElements::signUpWidgetFixedWidth, Constants::UIElements::signUpWidgetFixedHeight);
	m_roleComboBox->setMinimumWidth(m_passwordLineEdit->sizeHint().width());
}

void SignUpWidget::makeConnections()
{
	QObject::connect(m_roleComboBox, &QComboBox::currentTextChanged, this, &SignUpWidget::onRoleChange);
	if (m_isAddWidget) {
		QObject::connect(m_saveButton, &QPushButton::clicked, this, &SignUpWidget::onAdd);
		QObject::connect(m_cancelButton, &QPushButton::clicked, this, &SignUpWidget::close);
	}
	else {
		QObject::connect(m_saveButton, &QPushButton::clicked, this, &SignUpWidget::onSignUp);
	}
}

void SignUpWidget::clearValues()
{
	m_fullNameLineEdit->clear();
	m_emailLineEdit->clear();
	m_passwordLineEdit->clear();
	m_confirmPasswordLineEdit->clear();
	m_roleComboBox->clear();

	if (ActiveUser->isAdmin()) {
		m_roleComboBox->addItems(Constants::Roles::standardRoles);
	}
	else {
		m_roleComboBox->addItems(Constants::Roles::standardRolesForManager);
	}
}

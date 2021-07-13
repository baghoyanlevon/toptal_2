#pragma once

#include <QWidget>

class QPushButton;
class SignUpWidget;
class SignInWidget;
class QStackedWidget;
class QFrame;

class SignInUpWidget : public QWidget
{
	Q_OBJECT

public:
	SignInUpWidget(QWidget* parent = nullptr);
	~SignInUpWidget();

signals:
	void successfullySignedIn();

private:
	void createMembers();
	void initializeMembers();
	void makeConnections();
	void setupLayouts();
private slots:
	void onSignInTabButtonPressed();
	void onSignUpTabButtonPressed();
private:
	QPushButton* m_signInTabButton;
	QPushButton* m_signUpTabButton;

	SignUpWidget* m_signUpWidget;
	SignInWidget* m_signInWidget;
	QStackedWidget* m_stackedWidget;
};

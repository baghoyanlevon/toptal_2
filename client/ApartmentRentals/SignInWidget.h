#pragma once

#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;

class SignInWidget : public QWidget
{
	Q_OBJECT

public:
	SignInWidget(QWidget* parent=nullptr);
	~SignInWidget();
public slots:
	void onSignInAction();
signals:
	void successfullySignedIn();
private:
	void createMembers();
	void initializeMembers();
	void setupLayouts();
	void makeConnections();
private:
	QPushButton* m_signInButton;
	QLineEdit* m_emailLineEdit;
	QLineEdit* m_passwordLineEdit;
	QLabel* m_emailLabel;
	QLabel* m_passwordLabel;
};




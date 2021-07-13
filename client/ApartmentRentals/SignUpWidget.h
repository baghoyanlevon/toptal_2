#pragma once

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QSpinBox;

class SignUpWidget : public QWidget
{
	Q_OBJECT

public:
	SignUpWidget(bool addWidget = false, QWidget* parent = nullptr);
	~SignUpWidget();

public slots:
	void onSignUp();
	void onAdd();
	void onRoleChange(const QString& role);
	void clearValues();
signals:
	void successfullySignedUp();
	void canceled();
	void addUser(const QJsonObject& object);
private:
	void createMembers();
	void initializeMembers();
	void setupLayouts();
	void makeConnections();

private:
	QLineEdit* m_fullNameLineEdit;
	QLineEdit* m_emailLineEdit;
	QLineEdit* m_passwordLineEdit;
	QLineEdit* m_confirmPasswordLineEdit;
	QComboBox* m_roleComboBox;

	QLabel* m_fullNameLabel;
	QLabel* m_emailLabel;
	QLabel* m_passwordLabel;
	QLabel* m_confirmPasswordLabel;
	QLabel* m_roleLabel;

	QPushButton* m_saveButton;
	QPushButton* m_cancelButton;
	bool m_isAddWidget;
};


#include "UsersManagementWidget.h"

#include <QVBoxLayout>
#include <QToolButton>
#include <QMessageBox>

#include "CommonConstants.h"
#include "UsersTableWidget.h"
#include "User.h"

UsersManagementWidget::UsersManagementWidget(const User::Role &role, QWidget* parent)
	:IManagementWidget(parent)
{
	m_role = role;
	createMembers();
	initializeMembers();
	setupLayouts();
	makeConnections();
}

UsersManagementWidget::~UsersManagementWidget()
{
}

void UsersManagementWidget::updateTable()
{
	switch (m_role)
	{
	case User::Role::eClient:
	case User::Role::eRealtor:
		RequestManager::getInstance()->getAllRealtors();
		RequestManager::getInstance()->getAllClients();
		emit(userDataChanged());
		break;
	default:
		RequestManager::getInstance()->getAllUsers();
		break;
	}
}

void UsersManagementWidget::onDeleteUser(int userId)
{
	RequestManager::getInstance()->deleteUser(userId);
	updateTable();
}

void UsersManagementWidget::onSaveUser(int userId, const QJsonObject& object)
{
	if (RequestManager::getInstance()->updateUser(userId, object)) {
		updateTable();
	}
	/*else {
		updateTable();
	}*/
}

void UsersManagementWidget::onDeleteAll()
{
	QMessageBox msgBox;
	msgBox.setText("Are you sure you want to delete all users?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	if (msgBox.exec() == QMessageBox::No) {
		return;
	}
	std::vector<int> userIds = m_usersTableWidget->getAllUserIds();
	for (auto i = 0; i < userIds.size(); ++i) {
		RequestManager::getInstance()->deleteUser(userIds.at(i));
	}
	updateTable();
}

void UsersManagementWidget::onAddUser(const QJsonObject& object)
{
	if (RequestManager::getInstance()->addUser(object)) {
		m_addUserWidget->clearValues();
		m_addUserWidget->close();
		updateTable();
	}
}

void UsersManagementWidget::clearValues()
{
	m_addUserWidget->clearValues();
}

void UsersManagementWidget::initializeValues(const QJsonArray& arr)
{
	UsersModel* usersModel = new UsersModel;
	usersModel->initializeFromJson(arr);
	m_addUserWidget->clearValues();
	m_usersTableWidget->blockSignals(true);
	m_usersTableWidget->initializeValues(usersModel);
	m_usersTableWidget->blockSignals(false);

	auto data = m_usersTableWidget->getUsersWithId();
	switch (m_role)
	{
	case User::Role::eClient:
		ActiveUser->setClients(*usersModel);
		break;
	case User::Role::eRealtor:
		ActiveUser->setRealtors(*usersModel);
		break;
	default:
		break;
	}
	emit(availableUsersReady(*usersModel));
}

bool UsersManagementWidget::warnAboutEditedRows(bool update)
{
	if (m_usersTableWidget->isRowChanged()) {
		QMessageBox msgBox;
		msgBox.setText("You have been editing something.\nIf you proceed this opeartion without saving, your changes will be lost.\nDo you want to proceed (changes will be lost)?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		if (msgBox.exec() == QMessageBox::No) {
			return false;
		}
		else {
			m_usersTableWidget->discardAll();
		}
	}
	if (update) {
		updateTable();
	}
	return true;
}

void UsersManagementWidget::addNewUser()
{
	m_addUserWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
	m_addUserWidget->show();
}

void UsersManagementWidget::createMembers()
{
	m_usersTableWidget = new UsersTableWidget;
	m_addToolButton = new QToolButton;
	m_saveAllButton = new QToolButton;
	m_discardAllButton = new QToolButton;
	m_deleteAllButton = new QToolButton;
	m_addUserWidget = new SignUpWidget(true);
}

void UsersManagementWidget::initializeMembers()
{
	m_addToolButton->setIconSize(Constants::UIElements::iconsSize);
	m_saveAllButton->setIconSize(Constants::UIElements::iconsSize);
	m_discardAllButton->setIconSize(Constants::UIElements::iconsSize);
	m_deleteAllButton->setIconSize(Constants::UIElements::iconsSize);

	QIcon iconAdd(":/qrc/add.png");
	m_addToolButton->setIcon(iconAdd);
	m_addToolButton->setToolTip("Add New User");
	m_addToolButton->setAccessibleName("AddUserToolButton");

	QIcon iconSave(":/qrc/save.png");
	m_saveAllButton->setIcon(iconSave);
	m_saveAllButton->setToolTip("Save All Unsaved Changes");
	m_saveAllButton->setAccessibleName("SaveAllUserToolButton");

	QIcon iconDelete(":/qrc/delete.png");
	m_deleteAllButton->setIcon(iconDelete);
	m_deleteAllButton->setToolTip("Delete All Shown Users");
	m_deleteAllButton->setAccessibleName("DeleteAllUserToolButton");

	QIcon iconDiscard(":/qrc/cancel.png");
	m_discardAllButton->setIcon(iconDiscard);
	m_discardAllButton->setToolTip("Discard All Unsaved Changes");
	m_discardAllButton->setAccessibleName("DiscardAllUserToolButton");
}

void UsersManagementWidget::setupLayouts()
{
	QVBoxLayout* widgetLayout = new QVBoxLayout(this);
	widgetLayout->addWidget(m_usersTableWidget);
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(m_addToolButton, 1, Qt::AlignRight);
	buttonsLayout->addWidget(m_saveAllButton, 0, Qt::AlignRight);
	buttonsLayout->addWidget(m_discardAllButton, 0, Qt::AlignRight);
	buttonsLayout->addWidget(m_deleteAllButton, 0, Qt::AlignRight);
	widgetLayout->addLayout(buttonsLayout);
}

void UsersManagementWidget::makeConnections()
{	
	switch (m_role)
	{
	case User::Role::eClient:
		QObject::connect(RequestManager::getInstance(), &RequestManager::allClientsDataReady, this, &UsersManagementWidget::initializeValues);
		break;
	case User::Role::eRealtor:
		QObject::connect(RequestManager::getInstance(), &RequestManager::allRealtorsDataReady, this, &UsersManagementWidget::initializeValues);
		break;
	default:
		QObject::connect(RequestManager::getInstance(), &RequestManager::allUsersDataReady, this, &UsersManagementWidget::initializeValues);
		break;
	}

	QObject::connect(m_addToolButton, &QToolButton::clicked, this, [this]() {
		if (warnAboutEditedRows(false)) {
			addNewUser();
		}
	}); 

	QObject::connect(m_deleteAllButton, &QToolButton::clicked, this, &UsersManagementWidget::onDeleteAll);
	QObject::connect(m_saveAllButton, &QToolButton::clicked, this, [this]() {
		auto usersData = m_usersTableWidget->getAllUserData();
		for (auto const & ud : usersData) {
			RequestManager::getInstance()->updateUser(ud.first,ud.second);
		}
		updateTable();
	});
	QObject::connect(m_discardAllButton, &QToolButton::clicked, this, [this]() {
		m_usersTableWidget->discardAll();
		updateTable();
	});

	QObject::connect(m_addUserWidget, &SignUpWidget::addUser, this, &UsersManagementWidget::onAddUser);
	QObject::connect(m_usersTableWidget, &TableWidget::clickedOnDelete, this, &UsersManagementWidget::onDeleteUser);
	QObject::connect(m_usersTableWidget, &TableWidget::clickedOnSave, this, &UsersManagementWidget::onSaveUser);
}

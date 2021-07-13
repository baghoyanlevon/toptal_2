#pragma once

#include <QString>
#include <QStringList>
#include <QSize>
#include <QBrush>
#include <QColor>

namespace Constants
{
	namespace APIPaths {
		const static QString apiPrefix = "http://127.0.0.1:8000";

		const static QString admin = "admin";
		const static QString users = "users";
		const static QString apartments = "apartments";

		const static QString api = "api";

		const static QString apiUsers = api + "/" + users;
		const static QString apiMe = apiUsers + "/me";
		const static QString apiApartments = api + "/" + apartments;

		const static QString signIn = apiUsers + "/signin";
		const static QString signUp = apiUsers + "/signup";
	}

	namespace Roles {
		const static QStringList standardRoles = { "client", "realtor", "admin" };
		const static QStringList standardRolesSignUp = { "client" };
		const static QStringList standardRolesForManager = { "client", "realtor" };
	}


	namespace Users {
		const static QStringList memberNames = { "id",  "name", "email", "role"};
		const static QStringList columnNames = { "ID",  "Name", "Email", "Role"};
		const static int columnsCount = columnNames.size();
	}

	namespace Formats {
		const static char* timeFormat = "%02d:%02d";
		const static char* timeFormatReport = "%02dh %02dm";
		const static QString dateFormat = "yyyy-MM-dd";
	}

	namespace UIElements {

		const static int dashboardWidgetMinimumWidth = 1400;

		const static int signInWidgetFixedWidth = 320;
		const static int signInWidgetFixedHeight = 540;

		const static int signUpWidgetFixedWidth = 320;
		const static int signUpWidgetFixedHeight = 540;

		const static int signInUpWidgetFixedWidth = 352;
		const static int signInUpWidgetFixedHeight = 594;

		const static int addTimeRecordWidgetFixedWidth = 420;
		const static int addTimeRecordWidgetFixedHeight = 540;
		const static int editableItemWidth = 200;
		const static int userWidgetLabelsFixedWidth = 100;

		const static QString tabActiveStyle = "QPushButton{"
			"    color: rgb(153,153,153);"
			"    background:transparent;"
			"    border-radius:0px;"
			"    border: 1px solid rgb(153,153,153);"
			"    border-bottom: 1px transparent rgb(153,153,153);"
			"    font: bold 14px;"
			"}"
			"QPushButton:hover{"
			"    color:  rgb(153,153,153);"
			"    background:transparent;"
			"    border-radius:0px;"
			"    border: 1px solid rgb(108,108,108);"
			"    border-bottom: 1px transparent rgb(153,153,153);"
			"    font: bold 14px;"
			"}";
		const static QString tabPassiveStyle = "QPushButton{"
			"    color: rgb(153,153,153);"
			"    background: transparent;"
			"    border-radius: 0px;"
			"    border: 1px transparent rgb(153,153,153);"
			"    border-bottom: 1px solid rgb(153,153,153);"
			"    font: bold 14px;"
			"}"
			"QPushButton:hover{"
			"    color:  rgb(153,153,153);"
			"    background: rgb(208,208,208);"
			"    border-radius:0px;"
			"    border: 1px transparent rgb(153,153,153);"
			"    border-bottom: 1px solid rgb(153,153,153);"
			"    font: bold 14px;"
			"}";

		const static QSize iconsSize = QSize(28, 28);
	}
}

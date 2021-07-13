from pages.base_page import BasePage


class Realtors(BasePage):
    def __init__(self):
        super().__init__()
        if not self.signedIn:
            self.sign_in("levon@admin.com", "adminadmin")
        super().class_name_configuration()

    def open_page(self):
        self.app.top_window().RealtorsTabItem.click_input()

    def check_element_exists(self, name):
        return self.app.top_window()[name].exists()

    def print(self):
        self.app.top_window().print_control_identifiers()

    def name_field(self):
        return self.app.top_window().Full_NameEdit

    def select_realtor(self):
        self.app.top_window().RoleComboBox.click_input()
        self.app.top_window().realtorListItem.click_input()

    def email_field(self):
        return self.app.top_window().EmailEdit

    def password_field(self):
        return self.app.top_window().PasswordEdit

    def confirm_password_field(self):
        return self.app.top_window().Confirm_PasswordEdit

    def save_button(self):
        return self.app.top_window().SaveButton

    def cancel_button(self):
        return self.app.top_window().CancelButton

    def add_user_button(self):
        return self.app.top_window().AddUserToolButton

    def save_all_users_button(self):
        return self.app.top_window().SaveAllUserToolButton

    def discard_all_users_button(self):
        return self.app.top_window().DiscardAllUserToolButton

    def delete_all_users_button(self):
        return self.app.top_window().DeleteAllUserToolButton

    def yes_button_on_dialog(self):
        return self.app.top_window().YesButton

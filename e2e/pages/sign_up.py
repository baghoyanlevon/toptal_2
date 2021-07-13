from pages.base_page import BasePage


class SignUp(BasePage):
    def __init__(self):
        super().__init__()
        if self.signedIn:
            super().sign_out()
        self.app.top_window().SignUp.click_input()
        self.win = self.app.top_window()
        super().class_name_configuration()

    def name_field(self):
        return self.win.Full_NameEdit

    def email_field(self):
        return self.win.EmailEdit

    def password_field(self):
        return self.win.PasswordEdit

    def confirm_password_field(self):
        return self.win.Confirm_PasswordEdit

    def sign_up_button(self):
        return self.win.Sign_UpButton2

    def print_values(self):
        self.app.top_window().print_control_identifiers()
        self.win.print_control_identifiers()

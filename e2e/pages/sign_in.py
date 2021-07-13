from pages.base_page import BasePage


class SignIn(BasePage):
    def __init__(self):
        super().__init__()
        if self.signedIn:
            super().sign_out()
        self.app.top_window().SignIn.click_input()
        self.win = self.app.top_window()
        super().class_name_configuration()

    def email_field(self):
        return self.win.EmailEdit

    def get_app(self):
        return self.app

    def password_field(self):
        return self.win.PasswordEdit

    def sign_up_button(self):
        return self.win.Sign_InButton2

    def print_values(self):
        self.app.top_window().print_control_identifiers()
        self.win.print_control_identifiers()

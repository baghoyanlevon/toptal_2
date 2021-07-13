import os
import time

from pywinauto.application import Application

print(os.getcwd()+"../../ApartmentsRental/x64/Release/ApartmentRentals.exe")
_app = Application(backend="uia").start("../client/x64/Release/ApartmentRentals.exe",
                                        wait_for_idle=False)
_signedIn = False


class BasePage(object):
    def __init__(self):
        self.app = _app
        global _signedIn
        self.signedIn = _signedIn

    def class_name_configuration(self):
        self.class_name = self.app.top_window().class_name

    def set_signed_in(self, state):
        global _signedIn
        _signedIn = state
        self.signedIn = state

    def window_changed(self):
        if self.class_name == self.app.top_window().class_name:
            return False
        return True

    def check_element_exists(self, name):
        return self.app.top_window()[name].exists()

    def sign_out(self):
        self.app.top_window().SignOutButton().click_input()
        global _signedIn
        _signedIn = False
        self.signedIn = False

    def sign_in(self, email, password):
        self.app.top_window().EmailEdit.set_text(email)
        self.app.top_window().PasswordEdit.set_text(password)
        self.app.top_window().Sign_InButton2.click_input()
        global _signedIn
        _signedIn = True
        self.signedIn = True

    def wait_until_window_change(self, timeout=2, period=0.1):
        time.sleep(0.5)
        return True
        mustend = time.time() + timeout
        while time.time() < mustend:
            if self.window_changed():
                return True
            time.sleep(period)
        return False

    def close_mesage_box(self):
        self.app.top_window().OKButton.click_input()

    def message_value(self):
        if self.wait_until_window_change():
            return self.app.top_window().Static.texts()[0]
        return self.app.top_window().Static.texts()[0]

import time

import pytest
from pytest import mark

from pages.sign_in import SignIn


@mark.order(2)
class TestSignIn:
    def setup_method(self):
        self.sign_in_page = SignIn()

    def test_empty_email_field(self):
        """Test empty emil field"""
        self.sign_in_page.sign_up_button().click_input()
        assert self.sign_in_page.message_value().__contains__("email - This field may not be blank.")
        self.sign_in_page.close_mesage_box()

    def test_empty_password_field(self):
        """Test empty password field"""
        self.sign_in_page.email_field().set_text("test@email.com")
        self.sign_in_page.sign_up_button().click_input()
        assert self.sign_in_page.message_value().__contains__("password - This field may not be blank.")
        self.sign_in_page.close_mesage_box()

    def test_wrong_credentials(self):
        """Test wrong credentials"""
        self.sign_in_page.email_field().set_text("wrong")
        self.sign_in_page.password_field().set_text("wrong")
        self.sign_in_page.sign_up_button().click_input()
        assert self.sign_in_page.message_value().__contains__("Unable to authenticate with provided credentials")
        self.sign_in_page.close_mesage_box()

    def test_successfully_sign_in(self):
        """Test successfully sign in"""
        self.sign_in_page.email_field().set_text("levon@admin.com")
        self.sign_in_page.password_field().set_text("adminadmin")
        self.sign_in_page.sign_up_button().click_input()
        time.sleep(1)
        assert self.sign_in_page.check_element_exists("Apartments")
        self.sign_in_page.set_signed_in(True)

import time

from pytest import mark

from pages.realtors import Realtors


@mark.order(4)
class TestRealtors:
    is_opened = False

    def setup_method(self):
        self.realtors = Realtors()
        if not self.is_opened:
            self.realtors.open_page()

    def test_add_user_button(self):
        self.realtors.add_user_button().click_input()
        self.realtors.select_realtor()
        assert self.realtors.check_element_exists("Role")

    def test_empty_name_field(self):
        """Test empty name field"""
        self.realtors.save_button().click_input()
        assert self.realtors.message_value() == "Full Name may not be empty"
        self.realtors.close_mesage_box()

    def test_empty_email_field(self):
        """Test empty emil field"""
        self.realtors.name_field().set_text("Test Name")
        self.realtors.save_button().click_input()
        assert self.realtors.message_value() == "Email may not be empty"
        self.realtors.close_mesage_box()

    def test_empty_password_field(self):
        """Test empty password field"""
        self.realtors.email_field().set_text("test1@email.com")
        self.realtors.save_button().click_input()
        assert self.realtors.message_value() == "Password may not be empty"
        self.realtors.close_mesage_box()

    def test_password_and_confirm_password_matching(self):
        """Test password and confirm password matching"""
        self.realtors.password_field().set_text("pass1")
        self.realtors.confirm_password_field().set_text("pass2")
        self.realtors.save_button().click_input()
        assert self.realtors.message_value() == "Password and confirm password don't match"
        self.realtors.close_mesage_box()

    def test_invalid_email(self):
        """Test invalid email"""
        self.realtors.email_field().set_text("Testemailcom")
        self.realtors.password_field().set_text("password")
        self.realtors.confirm_password_field().set_text("password")
        self.realtors.save_button().click_input()
        assert self.realtors.message_value().__contains__("Enter a valid email address")
        self.realtors.close_mesage_box()

    def test_short_password(self):
        """Test shor password"""
        self.realtors.email_field().set_text("realtor@email.com")
        self.realtors.password_field().set_text("pass")
        self.realtors.confirm_password_field().set_text("pass")
        self.realtors.save_button().click_input()
        assert self.realtors.message_value().__contains__("Ensure this field has at least 5 characters.")
        self.realtors.close_mesage_box()

    def test_creat_user(self):
        """Test create user"""
        self.realtors.password_field().set_text("passpass")
        self.realtors.confirm_password_field().set_text("passpass")
        self.realtors.save_button().click_input()
        time.sleep(1)
        assert self.realtors.check_element_exists("test1@email.com")

    @mark.order(7)
    def test_delete_all_users(self):
        """Test delete all users"""

        self.realtors.delete_all_users_button().click_input()
        self.realtors.yes_button_on_dialog().click_input()
        time.sleep(0.4)
        assert not self.realtors.check_element_exists("test1@email.com")

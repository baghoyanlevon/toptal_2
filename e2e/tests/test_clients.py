import time

from pytest import mark

from pages.clients import Clients


@mark.order(3)
class TestClients:
    is_opened = False

    def setup_method(self):
        self.clients = Clients()
        if not self.is_opened:
            self.clients.open_page()
            self.is_opened = True

    def test_add_user_button(self):
        self.clients.add_user_button().click_input()
        assert self.clients.check_element_exists("Role")

    def test_empty_name_field(self):
        """Test empty name field"""
        self.clients.save_button().click_input()
        assert self.clients.message_value() == "Full Name may not be empty"
        self.clients.close_mesage_box()

    def test_empty_email_field(self):
        """Test empty emil field"""
        self.clients.name_field().set_text("Test Name")
        self.clients.save_button().click_input()
        assert self.clients.message_value() == "Email may not be empty"
        self.clients.close_mesage_box()

    def test_empty_password_field(self):
        """Test empty password field"""
        self.clients.email_field().set_text("test1@email.com")
        self.clients.save_button().click_input()
        assert self.clients.message_value() == "Password may not be empty"
        self.clients.close_mesage_box()

    def test_password_and_confirm_password_matching(self):
        """Test password and confirm password matching"""
        self.clients.password_field().set_text("pass1")
        self.clients.confirm_password_field().set_text("pass2")
        self.clients.save_button().click_input()
        assert self.clients.message_value() == "Password and confirm password don't match"
        self.clients.close_mesage_box()

    def test_invalid_email(self):
        """Test invalid email"""
        self.clients.email_field().set_text("Testemailcom")
        self.clients.password_field().set_text("password")
        self.clients.confirm_password_field().set_text("password")
        self.clients.save_button().click_input()
        assert self.clients.message_value().__contains__("Enter a valid email address")
        self.clients.close_mesage_box()

    def test_short_password(self):
        """Test shor password"""
        self.clients.email_field().set_text("client@email.com")
        self.clients.password_field().set_text("pass")
        self.clients.confirm_password_field().set_text("pass")
        self.clients.save_button().click_input()
        assert self.clients.message_value().__contains__("Ensure this field has at least 5 characters.")
        self.clients.close_mesage_box()

    def test_creat_user(self):
        """Test create user"""
        self.clients.password_field().set_text("passpass")
        self.clients.confirm_password_field().set_text("passpass")
        self.clients.save_button().click_input()
        time.sleep(1)
        assert self.clients.check_element_exists("test1@email.com")

    @mark.order(8)
    def test_delete_all_users(self):
        """Test delete all users"""

        self.clients.delete_all_users_button().click_input()
        self.clients.yes_button_on_dialog().click_input()
        time.sleep(0.4)
        assert not self.clients.check_element_exists("test1@email.com")

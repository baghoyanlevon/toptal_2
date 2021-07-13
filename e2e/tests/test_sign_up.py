from pytest import mark

from pages.sign_up import SignUp


@mark.order(1)
class TestSignUp:
    def setup_method(self):
        """Setup method"""
        self.sign_up_page = SignUp()

    def test_empty_name_field(self):
        """Test empty name field"""
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value() == "Full Name may not be empty"
        self.sign_up_page.close_mesage_box()

    def test_empty_email_field(self):
        """Test empty emil field"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value() == "Email may not be empty"
        self.sign_up_page.close_mesage_box()

    def test_empty_password_field(self):
        """Test empty password field"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.email_field().set_text("Test@email.com")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value() == "Password may not be empty"
        self.sign_up_page.close_mesage_box()

    def test_password_and_confirm_password_matching(self):
        """Test password and confirm password matching"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.email_field().set_text("Test@email.com")
        self.sign_up_page.password_field().set_text("pass1")
        self.sign_up_page.confirm_password_field().set_text("pass2")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value() == "Password and confirm password don't match"
        self.sign_up_page.close_mesage_box()

    def test_invalid_email(self):
        """Test invalid email"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.email_field().set_text("Testemailcom")
        self.sign_up_page.password_field().set_text("pass1")
        self.sign_up_page.confirm_password_field().set_text("pass1")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value().__contains__("Enter a valid email address")
        self.sign_up_page.close_mesage_box()

    def test_short_password(self):
        """Test shor password"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.email_field().set_text("Test@email.com")
        self.sign_up_page.password_field().set_text("pass")
        self.sign_up_page.confirm_password_field().set_text("pass")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value().__contains__("Ensure this field has at least 5 characters.")
        self.sign_up_page.close_mesage_box()

    def test_creat_user(self):
        """Test create user"""
        self.sign_up_page.name_field().set_text("Test Name")
        self.sign_up_page.email_field().set_text("test@email.com")
        self.sign_up_page.password_field().set_text("passpass")
        self.sign_up_page.confirm_password_field().set_text("passpass")
        self.sign_up_page.sign_up_button().click_input()
        assert self.sign_up_page.message_value() == ("You successfully signed up")
        self.sign_up_page.close_mesage_box()

from pytest import mark

from pages.apartments import Apartments


@mark.order(5)
class TestApartments:
    is_opened = False

    def setup_method(self):
        self.apartments = Apartments()
        if not self.is_opened:
            self.apartments.open_page()
            self.apartments.close_map_message()
            self.is_opened = True

    def test_add_aparment_button(self):
        """Test add apartment button"""

        self.apartments.add_apartment_button().click_input()
        assert self.apartments.check_element_exists("Next")

    def test_next_adding_button(self):
        """Test adding process"""
        self.apartments.next_adding_apartment_button().click_input()
        assert self.apartments.check_element_exists("Name")

    def test_empty_name_field(self):
        """Test empty name field"""
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.message_value() == "Name must be filled out"
        self.apartments.close_mesage_box()

    def test_empty_description_field(self):
        """Test empty description field"""
        self.apartments.name_edit().set_text("test name")
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.message_value() == "Description must be filled out"
        self.apartments.close_mesage_box()

    def test_empty_floor_size_field(self):
        """Test empty floor size field"""
        self.apartments.description_edit().set_text("test description")
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.message_value() == "Floor size must be valid number"
        self.apartments.close_mesage_box()

    def test_empty_price_field(self):
        """Test empty price field"""
        self.apartments.floor_size_edit().set_text(123)
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.message_value() == "Price must be valid number"
        self.apartments.close_mesage_box()

    def test_empty_number_of_rooms_field(self):
        """Test empty number of rooms field"""
        self.apartments.price_edit().set_text(123)
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.message_value() == "Number of rooms must be valid number"
        self.apartments.close_mesage_box()

    def test_add_apartment(self):
        self.apartments.number_of_rooms_edit().set_text(123)
        self.apartments.apartment_dialog_save_button().click_input()
        assert self.apartments.check_element_exists("test name")

    def test_delete_all_apartments(self):
        self.apartments.delete_all_apartments_button().click_input()
        assert not self.apartments.check_element_exists("test name")

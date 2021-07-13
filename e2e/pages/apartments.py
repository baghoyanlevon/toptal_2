from pages.base_page import BasePage


class Apartments(BasePage):
    def __init__(self):
        super().__init__()
        if self.signedIn == False:
            self.sign_in("levon@admin.com", "adminadmin")
        super().class_name_configuration()

    def open_page(self):
        self.app.top_window().ApartmentsTabItem.click_input()

    def check_element_exists(self, name):
        return self.app.top_window()[name].exists()

    def print(self):
        self.app.top_window().print_control_identifiers()

    def name_edit(self):
        return self.app.top_window().NameEdit

    def description_edit(self):
        return self.app.top_window().DescriptionEdit

    def floor_size_edit(self):
        return self.app.top_window().Floor_SizeEdit

    def price_edit(self):
        return self.app.top_window().Floor_SizeEdit2

    def number_of_rooms_edit(self):
        return self.app.top_window().Rooms_NumEdit

    def latitude_edit(self):
        return self.app.top_window().LatitudeEdit

    def longitude_edit(self):
        return self.app.top_window().LongitudeEdit

    def apartment_dialog_save_button(self):
        return self.app.top_window().SaveButton

    def apartment_dialog_cancel_button(self):
        return self.app.top_window().CancelButton

    def close_map_message(self):
        ok = self.app.top_window().OK2
        if ok.exists():
            ok.click_input()

    def add_apartment_button(self):
        return self.app.top_window().ApartmentAddToolButton

    def next_adding_apartment_button(self):
        return self.app.top_window().NextStatic

    def cancel_adding_apartment_button(self):
        return self.app.top_window().CancelStatic

    def save_all_apartments_button(self):
        return self.app.top_window().ApartmentSaveToolButton

    def discard_all_apartments_button(self):
        return self.app.top_window().ApartmentDiscardToolButton

    def delete_all_apartments_button(self):
        return self.app.top_window().ApartmentDeleteToolButton

    def yes_button_on_dialog(self):
        return self.app.top_window().ApartmentDeleteToolButton

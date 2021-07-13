from django.test import TestCase
from django.contrib.auth import get_user_model
from django.urls import reverse

from core.models import User, Apartment
from rest_framework.test import APIClient
from rest_framework import status

APARTMENTS_URL = reverse('apartment:apartment-list')


def detail_url(object_id):
    """Return data_for_annotation detail URL"""
    return reverse('apartment:apartment-detail', args=[object_id])


def create_user(**params):
    """Helper function to create new user"""
    return get_user_model().objects.create_user(**params)


def create_apartment(**params):
    """Helper function to create new apartment"""
    return Apartment.objects.create(**params)


class ApartmentApiTestsForAdmin(TestCase):
    """Test the apartments API for admin"""

    def setUp(self):
        self.client = APIClient()
        self.user = create_user(
            email='admin@test.com',
            password='testpass',
            name='name',
            role='admin'
        )
        self.user.role = User.ADMIN
        self.user.save()
        self.client.force_authenticate(user=self.user)

        self.apartment_owner_user = create_user(
            email='client@test.com',
            password='testpass',
            name='name',
            role='realtor'
        )
        self.apartment_owner_user.role = User.REALTOR
        self.apartment_owner_user.save()
        self.client.force_authenticate(user=self.user)

    def test_all_apartments_api(self):
        """Test getting all apartments using admin user"""
        res = self.client.get(APARTMENTS_URL)
        self.assertEqual(res.status_code, status.HTTP_200_OK)

    def test_add_apartment_api(self):
        """Test adding all apartments using admin user"""
        payload = {
            'user': self.apartment_owner_user.id,
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.3423,
            'longitude': 123.3422,
            'rented': False
        }
        res = self.client.post(APARTMENTS_URL, payload)
        self.assertEqual(res.status_code, status.HTTP_201_CREATED)
        self.assertIn('name', res.data)
        self.assertIn('description', res.data)
        self.assertIn('floor_area_size', res.data)
        self.assertIn('price_per_month', res.data)
        self.assertIn('number_of_rooms', res.data)
        self.assertIn('latitude', res.data)
        self.assertIn('longitude', res.data)

    def test_update_apartment_api(self):
        """Test updating all apartments using admin user"""
        payload = {
            'user': self.apartment_owner_user,
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234,
            'longitude': 123.34234
        }
        apartment = create_apartment(**payload)
        payload['description'] = 'changed description'
        url = detail_url(apartment.pk)
        payload['user'] = self.apartment_owner_user.id
        res = self.client.put(url, payload)
        self.assertEqual(res.status_code, status.HTTP_200_OK)
        self.assertEqual(res.data['description'], payload['description'])

    def test_delete_apartment_api(self):
        """Test deleting the apartment using admin user"""
        payload = {
            'user': self.apartment_owner_user,
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234,
            'longitude': 123.34234
        }
        apartment = create_apartment(**payload)
        url = detail_url(apartment.id)
        res = self.client.delete(url)
        self.assertEqual(res.status_code, status.HTTP_204_NO_CONTENT)

    def test_apartment_date_format(self):
        """Test date format"""
        payload = {
            'user': self.apartment_owner_user,
            'date': '20210101',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234,
            'longitude': 123.34234
        }
        res = self.client.post(APARTMENTS_URL, payload)
        self.assertIn('date', res.data)
        self.assertEqual(res.status_code, status.HTTP_400_BAD_REQUEST)

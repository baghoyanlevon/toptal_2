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


def create_apartment(user, **params):
    """Helper function to create new apartment"""
    return Apartment.objects.create(user=user, **params)


class ApartmentApiTestsForClient(TestCase):
    """Test the apartments API for client"""

    def setUp(self):
        self.client = APIClient()
        self.user = create_user(
            email='test@test.com',
            password='testpass',
            name='name'
        )
        self.user.role = User.CLIENT
        self.user.save()
        self.client.force_authenticate(user=self.user)

    def test_all_apartments_api(self):
        """Test geting all apartments using client user"""
        res = self.client.get(APARTMENTS_URL)
        self.assertEqual(res.status_code, status.HTTP_200_OK)

    def test_add_apartment_api(self):
        """Test adding apartment using client user"""
        payload = {
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'prive_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234234,
            'longitude': 123.34234234
        }
        res = self.client.post(APARTMENTS_URL, payload)
        self.assertNotIn('date', res.data)
        self.assertNotIn('name', res.data)
        self.assertNotIn('description', res.data)
        self.assertNotIn('floor_area_size', res.data)
        self.assertNotIn('comment', res.data)
        self.assertEqual(res.status_code, status.HTTP_403_FORBIDDEN)

    def test_update_apartment_api(self):
        """Test updating apartment using client user"""
        payload = {
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234234,
            'longitude': 123.34234234
        }
        apartment = create_apartment(self.user, **payload)
        payload['description'] = 'changed description'
        url = detail_url(apartment.id)
        res = self.client.put(url, payload)

        self.assertEqual(res.status_code, status.HTTP_403_FORBIDDEN)

    def test_delete_apartment_api(self):
        """Test deleting apartment using client user"""
        payload = {
            'date': '2021-01-01',
            'name': 'test name',
            'description': 'test description',
            'floor_area_size': 123.5,
            'price_per_month': 123,
            'number_of_rooms': 2,
            'latitude': 123.34234234,
            'longitude': 123.34234234
        }
        apartment = create_apartment(self.user, **payload)
        url = detail_url(apartment.id)
        res = self.client.delete(url)
        self.assertEqual(res.status_code, status.HTTP_403_FORBIDDEN)

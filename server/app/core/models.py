from django.db import models
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.conf import settings
from datetime import timedelta


class UserManager(BaseUserManager):
    def create_user(self, email, password=None, **extra_fields):
        """Creates and saves a new user"""
        if not email:
            raise ValueError('Users must have an email address')
        user = self.model(email=self.normalize_email(email), **extra_fields)
        user.set_password(password)
        user.save(using=self._db)

        return user

    def create_superuser(self, email, password):
        """Creates and saves a new super user"""
        user = self.create_user(email, password)
        user.is_staff = True
        user.is_superuser = True
        user.save(using=self._db)

        return user


class User(AbstractBaseUser, PermissionsMixin):
    """Custom user model that supports email instead username"""
    ADMIN = 'admin'
    REALTOR = 'realtor'
    CLIENT = 'client'

    ROLE_CHOICES = (
        (ADMIN, 'Admin'),
        (REALTOR, 'Realtor'),
        (CLIENT, 'Client')
    )

    email = models.EmailField(max_length=255, unique=True)
    name = models.CharField(max_length=255)
    is_active = models.BooleanField(default=True)
    is_staff = models.BooleanField(default=True)
    role = models.CharField(max_length=10, choices=ROLE_CHOICES, blank=True, null=True, default='client')
    objects = UserManager()

    USERNAME_FIELD = 'email'


class Apartment(models.Model):
    """Apartment model"""

    user = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        null=True,
    )
    name = models.CharField(max_length=255)
    description = models.CharField(max_length=255)
    floor_area_size = models.FloatField()
    price_per_month = models.IntegerField(blank=False)
    number_of_rooms = models.IntegerField(blank=False)
    latitude = models.DecimalField(max_digits=9, decimal_places=6)
    longitude = models.DecimalField(max_digits=9, decimal_places=6)
    date = models.DateField()
    rented = models.BooleanField(default=False)
    def __str__(self):
        return self.name

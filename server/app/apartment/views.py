from rest_framework import authentication
from rest_framework.decorators import action
from rest_framework import viewsets, status
from rest_framework.response import Response
import django.core.exceptions as exceptions

import apartment.serializers as serializers
from user.permissions import IsAdmin, IsRealtorUser, IsClientUser
from core.models import Apartment, User


class ApartmentsView(viewsets.ModelViewSet):
    """Create, read, update, delete a apartment"""
    authentication_classes = [authentication.TokenAuthentication, ]
    serializer_class = serializers.ApartmentSerializer
    queryset = Apartment.objects.all()

    def get_permissions(self):
        """Returns the list of permissions that this view requires"""
        if self.request.method == "GET":
            permission_classes = [IsAdmin | IsRealtorUser | IsClientUser]
        else:
            permission_classes = [IsAdmin | IsRealtorUser]
        return [permission() for permission in permission_classes]

    def _params_to_ints(self, qs):
        """Convert a list of string IDs to a list of integers"""
        return [int(str_id) for str_id in qs.split(',')]

    def perform_create(self, serializer):
        """Create a new apartment"""
        request_maker = self.request.user
        if request_maker.role == User.ADMIN:
            apartment_owner = User.objects.get(id=self.request.data['user'])
            if apartment_owner.role == User.REALTOR:
                serializer.save()
            else:
                raise exceptions.SuspiciousOperation()
        else:
            serializer.save(user=self.request.user)

    def get_serializer_class(self):
        """Return appropriate serializer class"""
        request_maker = self.request.user

        if request_maker.role == User.ADMIN:
            return serializers.ApartmentSerializerForAdmin

        return self.serializer_class

    def get_queryset(self):
        """Retrieve the apartment"""
        queryset = Apartment.objects.all()

        queryset = queryset.filter(user__role=User.REALTOR)
        if (self.request.user.role == User.REALTOR):
            queryset = queryset.filter(user=self.request.user)
        size_min = self.request.query_params.get('size_min')
        size_max = self.request.query_params.get('size_max')
        price_min = self.request.query_params.get('price_min')
        price_max = self.request.query_params.get('price_max')
        number_of_rooms_min = self.request.query_params.get('number_of_rooms_min')
        number_of_rooms_max = self.request.query_params.get('number_of_rooms_max')

        if size_min:
            queryset = queryset.filter(floor_area_size__gte=size_min)
        if size_max:
            queryset = queryset.filter(floor_area_size__lte=size_max)
        if price_min:
            queryset = queryset.filter(price_per_month__gte=price_min)
        if price_max:
            queryset = queryset.filter(price_per_month__lte=price_max)
        if number_of_rooms_min:
            queryset = queryset.filter(number_of_rooms__gte=number_of_rooms_min)
        if number_of_rooms_max:
            queryset = queryset.filter(number_of_rooms__lte=number_of_rooms_max)
        return queryset

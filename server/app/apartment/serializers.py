from rest_framework import serializers

from core.models import Apartment

# 'date': '2021-01-01',
#             'name': 'test name',
#             'description': 'test description',
#             'floor_area_size': 123.5,
#             'price_per_month': 123,
#             'number_of_rooms':2,
#             'latitude':123.34234234,
#             'longitude':123.34234234
class ApartmentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Apartment
        fields = ('id', 'name', 'date','description', 'floor_area_size', 'price_per_month', 'number_of_rooms','latitude','longitude','rented')
        read_only_fields = ('id',)


class ApartmentSerializerForAdmin(serializers.ModelSerializer):
    user_role = serializers.ReadOnlyField(source='user.role')
    class Meta:
        model = Apartment
        fields = ('id', 'name','date', 'description', 'floor_area_size', 'price_per_month', 'number_of_rooms','latitude','longitude','user', 'user_role','rented')
        read_only_fields = ('id',)

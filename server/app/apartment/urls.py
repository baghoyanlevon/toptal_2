from django.urls import path, include

from apartment import views
from rest_framework.routers import DefaultRouter

app_name = 'apartment'

router = DefaultRouter()

router.register('', views.ApartmentsView)
urlpatterns = [
    path('', include(router.urls)),
]

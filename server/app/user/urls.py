from django.urls import path, include

from user import views
from rest_framework.routers import DefaultRouter

app_name = 'user'

router = DefaultRouter()

router.register('', views.UserView)

urlpatterns = [
    path('signup/', views.CreateUserView.as_view(), name='signup'),
    path('signin/', views.CreateTokenView.as_view(), name='signin'),
    path('me/', views.ManageUserView.as_view(), name='me'),
    path('', include(router.urls)),
]

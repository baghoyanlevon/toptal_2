from rest_framework import generics, authentication, permissions
from rest_framework.authtoken.views import ObtainAuthToken
from rest_framework.settings import api_settings
from rest_framework import viewsets
from rest_framework.authtoken.models import Token
from rest_framework.response import Response

from user.permissions import IsAdmin, IsRealtorUser
from user.serializers import UserSerializer, AuthTokenSerializer, UserSerializerForAdmin

from core.models import User, Apartment


class UserView(viewsets.ModelViewSet):
    authentication_classes = (authentication.TokenAuthentication,)
    permission_classes = (IsAdmin | IsRealtorUser,)
    serializer_class = UserSerializerForAdmin
    queryset = User.objects.all()

    def perform_update(self, serializer):
        data = self.request.data
        if 'role' in data and data['role'] == User.CLIENT:
            Apartment.objects.filter(user__id = self.request.data['id']).delete()
        super().perform_update(serializer)

    def get_queryset(self):
        """Retrieve the user data"""
        queryset = User.objects.all()
        if self.request.user.role == User.REALTOR:
            queryset = queryset.filter(role=User.CLIENT)
        else:
            queryset = queryset.exclude(role=User.ADMIN)

        role_param = self.request.query_params.get('role')
        if role_param:
            queryset = queryset.filter(role = role_param)
        return queryset


class CreateUserView(generics.CreateAPIView):
    """Create a new user in the system"""
    serializer_class = UserSerializer


class CreateTokenView(ObtainAuthToken):
    """Create a new auth token for the user"""
    serializer_class = AuthTokenSerializer
    renderer_classes = api_settings.DEFAULT_RENDERER_CLASSES

    def post(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=request.data,
                                           context={'request': request})
        serializer.is_valid(raise_exception=True)
        user = serializer.validated_data['user']
        token, created = Token.objects.get_or_create(user=user)
        return Response({'token': token.key,
                         'email': user.email,
                         'role': user.role,
                         'name': user.name
                         }
                        )


class ManageUserView(generics.RetrieveUpdateAPIView):
    """Manage the authenticated user"""
    serializer_class = UserSerializer
    authentication_classes = (authentication.TokenAuthentication,)
    permission_classes = (permissions.IsAuthenticated,)

    def get_object(self):
        """Retrieve and return authentication user"""
        return self.request.user

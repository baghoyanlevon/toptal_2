from rest_framework.permissions import BasePermission


class IsAdmin(BasePermission):
    """Allows access only to adminUser users."""

    def has_permission(self, request, view):
        return bool(request.user and request.user.is_authenticated and request.user.role == request.user.ADMIN)


class IsClientUser(BasePermission):
    """Allows access only to client users."""

    def has_permission(self, request, view):
        return bool(request.user and request.user.is_authenticated and request.user.role == request.user.CLIENT)


class IsRealtorUser(BasePermission):
    """Allows access only to realtor users."""

    def has_permission(self, request, view):
        return bool(request.user and request.user.is_authenticated and request.user.role == request.user.REALTOR)

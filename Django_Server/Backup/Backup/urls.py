from django.contrib import admin
from django.urls import path, include
import store.views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('store/', include('store.urls')),
]

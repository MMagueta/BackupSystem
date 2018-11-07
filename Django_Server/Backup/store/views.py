from django.shortcuts import render
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt

@csrf_exempt
def index(request):
	if request.POST:
		print(request.POST.get('data'))
		return JsonResponse({'Yummy data!':':)'})
	else:
		return JsonResponse({'No data!':':('})

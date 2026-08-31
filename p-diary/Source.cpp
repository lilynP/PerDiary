#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib> 

using namespace std;
using namespace System;

struct entrada
{
	int id;
	char fecha[30];
	char titulo[100];
	char contenido[1000];
	char emocion[20];
	int palabras;

};

entrada* diario = nullptr;
int totalentradas = 0;
int siguienteid = 1; 


void obtenerfecha(char* fecha)
{
	time_t t;
	struct tm* info;
	time(&t);
	info = localtime(&t);
	strftime(fecha, 30, "%d/%m/%Y  %H:%M", info);
}
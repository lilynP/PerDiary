#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib> 
#include <ctime>

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

//obtener fecha? 
void obtenerfecha(char* fecha)
{
	time_t t;
	struct tm* info;
	time(&t);
	info = localtime(&t);
	strftime(fecha, 30, "%d/%m/%Y  %H:%M", info);
}

//contar palabras
int contarpalabras(char* texto)
{
	int contador = 0;
	int enpalabra = 0;

	for (int i = 0; texto[i] != '\0'; i++)
	{
		if (texto[i] != ' ' && texto[i] != '\n' && texto[i] != '\t')
		{
			if (!enpalabra)
			{
				contador++;
				enpalabra = true;
			}

		}
		else
		{
			enpalabra = false;
		}
	}
}

void agregarentrada()
{
	diario = (entrada*)realloc(diario, (totalentradas + 1) * sizeof(entrada));

	cout << "NUEVA ENTRADA";
	cout << "TITULO: ";
	cin.getline(diario[totalentradas].titulo, 100);
	if (strlen(diario[totalentradas].titulo) == 0)
	{
		cin.getline(diario[totalentradas].titulo, 100);
	}

	cout << "CONTENIDO: ";
	cin.getline(diario[totalentradas].contenido, 1000);

	cout << "EMOCION (feliz, triste, enojado, cansado, enamorado): ";
	cin.getline(diario[totalentradas].emocion, 20);


}

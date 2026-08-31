#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib> 
#include <ctime>
#include <windows.h>

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

void pausa()
{
	cout << "Presiona cualquier tecla para continuar..."; 
	_getch();
	system("cls");
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

void mostrarentrada(entrada e)
{
	SetConsoleOutputCP(65001);
	char* emoji = "(●'◡'●)";
	if (strcmp(e.emocion, "triste") == 0) emoji = "（；´д｀）ゞ";
	else if (strcmp(e.emocion, "enojado") == 0) emoji = "o(≧口≦)o";
	else if (strcmp(e.emocion, "cansado") == 0) emoji = "(￣﹃￣)";
	else if (strcmp(e.emocion, "enamorado") == 0) emoji = "(p≧w≦q)";

	cout << "\n ┌─────────────────────────────────────┐\n";
	cout << "| ID: #" << e.id << "                               |\n";
	cout << "│ T " << e.fecha << "                         │\n";
	cout << "│ E " << e.titulo << "\n";
	cout << "│ " << e.contenido << "\n";
	cout << "│ " << emoji << " " << e.emocion << "\n";
	cout << "│ E " << e.palabras << " palabras                     │\n";
	cout << "└─────────────────────────────────────┘\n";


	SetConsoleOutputCP(437);
}

void verentradas()
{
	if (totalentradas == 0)
	{
		cout << "\n no hay entradas en tu diario\n";
		return;
	}
	cout << "\n mis entradas \n";
	cout << "Total: %d entradas\n\n" << totalentradas;

	for (int i = 0; i < totalentradas; i++)
	{
		cout << "%d. [%s] %s - %s\n" << i + 1 << diario[i].fecha << diario[i].titulo << diario[i].emocion;
	}

	int opcion;
	cout << "Ver entrada en detalle? (0 = No, 1 = Si): "; cin >> opcion;
	if (opcion > 0 && opcion <= totalentradas)
	{
		system("cls");
		mostrarentrada(diario[opcion - 1]);
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

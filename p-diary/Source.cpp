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

char* citas[][2] =
{
	{"Escribe para vivir, no vivas para escribir.", "Anónimo"},
	{"La pluma es la lengua del alma.", "Cervantes"},
	{"Escribir es fácil. Solo hay que poner una palabra tras otra.", "Neil Gaiman"},
	{"Un escritor es alguien para quien escribir es más difícil que para otros.", "Thomas Mann"},
	{"La literatura es el arte de descubrir algo extraordinario sobre personas ordinarias.", "Pearl S. Buck"},
	{"Escribe sin miedo. Edita sin piedad.", "Anónimo"},
	{"La escritura es la pintura de la voz.", "Voltaire"},
	{"El lapiz es el mejor amigo del escritor.", "Anónimo"},
	{"Escribir es la forma más profunda de leer.", "Anónimo"},
	{"Un diario es un amigo que nunca juzga.", "Anónimo"},
	{"Las palabras son el disfraz de las ideas.", "Anónimo"},
	{"Escribir es pensar con otra tinta.", "Anónimo"},
	{"La poesia es el lenguaje de los sentimientos.", "Anónimo"},
	{"Leer es viajar sin mover los pies.", "Anónimo"},
	{"La escritura es el espejo del alma.", "Anónimo"}

};

int totalcitas = sizeof(citas) / sizeof(citas[0]);

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

	diario[totalentradas].id = siguienteid++;
	obtenerfecha(diario[totalentradas].fecha);
	diario[totalentradas].palabras = contarpalabras(diario[totalentradas].contenido);

}

void mostrarcitamotivacional()
{
	int indice = rand() % totalcitas;

	cout << "\n╔══════════════════════════════════════╗\n";
	cout << "║       frase chevere del dia :)       ║\n";
	cout << "╠══════════════════════════════════════╣\n";
	cout << "║                                      ║\n";
	cout << "║  \"" << citas[indice][0] << "\"\n";
	cout << "║                                      ║\n";
	cout << "║           - " << citas[indice][1] << "           ║\n";
	cout << "║                                      ║\n";
	cout << "╚══════════════════════════════════════╝\n";
	
}

int main()
{
	srand(time(NULL));
	int opcion;


	cout << "21111112222222221222222222221111122222222222\n";
	cout << "21122112222222212122222222221122112222222222\n";
	cout << "21122112222222212222222112221111222221222212\n";
	cout << "21111121112111112122211221221122112221222122\n";
	cout << "21122221112122212122111111121122221121111222\n";
	cout << "21122222222111112112122222211122222112211222\n";
	cout << "22222222222222222222222222222222222111112222\n";

	do
	{
		cout << "\n   =======MENU=====\n";
		cout << "\n1. QUIERO ESCRIBIR!!! >:D\n";
		cout << "\n2. Quiero ver mis entradas...\n";
		cout << "\n3. Salir...-_-\n";
		cout << "Opcion: "; cin >> opcion;

		switch (opcion)
		{
		case 1:
			system("cls");
			agregarentrada();
			break;
		case 2: 
			system("cls");
			verentradas();
			break;
		case 3:
			system("cls");
			cout << "Hasta pronto! :D Recuerda...";
			mostrarcitamotivacional();
			cout << "Sigue escribiendo!!!! >:D";
			break;
		}



	} while (opcion != 1 || opcion != 2 || opcion !=3);
}
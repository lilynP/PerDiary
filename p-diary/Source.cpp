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
string obtenerfecha(char* fecha)
{
	time_t t;
	struct tm* info;
	time(&t);
	info = localtime(&t);
	if (info == NULL) 
	{
		strcpy(fecha, "01/01/1970 00:00");
		return string(fecha);
	}
	strftime(fecha, 30, "%d/%m/%Y %H:%M", info);

	return string(fecha);
}

char* citas[][2] =
{
	{"Escribe para vivir, no vivas para escribir.", "Anonimo"},
	{"La pluma es la lengua del alma.", "Cervantes"},
	{"Escribir es fácil. Solo hay que poner una palabra tras otra.", "Neil Gaiman"},
	{"Un escritor es alguien para quien escribir es más difícil que para otros.", "Thomas Mann"},
	{"La literatura es el arte de descubrir algo extraordinario sobre personas ordinarias.", "Pearl S. Buck"},
	{"Escribe sin miedo. Edita sin piedad.", "Anonimo"},
	{"La escritura es la pintura de la voz.", "Voltaire"},
	{"El lapiz es el mejor amigo del escritor.", "Anonimo"},
	{"Escribir es la forma más profunda de leer.", "Anonimo"},
	{"Un diario es un amigo que nunca juzga.", "Anonimo"},
	{"Las palabras son el disfraz de las ideas.", "Anonimo"},
	{"Escribir es pensar con otra tinta.", "Anonimo"},
	{"La poesia es el lenguaje de los sentimientos.", "Anonimo"},
	{"Leer es viajar sin mover los pies.", "Anonimo"},
	{"La escritura es el espejo del alma.", "Anonimo"}

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
	bool enpalabra = false;

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
	return contador;
}

void mostrarentrada(entrada e)
{
	SetConsoleOutputCP(65001);
	string emoji = "(●'◡'●)";
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
	cout << "\n =======MIS ENTRADAS====== \n";
	cout << "Total: " << totalentradas << " entradas\n\n";

	for (int i = 0; i < totalentradas; i++)
	{
		cout << i + 1 << ". [" << diario[i].fecha << "] " << diario[i].titulo << " - " << diario[i].emocion << "\n";
	}

	int opcion;
	cout << "Ver entrada en detalle? (0 = No, 1 = Si): "; cin >> opcion;
	if (opcion > 0 && opcion <= totalentradas)
	{
		system("cls");
		mostrarentrada(diario[opcion - 1]);
	}
	pausa();
}


void agregarentrada()
{
	diario = (entrada*)realloc(diario, (totalentradas + 1) * sizeof(entrada));

	cout << "NUEVA ENTRADA" << endl;
	cout << "TITULO: ";
	cin.ignore();
	cin.getline(diario[totalentradas].titulo, 100);
	if (strlen(diario[totalentradas].titulo) == 0)
	{
		strcpy(diario[totalentradas].titulo, "Sin titulo");
		cout << "Titulo vacio, se asigno 'Sin titulo'. \n";
	}

	cout << "CONTENIDO: ";
	cin.getline(diario[totalentradas].contenido, 1000);

	cout << "EMOCION (feliz, triste, enojado, cansado, enamorado): ";
	cin.getline(diario[totalentradas].emocion, 20);

	diario[totalentradas].id = siguienteid++;
	obtenerfecha(diario[totalentradas].fecha);
	diario[totalentradas].palabras = contarpalabras(diario[totalentradas].contenido);

	totalentradas++;

	cout << "\n Entrada guardada con exito!\n";
	cout << "Fecha: "<< obtenerfecha(diario[totalentradas-1].fecha) << "\n";
	cout << "Palabras: " << contarpalabras(diario[totalentradas-1].contenido) << "\n";

	
	pausa();
}

void mostrarcitamotivacional()
{
	SetConsoleOutputCP(65001);
	int indice = rand() % totalcitas;
	cout << "\n╔══════════════════════════════════════╗\n";
	cout << "║       CITA DEL DÍA                   ║\n";
	cout << "╠══════════════════════════════════════╣\n";
	cout << "║                                      ║\n";
	cout << "║  \"" << citas[indice][0] << "\"\n";
	cout << "║                                      ║\n";
	cout << "║           - " << citas[indice][1] << "           ║\n";
	cout << "║                                      ║\n";
	cout << "╚══════════════════════════════════════╝\n";
	SetConsoleOutputCP(437);

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
			_getch();
			break;
		default:
			cout << "Pon algo valido >:(";
		}



	} while (opcion !=3);

	delete[]diario;
	return 0;
}
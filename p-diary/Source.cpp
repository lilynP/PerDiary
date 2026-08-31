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

#define filas 7
#define columnas 44

void ventana()
{
	Console::SetWindowSize(40, 40);
	Console::CursorVisible = false;
}

int matriz1[filas][columnas] =
{
	{2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2},
	{2,1,1,2,2,1,1,2,2,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,2,2,2,2,1,1,2,2,1,1,2,2,2,2,2,2,2,2,2,2},
	{2,1,1,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,1,2},
	{2,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,2,1,2,2,2,1,1,2,2,1,2,2,1,1,2,2,1,1,2,2,2,1,2,2,2,1,2,2},
	{2,1,1,2,2,2,2,1,1,1,2,1,2,2,2,1,2,1,2,2,1,1,1,1,1,1,1,2,1,1,2,2,2,2,1,1,2,1,1,1,1,2,2,2},
	{2,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,2,1,1,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2,2,1,1,2,2,1,1,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2},
};

int matriz2[filas][columnas] =
{
	{4,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4},
	{4,3,3,4,4,3,3,4,4,4,4,4,4,4,4,3,4,3,4,4,4,4,4,4,4,4,4,4,3,3,4,4,3,3,4,4,4,4,4,4,4,4,4,4},
	{4,3,3,4,4,3,3,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,3,3,4,4,4,3,3,3,3,4,4,4,4,4,3,4,4,4,4,3,4},
	{4,3,3,3,3,3,4,3,3,3,4,3,3,3,3,3,4,3,4,4,4,3,3,4,4,3,4,4,3,3,4,4,3,3,4,4,4,3,4,4,4,3,4,4},
	{4,3,3,4,4,4,4,3,3,3,4,3,4,4,4,3,4,3,4,4,3,3,3,3,3,3,3,4,3,3,4,4,4,4,3,3,4,3,3,3,3,4,4,4},
	{4,3,3,4,4,4,4,4,4,4,4,3,3,3,3,3,4,3,3,4,3,4,4,4,4,4,4,3,3,3,4,4,4,4,4,3,3,4,4,3,3,4,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,4,4,4,4}
};

int matriz3[filas][columnas] =
{
	{6,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,5,6,6,6,6,6,6,6,6,6,6,6,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6},
	{6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,6,5,6,6,6,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,6,6},
	{6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,6,6,6,6,6,6,6,5,5,6,6,6,5,5,5,5,6,6,6,6,6,5,6,6,6,6,5,6},
	{6,5,5,5,5,5,6,5,5,5,6,5,5,5,5,5,6,5,6,6,6,5,5,6,6,5,6,6,5,5,6,6,5,5,6,6,6,5,6,6,6,5,6,6},
	{6,5,5,6,6,6,6,5,5,5,6,5,6,6,6,5,6,5,6,6,5,5,5,5,5,5,5,6,5,5,6,6,6,6,5,5,6,5,5,5,5,6,6,6},
	{6,5,5,6,6,6,6,6,6,6,6,5,5,5,5,5,6,5,5,6,5,6,6,6,6,6,6,5,5,5,6,6,6,6,6,5,5,6,6,5,5,6,6,6},
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,5,5,5,5,6,6,6,6}
};

void color(int c)
{
	switch (c)
	{
	case 1:
		Console::ForegroundColor = ConsoleColor::Cyan; break;
	case 2:
		Console::ForegroundColor = ConsoleColor::Green; break;
	case 3:
		Console::ForegroundColor = ConsoleColor::Red; break;
	case 4: 
		Console::ForegroundColor = ConsoleColor::Magenta; break;
	case 5:
		Console::ForegroundColor = ConsoleColor::Yellow; break;
	case 6: 
		Console::ForegroundColor = ConsoleColor::White; break;
	}
}


void preferenciatitulo(int preferenciatitulo)
{


	switch (preferenciatitulo)
	{
	case 1: 
		for (int f = 0; f < filas; f++)
		{
			for (int c = 0; c < columnas; c++)
			{
				color(matriz1[f][c]);
				cout << (char)219;
			}
		}
		break;
	case 2: 
		for (int f = 0; f < filas; f++)
		{
			for (int c = 0; c < columnas; c++)
			{
				color(matriz2[f][c]);
				cout << (char)219;
			}
		}
		break;
	case 3: 
		for (int f = 0; f < filas; f++)
		{
			for (int c = 0; c < columnas; c++)
			{
				color(matriz3[f][c]);
				cout << (char)219;
			}
		}
		break;
	}
}

int* cambiarcoloresmenu(int colorfondo, int colortexto)
{
	ConsoleColor fondoactual = Console::BackgroundColor;
	ConsoleColor textoactual = Console::ForegroundColor;

	Console::BackgroundColor = (ConsoleColor)colorfondo;
	Console::ForegroundColor = (ConsoleColor)colortexto;

	system("cls");

	preferenciatitulo(1);

	Console::BackgroundColor = fondoactual;
	Console::ForegroundColor = textoactual;
}

void menucustomizacion()
{
	int opcolor;

	do
	{
		system("cls");

		Console::ForegroundColor = ConsoleColor::Cyan;
		preferenciatitulo(1);
		Console::ForegroundColor = ConsoleColor::White;

		cout << "\n    ______           __                  _          \n" << endl;
		cout << "\n   / ____/_  _______/ /_____  ____ ___  (_)___  ___ \n" << endl;
		cout << "\n  / /   / / / / ___/ __/ __ \/ __ `__ \/ /_  / / _ \\\n" << endl;
		cout << "\n / /___/ /_/ (__  ) /_/ /_/ / / / / / / / / /_/  __/\n" << endl;
		cout << "\n\\____/\\__,_/____/\\__/\\____/_/ /_/ /_/_/ /___/\\___/ \n" << endl;

		cout << "\n               ===TEMAS PREDEFINIDOS==\n";
		cout << "\n                <1. frutiger aero >\n";
		cout << "\n                <2. cherry cocacola> \n";
		cout << "\n                <3. SUNNYYYYYYYYYYY> \n";
		cout << "\n        <4. nah, solo quiero cambiar el color del fondo>\n";
		cout << "\n             <5. =VOLVER AL MENU PRINCIPAL=\n";
		cout << "\n                       Opcion: "; cin >> opcolor;

		switch (opcolor)
		{
		case 1:
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo(1);
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			_getch();
			break;
		case 2: 
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo(2);
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			_getch();
			break;
		case 3: 
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo(3);
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			_getch();
			break;
		case 4: 
			system("cls");
			cambiarcolorfondo();
			break;
		case 5: 
			system("cls");
			cout << "Volviendo al menu principal..." << endl;
			cout << "[";

			for (int i = 0; i < 20; i++)
			{
				_sleep(80);
				cout << (char)219;
			}
			cout << "] 100%\n";
			_sleep(300);
		}
	}
}



int main()
{
	srand(time(NULL));
	int opcion;

	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::White;

	system("cls");
	preferenciatitulo(1);

	Console::ForegroundColor = ConsoleColor::White;
	

	do
	{
		Console::ForegroundColor = ConsoleColor::Gray;
		Console::BackgroundColor = ConsoleColor::Black;
		cout << "\n       =======MENU=====\n";
		cout << "\n1. QUIERO ESCRIBIR!!! >:D\n";
		cout << "\n2. Quiero ver mis entradas...\n";
		cout << "\n3. Customize... :O\n";
		cout << "\n4. Salir...-_-\n";
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
			menucustomizacion();
			break;
		case 4:
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
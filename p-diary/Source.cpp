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
int temaactual = 1;
int colorfondoactual = 0;
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
	ConsoleColor fondoanterior = Console::BackgroundColor;
	ConsoleColor textoanterior = Console::ForegroundColor;
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
	Console::BackgroundColor = fondoanterior;
	Console::ForegroundColor = textoanterior;

	pausa();
}


void agregarentrada()
{
	ConsoleColor fondoanterior = Console::BackgroundColor;
	ConsoleColor textoanterior = Console::ForegroundColor;


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

	Console::BackgroundColor = fondoanterior;
	Console::ForegroundColor = textoanterior;

	pausa();
}

void mostrarcitamotivacional()
{
	SetConsoleOutputCP(65001);
	int indice = rand() % totalcitas;
	cout << endl;
	cout << "\n╔════════════════════════════════════════════════════════════════════╗\n";
	cout << "║                               CITA DEL DÍA                           ║\n";
	cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
	cout << "║                                                                      ║\n";
	cout << "║         " << citas[indice][0] << "                          \n";                
	cout << "║                                                                      ║\n";
	cout << "║                      -  " << citas[indice][1] << "           \n";
	cout << "║                                                                      ║\n";
	cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
	SetConsoleOutputCP(437);

}

#define filas 7
#define columnas 44


int matriz1[filas][columnas] =
{
	{2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2},
	{1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2},
	{2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1},
	{1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2},
	{2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1},
	{1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2},
	{2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1},

};

int matriz2[filas][columnas] =
{
	{4,4,3,3,4,4,4,4,3,3,4,4,4,4,4,4,3,3,4,4,4,4,4,4,3,3,4,4,4,4,4,4,3,3,4,4,4,4,4,4,3,3,4,4},
	{3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4},
	{4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3},
	{3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4},
	{4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3},
	{3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4},
	{4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3,4,4,3,3},
};

int matriz3[filas][columnas] =
{
	{6,6,5,5,6,6,6,6,5,5,6,6,6,6,6,6,5,5,6,6,6,6,6,6,5,5,6,6,6,6,6,6,5,5,6,6,6,6,6,6,5,5,6,6},
	{5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6},
	{6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5},
	{5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6},
	{6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5},
	{5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6},
	{6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5},

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


void preferenciatitulo()
{
	ConsoleColor fondoactual = Console::BackgroundColor;

	int anchoconsola = 80;
	int anchotitulo = columnas;
	int espaciosizquierda = (anchoconsola - anchotitulo) / 2;

	switch (temaactual)
	{
	case 1: 
		for (int f = 0; f < filas; f++)
		{
			for (int e = 0; e < espaciosizquierda; e++)
			{
				cout << " ";
			}
			for (int c = 0; c < columnas; c++)
			{
				color(matriz1[f][c]);
				cout << (char)177;
			}
			cout << "\n";
		}
		break;
	case 2: 
		for (int f = 0; f < filas; f++)
		{
			for (int e = 0; e < espaciosizquierda; e++)
			{
				cout << " ";
			}
			for (int c = 0; c < columnas; c++)
			{
				color(matriz2[f][c]);
				cout << (char)177;
			}
			cout << "\n";
		}
		break;
	case 3: 
		for (int f = 0; f < filas; f++)
		{
			for (int e = 0; e < espaciosizquierda; e++)
			{
				cout << " ";
			}
			for (int c = 0; c < columnas; c++)
			{
				color(matriz3[f][c]);
				cout << (char)177;
			}
			cout << "\n";
		}
		break;
	default:
		temaactual = 1;
		for (int f = 0; f < filas; f++)
		{
			for (int e = 0; e < espaciosizquierda; e++)
			{
				cout << " ";
			}
			for (int c = 0; c < columnas; c++)
			{
				color(matriz1[f][c]);
				cout << (char)177;
			}
			cout << "\n";
		}
		break;
	}

	Console::BackgroundColor = fondoactual;
}




void cambiarcolorfondo()
{
	int opcfondo;
	ConsoleColor fondoanterior = Console::BackgroundColor;
	ConsoleColor textoanterior = Console::ForegroundColor;
	
	cout << "\n ======= COLOR DE FONDO  ======\n";

	Console::ForegroundColor = ConsoleColor::White;
	cout << "1. Negro \n";

	Console::ForegroundColor = ConsoleColor::Red;
	cout << "2. Rojo \n";

	Console::ForegroundColor = ConsoleColor::Green;
	cout << "3. Verde \n";

	Console::ForegroundColor = ConsoleColor::Yellow;
	cout << "4. Amarillo \n";

	Console::ForegroundColor = ConsoleColor::Cyan;
	cout << "5. Cyan \n";

	Console::ForegroundColor = ConsoleColor::Blue;
	cout << "6. Azul \n";

	Console::ForegroundColor = ConsoleColor::Magenta;
	cout << "7. Morado \n";

	Console::ForegroundColor = ConsoleColor::White;
	cout << "8.Blanco \n";

	cout << "\n Opcion: "; cin >> opcfondo;

	colorfondoactual = opcfondo - 1;


	switch (opcfondo)
	{
	case 1:
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a negro :D" << endl;
		break;
	case 2:
		Console::BackgroundColor = ConsoleColor::Red;
		Console::ForegroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a rojo :D" << endl;
		break;
	case 3:
		Console::BackgroundColor = ConsoleColor::Yellow;
		Console::ForegroundColor = ConsoleColor::DarkGray;
		system("cls");
		cout << "Fondo cambiado a verde :D" << endl;
		break;
	case 4:
		Console::BackgroundColor = ConsoleColor::Green;
		Console::ForegroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a amarillo :D" << endl;
		break;
	case 5:
		Console::BackgroundColor = ConsoleColor::Cyan;
		Console::BackgroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a cyan :D" << endl;
		break;
	case 6:
		Console::BackgroundColor = ConsoleColor::Blue;
		Console::BackgroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a azul :D" << endl;
		break;
	case 7:
		Console::BackgroundColor = ConsoleColor::Magenta;
		Console::BackgroundColor = ConsoleColor::White;
		system("cls");
		cout << "Fondo cambiado a morado :D" << endl;
		break;
	case 8:
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::DarkGray;
		system("cls");
		cout << "Fondo cambiado a blanco :D" << endl;
		break;
	case 9:
		Console::BackgroundColor = fondoanterior;
		Console::ForegroundColor = textoanterior;
		return;
	default:
		cout << "Opcion invalida >:(";
	
	}

	cout << "Presiona una tecla para continuar..." << endl;
	_getch();

	Console::ForegroundColor = ConsoleColor::White;
}

void pantallacargando()
{
	system("cls");

	if (colorfondoactual == 3 || colorfondoactual == 7)
	{
		Console::ForegroundColor = ConsoleColor::Black;
	}
	else
	{
		Console::ForegroundColor = ConsoleColor::White;
	}
	cout << "Volviendo al menu principal..." << endl;
	cout << "[";

	for (int i = 0; i < 20; i++)
	{
		_sleep(80);
		cout << (char)177;
	}
	cout << "] 100%\n";
	_sleep(300);
	system("cls");
}

void aplicarcoloresguardados()
{
	ConsoleColor coloresfondo[] =
	{
		ConsoleColor::Black,
		ConsoleColor::Red,
		ConsoleColor::Green,
		ConsoleColor::Yellow,
		ConsoleColor::Cyan,
		ConsoleColor::Blue,
		ConsoleColor::Magenta,
		ConsoleColor::White
	};

	if (colorfondoactual >= 0 && colorfondoactual <= 7)
	{
		Console::BackgroundColor = coloresfondo[colorfondoactual];
	}
	else
	{
		Console::BackgroundColor = ConsoleColor::Black;
	}
	Console::ForegroundColor = ConsoleColor::White;

	if (colorfondoactual == 3 || colorfondoactual == 7)
	{
		Console::ForegroundColor = ConsoleColor::DarkGray;
	}
	else
	{
		Console::ForegroundColor = ConsoleColor::White;
	}
}

void menucustomizacion()
{
	int opcolor;

	do
	{
		system("cls");

		aplicarcoloresguardados();
		preferenciatitulo();
		
		if (colorfondoactual == 3 || colorfondoactual == 7)
		{
			Console::ForegroundColor = ConsoleColor::Black;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::White;
		}

		cout << "                                                                " << endl;
		cout << "                ______           __                  _          " << endl;
		cout << "               / ____/_  _______/ /_____  ____ ___  (_)___  ___ " << endl;
		cout << "              / /   / / / / ___/ __/ __ \/ __ `__ \/ /_  / / _ \\" << endl;
		cout << "             / /___/ /_/ (__  ) /_/ /_/ / / / / / / / / /_/  __/" << endl;
		cout << "             \\____/\\__,_/____/\\__/\\____/_/ /_/ /_/_/ /___/\\___/ " << endl;

		cout << "\n                          ==TEMAS PREDEFINIDOS==\n";
		cout << "\n                           <1. frutiger aero >\n";
		cout << "\n                           <2. cherry cocacola> \n";
		cout << "\n                           <3. SUNNYYYYYYYYYYY> \n";
		cout << "\n               <4. nah, solo quiero cambiar el color del fondo>\n";
		cout << "\n                         <5. =VOLVER AL MENU PRINCIPAL=\n";
		cout << "\n                                   Opcion: "; cin >> opcolor;

		switch (opcolor)
		{
		case 1:
			temaactual = 1;
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo();
			if (colorfondoactual == 3 || colorfondoactual == 7)
			{
				Console::ForegroundColor = ConsoleColor::DarkGray;
			}
			else
			{
				Console::ForegroundColor = ConsoleColor::White;
			}
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			
			break;
		case 2: 
			temaactual = 2;
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo();
			if (colorfondoactual == 3 || colorfondoactual == 7)
			{
				Console::ForegroundColor = ConsoleColor::DarkGray;
			}
			else
			{
				Console::ForegroundColor = ConsoleColor::White;
			}
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			
			break;
		case 3:
			temaactual = 3;
			system("cls");
			Console::ForegroundColor = ConsoleColor::White;
			preferenciatitulo();
			if (colorfondoactual == 3 || colorfondoactual == 7)
			{
				Console::ForegroundColor = ConsoleColor::DarkGray;
			}
			else
			{
				Console::ForegroundColor = ConsoleColor::White;
			}
			cout << "\n Cambiado con exito \n";
			cout << "\n Presiona cualquier tecla para continuar...";
			
			break;
		case 4: 
			system("cls");
			cambiarcolorfondo();
			break;
		case 5:
			pantallacargando();
			break;
		default: 
			cout << "Pon algo valido >:(\n";
			_getch();
			
		}
	} while (opcolor != 5);

}

void restaurarcoloresmenu()
{
	aplicarcoloresguardados();

	if (colorfondoactual == 3 || colorfondoactual == 7)
	{
		Console::ForegroundColor = ConsoleColor::DarkGray;
	}
	else
	{
		Console::ForegroundColor = ConsoleColor::Gray;
	}
}


void titulobuscar()
{

	Console::ForegroundColor = ConsoleColor::DarkBlue;
	cout << " ______                                              ___                    " << endl;
	cout << "|_   _ \\                                           .:---:.         _         " << endl;
	cout << "  | |_) | __   _   .--.   .---.  ,--.   _ .--.    // #   \\_...--'' \\       " << endl;
	cout << "  |  __'.[  | | | ( (`\\] / /'`\]`'_\\ : [ `/'`\\]   || #     |_         |       " << endl;
	cout << " _| |__) || \\_/ |, `'.'. | \\__. // | |, | |       \\     // ```--.._/              " << endl;
	cout << "|_______/ '.__.'_/[\\__) )'.___.'\\'-;__/[___]       ':===:'             " << endl;
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ```            " << endl;

	Console::ForegroundColor = ConsoleColor::Red;
}

void buscarporpalabra()
{
	char palabra[50];
	int encontradas = 0;

	system("cls");
	titulobuscar();

	cout << "Ingresa una PALABRA: "; cin >> palabra;

	Console::ForegroundColor = ConsoleColor::White;
	for (int i = 0; i < totalentradas; i++)
	{
		if (strstr(diario[i].titulo, palabra) != nullptr || strstr(diario[i].contenido, palabra) != nullptr)
		{
			mostrarentrada(diario[i]);
			encontradas++;
		}
	}

	if (encontradas == 0)
	{
		cout << "No se encontraron entradas con " << palabra << endl;
	}
	else
	{
		cout << "Encontradas: " << encontradas << " entradas." << endl;
	}
	pausa();
}

string normalizarfecha(string fecha) //hecho con ia
{
	int pos1 = fecha.find('/');
	int pos2 = fecha.find('/', pos1 + 1);

	if (pos1 == string::npos || pos2 == string::npos)
	{
		return fecha;
	}

	string dia = fecha.substr(0, pos1);
	string mes = fecha.substr(pos1 + 1, pos2 - pos1 - 1);
	string anio = fecha.substr(pos2 + 1);

	if (dia.length() == 1)
	{
		dia = "0" + dia;
	}
	if (mes.length() == 1)
	{
		mes = "0" + mes;
	}
	return dia + "/" + mes + "/" + anio;
}


void buscarporfecha()
{

	string fechainput;
	int encontradas = 0;

	system("cls");
	titulobuscar();

	cout << "Ingresa una FECHA (DD/MM/AAAA)"; cin >> fechainput;
	string fechanormalizada = normalizarfecha(fechainput);

	for (int i = 0; i < totalentradas; i++)
	{
		string fechaentrada = diario[i].fecha;
		if (fechaentrada.find(fechanormalizada) != string::npos)
		{
			mostrarentrada(diario[i]);
			encontradas++;
		}
	}

	if (encontradas == 0)
	{
		cout << "No hay entradas del " << fechanormalizada << endl;
	}
	else
	{
		cout << "Encontradas: " << encontradas << " entradas" << endl;
	}

	pausa();
}





int main()
{
	srand(time(NULL));
	int opcion;
	Console::SetWindowSize(40, 40);
	Console::CursorVisible = false;
	colorfondoactual = 0;
	aplicarcoloresguardados();
	if (colorfondoactual == 3 || colorfondoactual == 7)
	{
		Console::ForegroundColor = ConsoleColor::DarkGray;
	}
	else
	{
		Console::ForegroundColor = ConsoleColor::White;
	}
	do
	{
		system("cls");
		preferenciatitulo();
		aplicarcoloresguardados();
		Console::ForegroundColor = ConsoleColor::DarkGray;

		SetConsoleOutputCP(65001);
		cout << endl;
		cout << "                     ═══════════════════════════════════════════" << endl;
		cout << "\n                  |            =======MENU=====               |\n";      
		cout << "\n                  |        1. QUIERO ESCRIBIR!!! >:D          |\n";
		cout << "\n                  |      2. Quiero ver mis entradas...        |\n";
		cout << "\n                  |          3. Customize... :O               |\n";
		cout << "\n                  |        4. Buscar por PALABRA              |\n";
		cout << "\n                  |         5. buscar por FECHA               |\n";
		cout << "\n                  |             6. Salir...-_-                |\n";
		cout << "\n                   ═══════════════════════════════════════════ \n";
		cout << "\n                                    Opcion:                   \n"; cin >> opcion;
		cout << endl;
		
		if (colorfondoactual == 3 || colorfondoactual == 7)
		{
			Console::ForegroundColor = ConsoleColor::DarkGray;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::White;
		}

		
		SetConsoleOutputCP(437);

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
			buscarporpalabra();
			break;
		case 5:
			buscarporfecha();
			break;
		case 6:
			system("cls");
			cout << "Hasta pronto! :D Recuerda...";
			mostrarcitamotivacional();
			cout << "Sigue escribiendo!!!! >:D";
			_getch();
			break;
		default:
			cout << "Pon algo valido >:(";
		}



	} while (opcion !=6);

	delete[]diario;
	return 0;
}
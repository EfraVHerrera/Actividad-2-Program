#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// Estructuras
struct SLibro {
	string sTitulo;
	string sAutor;
	string sISBN;
	int nAnoPublicacion;
	string sIdioma;
	int nEdicion;
	int nNumPaginas;
};

struct SUsuario {
	int nUserID;
	string sNombre;
	string sApellido;
	string sEmail;
	string sFechaRegistro;
};

struct SBibliotecario {
	int nEmployeeID;
	string sNombre;
	string sApellido;
	string sEmail;
	string sCargo;
};

const int NUM_LIBROS = 3;
const int NUM_USUARIOS = 3;
const int NUM_BIBLIOTECARIOS = 3;

// Funciones para generar datos aleatorios
string obtenerElementoAleatorio(string arr[], int size) {
	return arr[rand() % size];
}

int obtenerAnoAleatorio() {
	return rand() % 50 + 1970; // Años aleatorios entre 1970 y 2019
}

string generarEmail(string nombre, string apellido) {
	return nombre + "." + apellido + "@upds.net.bo";
}

string generarFechaRegistro(string listaFechasRegistro[], int size) {
	return listaFechasRegistro[rand() % size]; // Se elige una fecha de registro aleatoria del array
}

// Funciones para llenar las estructuras con datos aleatorios
void llenarDatos(SLibro libros[], string listaTitulos[], string listaNombres[], string listaApellidos[], string listaIdiomas[]) {
	for (int i = 0; i < NUM_LIBROS; ++i) {
		libros[i].sTitulo = obtenerElementoAleatorio(listaTitulos, NUM_LIBROS);
		libros[i].sAutor = obtenerElementoAleatorio(listaNombres, 5) + " " + obtenerElementoAleatorio(listaApellidos, 5);
		libros[i].sISBN = ""; // Se inicializa vacío
		libros[i].nAnoPublicacion = obtenerAnoAleatorio();
		libros[i].sIdioma = obtenerElementoAleatorio(listaIdiomas, 8); // Se elige un idioma aleatorio
		libros[i].nEdicion = rand() % 10 + 1; // Número de edición aleatorio entre 1 y 10
		libros[i].nNumPaginas = rand() % 500 + 100; // Número de páginas aleatorio entre 100 y 599
	}
}

void llenarDatos(SUsuario usuarios[], string listaNombres[], string listaApellidos[], string listaFechasRegistro[], int size) {
	for (int i = 0; i < NUM_USUARIOS; ++i) {
		usuarios[i].nUserID = i + 1;
		usuarios[i].sNombre = obtenerElementoAleatorio(listaNombres, 5);
		usuarios[i].sApellido = obtenerElementoAleatorio(listaApellidos, 5);
		usuarios[i].sEmail = generarEmail(usuarios[i].sNombre, usuarios[i].sApellido);
		usuarios[i].sFechaRegistro = generarFechaRegistro(listaFechasRegistro, size); //HOY
	}
}

void llenarDatos(SBibliotecario bibliotecarios[], string listaNombres[], string listaApellidos[], string listaCargos[], int size) {
	for (int i = 0; i < NUM_BIBLIOTECARIOS; ++i) {
		bibliotecarios[i].nEmployeeID = i + 1;
		bibliotecarios[i].sNombre = obtenerElementoAleatorio(listaNombres, 5);
		bibliotecarios[i].sApellido = obtenerElementoAleatorio(listaApellidos, 5);
		bibliotecarios[i].sEmail = generarEmail(bibliotecarios[i].sNombre, bibliotecarios[i].sApellido);
		bibliotecarios[i].sCargo = obtenerElementoAleatorio(listaCargos, size); //HOY
	}
}

// Función para imprimir una fila de la tabla
void imprimirFila(const string& columna1, const string& columna2, const string& columna3 = "", const string& columna4 = "", const string& columna5 = "") {
	const int columna1Width = 20;
	const int columna2Width = 20;
	const int columna3Width = 20;
	const int columna4Width = 20;
	const int columna5Width = 20;
	
	cout << left << setw(columna1Width) << columna1.substr(0, columna1Width - 1);
	cout << left << setw(columna2Width) << columna2.substr(0, columna2Width - 1);
	if (!columna3.empty())
		cout << left << setw(columna3Width) << columna3.substr(0, columna3Width - 1);
	if (!columna4.empty())
		cout << left << setw(columna4Width) << columna4.substr(0, columna4Width - 1);
	if (!columna5.empty())
		cout << left << setw(columna5Width) << columna5.substr(0, columna5Width - 1);
	cout << endl;
}

// Funciones para imprimir los datos de las estructuras en forma de tabla
void imprimirDatos(SLibro *libros, int cant) {
	cout << "\n--- Listado de libros ---\n";
	imprimirFila("Título", "Autor", "ISBN", "Año de Publicación", "Idioma");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(libros[i].sTitulo, libros[i].sAutor, libros[i].sISBN, to_string(libros[i].nAnoPublicacion), libros[i].sIdioma);
	}
}

void imprimirDatos(SUsuario *usuarios, int cant) {
	cout << "\n--- Listado de usuarios ---\n";
	imprimirFila("ID", "Nombre", "Apellido", "Email", "Fecha de Registro");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(to_string(usuarios[i].nUserID), usuarios[i].sNombre, usuarios[i].sApellido, usuarios[i].sEmail, usuarios[i].sFechaRegistro);
	}
}

void imprimirDatos(SBibliotecario *bibliotecarios, int cant) {
	cout << "\n--- Listado de bibliotecarios ---\n";
	imprimirFila("ID", "Nombre", "Apellido", "Email", "Cargo");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(to_string(bibliotecarios[i].nEmployeeID), bibliotecarios[i].sNombre, bibliotecarios[i].sApellido, bibliotecarios[i].sEmail, bibliotecarios[i].sCargo);
	}
}

// Submenú para el listado
void submenuListado(SLibro libros[], SUsuario usuarios[], SBibliotecario bibliotecarios[]) {
	char opcion;
	do {
		cout << "\n--- Submenú Listado ---\n";
		cout << "A) Listado de libros\n";
		cout << "B) Listado de usuarios\n";
		cout << "C) Listado de bibliotecarios\n";
		cout << "D) Salir\n";
		cout << "Seleccione una opción: ";
		cin >> opcion;
		
		switch (opcion) {
		case 'A':
			imprimirDatos(libros, NUM_LIBROS);
			break;
		case 'B':
			imprimirDatos(usuarios, NUM_USUARIOS);
			break;
		case 'C':
			imprimirDatos(bibliotecarios, NUM_BIBLIOTECARIOS);
			break;
		case 'D':
			cout << "Saliendo del submenú de listado...\n";
			break;
		default:
			cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
		}
	} while (opcion != 'D');
}

// Función para buscar un libro por título
bool buscarLibro(SLibro* libros, int cant, const string& titulo, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string tituloLibro = libros[i].sTitulo;
		transform(tituloLibro.begin(), tituloLibro.end(), tituloLibro.begin(), ::tolower); // Convertir a minúsculas
		size_t found = tituloLibro.find(titulo); // Buscar la primera palabra del título
		if (found != string::npos && (found == 0 || tituloLibro[found - 1] == ' ')) {
			cout << "Título: " << libros[i].sTitulo << endl;
			cout << "Autor: " << libros[i].sAutor << endl;
			cout << "ISBN: " << libros[i].sISBN << endl;
			cout << "Año de Publicación: " << libros[i].nAnoPublicacion << endl;
			cout << "Idioma: " << libros[i].sIdioma << endl;
			cout << "Edición: " << libros[i].nEdicion << endl;
			cout << "Número de Páginas: " << libros[i].nNumPaginas << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}


// Función para buscar un usuario por nombre
bool buscarUsuario(SUsuario* usuarios, int cant, const string& nombre, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string nombreUsuario = usuarios[i].sNombre;
		transform(nombreUsuario.begin(), nombreUsuario.end(), nombreUsuario.begin(), ::tolower); // Convertir a minúsculas
		size_t found = nombreUsuario.find(nombre); // Buscar coincidencias en el nombre del usuario
		if (found != string::npos) {
			cout << "ID: " << usuarios[i].nUserID << endl;
			cout << "Nombre: " << usuarios[i].sNombre << endl;
			cout << "Apellido: " << usuarios[i].sApellido << endl;
			cout << "Email: " << usuarios[i].sEmail << endl;
			cout << "Fecha de Registro: " << usuarios[i].sFechaRegistro << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}

// Función para buscar un bibliotecario por nombre
bool buscarBibliotecario(SBibliotecario* bibliotecarios, int cant, const string& nombre, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string nombreBibliotecario = bibliotecarios[i].sNombre;
		transform(nombreBibliotecario.begin(), nombreBibliotecario.end(), nombreBibliotecario.begin(), ::tolower); // Convertir a minúsculas
		size_t found = nombreBibliotecario.find(nombre); // Buscar coincidencias en el nombre del bibliotecario
		if (found != string::npos) {
			cout << "ID: " << bibliotecarios[i].nEmployeeID << endl;
			cout << "Nombre: " << bibliotecarios[i].sNombre << endl;
			cout << "Apellido: " << bibliotecarios[i].sApellido << endl;
			cout << "Email: " << bibliotecarios[i].sEmail << endl;
			cout << "Cargo: " << bibliotecarios[i].sCargo << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}

//SUBMENU BUSQUEDA
void submenuBusqueda(SLibro libros[], SUsuario usuarios[], SBibliotecario bibliotecarios[]) {
	char opcion;
	do {
		cout << "\n--- Submenú Búsqueda ---\n";
		cout << "A) Búsqueda de libro\n";
		cout << "B) Búsqueda de usuario\n";
		cout << "C) Búsqueda de bibliotecario\n";
		cout << "D) Salir\n";
		cout << "Seleccione una opción: ";
		cin >> opcion;
		
		switch (opcion) {
		case 'A': {
			string titulo;
			cout << "Ingrese el título del libro: ";
			cin.ignore();
			getline(cin, titulo);
			transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);// Convertir a minúsculas
			// Lógica para buscar libro por título
			if (!buscarLibro(libros, NUM_LIBROS, titulo)) {
				cout << "No se encontraron libros con esa primera palabra en el título.\n";
			}
			break;
		}
		case 'B': {
			string nombre;
			cout << "Ingrese el nombre del usuario: ";
			cin >> nombre;
			transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower); // Convertir a minúsculas
			// Lógica para buscar usuario por nombre
			if (!buscarUsuario(usuarios, NUM_USUARIOS, nombre)) {
				cout << "No se encontró ningún usuario con ese nombre.\n";
			}
			break;
		}
		case 'C': {
			string nombre;
			cout << "Ingrese el nombre del bibliotecario: ";
			cin >> nombre;
			transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower); // Convertir a minúsculas
			// Lógica para buscar bibliotecario por nombre
			if (!buscarBibliotecario(bibliotecarios, NUM_BIBLIOTECARIOS, nombre)) {
				cout << "No se encontró ningún bibliotecario con ese nombre.\n";
			}
			break;
		}
		case 'D':
			cout << "Saliendo del submenú de búsqueda...\n";
			break;
		default:
			cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
		}
	} while (opcion != 'D');
}

int main() {
	// Semilla para números aleatorios
	srand(time(0));
	
	// Arrays fijos de datos
	string listaLibros[] = {"Aprende C", "Effective C++", "Programación en C++", "Curso de programación", "Modern C++", "Clean Code", "The Art of Computer Programming", "Programming Pearls", "Introduction to Algorithms"};
	string listaNombres[] = {"Juan", "Maria", "Pedro", "Ana", "Luis", "Efrain", "Jose", "Carlos", "Cristian"};
	string listaApellidos[] = {"Garcia", "Martinez", "Lopez", "Gonzalez", "Rodriguez", "Edmundo", "Flores", "Ponce", "Herrera"};
	string listaIdiomas[] = {"Español", "Inglés", "Francés", "Alemán", "Italiano", "Portugués", "Japonés", "Chino"};
	string listaFechasRegistro[] = {"01/01/2020", "15/03/2021", "30/06/2022", "26/06/2019"};
	string listaCargos[] = {"Bibliotecario jefe", "Bibliotecario Asistente", "Bibliotecario Junior", "Bibliotecario de tecnología de la información", "Bibliotecario de archivos y preservación"};
	
	// Generar estructuras
	SLibro libros[NUM_LIBROS];
	SUsuario usuarios[NUM_USUARIOS];
	SBibliotecario bibliotecarios[NUM_BIBLIOTECARIOS];
	
	// Menú principal
	char opcion;
	bool datosCargados = false; // Bandera para indicar si se han cargado los datos
	do {
		cout << "\n--- Menú Principal ---\n";
		cout << "1. Llenado de datos\n";
		cout << "2. Listado\n";
		cout << "3. Búsqueda\n";
		cout << "4. Salir\n";
		cout << "Seleccione una opción: ";
		cin >> opcion;
		
		switch (opcion) {
		case '1':
			// Generar datos de libros, usuarios y bibliotecarios
			llenarDatos(libros, listaLibros, listaNombres, listaApellidos, listaIdiomas);
			llenarDatos(usuarios, listaNombres, listaApellidos, listaFechasRegistro, sizeof(listaFechasRegistro) / sizeof(listaFechasRegistro[0]));
			llenarDatos(bibliotecarios, listaNombres, listaApellidos, listaCargos, sizeof(listaCargos) / sizeof(listaCargos[0]));
			cout << "Datos generados exitosamente.\n";
			datosCargados = true; // Se establece la bandera de datos cargados como verdadera
			break;
			
		case '2':
			if (datosCargados) // Solo se puede acceder al listado si los datos están cargados
				submenuListado(libros, usuarios, bibliotecarios);
			else
				cout << "Error: Debe cargar los datos primero (opción 1).\n";
			break;
			
		case '3':
			if (datosCargados) // Solo se puede acceder a la búsqueda si los datos están cargados
				submenuBusqueda(libros, usuarios, bibliotecarios);
			else
				cout << "Error: Debe cargar los datos primero (opción 1).\n";
			break;
			
		case '4':
			cout << "Saliendo del programa...\n";
			break;
			
		default:
			cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
		}
	} while (opcion != '4');
	
	return 0;
}

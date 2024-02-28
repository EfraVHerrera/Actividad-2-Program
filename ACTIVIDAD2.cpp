#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// Estructuras
struct Libro {
	string titulo;
	string autor;
	string ISBN;
	int anoPublicacion;
	string idioma;
	int edicion;
	int numPaginas;
};

struct Usuario {
	int userID;
	string nombre;
	string apellido;
	string email;
	string fechaRegistro;
};

struct Bibliotecario {
	int employeeID;
	string nombre;
	string apellido;
	string email;
	string cargo;
};

const int NUM_LIBROS = 3;
const int NUM_USUARIOS = 3;
const int NUM_BIBLIOTECARIOS = 3;

bool datosCargados = false; // Variable para verificar si los datos ya se han cargado

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
void llenarDatos(Libro libros[], string listaTitulos[], string listaNombres[], string listaApellidos[], string listaIdiomas[], bool generarISBN) {
	for (int i = 0; i < NUM_LIBROS; ++i) {
		libros[i].titulo = obtenerElementoAleatorio(listaTitulos, NUM_LIBROS);
		libros[i].autor = obtenerElementoAleatorio(listaNombres, 5) + " " + obtenerElementoAleatorio(listaApellidos, 5);
		if (generarISBN) // Solo generar ISBN si la opción está habilitada
			libros[i].ISBN = to_string(i + 1) + ",2,3,4,5"; // ISBN falso
		libros[i].anoPublicacion = obtenerAnoAleatorio();
		libros[i].idioma = obtenerElementoAleatorio(listaIdiomas, 8); // Se elige un idioma aleatorio
		libros[i].edicion = rand() % 10 + 1; // Número de edición aleatorio entre 1 y 10
		libros[i].numPaginas = rand() % 500 + 100; // Número de páginas aleatorio entre 100 y 599
	}
}

void llenarDatos(Usuario usuarios[], string listaNombres[], string listaApellidos[], string listaFechasRegistro[], int size) {
	for (int i = 0; i < NUM_USUARIOS; ++i) {
		usuarios[i].userID = i + 1;
		usuarios[i].nombre = obtenerElementoAleatorio(listaNombres, 5);
		usuarios[i].apellido = obtenerElementoAleatorio(listaApellidos, 5);
		usuarios[i].email = generarEmail(usuarios[i].nombre, usuarios[i].apellido);
		usuarios[i].fechaRegistro = generarFechaRegistro(listaFechasRegistro, size); //HOY
	}
}

void llenarDatos(Bibliotecario bibliotecarios[], string listaNombres[], string listaApellidos[], string listaCargos[], int size) {
	for (int i = 0; i < NUM_BIBLIOTECARIOS; ++i) {
		bibliotecarios[i].employeeID = i + 1;
		bibliotecarios[i].nombre = obtenerElementoAleatorio(listaNombres, 5);
		bibliotecarios[i].apellido = obtenerElementoAleatorio(listaApellidos, 5);
		bibliotecarios[i].email = generarEmail(bibliotecarios[i].nombre, bibliotecarios[i].apellido);
		bibliotecarios[i].cargo = obtenerElementoAleatorio(listaCargos, size); //HOY
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
void imprimirDatos(Libro *libros, int cant) {
	cout << "\n--- Listado de libros ---\n";
	imprimirFila("Título", "Autor", "ISBN", "Año de Publicación", "Idioma");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(libros[i].titulo, libros[i].autor, libros[i].ISBN, to_string(libros[i].anoPublicacion), libros[i].idioma);
	}
}

void imprimirDatos(Usuario *usuarios, int cant) {
	cout << "\n--- Listado de usuarios ---\n";
	imprimirFila("ID", "Nombre", "Apellido", "Email", "Fecha de Registro");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(to_string(usuarios[i].userID), usuarios[i].nombre, usuarios[i].apellido, usuarios[i].email, usuarios[i].fechaRegistro);
	}
}

void imprimirDatos(Bibliotecario *bibliotecarios, int cant) {
	cout << "\n--- Listado de bibliotecarios ---\n";
	imprimirFila("ID", "Nombre", "Apellido", "Email", "Cargo");
	for (int i = 0; i < cant; ++i) {
		imprimirFila(to_string(bibliotecarios[i].employeeID), bibliotecarios[i].nombre, bibliotecarios[i].apellido, bibliotecarios[i].email, bibliotecarios[i].cargo);
	}
}

// Submenú para el listado
void submenuListado(Libro libros[], Usuario usuarios[], Bibliotecario bibliotecarios[]) {
	if (!datosCargados) { // Verificar si los datos ya se han cargado
		cout << "Primero debe cargar los datos.\n";
		return;
	}
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
bool buscarLibro(Libro* libros, int cant, const string& titulo, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string tituloLibro = libros[i].titulo;
		transform(tituloLibro.begin(), tituloLibro.end(), tituloLibro.begin(), ::tolower); // Convertir a minúsculas
		size_t found = tituloLibro.find(titulo); // Buscar la primera palabra del título
		if (found != string::npos && (found == 0 || tituloLibro[found - 1] == ' ')) {
			cout << "Título: " << libros[i].titulo << endl;
			cout << "Autor: " << libros[i].autor << endl;
			cout << "ISBN: " << libros[i].ISBN << endl;
			cout << "Año de Publicación: " << libros[i].anoPublicacion << endl;
			cout << "Idioma: " << libros[i].idioma << endl;
			cout << "Edición: " << libros[i].edicion << endl;
			cout << "Número de Páginas: " << libros[i].numPaginas << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}


// Función para buscar un usuario por nombre
bool buscarUsuario(Usuario* usuarios, int cant, const string& nombre, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string nombreUsuario = usuarios[i].nombre;
		transform(nombreUsuario.begin(), nombreUsuario.end(), nombreUsuario.begin(), ::tolower); // Convertir a minúsculas
		size_t found = nombreUsuario.find(nombre); // Buscar coincidencias en el nombre del usuario
		if (found != string::npos) {
			cout << "ID: " << usuarios[i].userID << endl;
			cout << "Nombre: " << usuarios[i].nombre << endl;
			cout << "Apellido: " << usuarios[i].apellido << endl;
			cout << "Email: " << usuarios[i].email << endl;
			cout << "Fecha de Registro: " << usuarios[i].fechaRegistro << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}

// Función para buscar un bibliotecario por nombre
bool buscarBibliotecario(Bibliotecario* bibliotecarios, int cant, const string& nombre, int index = 0) {
	bool encontrado = false;
	for (int i = 0; i < cant; ++i) {
		string nombreBibliotecario = bibliotecarios[i].nombre;
		transform(nombreBibliotecario.begin(), nombreBibliotecario.end(), nombreBibliotecario.begin(), ::tolower); // Convertir a minúsculas
		size_t found = nombreBibliotecario.find(nombre); // Buscar coincidencias en el nombre del bibliotecario
		if (found != string::npos) {
			cout << "ID: " << bibliotecarios[i].employeeID << endl;
			cout << "Nombre: " << bibliotecarios[i].nombre << endl;
			cout << "Apellido: " << bibliotecarios[i].apellido << endl;
			cout << "Email: " << bibliotecarios[i].email << endl;
			cout << "Cargo: " << bibliotecarios[i].cargo << endl << endl;
			encontrado = true;
		}
	}
	return encontrado;
}

//SUBMENU BUSQUEDA
void submenuBusqueda(Libro libros[], Usuario usuarios[], Bibliotecario bibliotecarios[]) {
	if (!datosCargados) { // Verificar si los datos ya se han cargado
		cout << "Primero debe cargar los datos.\n";
		return;
	}
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
	Libro libros[NUM_LIBROS];
	Usuario usuarios[NUM_USUARIOS];
	Bibliotecario bibliotecarios[NUM_BIBLIOTECARIOS];
	
	
	// Menú principal
	char opcion;
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
			llenarDatos(libros, listaLibros, listaNombres, listaApellidos, listaIdiomas, true); // La opción true indica que se generará el ISBN
			llenarDatos(usuarios, listaNombres, listaApellidos, listaFechasRegistro, sizeof(listaFechasRegistro) / sizeof(listaFechasRegistro[0]));
			llenarDatos(bibliotecarios, listaNombres, listaApellidos, listaCargos, sizeof(listaCargos) / sizeof(listaCargos[0]));
			datosCargados = true; // Establecer que los datos se han cargado
			cout << "Datos generados exitosamente.\n";
			break;
		case '2':
			submenuListado(libros, usuarios, bibliotecarios);
			break;
		case '3':
			submenuBusqueda(libros, usuarios, bibliotecarios);
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

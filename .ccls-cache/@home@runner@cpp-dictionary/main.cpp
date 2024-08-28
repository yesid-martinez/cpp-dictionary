#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Palabra {
  string texto;
  string descripciones[3];
};

void mostrarMenu();
void agregarPalabra(vector<Palabra> &diccionario);
void mostrarDiccionario(const vector<Palabra> &diccionario);
void modificarDescripcion(vector<Palabra> &diccionario);
void eliminarPalabra(vector<Palabra> &diccionario);
int obtenerOpcion();

int main() {
  vector<Palabra> diccionario;
  int opcion;

  do {
    mostrarMenu();
    opcion = obtenerOpcion();

    switch (opcion) {
    case 1:
      agregarPalabra(diccionario);
      break;
    case 2:
      mostrarDiccionario(diccionario);
      break;
    case 3:
      modificarDescripcion(diccionario);
      break;
    case 4:
      eliminarPalabra(diccionario);
      break;
    case 5:
      cout << "Saliendo del programa." << endl;
      break;
    default:
      cout << "Opción no válida. Intenta de nuevo." << endl;
    }
  } while (opcion != 5);

  return 0;
}

void mostrarMenu() {
  cout << "\n--- Menú del Diccionario ---" << endl;
  cout << "1. Agregar Palabra" << endl;
  cout << "2. Mostrar Diccionario" << endl;
  cout << "3. Modificar Descripción" << endl;
  cout << "4. Eliminar Palabra" << endl;
  cout << "5. Salir" << endl;
  cout << "Selecciona una opción: ";
}

void agregarPalabra(vector<Palabra> &diccionario) {
  Palabra nuevaPalabra;
  cout << "Introduce la palabra: ";
  cin >> nuevaPalabra.texto;
  cin.ignore(); // Limpiar el buffer después de leer la palabra

  for (int i = 0; i < 3; ++i) {
    cout << "Introduce la descripción " << (i + 1) << ": ";
    getline(cin, nuevaPalabra.descripciones[i]); // Usar getline sin problemas
  }

  diccionario.push_back(nuevaPalabra);
  cout << "Palabra agregada exitosamente." << endl;
}

void mostrarDiccionario(const vector<Palabra> &diccionario) {
  if (diccionario.empty()) {
    cout << "El diccionario está vacío." << endl;
    return;
  }

  vector<Palabra> diccionarioOrdenado = diccionario;

  sort(diccionarioOrdenado.begin(), diccionarioOrdenado.end(),
       [](Palabra a, Palabra b) {
         transform(a.texto.begin(), a.texto.end(), a.texto.begin(), ::tolower);
         transform(b.texto.begin(), b.texto.end(), b.texto.begin(), ::tolower);
         return a.texto < b.texto; // Cambiar '>' por '<' para orden ascendente
       });

  for (const auto &palabra : diccionarioOrdenado) {
    cout << "Palabra: " << palabra.texto << endl;
    for (int i = 0; i < 3; ++i) {
      cout << "Descripción " << (i + 1) << ": " << palabra.descripciones[i]
           << endl;
    }
    cout << "-------------------" << endl;
  }
}

void modificarDescripcion(vector<Palabra> &diccionario) {
  string palabraBuscada;
  cout << "Introduce la palabra que deseas modificar: ";
  cin >> palabraBuscada;

  for (auto &palabra : diccionario) {
    if (palabra.texto == palabraBuscada) {
      int numDescripcion;
      cout << "¿Qué descripción deseas modificar? (1-3): ";
      cin >> numDescripcion;

      // Validación de entrada
      while (cin.fail() || numDescripcion < 1 || numDescripcion > 3) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Ignorar entrada incorrecta
        cout << "Número de descripción no válido. Intenta de nuevo (1-3): ";
        cin >> numDescripcion;
      }

      cout << "Introduce la nueva descripción: ";
      cin.ignore(); // Limpiar el buffer
      getline(cin, palabra.descripciones[numDescripcion - 1]);
      cout << "Descripción modificada exitosamente." << endl;
      return;
    }
  }
  cout << "Palabra no encontrada en el diccionario." << endl;
}

void eliminarPalabra(vector<Palabra> &diccionario) {
  string palabraBuscada;
  cout << "Introduce la palabra que deseas eliminar: ";
  cin >> palabraBuscada;

  for (auto it = diccionario.begin(); it != diccionario.end(); ++it) {
    if (it->texto == palabraBuscada) {
      diccionario.erase(it);
      cout << "Palabra eliminada exitosamente." << endl;
      return;
    }
  }
  cout << "Palabra no encontrada en el diccionario." << endl;
}

int obtenerOpcion() {
  int opcion;
  while (true) {
    cin >> opcion;
    if (cin.fail() || opcion < 1 || opcion > 5) {
      cin.clear(); // Limpiar el estado de error
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Ignorar entrada incorrecta
      cout << "Opción no válida. Intenta de nuevo: ";
    } else {
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Limpiar el buffer
      return opcion;
    }
  }
}

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main() {
    HashTable<string, int> edades;

    edades.set("Ana", 21);
    edades.set("Luis", 25);
    edades.set("Ana", 22); // actualiza

    cout << "Contenido de la tabla de edades: ";
    edades.display();

    cout << "Tamano: " << edades.size() << "\n";
    cout << "Contiene 'Luis'? " << (edades.contains("Luis") ? "si" : "no") << "\n";

    edades.erase("Luis");
    cout << "Tras borrar 'Luis': ";
    edades.display();

    // Otro ejemplo con valores string
    HashTable<string, string> capitales;
    capitales.set("Mexico", "CDMX");
    capitales.set("Canada", "Ottawa");
    cout << "Tabla de capitales: ";
    capitales.display();

    return 0;
}

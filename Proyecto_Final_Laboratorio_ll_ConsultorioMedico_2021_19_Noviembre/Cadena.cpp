#include "Cadena.h"
#include <iostream>
#include <cstring>

using namespace std;

Cadena::Cadena(const char* cad) {
    tam = strlen(cad) + 1;
    p = new char[tam];
    if (p == NULL)return;
    strcpy(p, cad);
}

void Cadena::Mostrar() {
    cout << p << endl;
}
void Cadena::setValor(const char* cad) {
    delete p;
    tam = strlen(cad) + 1;
    p = new char[tam];
    if (p == NULL) return;
    strcpy(p, cad);
}
char *Cadena::getCadena() {
    return p;
}

Cadena::~Cadena() {
    delete p;
}

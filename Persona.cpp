#include "Persona.h"
#include <iostream>
#include <cstring>

using namespace std;

Persona::Persona(int DNI, const char* nombres, const char* apellidos) {
    _DNI = DNI;
    strcpy(_nombres, nombres);
    strcpy(_apellidos, apellidos);
}
Persona::~Persona()
{

}
void Persona::setDNI(int dni) {
    if (dni > 0) {
        _DNI = dni;
    }
}
void Persona::setNombres(const char* nombres) {
    if (strlen(nombres) > 1) {
        strcpy(_nombres, nombres);
    }
}
void Persona::setApellidos(const char* apellidos) {
    if (strlen(apellidos) > 1) {
        strcpy(_apellidos, apellidos);
    }
}
void Persona::setEdad(int edad) {
    if (edad >= 0 && edad <=120) {
        _edad = edad;
    }
}
int  Persona::getDNI() {
    return _DNI;
}
char* Persona::getNombres() {
    return _nombres;
}
char* Persona::getApellidos() {
    return _apellidos;
}
int Persona::getEdad() {
    return _edad;
}
void Persona::Mostrar() {
    cout << "DNI: " << _DNI << endl;
    cout << "Nombres: " << _nombres << endl;
    cout << "Apellidos: " << _apellidos << endl;
    cout << "Edad: " << _edad << endl;
}

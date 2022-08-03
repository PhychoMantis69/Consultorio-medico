#include "Direccion.h"
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

Direccion::Direccion(const char* calle, const char* localidad, const char* partido, const char* provincia,
    const char* codigoPostal, const char* pais) {
    strcpy(_calle, calle);
    strcpy(_localidad, localidad);
    strcpy(_partido, partido);
    strcpy(_provincia, provincia);
    strcpy(_codigoPostal, codigoPostal);
    strcpy(_pais, pais);
}

Direccion::~Direccion()
{

}

///SETTERS
void Direccion::setCalle(const char* calle)
{
    if (strlen(calle) >= 4) {
        strcpy(_calle, calle);
    }
}

void Direccion::setLocalidad(const char* localidad)
{
    if (strlen(localidad) >= 2) {
        strcpy(_localidad, localidad);
    }
}

void Direccion::setPartido(const char* partido)
{
    if (strlen(partido) >= 4) {
        strcpy(_partido, partido);
    }
}

void Direccion::setProvincia(const char* provincia)
{
    if (strlen(provincia) >= 4) {
        strcpy(_provincia, provincia);
    }
}

void Direccion::setCodigoPostal(const char* codigoPostal)
{
    if (strlen(codigoPostal) >= 2) {
        strcpy(_codigoPostal, codigoPostal);
    }
}

void Direccion::setPais(const char* pais)
{
    if (strlen(pais) >= 3) {
        strcpy(_pais, pais);
    }
}


///GETTERS
char* Direccion::getCalle()
{
    return _calle;
}

char* Direccion::getLocalidad()
{
    return _localidad;
}

char* Direccion::getPartido()
{
    return _partido;
}

char* Direccion::getProvincia()
{
    return _provincia;
}

char* Direccion::getCodigoPostal()
{
    return _codigoPostal;
}

char* Direccion::getPais()
{
    return _pais;
}




void Direccion::Mostrar() {

    cout << "Calle: " << _calle << endl;
    cout << "Localidad: " << _localidad << endl;
    cout << "Partido: " << _partido << endl;
    cout << "Provincia: " << _provincia << endl;
    cout << "Codigo postal: " << _codigoPostal << endl;
    cout << "Pais: " << _pais << endl;

}

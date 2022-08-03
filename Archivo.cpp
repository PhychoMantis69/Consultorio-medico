#include "Archivo.h"
#include <iostream>
#include <cstdio>

using namespace std;

Archivo::Archivo(const char* nombre, bool estado) {
	strcpy(_nombre, nombre);
	_estado = estado;
}
void Archivo::setNombre(const char* nombre) {
	strcpy(_nombre, nombre);
}
void Archivo::setEstado(bool estado) {
	_estado = estado;
}
char *Archivo::getNombre() {
	return _nombre;
}
bool Archivo::getEstado() {
	return _estado;
}
bool Archivo::leerDeDisco(int pos, const char* ruta) {
	FILE* p;
	p = fopen(ruta, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Archivo) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Archivo), 1, p);
	fclose(p);
	return ok;
}
bool Archivo::grabarEnDisco(const char* ruta, int pos) {
	FILE* p;
	if (pos == 0) {
		p = fopen(ruta, "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(Archivo), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen(ruta, "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(Archivo) * pos, 0);
		ok = fwrite(this, sizeof(Archivo), 1, p);
		fclose(p);
		return ok;
	}
}

void Archivo::Mostrar() {
	cout << _nombre;
	if (_estado == true) cout << "\t" << "Activo" << endl;
	else cout << "\t" << "Inactivo" << endl;
}
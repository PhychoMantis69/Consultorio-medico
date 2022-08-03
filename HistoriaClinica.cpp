#include "HistoriaClinica.h"
#include <iostream>
#include<cstring>

using namespace std;

HistoriaClinica::HistoriaClinica() {
	_IDTurno = 0;
	strcpy(_detallesConsulta, "Vacio");
}
HistoriaClinica::HistoriaClinica(int IDTurno, const char* detallesConsulta) {
	_IDTurno = IDTurno;
	strcpy(_detallesConsulta, detallesConsulta);
}
HistoriaClinica::~HistoriaClinica() {

}
void HistoriaClinica::setIDTurno(int IDTurno) {
	_IDTurno = IDTurno;
}
void HistoriaClinica::setDetallesConsulta(char* detallesConsulta) {
	strcpy(_detallesConsulta, detallesConsulta);
}
int HistoriaClinica::getIDTurno() {
	return _IDTurno;
}
char* HistoriaClinica::getDetallesConsulta() {
	return _detallesConsulta;
}
void HistoriaClinica::Mostrar() {
	cout << "ID de turno: " << _IDTurno << endl;
	cout << "Detalles de la consulta: " << _detallesConsulta << endl;
}
bool HistoriaClinica::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("HistoriasClinicas.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(HistoriaClinica) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(HistoriaClinica), 1, p);
	fclose(p);
	return ok;
}
bool HistoriaClinica::grabarEnDisco(int pos) {
	FILE* p;
	if (pos == 0) {
		p = fopen("HistoriasClinicas.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(HistoriaClinica), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("HistoriasClinicas.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(HistoriaClinica) * pos, 0);
		ok = fwrite(this, sizeof(HistoriaClinica), 1, p);
		fclose(p);
		return ok;
	}
}
bool HistoriaClinica::leerCopiaDeDisco(int pos, const char* ruta) {
	FILE* p;
	p = fopen(ruta, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(HistoriaClinica) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(HistoriaClinica), 1, p);
	fclose(p);
	return ok;
}
bool HistoriaClinica::GrabarCopiaEnDisco(const char* ruta) {
	FILE* p;
	p = fopen(ruta, "wb");
	if (p == NULL) {
		return false;
	}
	bool ok = fwrite(this, sizeof(HistoriaClinica), 1, p);
	fclose(p);
	return ok;
}
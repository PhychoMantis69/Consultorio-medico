#include "Fecha.h"
#include "Cadena.h"
#include <ctime>
#include<conio.h>
#include<dos.h>    /* para el uso de getdate" y "gettime" */
#include<stdio.h>
#include <iostream>

using namespace std;

Fecha::Fecha(int dia, int mes, int anio) {
	_dia = dia;
	_mes = mes;
	_anio = anio;
	Cadena dias[7] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };
	_numDia= (_dia + ((153 * (_mes + 12 * ((14 - _mes) / 12) - 3) + 2) / 5) + (365 * (_anio + 4800 - ((14 - _mes) / 12))) +
		((_anio + 4800 - ((14 - _mes) / 12)) / 4) - ((_anio + 4800 - ((14 - _mes) / 12)) / 100) +
		((_anio + 4800 - ((14 - _mes) / 12)) / 400) - 32045) % 7;
	strcpy(_nombreDia, dias[_numDia].getCadena());
	_numDia++;
	_feriado = false;
}
Fecha::~Fecha() {

}
void Fecha::setFecha(int dia, int mes, int anio) {
	_dia = dia;
	_mes = mes;
	_anio = anio;
	setNombreDia(dia, mes, anio);
	//setFeriado(dia, mes);
}
void Fecha::setNombreDia(int dia, int mes, int anio) {
	Cadena dias[7] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };
	//const char* dias[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };
	//int nombreDiaSemana = (dia += mes < 3 ? anio-- : anio - 2, 23 * mes / 9 + dia + 4 + anio / 4 - anio / 100 + anio / 400) % 7;
	_numDia = (dia + ((153 * (mes + 12 * ((14 - mes) / 12) - 3) + 2) / 5) + (365 * (anio + 4800 - ((14 - mes) / 12))) +
		((anio + 4800 - ((14 - mes) / 12)) / 4) - ((anio + 4800 - ((14 - mes) / 12)) / 100) +
		((anio + 4800 - ((14 - mes) / 12)) / 400) - 32045) % 7;
	strcpy(_nombreDia, dias[_numDia].getCadena());
	_numDia++;
}
bool Fecha::esFeriado(int dia, int mes) {
	//if (_numDia == 6 || _numDia == 7) return true;
	if (dia == 1 && mes == 1) return true;
	if (dia == 24 && mes == 3)return true;
	if (dia == 2 && mes == 4)return true;
	if (dia == 1 && mes == 5)return true;
	if (dia == 25 && mes == 5)return true;
	if (dia == 20 && mes == 6)return true;
	if (dia == 9 && mes == 7)return true;
	if (dia == 8 && mes == 12)return true;
	if (dia == 25 && mes == 12)return true;
	return false;
	//if (_dia == 25 && _mes == 12 || _dia == 1 && _mes == 1 || _numDia == 6 || _numDia == 7) _feriado = true;
	//_feriado = false;
	//return _feriado;
}
int  Fecha::getDia() {
	return _dia;
}
int  Fecha::getMes() {
	return _mes;
}
int  Fecha::getAnio() {
	return _anio;
}
bool Fecha::esCorrecta(int dia, int mes, int anio) {
	int vectorDiasMes[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	if (anio == 0) return false;
	if (dia <= 0 || dia > 31) return false;
	if (mes <= 0 || mes > 12) return false;
	if (mes == 2 && dia > 29) return false;
	if (vectorDiasMes[mes - 1] < dia) return false;
	if (mes == 2 && dia == 29 && !esBisiesto(anio)) return false;
	return true;
}
bool Fecha::esBisiesto(int anio) {
	if ((anio % 4 == 0) || (anio % 400 == 0) && (anio % 100 != 0)) {
		return true;
	}
	else {
		return false;
	}
}
/*int Fecha::MaxDiasMes(int mes, bool bisiesto) {
	if (bisiesto) {
		int AnioBisiesto[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return AnioBisiesto;
	}
}
bool Fecha::Bisiesto() {
	//int AnioBisiesto[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//int AnioNoBisiesto[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (_anio % 4 == 0 && _anio % 100 != 0 || _anio % 400 == 0) {
		return true;
	}
		return false;
}*/



char *Fecha::getNombreDia() {
	return _nombreDia;
}
int Fecha::getNumeroDia() {
	return _numDia;
}
bool Fecha::getFeriado() {
	return _feriado;
}
void Fecha::Mostrar() {
	cout << _nombreDia << " ";
	if (_dia < 10) {
		cout << "0";
	}
	cout << _dia << "/";
	if (_mes < 10) {
		cout << "0";
	}
	cout << _mes << "/";
	if (_anio < 10) {
		cout << "0";
	}
	if (_anio < 100) {
		cout << "0";
	}
	if (_anio < 1000) {
		cout << "0";
	}
	cout << _anio << endl;
}
///SOBREVARGAS
bool Fecha :: operator > (Fecha& f)
{
	/*if (_anio > f.getAnio()) {
		return true;
	}
	if (_anio < f.getAnio()) {
		return false;
	}
	if (_anio == f.getAnio()) {
		if (_mes > f.getMes()) {
			return true;
		}
		if (_mes < f.getMes()) {
			return false;
		}
		if (_mes == f.getMes()) {
			if (_dia > f.getDia()) {
				return true;
			}
			else {
				return false;
			}
		}
	}*/

	if (_anio < f.getAnio()) return false;
	if (_anio == f.getAnio() && _mes < f.getMes()) return false;
	if (_anio == f.getAnio() && _mes == f.getMes() && _dia < f.getDia()) return false;
	return true;
}



bool Fecha :: operator < (Fecha& f) {

	/*if (_anio < f.getAnio()) {
		return true;
	}
	if (_anio > f.getAnio()) {
		return false;
	}
	if (_anio == f.getAnio()) {
		if (_mes < f.getMes()) {
			return true;
		}
		if (_mes > f.getMes()) {
			return false;
		}
		if (_mes == f.getMes()) {
			if (_dia < f.getDia()) {
				return true;
			}
			else {
				return false;
			}
		}
	}*/

	if (_anio > f.getAnio()) return false;
	if (_anio == f.getAnio() && _mes > f.getMes()) return false;
	if (_anio == f.getAnio() && _mes == f.getMes() && _dia > f.getDia()) return false;
	return true;
}

bool Fecha::operator ==(Fecha& f) {
	if (_dia != f.getDia()) return false;
	if (_mes != f.getMes()) return false;
	if (_anio != f.getAnio()) return false;
	return true;
}

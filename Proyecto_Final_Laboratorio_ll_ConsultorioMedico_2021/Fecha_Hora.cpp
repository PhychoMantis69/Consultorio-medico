#include "Fecha_Hora.h"
#include <cstring>
#include <iostream>

using namespace std;

Fecha_Hora::Fecha_Hora(int hora, int minuto, int dia, int mes, int anio) {
	int millares = anio / 1000;
	int centenas = (anio - (millares * 1000)) / 100;
	int decenas = (anio - (millares * 1000 + centenas * 100)) / 10;
	int unidades = anio - (millares * 1000 + centenas * 100 + decenas * 10);
	_fechaHora[0] = (char)(hora / 10) + 48;
	_fechaHora[1] = (char)(hora - ((hora / 10) * 10)) + 48;
	_fechaHora[2] = ':';
	_fechaHora[3] = (char)(minuto / 10) + 48;
	_fechaHora[4] = (char)(minuto - ((minuto / 10) * 10)) + 48;
	_fechaHora[5] = ' ';
	_fechaHora[6] = (char)(dia / 10) + 48;
	_fechaHora[7] = (char)(dia - ((dia / 10) * 10)) + 48;
	_fechaHora[8] = '/';
	_fechaHora[9] = (char)(mes / 10) + 48;
	_fechaHora[10] = (char)(mes - ((mes / 10) * 10)) + 48;
	_fechaHora[11] = '/';
	_fechaHora[12] = (char)(millares)+48;
	_fechaHora[13] = (char)(centenas)+48;
	_fechaHora[14] = (char)(decenas)+48;
	_fechaHora[15] = (char)(unidades)+48;
	_fechaHora[16] = '\0';
}
void Fecha_Hora::setFechaHora(int hora, int minuto, int dia, int mes, int anio) {
	int millares = anio / 1000;
	int centenas = (anio - (millares * 1000)) / 100;
	int decenas = (anio - (millares * 1000 + centenas * 100)) / 10;
	int unidades = anio - (millares * 1000 + centenas * 100 + decenas * 10);
	/*if (hora < 10) {
		aux[0] = '0';
		aux[1] = (char)hora + 48;
	}
	else if(hora<20) {
		aux[0] = '1';
		aux[1] = (char)(hora-10) + 48;
	}
	else {
		aux[0] = '2';
		aux[1] = (char)(hora - 20) + 48;
	}*/
	_fechaHora[0] = (char)(hora / 10) + 48;
	_fechaHora[1] = (char)(hora - ((hora / 10) * 10)) + 48;
	_fechaHora[2] = ':';
	_fechaHora[3] = (char)(minuto / 10) + 48;
	_fechaHora[4] = (char)(minuto - ((minuto / 10) * 10)) + 48;
	_fechaHora[5] = ' ';
	_fechaHora[6] = (char)(dia / 10) + 48;
	_fechaHora[7] = (char)(dia - ((dia / 10) * 10)) + 48;
	_fechaHora[8] = '/';
	_fechaHora[9] = (char)(mes / 10) + 48;
	_fechaHora[10] = (char)(mes - ((mes / 10) * 10)) + 48;
	_fechaHora[11] = '/';
	_fechaHora[12] = (char)(millares) + 48;
	_fechaHora[13] = (char)(centenas) + 48;
	_fechaHora[14] = (char)(decenas)+48;
	_fechaHora[15] = (char)(unidades)+48;
	_fechaHora[16] = '\0';
}
char *Fecha_Hora::getFechaHora() {
	return _fechaHora;
}
void Fecha_Hora::Mostrar() {
	cout << _fechaHora << endl;
}
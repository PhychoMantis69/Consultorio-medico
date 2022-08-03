#include "Hora.h"
#include <iostream>

using namespace std;

Hora::Hora(int hora, int minuto) {
	_hora = hora;
	_minuto = minuto;
}
Hora::~Hora() {

}
void Hora::setHora(int hora) {
	if (hora >= 0 && hora <= 23) {
		_hora = hora;
	}
}
void Hora::setMinuto(int minuto) {
	if (minuto >= 0 && minuto <= 59) {
		_minuto = minuto;
	}
}
int  Hora::getHora() {
	return _hora;
}
int  Hora::getMinuto() {
	return _minuto;
}
void Hora::Mostrar() {
	if (_hora < 10) {
		cout << "0";
	}
	cout << _hora << ":";
	if (_minuto < 10) {
		cout << "0";
	}
	cout << _minuto;
}

#include "Especialidad.h"
#include <iostream>
#include <cstring>

using namespace std;

Especialidad::Especialidad() {
	_IDEmpleado = 0;
	_nEspecialidades = -1;
		strcpy(_especialidades[0], "Administrador");
		strcpy(_especialidades[1], "Administrativo");
		strcpy(_especialidades[2], "Pediatria");
		strcpy(_especialidades[3], "Kinesiologia");
		strcpy(_especialidades[4], "Oftalmologia");
		strcpy(_especialidades[5], "Traumatologia");
		strcpy(_especialidades[6], "Obstetricia");
		strcpy(_especialidades[7], "Psicologia");
		strcpy(_especialidades[8], "Nutricion");
		strcpy(_especialidades[9], "Psiquiatria");
		strcpy(_especialidades[10], "Dermatologia");
		strcpy(_especialidades[11], "Cardiologia");
}
/*Especialidad::Especialidad(int idEmpleado = 0) {
	_IDEmpleado = idEmpleado;
}*/
void Especialidad::setIDEmpleado(int IDEmpleado) {
	if (IDEmpleado > 0 && IDEmpleado < 100000) {
		_IDEmpleado = IDEmpleado;
	}
}
void Especialidad::setEspecialidades(char Especialidades[][20]) {
	for (int i = 0; i < 12; i++)
	{
		strcpy(_especialidades[i], Especialidades[i]);
	}
}
void Especialidad::setNEspecialidades(int nEspecialidades) {
	if (nEspecialidades >= 0 && nEspecialidades <= 12) {
		_nEspecialidades = nEspecialidades;
	}
}
int  Especialidad::getIDEmpleado() {
	return _IDEmpleado;
}
char* Especialidad::getEspecialidades() {
	return *_especialidades;
}
int Especialidad::getNEspecialidades() {
	return _nEspecialidades;
}
void Especialidad::Mostrar() {
	cout << "Legajo de empleado: " << _IDEmpleado << endl;
	cout << "Especialidad: " << _especialidades[_nEspecialidades]<<endl;
}
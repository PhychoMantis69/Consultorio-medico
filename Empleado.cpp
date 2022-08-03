#include "Empleado.h"
#include <iostream>
#include <cstring>

using namespace std;

Empleado::Empleado() {
	_DNI = 0;
	strcpy(_nombres, "Vacio");
	strcpy(_apellidos, "Vacio");
	_legajo = 0;
	strcpy(_password, "Vacio");
	strcpy(_email, "Vacio");
	_tipoEmpleado = 0;
	//_especialidad = 0;
	///_horaEntrada = horaEntrada;
	///_horaSalida = horaSalida;
	_estado = true;
}
/*Empleado::Empleado(int dni, const char* nombres, const char* apellidos, int legajo, const char* password,
	const char* email, int tipoEmpleado, bool estado) {
	_DNI = dni;
	strcpy(_nombres, nombres);
	strcpy(_apellidos, apellidos);
	strcpy(_password, password);
	strcpy(_email, email);
	_tipoEmpleado = tipoEmpleado;
	//_especialidad = especialidad;
	//_horarioEntradaSalida = horarioEntradaSalida;
	_estado = estado;
}*/
Empleado::~Empleado() {

}
void Empleado::setLegajo(int legajo) {
	if (legajo > 0 && legajo < 100000) {
		_legajo = legajo;
	}
}
void Empleado::setPassword(char* password) {
	if (strlen(password) >= 8) {
		strcpy(_password, password);
	}
}
void Empleado::setEmail(const char* email) {
	if (strlen(email) > 7) {
		strcpy(_email, email);
	}
}
void Empleado::setTipoEmpleado(int tipoEmpleado) {
	if (tipoEmpleado >= 1 && tipoEmpleado <= 2 || tipoEmpleado == 99) {
		_tipoEmpleado = tipoEmpleado;
	}
}
void Empleado::setEspecialidad(Especialidad especialidad) {
		_especialidad = especialidad;
}
void Empleado::setHoraEntradaSalida(HorarioEmpleado horarioEntradaSalida) {
	_horarioEntradaSalida = horarioEntradaSalida;
}
void Empleado::setEstado(bool estado) {
	if (estado == true || estado == false) {
		_estado = estado;
	}
}
int  Empleado::getLegajo() {
	return _legajo;
}
char* Empleado::getPassword() {
	return _password;
}
char* Empleado::getEmail() {
	return _email;
}
int  Empleado::getTipoEmpleado() {
	return _tipoEmpleado;
}
Especialidad  Empleado::getEspecialidad() {
	return _especialidad;
}
HorarioEmpleado Empleado::getHoraEntradaSalida() {
	return _horarioEntradaSalida;
}
bool Empleado::getEstado() {
	return _estado;
}
void Empleado::Mostrar() {
	Persona::Mostrar();
	cout << "Legajo: " << _legajo << endl;
	cout << "Password" << _password << endl;
	cout << "Email: " << _email << endl;
	cout << "Tipo de Empleado (1- Administrativo, 2- Medico, 99-Administrador): " << _tipoEmpleado << endl;
	if (_tipoEmpleado == 2) {
		cout << "Especialidad Medico: " << _especialidad.getEspecialidades()<<endl;
	}
	_horarioEntradaSalida.Mostrar();
	cout << endl;
}
bool Empleado::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("Empleados.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Empleado) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Empleado), 1, p);
	fclose(p);
	return ok;
}
bool Empleado::grabarEnDisco(int pos) {
	FILE* p;
	if (pos == 0) {
		p = fopen("Empleados.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(Empleado), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("Empleados.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(Empleado) * pos, 0);
		ok = fwrite(this, sizeof(Empleado), 1, p);
		fclose(p);
		return ok;
	}
}
bool Empleado::leerCopiaDeDisco(int pos, const char* ruta) {
	FILE* p;
	p = fopen(ruta, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Empleado) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Empleado), 1, p);
	fclose(p);
	return ok;
}
bool Empleado::GrabarCopiaEnDisco(const char* ruta) {
	FILE* p;
	p = fopen(ruta, "wb");
	if (p == NULL) {
		return false;
	}
	bool ok = fwrite(this, sizeof(Empleado), 1, p);
	fclose(p);
	return ok;
}
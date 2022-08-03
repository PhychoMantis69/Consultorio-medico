#include "Paciente.h"
#include <iostream>
#include <cstring>


using namespace std;

Paciente::Paciente() {
	_DNI = 0;
	strcpy(_nombres, "Vacio");
	strcpy(_apellidos, "Vacio");
	_ID = 0;
	strcpy(_telefono, "Vacio");
	strcpy(_email, "Vacio");
	_estado = true;
}
Paciente::Paciente(Direccion direccionPaciente, int dni, const char* nombres, const char* apellidos, int id,
	const char* telefono, const char* email, bool estado) {
	_DNI = dni;
	strcpy(_nombres, nombres);
	strcpy(_apellidos, apellidos);
	_ID = id;
	strcpy(_telefono, telefono);
	strcpy(_email, email);
	_estado = estado;
}
Paciente::~Paciente() {

}
void Paciente::setID(int id) {
	if (id > 0 && id < 100000) {
		_ID = id;
	}
}
void Paciente::setTelefono(char* telefono) {
	if (strlen(telefono) >= 4) {
		strcpy(_telefono, telefono);
	}
}
void Paciente::setEmail(char* email) {
	if (strlen(email) >= 7) {
		strcpy(_email, email);
	}
}
void Paciente::setFechaNac(Fecha fechaNac) {
	if (fechaNac.getDia() > 0 && fechaNac.getDia() <= 31) {
		if (fechaNac.getMes() > 0 && fechaNac.getMes() <= 12) {
			if (fechaNac.getAnio() >= 1900 && fechaNac.getAnio() < 2021) {
				_fechaNac = fechaNac;
			}
		}
	}
}
void Paciente::setDireccionPaciente(Direccion direccionPaciente) {
	if (strlen(direccionPaciente.getCalle()) >= 2) {
		if (strlen(direccionPaciente.getLocalidad()) >= 3) {
			if (strlen(direccionPaciente.getPartido()) >= 3) {
				if (strlen(direccionPaciente.getProvincia()) >= 3) {
					if (strlen(direccionPaciente.getCodigoPostal()) >= 2) {
						if (strlen(direccionPaciente.getPais()) >= 3) {
							_direccionPaciente = direccionPaciente;
						}
					}
				}
			}
		}

	}
}
void Paciente::setEstado(bool estado) {
	if (estado == true || estado == false) {
		_estado = estado;
	}
}
int  Paciente::getID() {
	return _ID;
}
char* Paciente::getTelefono() {
	return _telefono;
}
char* Paciente::getEmail() {
	return _email;
}
Fecha Paciente::getFechaNac() {
	return _fechaNac;
}
Direccion Paciente::getDireccionPaciente() {
	return _direccionPaciente;
}
bool Paciente::getEstado() {
	return _estado;
}
void Paciente::Mostrar() {
	Persona::Mostrar();
	cout << "ID: " << _ID << endl;
	cout << "Telefono: " << _telefono << endl;
	cout << "Email: " << _email << endl;
	_fechaNac.Mostrar();
	_direccionPaciente.Mostrar();
}
bool Paciente::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("Pacientes.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Paciente) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Paciente), 1, p);
	fclose(p);
	return ok;
}
bool Paciente::GrabarEnDisco(int pos) {
	FILE* p;
	if (pos == 0) {
		p = fopen("Pacientes.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(Paciente), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("Pacientes.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(Paciente) * pos, 0);
		ok = fwrite(this, sizeof(Paciente), 1, p);
		fclose(p);
		return ok;
	}
}
bool Paciente::leerCopiaDeDisco(int pos, const char* ruta) {
	FILE* p;
	p = fopen(ruta, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Paciente) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Paciente), 1, p);
	fclose(p);
	return ok;
}
bool Paciente::GrabarCopiaEnDisco(const char* ruta) {
	FILE* p;
	p = fopen(ruta, "wb");
	if (p == NULL) {
		return false;
	}
	bool ok = fwrite(this, sizeof(Paciente), 1, p);
	fclose(p);
	return ok;
}
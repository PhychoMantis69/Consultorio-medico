#include "Turno.h"
#include <iostream>
#include <ctime>

using namespace std;
Turno::Turno() {
	_ID = 0;
	_IDPaciente = 0;
	_obraSocial = 0;
	_legajoMedico = 0;
	_asistencia = false;
	_estado = true;
}
Turno::Turno(Fecha fechaTurno, Hora horaTurno, Fecha fechaAsignacionTurno, int ID, int IDPaciente,
	int obraSocial, int legajoMedico, bool asistencia, bool estado) {
	_ID = ID;
	_IDPaciente = IDPaciente;
	_obraSocial = obraSocial;
	_fechaTurno = fechaTurno;
	_fechaAsignacionTurno = fechaAsignacionTurno;
	_legajoMedico = legajoMedico;
	_asistencia = asistencia;
	_estado = estado;
}
Turno::~Turno() {

}

void Turno::setID(int id) {
	if (id > 0) {
		_ID = id;
	}
}
void Turno::setIDPaciente(int idPaciente) {
	if (idPaciente > 0 && idPaciente < 100000) {
		_IDPaciente = idPaciente;
	}
}
void Turno::setObraSocial(int obraSocial) {
	if (obraSocial > 0 && obraSocial < 100) {
		_obraSocial = obraSocial;
	}
}
void Turno::setFechaTurno(Fecha fechaTurno) {
	if (fechaTurno.getDia() > 0 && fechaTurno.getDia() <= 31) {
		if (fechaTurno.getMes() > 0 && fechaTurno.getMes() <= 12) {
			if (fechaTurno.getAnio() >= 2021 && fechaTurno.getAnio() < 2100) {
				_fechaTurno = fechaTurno;
			}
		}
	}
}
void Turno::setHoraTurno(Hora horaTurno) {
	if (horaTurno.getHora() >= 0 && horaTurno.getHora() <= 23) {
		if (horaTurno.getMinuto() >= 0 && horaTurno.getMinuto() <= 59) {
			_horaTurno = horaTurno;
		}
	}
}
void Turno::setFechaAsignacionTurno() {
	int dia, mes, anio;
	time_t t;
	struct tm* f;
	time(&t);
	f = localtime(&t);
	dia = (f->tm_mday);
	mes = (f->tm_mon + 1);
	anio = (f->tm_year + 1900);
	_fechaAsignacionTurno.setFecha(dia, mes, anio);
}
void Turno::setLegajoMedico(int legajoMedico) {
	if (legajoMedico > 0 && legajoMedico <= 100000) {
		_legajoMedico = legajoMedico;
	}
}
void Turno::setAsistencia(bool asistencia) {
	if (asistencia == true || asistencia == false) {
		_asistencia = asistencia;
	}
}
void Turno::setEstado(bool estado) {
	if (estado == true || estado == false) {
		_estado = estado;
	}
}
int  Turno::getID() {
	return _ID;
}
int  Turno::getIDPaciente() {
	return _IDPaciente;
}
int  Turno::getObraSocial() {
	return _obraSocial;
}
Fecha Turno::getFechaTurno() {
	return _fechaTurno;
}
Hora Turno::getHoraTurno() {
	return _horaTurno;
}
Fecha Turno::getFechaAsignacionTurno() {
	return _fechaAsignacionTurno;
}
int  Turno::getLegajoMedico() {
	return _legajoMedico;
}
bool Turno::getAsistencia() {
	return _asistencia;
}
bool Turno::getEstado() {
	return _estado;
}
void Turno::Mostrar() {
	cout << "ID: " << _ID << endl;
	cout << "ID Paciente: " << _IDPaciente << endl;
	cout << "Obra Social: " << _obraSocial << endl;
	cout << "Fecha de turno: ";
	_fechaTurno.Mostrar();
	cout << "Hora de turno: ";
	_horaTurno.Mostrar();
	cout << endl;
	cout << "Fecha de asignacion de turno: ";
	_fechaAsignacionTurno.Mostrar();
	cout << endl;
}
bool Turno::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("Turnos.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(Turno) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(Turno), 1, p);
	fclose(p);
	return ok;
}
bool Turno::grabarEnDisco(int pos = 0) {
	FILE* p;
	if (pos == 0) {
		p = fopen("Turnos.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(Turno), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("Turnos.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(Turno) * pos, 0);
		ok = fwrite(this, sizeof(Turno), 1, p);
		fclose(p);
		return ok;
	}
}

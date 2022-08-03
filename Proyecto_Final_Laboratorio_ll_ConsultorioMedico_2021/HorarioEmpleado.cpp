#include "HorarioEmpleado.h"
#include <iostream>
#include <cstring>

using namespace std;

HorarioEmpleado::HorarioEmpleado() {
	_IDEmpleado = 0;
	_estado = true;
	strcpy(_dias[0], "Lunes");
	strcpy(_dias[1], "Martes");
	strcpy(_dias[2], "Miercoles");
	strcpy(_dias[3], "Jueves");
	strcpy(_dias[4], "Viernes");
	strcpy(_dias[5], "Sabado");
	strcpy(_dias[6], "Domingo");
	for (int i = 0; i < 7; i++)
	{
		_diasATrabajar[i] = false;
	}
}
/*HorarioEmpleado::HorarioEmpleado(int IDEmpleado, bool* diasATrabajar, Hora* horaEntrada, Hora* horaSalida) {
	_IDEmpleado = IDEmpleado;
	strcpy(_dias[0], "Lunes");
	strcpy(_dias[1], "Martes");
	strcpy(_dias[2], "Miercoles");
	strcpy(_dias[3], "Jueves");
	strcpy(_dias[4], "Viernes");
	strcpy(_dias[5], "Sabado");
	strcpy(_dias[6], "Domingo");
	for (int i = 0; i < 7; i++)
	{
		_diasATrabajar[i] = diasATrabajar[i];
		_horaEntrada[i] = horaEntrada[i];
		_horaSalida[i] = horaSalida[i];
	}

}*/
void HorarioEmpleado::setIDEmpleado(int idEmpleado) {
	if (idEmpleado > 0 && idEmpleado < 100000) {
		_IDEmpleado = idEmpleado;
	}
}
void HorarioEmpleado::setDias(const char (*dias)[11]) {
	for (int i = 0; i < 7; i++)
	{
		strcpy(_dias[i], dias[i]);
	}
}
void HorarioEmpleado::setDiasATrabajar(bool* diasATrabajar) {
	for (int i = 0; i < 7; i++)
	{
		_diasATrabajar[i] = diasATrabajar[i];
	}
}
void HorarioEmpleado::setHoraEntrada(Hora* horaEntrada) {
	for (int i = 0; i < 7; i++)
	{
			if (horaEntrada[i].getHora() < 0 || horaEntrada[i].getHora() > 23 ||
				horaEntrada[i].getMinuto() < 0 || horaEntrada[i].getMinuto() > 59) {
				return;
			}
	}
	for (int i = 0; i < 7; i++) {
		_horaEntrada[i] = horaEntrada[i];
	}
}
void HorarioEmpleado::setHoraSalida(Hora* horaSalida) {
	for (int i = 0; i < 7; i++)
	{
		if (horaSalida[i].getHora() < 0 || horaSalida[i].getHora() > 23 ||
			horaSalida[i].getMinuto() < 0 || horaSalida[i].getMinuto() > 59) {
			return;
		}
	}
	for (int i = 0; i < 7; i++) {
		_horaSalida[i] = horaSalida[i];
	}
}
void HorarioEmpleado::setEstado(bool estado) {
	if (estado == true || estado == false) {
		_estado = estado;
	}
}
int  HorarioEmpleado::getIDEmpleado() {
	return _IDEmpleado;
}
char *HorarioEmpleado::getDias() {
	return *_dias;
}
bool* HorarioEmpleado::getDiasATrabajar() {
	return _diasATrabajar;
}
Hora* HorarioEmpleado::getHoraEntrada() {
	return _horaEntrada;
}
Hora* HorarioEmpleado::getHoraSalida() {
	return _horaSalida;
}
bool HorarioEmpleado::getEstado() {
	return _estado;
}
void HorarioEmpleado::Mostrar() {
	cout << "Legajo de empleado: ";
	cout << _IDEmpleado << endl;
	cout << "Dias a trabajar: " << endl;
	for (int i = 0; i < 7; i++)
	{
		if (_diasATrabajar[i]==true)
		{
			cout << _dias[i] << " de ";
			_horaEntrada[i].Mostrar();
			cout << " a ";
			_horaSalida[i].Mostrar();
			cout << endl;
		}
	}
}
bool HorarioEmpleado::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("HorariosEmpleados.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(HorarioEmpleado), 0);
	bool ok;
	ok = fread(this, sizeof(HorarioEmpleado) * pos, 1, p);
	fclose(p);
	return ok;
}
bool HorarioEmpleado::grabarEnDisco(int pos=0) {
	FILE* p;
	if (pos == 0) {
		p = fopen("HorariosEmpleados.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(HorarioEmpleado), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("Turnos.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(HorarioEmpleado) * pos, 0);
		ok = fwrite(this, sizeof(HorarioEmpleado), 1, p);
		fclose(p);
		return ok;
	}
}
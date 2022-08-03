#pragma once
#include "Hora.h"
#include "FuncionesGlobales.h"
//#include "Empleado.h"

class HorarioEmpleado
{
public:
	HorarioEmpleado();
	//HorarioEmpleado(int IDEmpleado, bool *diasATrabajar, Hora *horaEntrada, Hora *horaSalida);
	void setIDEmpleado(int idEmpleado);
	void setDias(const char (*dias)[11]);
	void setDiasATrabajar(bool* diasATrabajar);
	void setHoraEntrada(Hora* horaEntrada);
	void setHoraSalida(Hora* horaSalida);
	void setEstado(bool estado);
	int getIDEmpleado();
	char* getDias();
	bool* getDiasATrabajar();
	Hora* getHoraEntrada();
	Hora* getHoraSalida();
	bool getEstado();
	void Mostrar();
	bool leerDeDisco(int pos);
	bool grabarEnDisco(int pos);
private:
	int _IDEmpleado;
	char _dias[7][11];
	bool _diasATrabajar[7];
	Hora _horaEntrada[7];
	Hora _horaSalida[7];
	bool _estado;
};


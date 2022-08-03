#pragma once
#include "Fecha_Hora.h"
class Turno
{
public:
	Turno();
	Turno(Fecha fechaTurno, Hora horaTurno, Fecha fechaAsignacionTurno, int ID = 0, int IDPaciente = 0,
		int obraSocial = 0, int legajoMedico = 0, bool asistencia = false, bool estado = true);
	~Turno();

	void setID(int id);
	void setIDPaciente(int idPaciente);
	void setObraSocial(int obraSocial);
	void setFechaTurno(Fecha fechaTurno);
	void setHoraTurno(Hora horaTurno);
	void setFechaAsignacionTurno();
	void setLegajoMedico(int legajoMedico);
	void setAsistencia(bool asistencia);
	void setEstado(bool estado);

	int getID();
	int getIDPaciente();
	int getObraSocial();
	Fecha getFechaTurno();
	Hora getHoraTurno();
	Fecha getFechaAsignacionTurno();
	int getLegajoMedico();
	bool getAsistencia();
	bool getEstado();

	void Mostrar();
	bool leerDeDisco(int pos);
	bool grabarEnDisco(int pos = 0);

	bool leerCopiaDeDisco(int pos, const char* ruta);
	bool GrabarCopiaEnDisco(const char* ruta);

private:
	int _ID;
	int _IDPaciente;
	int _obraSocial;
	Fecha _fechaTurno;
	Hora _horaTurno;
	Fecha _fechaAsignacionTurno;
	int _legajoMedico;
	bool _asistencia;
	bool _estado;
};



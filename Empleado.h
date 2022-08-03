#pragma once
#include "Persona.h"
#include "Fecha.h"
#include "Hora.h"
#include "HorarioEmpleado.h"
#include "Especialidad.h"

class Empleado : public Persona
{
public:
	Empleado();
	/*Empleado(int dni = 0, const char* nombres = "vacio", const char* apellidos = "vacio",
		int legajo = 0, const char* password = "vacio", const char* email = "vacio", int tipoEmpleado = 0, bool estado = true);*/
	~Empleado();
	void setLegajo(int legajo);
	void setPassword(char* password);
	void setEmail(const char* email);
	void setTipoEmpleado(int tipoEmpleado);
	void setEspecialidad(Especialidad especialidad);
	void setHoraEntradaSalida(HorarioEmpleado horarioEntradaSalida);
	void setEstado(bool estado);

	int getLegajo();
	char* getPassword();
	char* getEmail();
	int getTipoEmpleado();
	Especialidad getEspecialidad();
	HorarioEmpleado getHoraEntradaSalida();
	bool getEstado();

	void Mostrar();
	bool leerDeDisco(int pos);
	bool grabarEnDisco(int pos = 0);

	bool leerCopiaDeDisco(int pos, const char* ruta);
	bool GrabarCopiaEnDisco(const char* ruta);

private:
	int _legajo;
	char _password[30];
	char _email[50];
	int _tipoEmpleado;
	Especialidad _especialidad;
	HorarioEmpleado _horarioEntradaSalida;
	bool _estado;
};
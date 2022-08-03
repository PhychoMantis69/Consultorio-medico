#pragma once
#include "Persona.h"
#include "Direccion.h"
#include "Fecha.h"

class Paciente : public Persona
{
public:
	Paciente();
	Paciente(Direccion direccionPaciente, int dni = 0, const char* nombres = "vacio", const char* apellidos = "vacio",
		int id = 0, const char* telefono = "vacio", const char* email = "vacio", bool estado = true);
	~Paciente();

	void setID(int id);
	void setTelefono(char* telefono);
	void setEmail(char* email);
	void setFechaNac(Fecha fechaNac);
	void setDireccionPaciente(Direccion direccionPaciente);
	void setEstado(bool estado);


	int getID();
	char* getTelefono();
	char* getEmail();
	Fecha getFechaNac();
	Direccion getDireccionPaciente();
	bool getEstado();

	void Mostrar();
	bool leerDeDisco(int pos);
	bool GrabarEnDisco(int pos = 0);

	bool leerCopiaDeDisco(int pos, const char* ruta);
	bool GrabarCopiaEnDisco(const char* ruta);

private:
	int _ID;
	char _telefono[30];
	char _email[50];
	Fecha _fechaNac;
	Direccion _direccionPaciente;
	bool _estado;
};
#pragma once
class Especialidad
{
public:
	Especialidad();
	void setIDEmpleado(int IDEmpleado);
	void setEspecialidades(char Especialidades[][20]);
	void setNEspecialidades(int nEspecialidades);
	int getIDEmpleado();
	char* getEspecialidades();
	int getNEspecialidades();
	void Mostrar();
private:
	int _IDEmpleado;
	char _especialidades[12][20];
	int _nEspecialidades;
};


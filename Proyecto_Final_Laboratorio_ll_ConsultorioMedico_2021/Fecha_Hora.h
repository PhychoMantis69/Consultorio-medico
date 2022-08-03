#pragma once
#include "Fecha.h"
#include "Hora.h"

class Fecha_Hora : public Fecha, public Hora
{
public:
	Fecha_Hora(int hora = 0, int minuto = 0, int dia = 0, int mes = 0, int anio = 0);
	void setFechaHora(int hora, int minuto, int dia, int mes, int anio);
	char* getFechaHora();
	void Mostrar();
private:
	char _fechaHora[17];
};


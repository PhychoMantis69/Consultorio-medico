#pragma once
#include "Fecha.h"
class FacturaConsulta
{
public:
	FacturaConsulta();
	FacturaConsulta(Fecha fechaFactura, Fecha fechaTurno, int ID = 0, float precioConsulta=0, int IDPaciente = 0,
		int obraSocial = 0, int legajoAdministrativo = 0, int formaPago = 0, int legajoMedico=0);
	~FacturaConsulta();

	void setID(int id);
	void setPrecioConsulta(float precioConsulta);
	void setIDPaciente(int idPaciente);
	void setObraSocial(int obraSocial);
	void setFechaFactura(Fecha fechaFactura);
	void setFechaTurno(Fecha fechaTurno);
	void setLegajoAdministrativo(int legajoAdministrativo);
	void setFormaPago(int formaPago);
	void setLegajoMedico(int legajoMedico);

	int getID();
	float getPrecioConsulta();
	int getIDPaciente();
	int getObraSocial();
	Fecha getFechaFactura();
	Fecha getFechaTurno();
	int getLegajoAdministrativo();
	int getFormaPago();
	int getLegajoMedico();

	void Mostrar();
	bool leerDeDisco(int pos);
	bool grabarEnDisco(int pos = 0);

	bool leerCopiaDeDisco(int pos, const char* ruta);
	bool GrabarCopiaEnDisco(const char* ruta);

private:
	int _ID;
	float _precioConsulta;
	int _IDPaciente;
	int _obraSocial;
	Fecha _fechaFactura;
	Fecha _fechaTurno;
	int _legajoAdministrativo;
	int _formaPago;
	int _legajoMedico;
};



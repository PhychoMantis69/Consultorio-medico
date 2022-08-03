#include "FacturaConsulta.h"
#include <iostream>

using namespace std;

FacturaConsulta::FacturaConsulta() {
	_ID = 0;
	_precioConsulta = 0;
	_IDPaciente = 0;
	_obraSocial = 0;
	_legajoAdministrativo = 0;
	_formaPago = 0;
	_legajoMedico = 0;
}
FacturaConsulta::FacturaConsulta(Fecha fechaFactura, Fecha fechaTurno, int ID, float precioConsulta, int IDPaciente,
	int obraSocial, int legajoAdministrativo, int formaPago, int legajoMedico) {
	_ID = ID;
	_precioConsulta = precioConsulta;
	_IDPaciente = IDPaciente;
	_obraSocial = obraSocial;
	_fechaFactura = fechaFactura;
	_fechaTurno = fechaTurno;
	_legajoAdministrativo = legajoAdministrativo;
	_formaPago = formaPago;
	_legajoMedico = legajoMedico;
}
FacturaConsulta::~FacturaConsulta() {

}
void FacturaConsulta::setID(int id) {
	if (id > 0) {
		_ID = id;
	}
}
void FacturaConsulta::setPrecioConsulta(float precioConsulta) {
	if (precioConsulta > 0) {
		_precioConsulta = precioConsulta;
	}
}
void FacturaConsulta::setIDPaciente(int idPaciente) {
	if (idPaciente > 0 && idPaciente < 100000) {
		_IDPaciente = idPaciente;
	}
}
void FacturaConsulta::setObraSocial(int obraSocial) {
	if (obraSocial > 0 && obraSocial < 100) {
		_obraSocial = obraSocial;
	}
}
void FacturaConsulta::setFechaFactura(Fecha fechaFactura) {
	if (fechaFactura.getDia() > 0 && fechaFactura.getDia() <= 31) {
		if (fechaFactura.getMes() > 0 && fechaFactura.getMes() <= 12) {
			if (fechaFactura.getAnio() >= 2021 && fechaFactura.getAnio() < 2030) {
				_fechaFactura = fechaFactura;
			}
		}
	}
}
void FacturaConsulta::setFechaTurno(Fecha fechaTurno) {
	if (fechaTurno.getDia() > 0 && fechaTurno.getDia() <= 31) {
		if (fechaTurno.getMes() > 0 && fechaTurno.getMes() <= 12) {
			if (fechaTurno.getAnio() >= 2021 && fechaTurno.getAnio() < 2030) {
				_fechaTurno = fechaTurno;
			}
		}
	}
}
void FacturaConsulta::setLegajoAdministrativo(int legajoAdministrativo) {
	if (legajoAdministrativo > 0 && legajoAdministrativo < 100000) {
		_legajoAdministrativo = legajoAdministrativo;
	}
}
void FacturaConsulta::setFormaPago(int formaPago) {
	if (formaPago > 0 && formaPago <= 3) {
		_formaPago = formaPago;
	}
}
void FacturaConsulta::setLegajoMedico(int legajoMedico) {
	if (legajoMedico > 0 && legajoMedico < 100000) {
		_legajoMedico = legajoMedico;
	}
}
int FacturaConsulta::getID() {
	return _ID;
}
float FacturaConsulta::getPrecioConsulta() {
	return _precioConsulta;
}
int FacturaConsulta::getIDPaciente() {
	return _IDPaciente;
}
int FacturaConsulta::getObraSocial() {
	return _obraSocial;
}
Fecha FacturaConsulta::getFechaFactura() {
	return _fechaFactura;
}
Fecha FacturaConsulta::getFechaTurno() {
	return _fechaTurno;
}
int FacturaConsulta::getLegajoAdministrativo() {
	return _legajoAdministrativo;
}
int FacturaConsulta::getFormaPago() {
	return _formaPago;
}
int FacturaConsulta::getLegajoMedico() {
	return _legajoMedico;
}
void FacturaConsulta::Mostrar() {
	cout << "ID: " << _ID << endl;
	cout << "Precio de la consulta: $" << _precioConsulta << endl;
	cout << "ID del paciente: " << _IDPaciente << endl;
	cout << "Obra social: " << _obraSocial << endl;
	cout << "Legajo del medico: " << _legajoMedico << endl;
	cout << "Fecha de Factura: ";
	_fechaFactura.Mostrar();
	cout << "Fecha del turno: ";
	_fechaTurno.Mostrar();
	cout << "Legajo Usuario: " << _legajoAdministrativo << endl;
	cout << "Forma de Pago: " << _formaPago << endl;
}
bool FacturaConsulta::leerDeDisco(int pos) {
	FILE* p;
	p = fopen("FacturasConsultas.dat", "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(FacturaConsulta) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(FacturaConsulta), 1, p);
	fclose(p);
	return ok;
}
bool FacturaConsulta::grabarEnDisco(int pos) {
	FILE* p;
	if (pos == 0) {
		p = fopen("FacturasConsultas.dat", "ab");
		if (p == NULL) {
			return false;
		}
		bool ok;
		ok = fwrite(this, sizeof(FacturaConsulta), 1, p);
		fclose(p);
		return ok;
	}
	else {
		p = fopen("FacturasConsultas.dat", "rb+");
		if (p == NULL) {
			return false;
		}
		bool ok;
		fseek(p, sizeof(FacturaConsulta) * pos, 0);
		ok = fwrite(this, sizeof(FacturaConsulta), 1, p);
		fclose(p);
		return ok;
	}
}
bool FacturaConsulta::leerCopiaDeDisco(int pos, const char* ruta) {
	FILE* p;
	p = fopen(ruta, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, sizeof(FacturaConsulta) * pos, 0);
	bool ok;
	ok = fread(this, sizeof(FacturaConsulta), 1, p);
	fclose(p);
	return ok;
}
bool FacturaConsulta::GrabarCopiaEnDisco(const char* ruta) {
	FILE* p;
	p = fopen(ruta, "wb");
	if (p == NULL) {
		return false;
	}
	bool ok = fwrite(this, sizeof(FacturaConsulta), 1, p);
	fclose(p);
	return ok;
}
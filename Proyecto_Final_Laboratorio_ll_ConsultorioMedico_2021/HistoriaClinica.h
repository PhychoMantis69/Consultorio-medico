#pragma once
#include "Turno.h"
#include "Fecha.h"
#include "Hora.h"
class HistoriaClinica
{
public:
    HistoriaClinica();
    HistoriaClinica(int IDTurno, const char* detallesConsulta = "vacio");
    ~HistoriaClinica();


    void setIDTurno(int IDTurno);
    void setDetallesConsulta(char* detallesConsulta);


    int getIDTurno();
    char* getDetallesConsulta();

    void Mostrar();
    bool leerDeDisco(int pos);
    bool grabarEnDisco(int pos);
private:
    int _IDTurno;
    char _detallesConsulta[2000];
};


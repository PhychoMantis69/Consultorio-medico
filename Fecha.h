#pragma once
class Fecha
{
public:
    Fecha(int dia = 1, int mes = 1, int anio = 2000);
    ~Fecha();

    void setFecha(int dia, int mes, int anio);
    void setNombreDia(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();
    char* getNombreDia();
    int getNumeroDia();
    bool getFeriado();
    bool esFeriado(int dia, int mes);
    bool esCorrecta(int dia, int mes, int anio);
    bool esBisiesto(int anio);
    void Mostrar();
    bool operator > (Fecha& f);
    bool operator < (Fecha& f);
    bool operator ==(Fecha& f);
    //bool operator >=(Fecha& f);
    //bool operator <=(Fecha& f);

private:
    int _dia;
    int _mes;
    int _anio;
    char _nombreDia[10];
    int _numDia;
    bool _feriado;
};

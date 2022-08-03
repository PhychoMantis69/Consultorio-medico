#pragma once
class Direccion
{
public:
    Direccion(const char* calle = "vacio", const char* localidad = "vacio", const char* partido = "vacio",
        const char* provincia = "vacio", const char* codigoPostal = "vacio", const char* pais = "vacio");
    ~Direccion();

    void  setCalle(const char* calle);
    void  setLocalidad(const char* localidad);
    void  setPartido(const char* partido);
    void  setProvincia(const char* provincia);
    void  setCodigoPostal(const char* codigoPostal);
    void  setPais(const char* pais);


    char* getCalle();
    char* getLocalidad();
    char* getPartido();
    char* getProvincia();
    char* getCodigoPostal();
    char* getPais();

    void Mostrar();

private:
    char _calle[30];
    char _localidad[40];
    char _partido[30];
    char _provincia[30];
    char _codigoPostal[6];
    char _pais[30];
};
#pragma once
class Persona
{
public:
    Persona(int DNI = 0, const char* nombres = "vacio", const char* apellidos = "vacio");
    ~Persona();
    void setDNI(int dni);
    void setNombres(const char* nombres);
    void setApellidos(const char* apellidos);
    void setEdad(int edad);
    int getDNI();
    char* getNombres();
    char* getApellidos();
    int getEdad();
    void Mostrar();
    //void Modificadion();
protected:
    int  _DNI;
    char _nombres[50];
    char _apellidos[50];
    int  _edad;

};

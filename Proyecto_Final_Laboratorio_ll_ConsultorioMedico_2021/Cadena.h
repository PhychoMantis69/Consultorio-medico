#pragma once

class Cadena
{
public:
    /*Cadena(){
        tam=5;
        p=new char[tam];
        if(p==NULL)return;
        strcpy(p,"0000");
    }*/
    Cadena(const char* cad = "00:00");
    void Mostrar();
    void setValor(const char* cad);
    char *getCadena();
    ~Cadena();
private:
    char* p;
    int tam;
};



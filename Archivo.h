#pragma once
class Archivo
{
public:
	Archivo(const char* nombre = "xxx", bool estado = false);
	void setNombre(const char* nombre);
	void setEstado(bool estado);

	char* getNombre();
	bool getEstado();

	bool leerDeDisco(int pos, const char* ruta);
	bool grabarEnDisco(const char* ruta, int pos = 0);

	void Mostrar();
private:
	char _nombre[41];
	bool _estado;
};


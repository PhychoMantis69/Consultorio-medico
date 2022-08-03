#include "FuncionesGlobalesDeMenus.h"
#include "Direccion.h"
#include "Empleado.h"
#include "FacturaConsulta.h"
#include "Fecha.h"
#include "Fecha_Hora.h"
#include "HistoriaClinica.h"
#include "Hora.h"
#include "Paciente.h"
#include "Persona.h"
#include "Turno.h"
#include "Cadena.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <ctime> 
#include <fstream>
#include <Windows.h>

using namespace std;
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
bool esBisiesto(int anio) {
	if (anio % 4 == 0 && anio % 100 != 0 || anio % 400 == 0) {
		return true;
	}
	return false;
}

int dias_mes(int mes, int anio) {
	int dias = 31;
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		dias = 30;
	}
	else if (mes == 2) {
		if (esBisiesto(anio)) {
			dias = 29;
		}
		else {
			dias = 28;
		}
	}
	return dias;
}
void cargarHorarios(Hora *vHorarios) {
	int nro, aux=0;
	for (int i = 0; i < 19; i+=2)
	{
			vHorarios[i].setHora(aux + 8);
			vHorarios[i].setMinuto(0);
			vHorarios[i + 1].setHora(aux + 8);
			vHorarios[i + 1].setMinuto(30);
			aux++;
	}
}
void cargarFechaHoy(Fecha& fechaHoy) {
	int dia, mes, anio;
	time_t t;
	struct tm* f;
	time(&t);
	f = localtime(&t);
	dia = (f->tm_mday);
	mes = (f->tm_mon + 1);
	anio = (f->tm_year + 1900);
	fechaHoy.setFecha(dia, mes, anio);
}
void cargarFechaMax(Fecha& fechaMax, Fecha& fechaHoy, Fecha* vFechas) {
	int dia = fechaHoy.getDia();
	int mes = fechaHoy.getMes();
	int anio = fechaHoy.getAnio();
	for (int i = 0; i < 59; i++) {
		dia++;
		if (dia > dias_mes(mes, anio)) {
			dia = 1;
			mes++;
			if (mes > 12) {
				mes = 1;
				anio++;
			}
		}
		vFechas[i].setFecha(dia, mes, anio);
	}
	fechaMax.setFecha(dia, mes, anio);
}
bool estaEnRangoFecha(int dia, int mes, int anio, Fecha* vFechas) {
	Fecha aux(dia,mes);
	if (aux.esFeriado(dia, mes))return false;
	for (int i = 0; i < 59; i++)
	{
		if (vFechas[i].getDia() == dia && vFechas[i].getMes() == mes && vFechas[i].getAnio() == anio) {
			return true;
		}
	}
	return false;
}
bool buscarLegajoMedico(int legajoMedico, Turno& t) {
	Empleado reg;
	int pos = 0;
	while (reg.leerDeDisco(pos)) {
		if (reg.getTipoEmpleado()==2 && reg.getLegajo()==legajoMedico) {
			t.setLegajoMedico(legajoMedico);
			return true;
		}
		pos++;
	}
	return false;
}
bool existeEspecialidad(int especialidad, Turno& t) {
	Empleado reg;
	int pos = 0;
	while (reg.leerDeDisco(pos))
	{
		if (reg.getEspecialidad().getNEspecialidades() == especialidad) {
			t.setLegajoMedico(reg.getLegajo());
			return true;
		}
		pos++;
	}
	return false;
}
bool noSeRepiteIDTurno(int nro) {
	Turno obj;
	int pos = 0;
	while (obj.leerDeDisco(pos++))
	{
		if (nro == obj.getID()) {
			return false;
		}
	}
	return true;
}
int generarIDTurno() {
	int nro, desde=1, hasta=100000;
	srand(time(NULL));
	while (true)
	{
		nro = rand() % (hasta - desde + 1) + desde;
		if (noSeRepiteIDTurno(nro)) {
			return nro;
		}
	}
}
bool empleadoOcupado(Turno& b) {
	Turno aux;
	int pos = 0;
	while (aux.leerDeDisco(pos))
	{
		if (aux.getFechaTurno().getDia() == b.getFechaTurno().getDia() && aux.getFechaTurno().getMes() == b.getFechaTurno().getMes() &&
			aux.getFechaTurno().getAnio() == b.getFechaTurno().getAnio()) {
			if (aux.getLegajoMedico() == b.getLegajoMedico() && aux.getEstado() == true) {
				if (aux.getHoraTurno().getHora() == b.getHoraTurno().getHora() && aux.getHoraTurno().getMinuto()
					== b.getHoraTurno().getMinuto()) {
					return true;
				}
			}
		}
		pos++;
	}
	return false;
}
void MostrarTurnosPorMedico(Fecha f, Turno *vTurnosDia, int tam, Turno *vTurnosOk) {
	int b=0, a=0, hora, minuto, dia ,mes, anio;
	for (int i = 0; i < tam; i++)
	{
		if (vTurnosDia[i].getEstado() == true) {
			b++;
		}
	}
	if (b == tam-1) {
		cout << "No hay turnos disponibles." << endl;
		return;
	}
	cout << "Turnos disponibles desde el " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ": " << endl;
	for (int i = 0; i < tam; i++)
	{
		if (!vTurnosDia[i].getEstado()/* && !vTurnosDia[i].getFechaTurno().esFeriado()*/) {
			vTurnosOk[a] = vTurnosDia[i];
			a++;
			cout << a << ". ";
			hora = vTurnosDia[i].getHoraTurno().getHora();
			minuto = vTurnosDia[i].getHoraTurno().getMinuto();
			dia = vTurnosDia[i].getFechaTurno().getDia();
			mes = vTurnosDia[i].getFechaTurno().getMes();
			anio = vTurnosDia[i].getFechaTurno().getAnio();
			Fecha_Hora FH(hora, minuto, dia, mes, anio);
			FH.Mostrar();
		}
		if (a == 20) return;
	}

}
bool nextDia(Fecha& f, Fecha *vFechas) {
	int tam = 0;
	Fecha aux = f;
	int dia = aux.getDia();
	int mes = aux.getMes();
	int anio = aux.getAnio();
	if (aux.getNumeroDia() == 5) {
		tam = 3;
	}
	else {
			tam = 1;
	}
	for (int i = 0; i < tam; i++)
	{
		dia++;
		if (dia > dias_mes(mes, anio)) {
			dia = 1;
			mes++;
			if (mes > 12) {
				mes = 1;
				anio++;
			}
		}
		if (aux.getNumeroDia()<5 && aux.esFeriado(dia,mes))
		{
			i--;
		}

	}
	if (estaEnRangoFecha(dia, mes, anio, vFechas)) {
		f.setFecha(dia, mes, anio);
		return true;
	}
	return false;
}

int nroDiaEnRango(Fecha* vFechas, Fecha& f, Fecha& aux) {
	int cont = 0;
	for (int i = 0; i < 60; i++)
	{
		cont++;
		if (vFechas[i].getDia() == f.getDia() && vFechas[i].getMes() == f.getMes() && vFechas[i].getAnio() == f.getAnio()) {
			aux.setFecha(f.getDia(), f.getMes(), f.getAnio());
			return cont;
		}
	}
}
bool opcionValida(int opcion) {
	if (opcion >= 1 && opcion <= 20)return true;
	return false;
}
void turnosDisponiblesPorMedico(int legajoMedico, Fecha& f, Hora* vHorarios, Turno& t, Fecha* vFechas) {
	Turno vTurnosOk[20];
	Hora h;
	Fecha aux;
	int pos = 0, opcion, a = 1;
	int cont = nroDiaEnRango(vFechas,f,aux);
	bool b = true;
	int tam = ((60 - cont)) * 20;
	Turno* vTurnosDia = new Turno[tam];
	for (int i = 0; i < tam; i++){
		if (a == 21) {
			nextDia(aux, vFechas);
			a = 1;
		}
		vTurnosDia[i].setFechaTurno(aux);
		h.setHora(vHorarios[a - 1].getHora());
		h.setMinuto(vHorarios[a - 1].getMinuto());
		vTurnosDia[i].setHoraTurno(h);
		vTurnosDia[i].setLegajoMedico(legajoMedico);
		a++;
		Turno b = vTurnosDia[i];
			if (empleadoOcupado(b)) {
				vTurnosDia[i].setEstado(true);
			}
			else {
					vTurnosDia[i].setEstado(false);
			}
	}

	while (true)
	{
		system("cls");
		MostrarTurnosPorMedico(f, vTurnosDia, tam, vTurnosOk);

		cout << "Elija una fecha y horario: ";
		cin >> opcion;
		if (opcionValida(opcion)) {
			Hora h1;
			int dia, mes, anio;
			h1.setHora(vTurnosOk[opcion - 1].getHoraTurno().getHora());
			h1.setMinuto(vTurnosOk[opcion - 1].getHoraTurno().getMinuto());
			dia = vTurnosOk[opcion - 1].getFechaTurno().getDia();
			mes = vTurnosOk[opcion - 1].getFechaTurno().getMes();
			anio = vTurnosOk[opcion - 1].getFechaTurno().getAnio();
			aux.setFecha(dia, mes, anio);
			t.setHoraTurno(h1);
			t.setFechaTurno(aux);
			t.setEstado(true);
			break;
		}
		else {
			cout << "Opcion Incorrecta. Vuelva a intentar." << endl;
			system("pause");
			continue;
		}
	}
}

void AsignarTurno() {
	int dia, mes, anio, hora, minuto, idTurno, idPaciente, DNIPaciente, obraSocial, especialidad = -1, legajoMedico = 0, opcion, opcionTurnoDia;
	bool b = false, x = false, b1 = true;
	Turno t;
	Fecha f, fechaAsignacion, fechaHoy, fechaMax;

	Fecha vFechas[60];
	Hora h;
	Hora vHorarios[20];
	cargarHorarios(vHorarios);
	cargarFechaHoy(fechaHoy);
	cargarFechaMax(fechaMax, fechaHoy, vFechas);
	while (true)
	{
		system("cls");
		cout << "Solo puede asignar turnos hasta el: ";
		fechaMax.Mostrar();
		cout << endl;
		cout << "Asignar turnos por: " << endl;
		cout << "1. Medico." << endl;
		cout << "2.Especialidad." << endl;
		cout << "---------------------------------" << endl;
		cout << "Ingrese opcion: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			system("cls");
			cout << "Ingrese legajo del Medico: ";
			cin >> legajoMedico;
			if (!buscarLegajoMedico(legajoMedico, t))
			{
				b1 = false;
				cout << "El legajo no existe. " << endl;
				system("pause");

			}
			else {
				while (true) {
					system("cls");
					cout << "Ingrese dia: ";
					cin >> dia;
					cout << "Ingrese mes: ";
					cin >> mes;
					cout << "Ingrese anio: ";
					cin >> anio;
					if (f.esCorrecta(dia, mes, anio)) {
						f.setFecha(dia, mes, anio);
					}
					if (estaEnRangoFecha(dia, mes, anio, vFechas)) {
						b = true;
						if (legajoMedico != 0) {
							turnosDisponiblesPorMedico(legajoMedico, f, vHorarios, t, vFechas);
						}
						x = true;
						//cout << "Ingrese ID Paciente: ";
						//cin >> idPaciente;
						cout << "Ingrese DNI del Paciente: ";
						cin >> DNIPaciente;
                        if (!existeDNI(DNIPaciente)) {
                            cout << "El DNI no se encuentra registrado en la base de pacientes." << endl;
                            cin.ignore();
                            AgregarPaciente(DNIPaciente);

                        }
						cout << "Ingrese Obra Social: ";
						cin >> obraSocial;
						t.setFechaAsignacionTurno();
						t.setID(generarIDTurno());

						t.setIDPaciente(obtenerID(DNIPaciente));
						//t.setDNIPaciente(DNIPaciente);
						t.setObraSocial(obraSocial);
						//t.setEspecialidad(especialidad);
						t.setFechaTurno(f);
						//t.setLegajoMedico(legajoMedico);
						t.setEstado(true);
						if (t.grabarEnDisco(0)) {
							cout << "El turno ha sido reservado." << endl;
                            //system("pause");
							return;
						}

					}
					else if (!b) {
						cout << "La fecha ingresada se encuentra fuera del rango permitido. Ingrese nuevamente." << endl;
						system("pause");
						continue;
					}
					/*if (b && !x) {
						cout << "Ya existe un turno asignado en ese rango de fecha, ingrese nuevamente." << endl;
						system("pause");
					}*/
				}
			}
			break;
		case 2:
			cout << "Ingrese especialidad: ";
			cin >> especialidad;
			if (!existeEspecialidad(especialidad, t)) {
				cout << "La especialidad no existe." << endl;
				system("pause");
				break;
			}
			break;
		case 0:
			return;
			break;
		default:
			cout << "Opcion incorrecta. Vuelta a intentarlo." << endl;
			break;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
bool existeDNI(int dni) {
    Paciente reg;
    int pos = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (dni == reg.getDNI()) {
            return true;
        }
    }
    return false;
}

int obtenerID(int dni) {
    Paciente reg;
    int pos = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (dni == reg.getDNI()) {
            return reg.getID();
        }
    }
    return -1;
}
bool existeTurno(Turno& t, int dni, Fecha& f) {
    int pos = 0;
    int id = obtenerID(dni);
    if (id == -1) return false;
    while (t.leerDeDisco(pos++))
    {
        if (id == t.getIDPaciente() && t.getFechaTurno().getDia() == f.getDia() && t.getFechaTurno().getMes() == f.getMes()
            && t.getFechaTurno().getAnio() == f.getAnio()) {
            return true;
        }
    }
    return false;
}
void modificarTurnoPaciente(Turno& t) {
    Turno aux;
    int pos = 0;
    while (aux.leerDeDisco(pos++))
    {
        if (t.getIDPaciente() == aux.getIDPaciente()) {
            aux = t;
            aux.grabarEnDisco(pos);
        }
        return;
    }
}
void modificarTurnoDNI(Turno& t) {
    Paciente reg;
    int DNI;
    while (true)
    {
        cout << "Ingrese el nuevo DNI: ";
        cin >> DNI;
        if (existeDNI(DNI)) {
            t.setIDPaciente(obtenerID(DNI));
            return;
        }
        else {
            cout << "El DNI no existe en la base de pacientes. Ingrese de nuevo." << endl;
            system("pause");
        }
        system("cls");
    }
}
void modificarFechaTurno(Turno& t) {
    Fecha aux, vFechas[60], fechaHoy, fechaMax;
    Hora vHorarios[20], h;
    int dia, mes, anio;
    while (true)
    {
        cout << "Ingrese la nueva fecha del turno: " << endl;
        cout << "Dia: ";
        cin >> dia;
        cout << "Mes";
        cin >> mes;
        cout << "Anio: ";
        cin >> anio;
        if (aux.esCorrecta(dia, mes, anio)) {
            aux.setFecha(dia, mes, anio);
            break;
        }
        else {
            cout << "Error. Vuelva a introducir fecha." << endl;
            system("pause");
            //continue;
        }
    }
        cargarHorarios(vHorarios);
        cargarFechaHoy(fechaHoy);
        cargarFechaMax(fechaMax, fechaHoy, vFechas);
        system("cls");
        cout << "Solo puede asignar turnos hasta el: ";
        fechaMax.Mostrar();
        turnosDisponiblesPorMedico(t.getLegajoMedico(), aux, vHorarios, t, vFechas);

}

//ESTA FUNCION PERTENECE AL MENU ADMINISTRATIVO.--------------
//todo: hay que corregir bugs..ya que no se modifica el turno..sino que se crea otro...y el anterior sigue activo
void ModificarTurno()
{
    Fecha f;
    Turno t;
    int pos = 0, dni/*, ID*/, opcion, dia, mes, anio;
    while (true)
    {
        system("cls");
        cout << "Ingrese DNI del paciente: ";
        cin >> dni;
        if (existeDNI(dni)) {
            cout << "Ingrese dia de turno:";
            cin >> dia;
            cout << "Ingrese mes de turno:";
            cin >> mes;
            cout << "Ingrese anio de turno:";
            cin >> anio;
            if (f.esCorrecta(dia, mes, anio)) {
                Fecha f(dia, mes, anio);
                if (existeTurno(t, dni, f)) {
                    while (true) {
                        system("cls");
                        cout << "MODIFICACION DE TURNO." << endl;
                        cout<<"------------------------------------" << endl;
                        cout << "1. Modificar DNI: " << endl;
                        cout << "2. Modificar fecha: " << endl;
                        cout << "0. Salir. " << endl << endl;
                        cin >> opcion;

                        switch (opcion) {
                        case 1:
                            system("cls");
                            modificarTurnoDNI(t);
                            modificarTurnoPaciente(t);
                            cout << "Turno modificado!" << endl;
                            return;
                        case 2:
                            system("cls");
                            modificarFechaTurno(t);
                            modificarTurnoPaciente(t);
                            cout << "Turno modificado!" << endl;
                            return;
                        case 0:
                            return;
                        default:
                            system("cls");
                            cout << "Opcion incorrecta. Vuelva a intentarlo." << endl;
                            system("pause");
                            break;
                        }
                    }
                    //modificarTurnoPaciente(t);
                    //cout << "Turno modificado!" << endl;
                    //return;
                }
                else {
                    cout << "Este paciente no tiene un turno asignado en esta fecha." << endl;
                    system("pause");
                }
                continue;
            }
            else {
                cout << "Fecha incorrecta. Vuelva a intentar." << endl;
                system("pause");
                continue;
            }
        }
        else {
            cout << "No existe DNI. Ingrese nuevamente." << endl;
            system("pause");
            continue;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void eliminarTurnoPaciente(Turno& t) {
    Turno aux;
    int pos = 0;
    while (aux.leerDeDisco(pos++))
    {
        if (t.getIDPaciente() == aux.getIDPaciente()) {
            aux = t;
            aux.setEstado(false);
            aux.grabarEnDisco(pos);
            return;
        }
    }
}
//todo: modificar esta funcion que fue copiada de modificar turno
void EliminarTurno() {
    Fecha f;
    Turno t;
    int pos = 0, dni/*, ID*/, opcion, dia, mes, anio;
    while (true)
    {
        cout << "Ingrese DNI del paciente: ";
        cin >> dni;
        if (existeDNI(dni)) {
            cout << "Ingrese dia de turno:";
            cin >> dia;
            cout << "Ingrese mes de turno:";
            cin >> mes;
            cout << "Ingrese anio de turno:";
            cin >> anio;
            if (f.esCorrecta(dia, mes, anio)) {
                Fecha f(dia, mes, anio);
                if (existeTurno(t, dni, f)) {
                    eliminarTurnoPaciente(t);
                    cout << "Turno modificado!" << endl;
                    return;
                }
                else {
                    cout << "Este paciente no tiene un turno asignado en esta fecha." << endl;
                    system("pause");
                }
                continue;
            }
            else {
                cout << "Fecha incorrecta. Vuelva a intentar." << endl;
                system("pause");
                continue;
            }
        }
        else {
            cout << "No existe DNI. Ingrese nuevamente." << endl;
            system("pause");
            continue;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
bool noSeRepiteIDPaciente(int nro) {
    Paciente obj;
    int pos = 0;
    while (obj.leerDeDisco(pos++))
    {
        if (nro == obj.getID()) {
            return false;
        }
    }
    return true;
}
//todo: hacerlo autonumerico(1,2,3...etc)..tambien con turnos
int generarIDPaciente() {
    int nro, desde = 1, hasta = 100000;
    srand(time(NULL));
    while (true)
    {
        nro = rand() % (hasta - desde + 1) + desde;
        if (noSeRepiteIDPaciente(nro)) {
            return nro;
        }
    }
}

bool noExistePaciente(int dni) {
    Paciente obj;
    int pos = 0;
    while (obj.leerDeDisco(pos++))
    {
        if (obj.getDNI() == dni)return false;
    }
    return true;
}

int obtenerEdad(Fecha& f) {
    int dia = f.getDia();
    int mes = f.getMes();
    int anio = f.getAnio();
    int diaActual, mesActual, anioActual, edad;
    time_t now;
    struct tm* now_tm;
    now = time(NULL);
    now_tm = localtime(&now);

    diaActual = now_tm->tm_mday;
    mesActual = now_tm->tm_mon + 1;
    anioActual = now_tm->tm_year;
    anioActual += 1900;

    edad = anioActual - anio;
    if (mesActual < mes) {
        edad--;
    }
    else if (mesActual == mes) {
        if (diaActual < dia)edad--;
    }
    return edad;
}

void AgregarPaciente(int dni) {
    Paciente reg;
    Direccion d;
    Fecha f;
    int dia, mes, anio;
    char nombres[50], apellidos[50], telefono[30], email[50], calle[30], localidad[40], partido[30],
        provincia[30], codigoPostal[30], pais[30] = { "Argentina" };
    if (dni==0)
    {
        while (true)
        {
            system("cls");
            cout << "Ingrese los datos del nuevo paciente: " << endl;
            cout << "DNI: ";
            cin >> dni;
            cin.ignore();
            if (noExistePaciente(dni)) {
                break;
            }
            else {
                cout << "El DNI ingresado ya existe en la base de pacientes." << endl;
                system("pause");
            }
        }
    }
    
    cout << "Nombre/s: ";
    cargarCadena(nombres, 49);
    cout << "Apellido/s: ";
    cargarCadena(apellidos, 49);
    cout << "Ingrese fecha de nacimiento:" << endl;
    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    cin.ignore();
    if (f.esCorrecta(dia, mes, anio)) {
        f.setFecha(dia, mes, anio);
    }
    cout << "Telefono: ";
    cargarCadena(telefono, 29);
    cout << "Email: ";
    cargarCadena(email, 49);
    cout << "Calle: ";
    cargarCadena(calle, 29);
    cout << "Localidad: ";
    cargarCadena(localidad, 39);
    cout << "Partido: ";
    cargarCadena(partido, 29);
    cout << "Provincia: ";
    cargarCadena(provincia, 29);
    cout << "Codigo Postal: ";
    cargarCadena(codigoPostal, 29);

    reg.setDNI(dni);
    reg.setNombres(nombres);
    reg.setApellidos(apellidos);
    reg.setEdad(obtenerEdad(f));
    reg.setID(generarIDPaciente());
    reg.setFechaNac(f);
    reg.setTelefono(telefono);
    reg.setEmail(email);
    d.setCalle(calle);
    d.setLocalidad(localidad);
    d.setPartido(partido);
    d.setProvincia(provincia);
    d.setCodigoPostal(codigoPostal);
    d.setPais(pais);
    reg.setDireccionPaciente(d);
    reg.setEstado(true);
    if (reg.GrabarEnDisco()) {
        cout << "Paciente agregado al sistema." << endl;
    }
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


///Validacion de la parte de medico
/*Turno aux;
aux = t; ///Esto hace una copia del objeto t a aux
int Pos = 0;
int TurnoYaExiste = 0;
while (t.leerDeDisco(Pos) == true)
{
	///Aca pregunta si ya hay un registro de turno guardado que tenga la especialidad
	///que se ingresa por teclado,y si lo hay, entonces entra al if
	if (t.getEspecialidad() == especialidad)
	{
		///Aca pregunta si el dia, mes y el anio del registro son iguales a los que se ingreesan por teclado
		if (t.getFechaTurno().getMes() == mes && t.getFechaTurno().getDia() == dia && t.getFechaTurno().getAnio() == anio)
		{
			///Y aca pregunta si la hora y los minutos del registro son iguales a los que se ingresan por teclado
			if (t.getHoraTurno().getHora() == hora && t.getHoraTurno().getMinuto() == minuto)
			{
				TurnoYaExiste++; ///Si todo lo anterior es verdadero, es porque ya existe un turno para
								 ///esa especialidad en la fecha que se ingresa por teclado
			}
		}
	}
	Pos++;
}

if (TurnoYaExiste == 0)
{
	cout << "HAY TURNO DISPOBIBLE PARA LA ESPECIALIDAD Y FECHA INGRESADA" << endl;
	if (aux.grabarEnDisco(0) == true) {
		cout << "TURNO AGREGADO CORRECTAMENTE" << endl;
	}

}

else
{
	cout << "YA HAY UN TURNO PARA ESA ESPECIALIDAD EN LA FECHA QUE INGRESO, INTENTE CON OTRA FECHA" << endl;
}*/


///Cuenta y devuelve la cantidad de registros que hay en el archivo de pacientes
int ContarCantidadRegistrosPacientes()
{

    Paciente reg;
    int pos = 0;
    while (reg.leerDeDisco(pos) == true)
    {
        pos++;

    }

    return pos;
}

int ContarCantidadRegistrosEmpleados()
{
    Empleado reg;
    int pos = 0;
    int Cont = 0; ///CUENTA LA CANTIDAD DE VECES QUE ENCUENTRE UN REGISTRO CON NUMERO DE EMPLEADO = 1 (Administrativo)
    while (reg.leerDeDisco(pos) == true)
    {
        if (reg.getTipoEmpleado() == 1)
        {
            Cont++;
        }
        pos++;
    }
    return Cont;


}


int ContarCantidadRegistroTurnos()
{

    Turno reg;
    int pos = 0;
    while (reg.leerDeDisco(pos) == true)
    {
        pos++;
    }
    return pos;


}

void CopiarRegistros(Paciente* p, int cantRegistros)
{
    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].leerDeDisco(x);

    }

}


void CopiarRegistrosEmpleadoAdminitrativo(Empleado* p, int cantRegistros)
{
    Empleado reg;
    int Indice = 0;
    int Pos = 0;
    while (reg.leerDeDisco(Pos) == true)
    {
        if (reg.getTipoEmpleado() == 1)
        {
            p[Indice] = reg;
            Indice++;
        }
        Pos++;
    }

}

void CopiarRegistrosTurnos(Turno* p, int cantRegistros)
{

    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].leerDeDisco(x);

    }

}


///Ordena el vector de pacientes por apellido en orden alfabetico
void OrdenarRegistrosPorNombre(Paciente* p, int cantRegistros)
{

    int i, j;

    Paciente aux;

    for (i = 0; i < cantRegistros; i++)
    {

        for (j = 0; j < cantRegistros - 1; j++)
        {
            if (strcmp(p[j].getApellidos(), p[j + 1].getApellidos()) > 0)
            {

                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }
}


void OrdenarRegistrosAdminitrativoPorLegajo(Empleado* p, int cantRegistros)
{

    int i, j;

    Empleado aux;

    for (i = 0; i < cantRegistros; i++)
    {

        for (j = 0; j < cantRegistros - 1; j++)
        {
            if (p[j].getLegajo() < p[j + 1].getLegajo())
            {

                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }

}


void OrdenarRegistrosAdminitrativoPorNombre(Empleado* p, int cantRegistros)
{

    int i, j;

    Empleado aux;

    for (i = 0; i < cantRegistros; i++)
    {

        for (j = 0; j < cantRegistros - 1; j++)
        {
            if (strcmp(p[j].getApellidos(), p[j + 1].getApellidos()) > 0)
            {

                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }

}

void OrdenarTurnosPorFecha(Turno* p, int cantRegistros)
{

    int i, j;

    Turno aux;
    Fecha f1;

    for (i = 0; i < cantRegistros; i++)
    {

        for (j = 0; j < cantRegistros - 1; j++)
        {

            f1 = p[j + 1].getFechaTurno();
            if (p[j].getFechaTurno() < f1)
            {

                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }

}


void MostrarPacientes(Paciente* p, int cantRegistros)
{

    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].Mostrar();
        cout << endl;
    }

}


void MostrarEmpleadosAdministrativos(Empleado* p, int cantRegistros)
{

    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].Mostrar();
        cout << endl;
    }

}

void MostrarTurnos(Turno* p, int cantRegistros)
{
    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].Mostrar();
        cout << endl;
    }

}


///NO ESTA COMPLETO, PORQUE PACIENTE NO TIENE NINGUN ATRIBUTO QUE SEA LA EDAD DEL PACIENTE
void OrdenarRegistrosPorEdad(Paciente* p, int cantRegistros)
{
    ///ACA USO EL ALGORITMO DE BURBUJA PARA ORDENAR A LOS PACIENTES POR LA EDAD
    int i, j;
    Paciente aux;

    for (i = 0; i < cantRegistros; i++)
    {
        for (j = 0; j < cantRegistros - 1; j++)
        {

            if (p[j].getEdad() < p[j + 1].getEdad())
            {
                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;

            }

        }
    }
}


void OrdenarRegistrosPorCiudad(Paciente* p, int cantRegistros)
{



    int i, j;
    Paciente aux;

    for (i = 0; i < cantRegistros; i++)
    {
        for (j = 0; j < cantRegistros - 1; j++)
        {
            if (strcmp(p[j].getDireccionPaciente().getLocalidad(), p[j + 1].getDireccionPaciente().getLocalidad()) > 0)
            {
                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }
}

///OBTRNER MINIMO, BUSCA UN REGISTRO QUE CONTENGA EL ANIO MINIMO EN EL ARCHIVO, facturaconsulta
int BuscarAnioMinFactura()
{

    FacturaConsulta reg;

    int b = 0;
    int AnioMin = 0;
    int Pos = 0;

    while (reg.leerDeDisco(Pos) == true)
    {
        if (b == 0)
        {
            AnioMin = reg.getFechaFactura().getAnio();
            b++;
        }

        else
        {
            if (reg.getFechaFactura().getAnio() < AnioMin)
            {
                AnioMin = reg.getFechaFactura().getAnio();
            }
        }
        Pos++;
    }
    return AnioMin;
}

///OBTRNER MAXIMO
int BuscarAnioMaxFactura()
{

    FacturaConsulta reg;
    int Pos = 0, b = 0;
    int AnioMax = 0;
    while (reg.leerDeDisco(Pos) == true)
    {

        if (b == 0)
        {
            AnioMax = reg.getFechaFactura().getAnio();
            b++;
        }

        else
        {
            if (reg.getFechaFactura().getAnio() > AnioMax)
            {
                AnioMax = reg.getFechaFactura().getAnio();
            }
        }

        Pos++;
    }

    return AnioMax;
}








//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//ESTA FUNCION PERTENECE ListadoDePacientes
void ListadoDePacientesPorApellido()
{
    int cantRegistros;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    ///Se puede hacer con ftell
    cantRegistros = ContarCantidadRegistrosPacientes();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS EN EL ARCHIVO DE PACIENTES, O EL ARCHIVO NO EXISTE" << endl;
        return;
    }

    Paciente* p;
    p = new Paciente[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE PACIENTES" << endl;
        return;
    }

    ///Esta funcion copia todos los registros del archivo de pacientes a un vector de pacientes
    CopiarRegistros(p, cantRegistros);

    OrdenarRegistrosPorNombre(p, cantRegistros);

    MostrarPacientes(p, cantRegistros);

   // delete p; //Comente este delete porque sino el programa me hacia un return raro

}




///ESTA FUNCION PERTENECE ListadoDePacientes
void PorEdad()
{

    int cantRegistros = 0;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    cantRegistros = ContarCantidadRegistrosPacientes();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS EN EL ARCHIVO DE PACIENTES, O EL ARCHIVO NO EXISTE" << endl;
        return;
    }

    Paciente* p;
    p = new Paciente[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE PACIENTES" << endl;
        return;
    }



    ///Esta funcion copia todos los registros del archivo de pacientes a un vector de pacientes
    CopiarRegistros(p, cantRegistros);

    ///ORDENA LOS PACIENTE POR EDAD DE MAYOR A MENOR, USA EL MOTODO BURBUJA
    OrdenarRegistrosPorEdad(p, cantRegistros);

    MostrarPacientes(p, cantRegistros);

    ///delete p; Comente este delete porque sino el programa me hacia un return raro
}

///ESTA FUNCION PERTENECE ListadoDePacientes
void PorCiudad()
{

    int cantRegistros;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    cantRegistros = ContarCantidadRegistrosPacientes();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS EN EL ARCHIVO DE PACIENTES, O EL ARCHIVO NO EXISTE" << endl;
        return;
    }

    Paciente* p;
    p = new Paciente[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE PACIENTES" << endl;
        return;
    }

    ///Esta funcion copia todos los registros del archivo de pacientes a un vector de pacientes
    CopiarRegistros(p, cantRegistros);

    OrdenarRegistrosPorCiudad(p, cantRegistros);

    MostrarPacientes(p, cantRegistros);


    //delete p;

}

///--------------------------------------------
///NO ESTA TERMINADA
void ListadoAdministrativosOrdenadoPorLegajo()
{

    int cantRegistros;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    cantRegistros = ContarCantidadRegistrosEmpleados();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE ADMINISTRATIVOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* p;
    p = new Empleado[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }

    CopiarRegistrosEmpleadoAdminitrativo(p, cantRegistros);

    OrdenarRegistrosAdminitrativoPorLegajo(p, cantRegistros);

    MostrarEmpleadosAdministrativos(p, cantRegistros);


    //delete p;


}


void ListadoAdministrativosOrdenadoPorNombre()
{

    int cantRegistros;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    cantRegistros = ContarCantidadRegistrosEmpleados();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE ADMINISTRATIVOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* p;
    p = new Empleado[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }

    CopiarRegistrosEmpleadoAdminitrativo(p, cantRegistros);

    OrdenarRegistrosAdminitrativoPorNombre(p, cantRegistros);

    MostrarEmpleadosAdministrativos(p, cantRegistros);

    //delete p;


}


void ListadoDeTurnosOrdenadosPorFecha()
{

    int cantRegistros;
    ///Cuenta la cantidad de registros que hay en el archivo de paciente
    cantRegistros = ContarCantidadRegistroTurnos();

    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE ADMINISTRATIVOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Turno* p;
    p = new Turno[cantRegistros];

    if (p == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }

    CopiarRegistrosTurnos(p, cantRegistros);

    OrdenarTurnosPorFecha(p, cantRegistros);

    MostrarTurnos(p, cantRegistros);

    ///delete p;
}


void ListadoDeTurnosOrdenadosPorEspecialidad()
{




}


///------------------------------------------------------------------

///ESTA FUNCION PERTENECE A ConsultaDePaciente, no tenia que hacerlo yo xd
void ConsultaPorDni()
{

    int DNI;

    cout << "Ingrese el Dni del paciente que desea buscar" << endl;
    cin >> DNI;
    cout << endl;

    Paciente reg;

    int Pos = 0;
    while (reg.leerDeDisco(Pos) == true)
    {

        if (reg.getDNI() == DNI)
        {
            reg.Mostrar();
            return;
        }
        Pos++;
    }
    cout << "No existe ningun paciente con ese Dni" << endl;

}

///----------------------------------------------------------------

///ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorRangoFecha()
{


    Fecha fecha1;
    int Dia_Inicial = 1;
    int Mes_Inicial;
    int Anio_Inicial;
    Fecha fecha2;
    int Dia_Final;
    int Mes_Final;
    int Anio_Final;
    while (Dia_Inicial != 0)
    {


        int Cont = 0;
        cout << "---------------BUSCAR PAGO POR RANGO DE FECHA---------------" << endl; ///Esto no se si dejarlo o sacarlo

        cout << "Ingrese el dia, el mes y el anio de la fecha inicial (Ingrese un dia inicial igual a 0 para volver al menu)" << endl;
        cout << "Ingrese el dia: ";
        cin >> Dia_Inicial;

        if (Dia_Inicial != 0)
        {
            cout << "Ingrese el mes: ";
            cin >> Mes_Inicial;
            cout << "Ingrese el anio: ";
            cin >> Anio_Inicial;
            cout << endl;
            cout << "Ingrese el dia, el mes y el anio de la fecha final" << endl;
            cout << "Ingrese el dia: ";
            cin >> Dia_Final;
            cout << "Ingrese el mes: ";
            cin >> Mes_Final;
            cout << "Ingrese el anio: ";
            cin >> Anio_Final;
            cout << endl;







            FacturaConsulta reg;

            int Pos = 0;
            while (reg.leerDeDisco(Pos) == true)
            {

                if (reg.getFechaFactura() > fecha1 && reg.getFechaFactura() < fecha2)
                {
                    Cont++;
                    reg.Mostrar();
                    cout << endl;
                }
                Pos++;
            }

            if (Cont == 0)
            {
                cout << "NO EXISTE UN PAGO QUE SE ENCUENTRE DENTRO DEL RANGO DE LAS DOS FECHAS INGRESADAS, INGRESE OTRAS FECHAS" << endl << endl;
            }

            system("pause");
            system("cls");

        }

    }





}


///ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorCliente()
{
    int DniPaciente =1 ;
    

    while (DniPaciente != 0)
    {
        int Cont = 0;
        cout << "---------------BUSCAR PAGO POR CLIENTE---------------" << endl; ///Esto no se si dejarlo o sacarlo

        cout << "Ingrese el DNI del paciente que desea buscar (ingrese 0 para volver al menu)" << endl;
        cin >> DniPaciente;
        cout << endl;

        if (DniPaciente != 0)
        {

            FacturaConsulta reg;

            int Pos = 0;
            while (reg.leerDeDisco(Pos) == true)
            {

                if (reg.getDniPaciente() == DniPaciente)
                {

                    Cont++;
                    reg.Mostrar();
                    cout << endl;

                }
                Pos++;
            }

            if (Cont == 0)
            {
                cout << "NO EXISTE UN PAGO CON ESE NUMERO DE DNI, INTENTE CON OTRO NUMERO" << endl << endl;
            }

            system("pause");
            system("cls");
        }

    }

}

///ESTA FUNCION PERTENECE A CONSULTA DE PAGOS
void ConsultaPorObraSocial()
{

    int ObraSocial = 1;


    while (ObraSocial >= 0)
    {
        int Cont = 0;
        cout << "---------------BUSCAR PAGO POR OBRA SOCIAL---------------" << endl; ///Esto no se si dejarlo o sacarlo
        cout << "Ingrese la obra social del pago que desea buscar (ingrese un numero negativo para volver al menu)" << endl;
        cin >> ObraSocial;
        cout << endl;

        if (ObraSocial >= 0)
        {

            FacturaConsulta reg;

            int Pos = 0;
            while (reg.leerDeDisco(Pos) == true)
            {

                if (reg.getObraSocial() == ObraSocial)
                {
                    Cont++;
                    reg.Mostrar();
                    cout << endl;

                }
                Pos++;
            }

            if (Cont == 0)
            {
                cout << "NO EXISTE UN PAGO CON ESE NUMERO DE OBRA SOCIAL, INTENTE CON OTRO NUMERO" << endl << endl;
            }


            system("pause");
            system("cls");
        }

    }

}

/// ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorAdministrativo()
{

    FacturaConsulta reg;

    int LegajoAdministrativo = 1;
    while (LegajoAdministrativo != 0)
    {
        int Cont = 0;
        cout << "---------------BUSCAR PAGO POR ADMINISTRATIVO QUE LO TOMO---------------" << endl; ///Esto no se si dejarlo o sacarlo
        cout << "Ingrese el legajo del administrativo que desea buscar (Ingrese 0 para volver al menu)" << endl;
        cin >> LegajoAdministrativo;
        cout << endl;

        if (LegajoAdministrativo != 0)
        {
            int Pos = 0;
            while (reg.leerDeDisco(Pos) == true)
            {

                if (reg.getLegajoAdministrativo() == LegajoAdministrativo)
                {
                    Cont++;
                    reg.Mostrar();
                    cout << endl;
                }
                Pos++;
            }


            if (Cont == 0)
            {
                cout << "EL NUMERO DE LEGAJO INGRESADO NO EXISTE EN EL ARCHIVO DE PACIENTES, INGRESE OTRO NUMERO" << endl;
            }

            system("pause");
            system("cls");
        }

    }
}




///ESTA FUNCION PERTENECE A INFORMES
void RecaudacionMensual()
{

    int AnioIngresado = 1;
    int MesIngresado;
    while (AnioIngresado != 0)
    {
        cout << "------------------Recaudacion Mensual------------------" << endl;
        cout << "Ingrese el anio en el quiera ver la recaudacion total de ese anio (Ingrese 0 para volver al menu)" << endl;
        cin >> AnioIngresado;
        cout << endl;

        if (AnioIngresado != 0)
        {

            cout << "Ingrese el mes en el que quiera ver la recaudacion total de ese anio" << endl;
            cin >> MesIngresado;
            cout << endl;


            ///Puedo usar el ftell()
            int CantRegistros = ContarCantidadRegistrosPacientes();
            int AnioMin, AnioMax;

            FacturaConsulta reg;

            AnioMin = BuscarAnioMinFactura();
            AnioMax = BuscarAnioMaxFactura();


            ///CREA UNA MATRIZ DINAMICA, PIDO MEMORIA PARA ESA MATRIZ
            int tam = (AnioMax - AnioMin) + 1; ///Este el tamanio de la cantidad de filas de la matriz
            float** p;
            int c = 12; /// Meses del anio (Columnas de la matriz)
            p = new float* [tam];


            for (int x = 0; x < tam; x++)
            {
                p[x] = new float[c];
            }


            ///PONE CADA ELEMENTO DE LA MATRIZ EN 0
            for (int x = 0; x < tam; x++)
            {
                for (int j = 0; j < c; j++)
                {
                    p[x][j] = 0;
                }
            }


            ///ASIGNA RECAUDACION DE LOS ANIOS A LA MATRIZ DINAMICA
            int Pos = 0;
            float RecaudacionTotal = 0; ///ACA SE GUARDA LA RECAUDACION TOTAL DE TODOS LOS MESES DEL ANIO INGRESADO
            ///Valida que el anio y el mes ingresado se encuentre en el archivo de facturaconsulta

            if (AnioIngresado >= AnioMin && AnioIngresado <= AnioMax && MesIngresado <= 12 && MesIngresado > 0)
            {

                while (reg.leerDeDisco(Pos) == true)
                {
                    p[reg.getFechaFactura().getAnio() - AnioMin][reg.getFechaFactura().getMes() - 1] += reg.getPrecioConsulta();
                    //RecaudacionTotal +=reg.getPrecioConsulta();
                    Pos++;
                }

                cout << "Anio: " << AnioIngresado << endl << endl;
                cout << "RECAUDACION DEL MES\t\t\t\tRECAUACION" << endl;
                cout << "------------------------------------------------------------" << endl;

                ///Muestra la recaudacion del anio y mes que se ingresaron por teclado
                cout << MesIngresado << "\t\t\t\t\t\t   " << p[AnioIngresado - AnioMin][MesIngresado - 1] << endl << endl;



            }

            else
            {
                cout << "EL ANIO Y/O MES INGRESADO NO SE ENCUENTRAN EN EL ARCHIVO, INTENTE CON OTRO MES Y/O ANIO " << endl;
            }

            system("pause");
            system("cls");
            /*
                     ///Libera la memoria de la matriz
                    for (int x = 0; x < CantRegistros; x++)
                    {
                        delete p[x];
                    }
            */
        }

    }

}


///ESTA FUNCION PERTENECE A INFORMES
void RecaudacionAnual()
{

    int AnioIngresado = 1;
    while (AnioIngresado != 0)
    {
        cout << "------------------Recaudacion Anual------------------" << endl;
        cout << "Ingrese el anio en el quiera ver la recaudacion total de ese anio (Ingrese 0 para volver al menu)" << endl;
        cin >> AnioIngresado;
        cout << endl;

        if (AnioIngresado != 0)
        {
            ///Puedo usar el ftell()
            int CantRegistros = ContarCantidadRegistrosPacientes();
            int AnioMin, AnioMax;

            FacturaConsulta reg;

            AnioMin = BuscarAnioMinFactura();
            AnioMax = BuscarAnioMaxFactura();

            ///CREA UNA MATRIZ DINAMICA, PIDO MEMORIA PARA ESA MATRIZ
            int tam = (AnioMax - AnioMin) + 1; ///Este el tamanio de la cantidad de filas de la matriz
            float** p;
            int c = 12; /// Meses del anio (columnas de la matriz)
            p = new float* [tam];


            for (int x = 0; x < tam; x++)
            {
                p[x] = new float[c];
            }


            ///PONE CADA ELEMENTO DE LA MATRIZ EN 0
            for (int x = 0; x < tam; x++)
            {
                for (int j = 0; j < c; j++)
                {
                    p[x][j] = 0;
                }
            }



            ///ASIGNA RECAUDACION DE LOS ANIOS A LA MATRIZ DINAMICA
            int Pos = 0;
            float RecaudacionTotal = 0; ///ACA SE GUARDA LA RECAUDACION TOTAL DE TODOS LOS MESES DEL ANIO INGRESADO
            ///Valida que el anio ingresado se encuentre en el archivo de facturaconsulta
            if (AnioIngresado >= AnioMin && AnioIngresado <= AnioMax)
            {
                while (reg.leerDeDisco(Pos) == true)
                {
                    p[reg.getFechaFactura().getAnio() - AnioMin][reg.getFechaFactura().getMes() - 1] += reg.getPrecioConsulta();
                    RecaudacionTotal += reg.getPrecioConsulta();
                    Pos++;
                }

                cout << "La recaudacion del anio " << AnioIngresado << " fue: " << endl << endl;
                cout << "MES\t\t\t\tRECAUACION" << endl;
                cout << "-------------------------------------------------------" << endl;
                for (int x = 0; x < 12; x++)
                {

                    cout << x + 1 << "\t\t\t\t   " << p[AnioIngresado - AnioMin][x] << endl;
                }

                cout << "-------------------------------------------------------" << endl;
                cout << "TOTAL:\t\t\t\t   " << RecaudacionTotal << endl << endl;
            }

            else
            {
                cout << "El anio que ingreso no se encuentra en el archivo, intente con otro anio" << endl;
            }
            /*
                ///Libera la memoria de la matriz
                for (int x = 0; x < CantRegistros; x++)
                {
                    delete p[x];
                }
            */

            system("pause");
            system("cls");
        }
    }



}

///ESTA FUNCION PERTENECE A Informes
void RecaudacionPorCliente()
{


    int DniCliente = 1;
    FacturaConsulta reg;
    while (DniCliente != 0)
    {
        int Cont = 0;
        cout << "--------------------Recaudacion por cliente--------------------" << endl;
        cout << "Ingrese el DNI de algun cliente para ver su recaudacion: (Ingrese 0 para volver al menu)" << endl;
        cin >> DniCliente;
        cout << endl;

        if (DniCliente != 0)
        {

            int Pos = 0;
            float Recaudacion = 0; ///ACA SE ACUMULA LA RECAUDACION DEL CLIENTE QUE SE BUSCA

            ///ESTO RECORRE EL ARCHIVO DE FACTURAS PARA ACUMULAR LA RECAUDACION
            ///DEL CLIENTE QUE SE INGRESO POR TECLADO
            while (reg.leerDeDisco(Pos) == true)
            {
                if (reg.getDniPaciente() == DniCliente)
                {
                    Recaudacion += reg.getPrecioConsulta();
                    Cont++;
                }

                Pos++;
            }

            if (Cont != 0)
            {

                Paciente obj;
                Pos = 0;
                ///BUSCA EL DNI QUE SE INGRESO EN EL ARCHIVO DE PACIENTES EL
                ///DNI QUE SE INGRESO POR TECLADO, PARA PODER MOSTRAR
                ///EL NOMBRE Y EL APELLIDO DEL CLIENTE

                while (obj.leerDeDisco(Pos) == true)
                {
                    if (obj.getDNI() == DniCliente)
                    {
                        cout << "Cliente\t\t\t\tTotal Recaudado" << endl;
                        cout << "--------------------------------------------------" << endl;
                        cout << obj.getNombres() << " " << obj.getApellidos() << "\t\t\t\t $" << Recaudacion << endl << endl;
                    }
                    Pos++;
                }

            }

            else
            {
                cout << "No existe niguna factura con el numero de dni ingresado, intente con otro numero" << endl << endl;
            }

            system("pause");
            system("cls");
        }


    }

}

void VerTurnosDelDia(int Usuario)
{

    Turno reg;
    int Pos = 0;
    cout << "---------------------VER TURNOS PARA EL DIA DE HOY---------------------" << endl;
    while (reg.leerDeDisco(Pos) == true)
    {
        if (reg.getLegajoMedico() == Usuario) {
            reg.Mostrar();
            cout << endl;
        }
        Pos++;
    }

}


///ESTA FUNCION PERTENECE A Configuracion > ExportarDatos
void ExportarPacientes()
{

    Paciente reg;
    //reg.GrabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo paciente a un archivo de pacientes


    ofstream File;
    int Pos = 0;
    File.open("csv/pacientes.csv"); //Este es el direcctorio adonde se guarda el archivo csv
    File << ";" << "DNI" << ";" << "Nombres" << ";" << "Apellidos" << ";" << "Edad";
    File << ";" << "ID" << ";" << "Telefono" << ";" << "Email";
    File << ";" << "Calle" << ";" << "Localidad" << ";" << "Partido" << ";" << "Provincia" << ";" << "CodigoPostal" << ";" << "Pais" << ";" << "Estado" << endl;


    while (reg.leerDeDisco(Pos) == true) //Esto carga a un objeto de tipo paciente un registro de un archivo de oacientes
    {
        ///Esto convierte lo que esta cargado en el objeto de tipo paciente a un archivo csv y lo guarda ahi
        File << ";" << reg.getDNI() << ";" << reg.getNombres() << ";" << reg.getApellidos() << ";" << reg.getEdad();
        File << ";" << reg.getID() << ";" << reg.getTelefono() << ";" << reg.getEmail();
        File << ";" << reg.getDireccionPaciente().getCalle() << ";" << reg.getDireccionPaciente().getLocalidad() << ";" << reg.getDireccionPaciente().getPartido();
        File << ";" << reg.getDireccionPaciente().getProvincia() << ";" << reg.getDireccionPaciente().getCodigoPostal() << ";" << reg.getDireccionPaciente().getCodigoPostal();
        File << ";" << reg.getEstado() << endl;
        Pos++;
    }

}


void ExportarTurnos()
{

    Turno reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo Turno a un archivo de Turnos

    ofstream File;
    File.open("csv/Turnos.csv"); //Este es el direcctorio adonde se guarda el archivo csv


    File << ";" << "ID" << ";" << "IDPaciente" << ";" << "ObraSocial";
    File << ";" << "Dia del turno" << ";" << "Mes del turno" << ";" << "Anio del turno";
    File << ";" << "Hora del turno" << ";" << "Minuto del turno";
    File << ";" << "Dia asignacion turno" << ";" << "Mes asignacion turno" << ";" << "Anio asignacion turno";
    File << ";" << "LegajoMedico" << ";" << "Asistencia" << ";" << "Estado" << endl;

    int Pos = 0;
    while (reg.leerDeDisco(Pos) == true) //Esto carga a un objeto de tipo Turno un registro de un archivo de Turnos
    {
        ///Esto convierte lo que esta cargado en el objeto de tipo Turno a un archivo csv y lo guarda ahi
        File << ";" << reg.getID() << ";" << reg.getIDPaciente() << ";" << reg.getObraSocial();
        File << ";" << reg.getFechaTurno().getDia() << ";" << reg.getFechaTurno().getMes() << ";" << reg.getFechaTurno().getAnio();
        File << ";" << reg.getHoraTurno().getHora() << ";" << reg.getHoraTurno().getMinuto();
        File << ";" << reg.getFechaAsignacionTurno().getDia() << ";" << reg.getFechaAsignacionTurno().getMes() << ";" << reg.getFechaAsignacionTurno().getAnio();
        File << ";" << reg.getLegajoMedico() << ";" << reg.getAsistencia() << ";" << reg.getEstado() << endl;
        Pos++;
    }


}



void ExportarPagosConsultas()
{

    FacturaConsulta reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo FacturaConsulta a un archivo de FacturaConsulta

    ofstream File;
    File.open("csv/FacturasConsultas.csv"); //Este es el direcctorio adonde se guarda el archivo csv


    File << ";" << "ID" << ";" << "PrecioConsulta" << ";" << "IDPaciente" << ";" << "ObraSocial";
    File << ";" << "DiaFactura" << ";" << "MesFactura" << ";" << "AnioFactura";
    File << ";" << "DiaTurno" << ";" << "MesTurno" << ";" << "AnioTurno";
    File << ";" << "LegajoAdmin" << ";" << "FormaPago" << endl;

    int Pos = 0;

    while (reg.leerDeDisco(Pos) == true)
    {
        ///Esto convierte lo que esta cargado en el objeto de tipo FacturaConsulta a un archivo csv y lo guarda ahi
        ///Falta el get de precioconsulta
        File << ";" << reg.getID() << ";" << "precioConsul" << ";" << reg.getIDPaciente() << ";" << reg.getObraSocial();
        File << ";" << reg.getFechaFactura().getDia() << ";" << reg.getFechaFactura().getMes() << ";" << reg.getFechaFactura().getAnio();
        File << ";" << reg.getFechaTurno().getDia() << ";" << reg.getFechaTurno().getMes() << ";" << reg.getFechaTurno().getAnio();
        File << ";" << reg.getLegajoAdministrativo() << ";" << reg.getFormaPago() << endl;
        Pos++;
    }


}



void ExportarHistoriasClinicas()
{

    HistoriaClinica reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo HistoriaClinica a un archivo de HistoriaClinica

    ofstream File;
    File.open("csv/HistoriasClinicas.csv"); //Este es el direcctorio adonde se guarda el archivo csv


    File << ";" << "IDTurno" << ";" << "DetallesConsulta" << endl;
    int Pos = 0;

    while (reg.leerDeDisco(Pos) == true)
    {

        File << ";" << reg.getIDTurno() << ";" << reg.getDetallesConsulta() << endl;
        Pos++;
    }


}



void ExportarEmpleados()
{

    Empleado reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo Empleado a un archivo de Empleado

    ofstream File;
    File.open("csv/Empleados.csv"); //Este es el direcctorio adonde se guarda el archivo csv

    /*private:
    int _legajo;
    char _password[30];
    char _email[50];
    int _tipoEmpleado;
    Especialidad _especialidad;
    HorarioEmpleado _horarioEntradaSalida;
    bool _estado;*/

    /*
        class Especialidad
        private:
        int _IDEmpleado;
        char _especialidades[12][20];
        int _nEspecialidades;
        */

        //class HorarioEmpleado
        /* private:
        int _IDEmpleado;
        char _dias[7][11];
        bool _diasATrabajar[7];
        Hora _horaEntrada[7];
        Hora _horaSalida[7];
        bool _estado; */

        ///Aca tengo un problema con _especialidad > Esoecialidades
    File << ";" << "Legajo" << ";" << "Password" << ";" << "Email" << ";" << "TipoEmpleado";
    File << ";" << "IDEmpleado" << ";" << "Especialidades" << ";" << "NEspecialidades";
    //File <<";"<<"IDempleado"<<";"<<"Dias"<<";"<<"DiasAtrabajar"<<";"<<
}



void ExportarTodosLosArchivos()
{

    ExportarPacientes();

    ExportarTurnos();

    ExportarPagosConsultas();

    ExportarHistoriasClinicas();

    ExportarEmpleados();


}

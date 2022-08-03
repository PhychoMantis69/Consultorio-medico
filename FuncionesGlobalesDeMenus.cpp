#include "FuncionesGlobalesDeMenus.h"

//#include "Archivo.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <ctime> 
#include <fstream>
#include <Windows.h>
#include <random>
///ESTA ES UNA PRUEBA DE USO DE GITHUB DESDE VISUAL STUDIO 2019
///ESTA ES UNA PRUEBA DE USO DE GITHUB DESDE VISUAL STUDIO 2019
using namespace std;
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

void obtenerEmpleado(int usuario, Empleado& e) {
    int pos = 0;
    while (e.leerDeDisco(pos++))
    {
        if (e.getLegajo() == usuario) return;
    }
}

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
    int nro;
    Turno reg;
    FILE* p;
    p = fopen("Turnos.dat", "rb");
    if (p == NULL) return -1;
    fseek(p, 0, 2);
    nro = ftell(p) / sizeof(Turno);
    fclose(p);
    return nro + 1;
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
		if (vFechas[i]==f/*vFechas[i].getDia() == f.getDia() && vFechas[i].getMes() == f.getMes() && vFechas[i].getAnio() == f.getAnio()*/) {
			aux.setFecha(f.getDia(), f.getMes(), f.getAnio());
			return cont;
		}
	}
    return -1;
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

    Empleado reg;
    Turno turnito;
    int Pocision = 0;

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
            //int DiaTurno, MesTurno, AnioTurno;
            cout << "Ingrese especialidad: ";
            cin >> especialidad;
            cout << endl;
            
            if (!existeEspecialidad(especialidad, t)) {
                cout << "La especialidad no existe." << endl;
                system("pause");
                break;
            }

            cout << "Ingrese el dia: ";
            cin >> dia;
            cout << endl;

            cout << "Ingrese el Mes: ";
            cin >> mes;
            cout << endl;

            cout << "Ingrese el Anio: ";
            cin >> anio;
            cout << endl;

            if (f.esCorrecta(dia, mes, anio)) {
                f.setFecha(dia, mes, anio);
            }
            //todo:Faltan ver cosas aca
            if (estaEnRangoFecha(dia, mes, anio, vFechas)) {
            while (reg.leerDeDisco(Pocision) == true) {
                if (reg.getEspecialidad().getNEspecialidades() == especialidad) {
                    int Pos2 = 0;
                    int TurnosOcupados = 0;
                    //todo:ACA PUEDO USAR LA FUNCION DE LEANDRO PARA VER SI HAY UN TURNO DISPONIBLE
                    ///todo: ACA PIDE LOS DATOS ALREVEZ 
                    while (turnito.leerDeDisco(Pos2) == true) {
                        if (reg.getLegajo() == turnito.getLegajoMedico() && dia == turnito.getFechaTurno().getDia() && mes == turnito.getFechaTurno().getMes() && anio == turnito.getFechaTurno().getAnio() &&  turnito.getHoraTurno().getHora() == vHorarios[TurnosOcupados].getHora() && turnito.getHoraTurno().getMinuto() == vHorarios[TurnosOcupados].getMinuto()) {
                            TurnosOcupados++;
                        }
                        Pos2++;
                    }

                    //cout <<"Turno Ocupado: " <<  TurnosOcupados << endl;
                    
                    if (TurnosOcupados != 20) {
                       cout << reg.getApellidos() << " " << reg.getNombres() << " " << reg.getLegajo() << endl << endl;
                    }
                    
                }
                Pocision++;
            }

            cout << "Ingrese el legajo del medico con el que quiera sacar el turno: ";
            cin >> legajoMedico;
            cout << endl;

            //CREO QUE ESTA VALIDACIO ACA ESTA DE MAS 
            if (!buscarLegajoMedico(legajoMedico, t))
            {
                b1 = false;
                cout << "El legajo no existe. " << endl;
                system("pause");

            }

            else {
                while (true) {
                    system("cls");
                    if (f.esCorrecta(dia, mes, anio)) {
                        f.setFecha(dia, mes, anio);
                    }

                    if (estaEnRangoFecha(dia, mes, anio, vFechas)) {
                        b = true;
                        if (legajoMedico != 0) {
                            turnosDisponiblesPorMedico(legajoMedico, f, vHorarios, t, vFechas);
                        }
                        x = true;


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

                }
            }

            }

            else { cout << "La fecha que ingreso se encuentra fuera del rango de fecha o es incorrecta, ingrese otra fecha" << endl; }
            system("pause");
           
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
        if (t.getID() == aux.getID() /* && t.getIDPaciente() == aux.getIDPaciente()*/) {
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
    int nro;
    Paciente reg;
    FILE* p;
    p = fopen("Pacientes.dat", "rb");
    if (p == NULL) return -1;
    fseek(p, 0, 2);
    nro = ftell(p) / sizeof(Paciente);
    fclose(p);
    return nro + 1;
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


void GestionarPagos() {

    int dia, mes, anio, hora, minuto;
    Fecha f;
    cout << "-------------------------Gestionar Pagos-------------------------" << endl;
    cout << "Ingrese la fecha del turno para pasarle asistencia" << endl;
    //todo:aca puedo usar la funcion cargarfechaHoy
    

    //cargarFechaHoy(f)

    cout << "Ingrese el dia: ";
    cin >> dia;
    cout << endl;

    cout << "Ingrese el mes: ";
    cin >> mes;
    cout << endl;

    cout << "Ingrese la hora: ";
    cin >> anio;
    cout << endl;

    cout << "Ingrese los minutos: ";
    cin >> hora;
    cout << endl;

    cout << "Ingrese el anio: ";
    cin >> minuto;
    cout << endl;

    Turno reg;
    
    int Pos = 0;
    int Posicion = 0;
    while (reg.leerDeDisco(Pos)) {
        if(reg.getFechaTurno().getDia() == dia && reg.getFechaTurno().getMes() == mes && reg.getFechaTurno().getAnio() == anio && reg.getHoraTurno().getHora() == hora && reg.getHoraTurno().getMinuto() == minuto){
        //todo:ACA TENGO QUE PONER EN TRUE EL ESTADO ASISTENCIA Y DESPUES GRABAR
            Posicion = Pos;
        }
        Pos++;
    }
    
    reg.leerDeDisco(Posicion);
    reg.setEstado(true);
    FILE* p;
    p = fopen("FacturaConsulta.dat", "rb+"); ///No me acuerdo si era rb o ab
    if (p == NULL) {
        cout << "No se pudo abrir el archivo de facturas" << endl;
        return;
    }


    fseek(p, sizeof(FacturaConsulta) * Posicion, 0);
    fwrite(&reg, sizeof(FacturaConsulta), 1, p);
    //obj.grabarEnDisco(Cont);
    fclose(p);


    FacturaConsulta obj;
    int   IDFactura;
    float precioConsultaFactura;
    int   IDPacienteFactura;
    int   obraSocialFactura;
    //Fecha _fechaFactura;
    int diaFactura;
    int mesFactura;
    int anioFactura;
    //Fecha _fechaTurno;
    int diaTurno;
    int mesTurno;
    int anioTurno;

    int legajoAdministrativoFactura;
    int formaPagoFactura;
    int legajoMedicoFactura;
    

    //todo:falta validaciones para todos los ingresos de datos
    cout << "Ingrese el ID del turno" << endl; //todo:esto es un autonumerico
    cin >> IDFactura;
    cout << endl;

    cout << "Ingrese el precio del turno" << endl; 
    cin >> precioConsultaFactura;
    cout << endl;

    cout << "Ingrese el ID del paciente" << endl; 
    cin >> IDPacienteFactura;
    cout << endl;

    cout << "Ingrese el dia de la factura" << endl;
    cin >> diaFactura;
    cout << endl;

    cout << "Ingrese el mes de la factura" << endl;
    cin >> mesFactura;
    cout << endl;

    cout << "Ingrese el anio de la factura" << endl;
    cin >> anioFactura;
    cout << endl;

    cout << "Ingrese el dia del turno" << endl;
    cin >> diaTurno;
    cout << endl;

    cout << "Ingrese el mes del turno" << endl;
    cin >> mesTurno;
    cout << endl;

    cout << "Ingrese el anio del turno" << endl;
    cin >> anioTurno;
    cout << endl;

    //todo:Esto tiene que ser a utonumerico creo
    cout << "Ingrese su numero de legajo" << endl; 
    cin >> legajoAdministrativoFactura;
    cout << endl;

    cout << "Ingrese la forma de pago de lña factura" << endl;
    cin >> formaPagoFactura;
    cout << endl;

    cout << "Ingrese el numero de legajo del medico con el que se tuvo el turno" << endl;
    cin >> legajoMedicoFactura;
    cout << endl;

    obj.setID(IDFactura);
    obj.setPrecioConsulta(precioConsultaFactura);
    obj.setIDPaciente(IDPacienteFactura);
    Fecha FechaFactura, FechaTurno;
    FechaFactura.setFecha(diaFactura, mesFactura, anioFactura);
    obj.setFechaFactura(FechaFactura);
    FechaTurno.setFecha(diaTurno, mesTurno, anioTurno);
    obj.setLegajoAdministrativo(legajoAdministrativoFactura);
    obj.setFormaPago(formaPagoFactura);
    obj.setLegajoMedico(legajoMedicoFactura);

    if (obj.grabarEnDisco() == true) {
        cout << "La factura se agrego correctamente" << endl;
    }

    else {
        cout << "No se pudo agregar la factura" << endl;
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
//todo:1
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
    int pos = 0;
    while (reg.leerDeDisco(pos))
    {
        if (reg.getTipoEmpleado() == 1)
        {
            p[Indice] = reg;
            Indice++;
        }
        pos++;
    }

}
//todo:1
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
//todo:1
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

void OrdenarTurnosPorLegajo(Turno* p, int cantRegistros) {

    int i, j;

    Turno aux;

    for (i = 0; i < cantRegistros; i++)
    {

        for (j = 0; j < cantRegistros - 1; j++)
        {

 
            if (p[j].getLegajoMedico() < p[j+1].getLegajoMedico())
            {

                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }


}


void MostrarPacientes(Paciente* VPacientes, int cantRegistros)
{
    for (int i = 0; i < cantRegistros; i++)
    {
        VPacientes[i].Mostrar();
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
//todo:1
void MostrarTurnos(Turno* p, int cantRegistros)
{
    for (int x = 0; x < cantRegistros; x++)
    {
        p[x].Mostrar();
        cout << endl;
    }

}

///NO ESTA COMPLETO, PORQUE PACIENTE NO TIENE NINGUN ATRIBUTO QUE SEA LA EDAD DEL PACIENTE
void OrdenarRegistrosPorEdad(Paciente* vPacientes, int cantRegistros)
{
    ///ACA USO EL ALGORITMO DE BURBUJA PARA ORDENAR A LOS PACIENTES POR LA EDAD
    Paciente aux;
    for (int i = 0; i < cantRegistros; i++)
    {
        for (int j = 0; j < cantRegistros - 1; j++)
        {
            if (vPacientes[j].getEdad() < vPacientes[j + 1].getEdad())
            {
                aux = vPacientes[j + 1];
                vPacientes[j + 1] = vPacientes[j];
                vPacientes[j] = aux;
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
//todo:3
bool ExisteHistoriaClinica(int IdTurno) {

    HistoriaClinica reg;
    //cout << "IdTurno: " << IdTurno << endl;
    int Pos = 0;

    while (reg.leerDeDisco(Pos) == true) {

        if (reg.getIDTurno() == IdTurno) {
            //cout << "Ya existe una historia clinica para el dia de hoy" << endl;
            return true;
        }

        Pos++;
    }
    return false;
}


bool BuscarYMostrarHistoriasClinicas(int IdPaciente, int Usuario, Fecha f)
{
    int Cont = 0;
    Turno reg;
    HistoriaClinica obj;
    int Pos = 0;


    while (reg.leerDeDisco(Pos) == true)
    {
        if (reg.getLegajoMedico() == Usuario && reg.getFechaTurno() > f && reg.getIDPaciente() == IdPaciente)
        {
            int Pos2 = 0;
            while (obj.leerDeDisco(Pos2) == true) {
                if (obj.getIDTurno() == reg.getID()) {
                    obj.Mostrar();
                    Cont++;
                    cout << endl;
                }

                Pos2++;
            }

        }
        Pos++;
    }

    if (Cont != 0) {
        return true;
    }

    else {
        return false;
    }

}


int BuscarPosiocionID(int ID) {


    int Pos = 0;
    int Cont = 0;
    HistoriaClinica obj;
    while (obj.leerDeDisco(Pos) == true) {
        if (obj.getIDTurno() == ID) {
            Cont = Pos;
        }
        Pos++;
    }

    return Cont;
}


void MostrarTurnosDeCadaEspecialidad(int Legajo) {

    Turno reg;
    int Pos = 0;
    while (reg.leerDeDisco(Pos)==true) {
        if (reg.getLegajoMedico() == Legajo) {
            reg.Mostrar();
            cout << endl;
        }
        Pos++;
    }


}

void MostrarTurnosOrdenadosPorEspecialidad(Empleado* vEmpleados, int cantRegistros) {

    Empleado reg;
    int Pos = 0;
    while(reg.leerDeDisco(Pos)){
        cout << "Especialidad: " << reg.getEspecialidad().getNEspecialidades() << endl << endl;
        MostrarTurnosDeCadaEspecialidad(reg.getLegajo());
        Pos++;
    }

}

///ESTA FUNCION PERTENECE ListadoDePacientes
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

    MostrarPacientesListadosPorApellidos(p, cantRegistros);
    //MostrarPacientes(p, cantRegistros);

    delete[] p; //Comente este delete porque sino el programa me hacia un return raro

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

    delete[] p;
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


    delete[] p;

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


    delete[] p;


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

    delete[] p;


}
//todo:2
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

    delete[] p;
}


void ListadoDeTurnosOrdenadosPorEspecialidad()
{
    int cantRegistros, tipoEmpleado = 2;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE MEDICOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorEspecialidad(vEmpleados, cantRegistros);
    MostrarTurnosOrdenadosPorEspecialidad(vEmpleados, cantRegistros);
   
    //delete vEmpleados;
}

void ListadoDeTurnosOrdenadosPorMedicoTratante() {

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

    OrdenarTurnosPorLegajo(p, cantRegistros);

    MostrarTurnos(p, cantRegistros);

    delete[] p;


}

///------------------------------------------------------------------
int cantEmpleados(int tipoEmpleado) {
    Empleado reg;
    int pos = 0, cont = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (reg.getTipoEmpleado() == tipoEmpleado) cont++;
    }
    return cont;
}

void CargarVectorEmpleados(Empleado* vEmpleados, int tipoEmpleado) {
    Empleado reg;
    int i = 0;
    int pos = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (reg.getTipoEmpleado() == tipoEmpleado)
        {
            vEmpleados[i] = reg;
            i++;
        }
    }
}

void OrdenarVectorEmpleadosPorLegajo(Empleado* vEmpleados, int cantRegistros) {
    Empleado aux;
    for (int i = 0; i < cantRegistros; i++)
    {
        for (int j = 0; j < cantRegistros - 1; j++)
        {
            if (vEmpleados[j].getLegajo() < vEmpleados[j + 1].getLegajo())
            {
                aux = vEmpleados[j + 1];
                vEmpleados[j + 1] = vEmpleados[j];
                vEmpleados[j] = aux;
            }
        }
    }
}

void MostrarEmpleados(Empleado* vEmpleados, int cantRegistros) {
    for (int i = 0; i < cantRegistros; i++)
    {
        vEmpleados[i].Mostrar();
        cout << endl;
    }
}

void ListadoAdministradoresOrdenadoPorLegajo() {
    int cantRegistros, tipoEmpleado = 99;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE ADMINISTRADORES EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorLegajo(vEmpleados, cantRegistros);
    MostrarEmpleados(vEmpleados, cantRegistros);

    //delete[] vEmpleados;
}
///------------------------------------------------------------------
void OrdenarVectorEmpleadosPorApellido(Empleado* vEmpleados, int cantRegistros) {
    Empleado aux;
    for (int i = 0; i < cantRegistros; i++)
    {
        for (int j = 0; j < cantRegistros - 1; j++)
        {
            if (strcmp(vEmpleados[j].getApellidos(), vEmpleados[j + 1].getApellidos()) > 0){
                aux = vEmpleados[j + 1];
                vEmpleados[j + 1] = vEmpleados[j];
                vEmpleados[j] = aux;
            }
        }
    }
}

void ListadoAdministradoresOrdenadoPorApellido() {
    int cantRegistros, tipoEmpleado = 99;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE ADMINISTRADORES EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorApellido(vEmpleados, cantRegistros);
    MostrarEmpleados(vEmpleados, cantRegistros);

    delete[] vEmpleados;
}
///------------------------------------------------------------------
void ListadoMedicosOrdenadoPorLegajo() {
    int cantRegistros, tipoEmpleado = 2;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE MEDICOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorLegajo(vEmpleados, cantRegistros);
    MostrarEmpleados(vEmpleados, cantRegistros);

    //delete[] vEmpleados;
}
//-------------------------------------------------------------------
void ListadoMedicosOrdenadoPorApellido() {
    int cantRegistros, tipoEmpleado = 2;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE MEDICOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorApellido(vEmpleados, cantRegistros);
    MostrarEmpleados(vEmpleados, cantRegistros);

    //delete[] vEmpleados;
}
//-------------------------------------------------------------------
void OrdenarVectorEmpleadosPorEspecialidad(Empleado* vEmpleados, int cantRegistros) {
    Empleado aux;

    for (int i = 0; i < cantRegistros; i++)
    {
        for (int j = 0; j < cantRegistros - 1; j++)
        {
            if (vEmpleados[j].getEspecialidad().getNEspecialidades() > vEmpleados[j + 1].getEspecialidad().getNEspecialidades())
            {
                aux = vEmpleados[j + 1];
                vEmpleados[j + 1] = vEmpleados[j];
                vEmpleados[j] = aux;
            }
        }
    }
}

void ListadoMedicosOrdenadoPorEspecialidad() {
    int cantRegistros, tipoEmpleado = 2;
    cantRegistros = cantEmpleados(tipoEmpleado);///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE MEDICOS EN EL ARCHIVO DE EMPLEADOS" << endl;
        return;
    }

    Empleado* vEmpleados;
    vEmpleados = new Empleado[cantRegistros];

    if (vEmpleados == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE EMPLEADOS" << endl;
        return;
    }
    CargarVectorEmpleados(vEmpleados, tipoEmpleado);
    OrdenarVectorEmpleadosPorEspecialidad(vEmpleados, cantRegistros);
    MostrarEmpleados(vEmpleados, cantRegistros);

    //delete[] vEmpleados;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
///CONSULTAS
///ESTA FUNCION PERTENECE A ConsultaDePacientes, no tenia que hacerlo yo xd
///ESTA FUNCION YA ESTA VALIDADA, REVISAR BIEN POR LAS DUDAS c
void ConsultaPacientePorDNI()
{
    int DNI = 1;
    while(DNI != 0){
    while (true)
    {
        system("cls");
        cout << "-----------------Consulta de paciente por dni-----------------" << endl;
        cout << "Ingrese el Dni del paciente que desea buscar (ingrese 0 para volver al menu): " << endl;
        cin >> DNI;
        cout << endl;

        if (DNI == 0) {
            return;
        }

        if (existeDNI(DNI)) break;
        else {
            cout << "No existe ningun paciente con ese DNI. Intente de nuevo." << endl; 
            system("pause");
            }
    }
    Paciente reg;
    int pos = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (reg.getDNI() == DNI)
        {
            reg.Mostrar();
            system("pause");
            //return; //Te comente esto porque sino me cortaba el programa
        }
    }

    }
}

///----------------------------------------------------------------
int cantPacientes() {
    FILE* p;
    p=fopen("Pacientes.dat", "rb");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO." << endl;
        return -1;
    }
    fseek(p, 0, 2);
    int cant = ftell(p) / sizeof(Paciente);
    fclose(p);
    return cant;
}

bool validarEdad(int edadInicial, int edadTope) {
    if (edadInicial >= 0 && edadTope <= 120) return true;
    return false;
}

void CargarVectorPacientes(Paciente* vPacientes, int edadInicial, int edadTope) {
    Paciente reg;
    int i = 0;
    int pos = 0;
    while (reg.leerDeDisco(pos++))
    {
        if (reg.getEdad()>=edadInicial && reg.getEdad()<=edadTope)
        {
            vPacientes[i] = reg;
            i++;
        }
    }
}


//ESTA FUNCION ESTA VALIDAD, REVISAR BIEN POR LAS DUDAS c
void ConsultaPacientePorRangoEdad() {
    int cantRegistros, edadInicial = 1, edadTope;
    cantRegistros = cantPacientes();///Cuenta la cantidad de registros que hay en el archivo de paciente
    if (cantRegistros == 0)
    {
        cout << "NO HAY REGISTROS DE PACIENTES EN EL ARCHIVO." << endl;
        system("pause");
        return;
    }
    while(edadInicial != 0){
    while (true)
    {
        system("cls");
        cout << "Ingrese un rango de edad (Ingrese una edad inicial igual a 0 para volcer al menu): " << endl;
        cout << "Desde: ";
        cin >> edadInicial;
        if (edadInicial == 0) { return; }
        cout << "Hasta: ";
        cin >> edadTope;
        if (validarEdad(edadInicial, edadTope)) break;
        else { cout << "Rango ingresado no valido. Vuelva a intentar." << endl; 
        system("pause");
        }
    }

    Paciente* vPacientes;
    vPacientes = new Paciente[cantRegistros];

    if (vPacientes == NULL)
    {
        cout << "NO SE PUDO OBTENER MEMORIA DINAMICA PARA EL VECTOR DE PACIENTES" << endl;
        return;
    }
    CargarVectorPacientes(vPacientes, edadInicial, edadTope);
    OrdenarRegistrosPorEdad(vPacientes, cantRegistros);//REUTILIZADO
    MostrarPacientes(vPacientes, cantRegistros);//MUESTRA LOS PACIENTES EN EL RANGO ESTABLECIDO(CON LOS LIMITES INCLUIDOS)

    delete[] vPacientes;
    }
}
///----------------------------------------------------------------
///ESTAS FUNCIONES PERTENECE A CONSULTA DE TURNOS
int obtenerCantTurnos() {
    FILE* p;
    p = fopen("Turnos.dat", "rb");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO." << endl;
        return -1;
    }
    fseek(p, 0, 2);
    int cant = ftell(p) / sizeof(Turno);
    fclose(p);
    return cant;
}

///ESTA FUNCION YA ESTA VALIDADA, REVISAR BIEN POR LAS DUDAS
void ConsultaDeTurnosNoAsistidos() {
    Turno turno;
    Fecha f;
    int cantTurnos = obtenerCantTurnos();
    if (cantTurnos == 0) {
        cout << "NO HAY REGISTROS DE TURNOS EN EL ARCHIVO." << endl;
        system("pause");
        return;
    }


    cargarFechaHoy(f);
    int pos = 0;
    while (turno.leerDeDisco(pos++))
    {
        if (!turno.getAsistencia() && turno.getFechaTurno() < f) {
            turno.Mostrar();
        }
    }
}
///----------------------------------------------------------------
///ESTA FUNCION YA ESTA VALIDAD, REVISAR BIEN POR LAS DUDAS c
void ConsultaDeTurnosPorRangoDeFecha() {
    Fecha fechaInicial;
    int Dia_Inicial = 1;
    int Mes_Inicial;
    int Anio_Inicial;
    Fecha fechaFinal;
    int Dia_Final;
    int Mes_Final;
    int Anio_Final;
    while (Dia_Inicial != 0) {
        cout << "---------------MOSTRAR TURNOS POR RANGO DE FECHA---------------" << endl; ///Esto no se si dejarlo o sacarlo

        cout << "Ingrese el dia, el mes y el anio de la fecha inicial" << endl;
        cout << "Ingrese el dia (Ingrese un 0 para volver al menu): ";
        cin >> Dia_Inicial;
        if (Dia_Inicial == 0) { return; }
        cout << "Ingrese el mes: ";
        cin >> Mes_Inicial;
        cout << "Ingrese el anio: ";
        cin >> Anio_Inicial;
        cout << endl;

        if (fechaInicial.esCorrecta(Dia_Inicial, Mes_Inicial, Anio_Inicial) == true) {
            fechaInicial.setFecha(Dia_Inicial, Mes_Inicial, Anio_Inicial);


            cout << "Ingrese el dia, el mes y el anio de la fecha final" << endl;
            cout << "Ingrese el dia: ";
            cin >> Dia_Final;
            cout << "Ingrese el mes: ";
            cin >> Mes_Final;
            cout << "Ingrese el anio: ";
            cin >> Anio_Final;
            cout << endl;

            if (fechaFinal.esCorrecta(Dia_Final, Mes_Final, Anio_Final) == true) {
            fechaFinal.setFecha(Dia_Final, Mes_Final, Anio_Final);

            Turno reg;
            int pos = 0;
            int CantidadDeTurnos = 0;
            while (reg.leerDeDisco(pos++))
            {
                if (reg.getFechaTurno() > fechaInicial && reg.getFechaTurno() < fechaFinal)
                {
                    reg.Mostrar();
                    CantidadDeTurnos++;
                    cout << endl;
                }
            }

            if (CantidadDeTurnos == 0) {
                cout << "No hay ningun turno entre los rangos de fechas ingresados" << endl; 
                }

            }

            else {
                cout << "La fecha final que ingreso es incorrecta, ingrese otra fecha" << endl;
            }

        }

        else {
            cout << "La fecha inicial que ingreso es incorrecta, ingrese otra fecha" << endl;
        }

        system("pause");
        system("cls");

    }
}
///----------------------------------------------------------------
int obtenerEspecialidad(int legajoMedico) {
    Empleado reg;
    int pos = 0, especialidad;
    while (reg.leerDeDisco(pos++))
    {
        if (reg.getLegajo() == legajoMedico) {
            especialidad = reg.getEspecialidad().getNEspecialidades();
            return especialidad;
        }
    }
    return -1;
}

void ConsultaDeTurnosPorEspecialidad() {
    Turno turno;
    int pos = 0, especialidad = 2, cont = 0;
    while (especialidad != 0)
    {
        system("cls");
        cout << "---------------CONSULTA DE TURNOS POR ESPECIALIDAD---------------" << endl<<endl;
        cout << "1. Pediatria" << endl;
        cout << "2. Kinesiologia" << endl;
        cout << "3. Oftalmologia" << endl;
        cout << "4. Traumatologia" << endl;
        cout << "5. Obstetricia" << endl;
        cout << "6. Psicologia" << endl;
        cout << "7. Nutricion" << endl;
        cout << "8. Psiquiatria" << endl;
        cout << "9. Dermatologia" << endl;
        cout << "10. Cardiologia" << endl;
        cout << "Ingrese la especialidad (Ingrese 0 para volver al menu): ";
        cin >> especialidad;
        cout << endl;

        if (especialidad == 0) { return; }

        if (especialidad >= 1 && especialidad <= 10) {
            especialidad++;
            while (turno.leerDeDisco(pos++))
            {
                if (obtenerEspecialidad(turno.getLegajoMedico()) == especialidad) {
                    turno.Mostrar();
                    cont++;
                }
            }
            
            if (cont > 0) {
                cout << "No hay ningun turno con esa especialidad, ingrese otra especialidad" << endl;
                
            }

        }
        else {
            cout << "OPCION INCORRECTA. VUELVA A INTENTAR." << endl;
            system("pause");
        }   

    }
}
///----------------------------------------------------------------
///----------------------------------------------------------------

///ESTA FUNCION PERTENECE A ConsultaDePagos
///ESTA FUNCION YA ESTA VALIDAD, REVISAR POR LAS DUDAS  c
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
    while(Dia_Inicial !=0){
    cout << "---------------Buscat pago por rango de fecha---------------" << endl; ///Esto no se si dejarlo o sacarlo

    cout << "Ingrese el dia, el mes y el anio de la fecha inicial" << endl;
    cout << "Ingrese el dia (Ingrese 0 para volver menu): ";
    cin >> Dia_Inicial;
    if (Dia_Inicial == 0) { return; }
    cout << "Ingrese el mes: ";
    cin >> Mes_Inicial;
    cout << "Ingrese el anio: ";
    cin >> Anio_Inicial;
    cout << endl;

    fecha1.setFecha(Dia_Inicial, Mes_Inicial, Anio_Inicial);
    
    if(fecha1.esCorrecta(Dia_Inicial, Mes_Inicial, Anio_Inicial)==true){
    cout << "Ingrese el dia, el mes y el anio de la fecha final" << endl;
    cout << "Ingrese el dia: ";
    cin >> Dia_Final;
    cout << "Ingrese el mes: ";
    cin >> Mes_Final;
    cout << "Ingrese el anio: ";
    cin >> Anio_Final;
    cout << endl;


    fecha2.setFecha(Dia_Final, Mes_Final, Anio_Final);
    if (fecha2.esCorrecta(Dia_Final, Mes_Final, Anio_Final) == true) {

        FacturaConsulta reg;

        int Pos = 0;
        while (reg.leerDeDisco(Pos) == true)
        {

            if (reg.getFechaFactura() > fecha1 && reg.getFechaFactura() < fecha2)
            {
                reg.Mostrar();
                cout << endl;
            }
            Pos++;
        }

    }

    else {
        cout << "La fecha final que ingreso es incorrecta, ingrese otra fecha" << endl;
    }

    }


    

    else {
        cout << "La fecha inicial que ingreso es incorrecta, ingrese otra fecha" << endl;
    }

    system("pause");
    system("cls");

    

    }
}


///ESTA FUNCION PERTENECE A ConsultaDePagos
///ESTA FUNCION YA ESTA VALIDAD, REVISAR POR LAS DUDAS c
void ConsultaPorCliente()
{

    int DniPaciente = 1;

    while (DniPaciente != 0)
    {
        int Cont = 0;
        cout << "---------------Buscar pago por cliente---------------" << endl; ///Esto no se si dejarlo o sacarlo

        cout << "Ingrese el DNI del paciente que desea buscar (ingrese 0 para volver al menu)" << endl;
        cin >> DniPaciente;
        cout << endl;

        if (DniPaciente == 0)
        {
            return;
        }
            FacturaConsulta reg;

            int Pos = 0;
            int id = obtenerID(DniPaciente);
            while (reg.leerDeDisco(Pos) == true)
            {

                if (reg.getIDPaciente() == id)
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

///ESTA FUNCION PERTENECE A CONSULTA DE PAGOS
///ESTA NO ME CONVENCE LO DEL NUMERO NEGATIVO
void ConsultaPorObraSocial()
{

    int ObraSocial = 1;
    while (ObraSocial != 0)
    {
        int Cont = 0;
        cout << "---------------BUSCAR PAGO POR OBRA SOCIAL---------------" << endl; ///Esto no se si dejarlo o sacarlo
        //todo:aca podriamos mostrar que es cada obra social
        cout << "Ingrese la obra social del pago que desea buscar (ingrese un 0 para volver al menu)" << endl;
        cin >> ObraSocial;
        cout << endl;

        if (ObraSocial == 0)
        {
            return;
        }

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

/// ESTA FUNCION PERTENECE A ConsultaDePagos
///ESTA FUNCION YA ESTA VLIDADA, REVISAR BIEN c 
void ConsultaPorAdministrativo()
{

    FacturaConsulta reg;

    int LegajoAdministrativo = 1;
    while (LegajoAdministrativo != 0)
    {
        int Cont = 0; ///ESTO LO USO COMO CONTADOR PARA VALIDAR SI EXISTE O NO UN PAGO CON EL LEGAJO INGRESADO
        cout << "---------------BUSCAR PAGO POR ADMINISTRATIVO QUE LO TOMO---------------" << endl; ///Esto no se si dejarlo o sacarlo
        cout << "Ingrese el legajo del administrativo que desea buscar (Ingrese 0 para volver al menu)" << endl;
        cin >> LegajoAdministrativo;
        cout << endl;

        if (LegajoAdministrativo == 0) { return; }
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

///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///ESTAS FUNCIONES PERTENECE A INFORMES
void mostrarCantTurnosAsignadosEnMes(int cont, int mes, int anio) {
    Cadena meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre",
    "Noviembre", "Diciembre" };
    cout << "MES\t\tTURNOS TOTALES" << endl;
    meses[mes - 1].Mostrar();
    cout << "\t\t" << cont << endl;
}

//todo: falta revisar bien 
void CantidadTurnosAsignadosEnMes() {
    int anio = 1, mes = 2, pos = 0, cont = 0;
    Turno reg;
    Fecha f;
    while(anio !=0 || mes != 0){
    while (true) {
        cout << "------------------Informe cantidad de turnos------------------" << endl;
        cout << "Ingrese el anio o mes (cero) para volver al menu anterior: ";
        cin >> anio;
        if (anio == 0) return;
        cout << "Ingrese el mes o 0 (cero) para volver al menu anterior: ";
        cin >> mes;
        if (mes == 0) return;
        if (f.esCorrecta(1, mes, anio)) {

            while (reg.leerDeDisco(pos++))
            {
                if (reg.getFechaTurno().getAnio() == anio && reg.getFechaTurno().getMes() == mes) {
                    cont++;
                }
            }
            break;
        }
        else {
            cout << "LA FECHA ES INCORRECTA. VUELVA A INGRESAR." << endl;
        }
    }
    mostrarCantTurnosAsignadosEnMes(cont, mes, anio);
    }
}
///------------------------------------------------------------------------------------------------------------
void mostrarAusenciasATurnosEnMes(int cont, int mes, int anio) {
    Cadena meses[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre",
    "Noviembre", "Diciembre" };
    cout << "MES\t\t CANTIDAD DE PERSONAS QUE NO ASISTIERON A LOS TURNOS" << endl;
    meses[mes - 1].Mostrar();
    cout << "\t\t" << cont << endl;
}

void AusenciasTurnosMes() {
    int anio, mes, pos = 0, cont = 0;
    Turno reg;
    Fecha f, hoy;
    cargarFechaHoy(hoy);
    while (true) {
        cout << "------------------Informe ausencias pacientes por mes------------------" << endl;
        cout << "Ingrese el anio o 0 (cero) para volver al menu anterior: ";
        cin >> anio;
        if (anio == 0) return;
        cout << "Ingrese el mes o 0 (cero) para volver al menu anterior: ";
        cin >> mes;
        if (mes == 0) return;
        if (f.esCorrecta(1, mes, anio)) {

            while (reg.leerDeDisco(pos++))
            {
                if (reg.getFechaTurno().getAnio() == anio && reg.getFechaTurno().getMes() == mes && !reg.getAsistencia() &&
                    reg.getFechaTurno()<hoy) {
                    cont++;
                }
            }
            break;
        }
        else {
            cout << "LA FECHA ES INCORRECTA. VUELVA A INGRESAR." << endl;
        }
    }
    mostrarAusenciasATurnosEnMes(cont, mes, anio);
}
///------------------------------------------------------------------------------------------------------------

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

        if (AnioIngresado == 0) { return; }
        

            cout << "Ingrese el mes en el que quiera ver la recaudacion total de ese anio" << endl;
            cin >> MesIngresado;
            cout << endl;

            ///Puedo usar el ftell()
            //int CantRegistros = ContarCantidadRegistrosPacientes();
            int AnioMin, AnioMax;

            FacturaConsulta reg;

            AnioMin = BuscarAnioMinFactura();
            AnioMax = BuscarAnioMaxFactura();
   
            float RecaudacioMensual = 0;
            
            ///Valida que el anio y el mes ingresado se encuentre en el archivo de facturaconsulta
            if (AnioIngresado >= AnioMin && AnioIngresado <= AnioMax && MesIngresado <= 12 && MesIngresado > 0)
            {
                int Pos = 0;
                while (reg.leerDeDisco(Pos) == true)
                {
                    
                    if(reg.getFechaFactura().getAnio()==AnioIngresado && reg.getFechaFactura().getMes() == MesIngresado){
                        RecaudacioMensual +=reg.getPrecioConsulta();
                    }
                    Pos++;
                }

                cout << "Anio: " << AnioIngresado << endl << endl;
                cout << "RECAUDACION DEL MES\t\t\t\tRECAUACION" << endl;
                cout << "------------------------------------------------------------" << endl;

                ///Muestra la recaudacion del anio y mes que se ingresaron por teclado
                cout << MesIngresado << "\t\t\t\t\t\t   " << RecaudacioMensual << endl << endl;

            }

            else
            {
                cout << "EL ANIO Y/O MES INGRESADO NO SE ENCUENTRAN EN EL ARCHIVO, INTENTE CON OTRO MES Y/O ANIO " << endl;
            }

            system("pause");
            system("cls");
       
    }

}
///----------------------------------------------------------------------------------------

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

        if (AnioIngresado == 0)
        {
            return;
        }
            ///Puedo usar el ftell()
            //int CantRegistros = ContarCantidadRegistrosPacientes();
            int AnioMin, AnioMax;

            FacturaConsulta reg;

            //todo: estas dos funciones no me convencen
            AnioMin = BuscarAnioMinFactura();
            AnioMax = BuscarAnioMaxFactura();
      
           
            float RecaudacionTotal = 0;
            float RecaudacionesMensuales[12] = {};

            ///Valida que el anio ingresado se encuentre en el archivo de facturaconsulta
            if (AnioIngresado >= AnioMin && AnioIngresado <= AnioMax)
            {
                int Pos = 0;
                while (reg.leerDeDisco(Pos) == true)
                {
                    if(reg.getFechaFactura().getAnio()==AnioIngresado){
                        RecaudacionesMensuales[reg.getFechaFactura().getMes() - 1] += reg.getPrecioConsulta();
                        RecaudacionTotal += reg.getPrecioConsulta();
                    }
                    Pos++;
                }

                cout << "La recaudacion del anio " << AnioIngresado << " fue: " << endl << endl;
                cout << "MES\t\t\t\tRECAUACION" << endl;
                cout << "-------------------------------------------------------" << endl;
                for (int x = 0; x < 12; x++)
                {
                    cout << x + 1 << "\t\t\t\t   " << RecaudacionesMensuales[x] << endl;
                }

                cout << "-------------------------------------------------------" << endl;
                cout << "TOTAL:\t\t\t\t   " << RecaudacionTotal << endl << endl;
            }

            else
            {
                cout << "El anio que ingreso no se encuentra en el archivo, intente con otro anio" << endl;
            }
            
            system("pause");
            system("cls");
        
    }



}
//---------------------------------------------------------------------------------------------------
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

        if (DniCliente == 0) {
            return;
        }

        if (existeDNI(DniCliente) == false) {
            cout << "No existe un paciente con el dni que ingreso o el dni es incorrecto " << endl;
            system("pause");
            system("cls");
        }
        else{
            int Pos = 0;
            float Recaudacion = 0; ///ACA SE ACUMULA LA RECAUDACION DEL CLIENTE QUE SE BUSCA
            ///ESTO RECORRE EL ARCHIVO DE FACTURAS PARA ACUMULAR LA RECAUDACION
            ///DEL CLIENTE QUE SE INGRESO POR TECLADO
            int id = obtenerID(DniCliente);
            while (reg.leerDeDisco(Pos) == true)
            {
                if (reg.getIDPaciente() == id)
                {
                    Recaudacion += reg.getPrecioConsulta();
                    Cont++;
                }

                Pos++;
            }

            if (Cont != 0)
            {
                Paciente obj;
                
                ///BUSCA EL DNI QUE SE INGRESO EN EL ARCHIVO DE PACIENTES EL
                ///DNI QUE SE INGRESO POR TECLADO, PARA PODER MOSTRAR
                ///EL NOMBRE Y EL APELLIDO DEL CLIENTE
                Pos = 0;
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

           
        
        }

    }

}
///----------------------------------------------------------------------------------------------
void mostrarRecaudacion(float* vTotalPorEspecialidad) {
    Especialidad reg;
    Cadena especialidades[10] = { "Pediatria", "Kinesiologia", "Oftalmologia", "Traumatologia", "Obstetricia", "Psicologia",
        "Nutricion", "Psiquiatria", "Dermatologia", "Cardiologia" };
    cout << "ESPECIALIDAD\t\t TOTAL RECAUDADO" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        especialidades[i].Mostrar();
        cout << "\t\t" << vTotalPorEspecialidad[i] << endl;
    }
}

void RecaudacionPorEspecialidad() {
    FacturaConsulta reg;
    int pos = 0, nroEspecialidad;
    float vTotalPorEspecialidad[10]{};

    while (reg.leerDeDisco(pos++))
    {
        nroEspecialidad = obtenerEspecialidad(reg.getLegajoMedico());
        vTotalPorEspecialidad[nroEspecialidad-2] += reg.getPrecioConsulta();
    }
    mostrarRecaudacion(vTotalPorEspecialidad);
}

//todo:4
//todo:Modificar cuando se pase a html para que muestre datos del paciente
void VerTurnosDelDia(int Usuario)
{

    Turno reg;
    int Pos = 0;
    int Cont = 0;

    Fecha f;
    cargarFechaHoy(f);

    cout << "---------------------VER TURNOS PARA EL DIA DE HOY---------------------" << endl;
    while (reg.leerDeDisco(Pos) == true)
    {
        if (reg.getLegajoMedico() == Usuario && reg.getFechaTurno().getDia() == f.getDia() && reg.getFechaTurno().getMes() == f.getMes() && reg.getFechaTurno().getAnio() == f.getAnio())
        {
            Cont++;
            reg.Mostrar();
            cout << endl;
        }
        Pos++;
    }

    if (Cont == 0)
    {
        cout << "No hay turnos para el dia de hoy" << endl;
    }

}

void AgregaRegistroDeHistoriaClinica(int usuario){
    Turno obj;
    int IdTurno;
    Fecha f;

    cargarFechaHoy(f);


    int hora = 1, minutos;
    while (hora != 0) {
        cout << "-----------------------Agregar registro de historia clinica-----------------------" << endl;
        cout << "Ingrese la hora del turno actual (Ingrese una hora igual a 0 para volver al menu)" << endl;
        cout << "Hora: ";
        cin >> hora;
        cout << endl;
        if (hora != 0) {
            return;
        }
            cout << "Minutos: ";
            cin >> minutos;
            cout << endl;

            int Cont = 0;
            int Pos = 0;
            while (obj.leerDeDisco(Pos) == true)
            {
                if (obj.getLegajoMedico() == usuario && obj.getFechaTurno().getDia() == f.getDia() && obj.getFechaTurno().getMes() == f.getMes() && obj.getFechaTurno().getAnio() == f.getAnio() && hora == obj.getHoraTurno().getHora() && minutos == obj.getHoraTurno().getMinuto())
                {
                    Cont++;
                    IdTurno = obj.getID();
                    obj.Mostrar();
                    cout << endl;
                }
                Pos++;
            }

            if (Cont == 0)
            {
                cout << "No hay turnos para el dia de hoy en el horaria ingresado, intente con otro horario" << endl;
            }


            if (Cont != 0) {
                HistoriaClinica reg;
                char DetallesConsulta[2000];
                bool HistoriaClinicaExiste;
                HistoriaClinicaExiste = ExisteHistoriaClinica(IdTurno);

                if (HistoriaClinicaExiste == true) {
                    cout << "Ya hay una historia clinica para el turno actual" << endl;
                }

                else {
                    reg.setIDTurno(IdTurno);
                    cin.ignore();
                    cout << "Ingrese los detalles de la consulta" << endl;
                    cin.getline(DetallesConsulta, 2000);
                    cout << endl << endl;

                    reg.setDetallesConsulta(DetallesConsulta);

                    if (reg.grabarEnDisco(0) == true)
                    {
                        cout << "El registro se agrego correctamente" << endl;
                    }

                    else
                    {
                        cout << "No se pudo agregar el registro correctamente" << endl;
                    }
                }

            }

            system("pause");
            system("cls");

    }

}
//todo: validar cuando no haya historias clinicas en el archivo
//todo:Si ingreso un 2, 2, 2 en dia, mes, anio, me lo toma igual
//todo:cuando el usuario ingresa un id que no existe le pide nuevamente que ingrese la fecha 
//todo:Meter el codigo en funciones pare que no me quede un spaggeti
void ModificarRegistroDeHistoriaClinica(int usuario){
    int Dia = 1, Mes, Anio, DniPaciente, IdPaciente, ID;
    while (Dia != 0) {
        cout << "--------------------------Modificar historia clinica--------------------------" << endl;
        cout << "Buscar historias clinicas en un rango de fechas" << endl << endl;
        cout << "Ingrese una fecha inicial (Ingrese un dia igual a 0 para volver al menu)" << endl;

        cout << "Ingrese el Dia: ";
        cin >> Dia;
        if (Dia != 0) {
            return;
        }
            cout << "Ingrese el Mes: ";
            cin >> Mes;

            cout << "Ingrese el Anio: ";
            cin >> Anio;

            Fecha f;

            if (f.esCorrecta(Dia, Mes, Anio) == false) {
                cout << "La fecha que ingreso es incorrecta, ingrese otra fecha" << endl;
            }


            else {
                f.setFecha(Dia, Mes, Anio);
                cout << "Ingrese el DNI del paciente: ";
                cin >> DniPaciente;
                cout << endl;

                if (existeDNI(DniPaciente) == false) {
                    cout << "No existe un paciente con el DNI que ingreso, ingrese otro dni" << endl;
                }

                else {
                    IdPaciente = obtenerID(DniPaciente);
                    if (!BuscarYMostrarHistoriasClinicas(IdPaciente, usuario, f)) {
                        //todo:revisar bien este mensaje
                        cout << "No existe ningun registro de historia clinica para el paciente y rango de fecha ingresados, ingrese otra fecha y/o dni de paciente" << endl;
                    }

                    else {

                        Turno reg;
                        HistoriaClinica obj;
                        bool HistoriaClinicaExiste;

                        cout << "Ingrese el ID de la historia clinica que quiera modificar:  ";
                        cin >> ID;
                        cout << endl;

                        HistoriaClinicaExiste = ExisteHistoriaClinica(ID);

                        if (HistoriaClinicaExiste == false) {
                            cout << "No existe una historia clinica con el ID que ingreso, ingrese otro ID" << endl;
                        }

                        else {

                            int Cont;

                            Cont = BuscarPosiocionID(ID);

                            obj.leerDeDisco(Cont);

                            char DetallesConsulta[2000];
                            cin.ignore();
                            cout << "Ingrese los detalles de la consulta para modificar (2000 caracteres maximo)" << endl;
                            cin.getline(DetallesConsulta, 2000);
                            cout << endl;

                            obj.setDetallesConsulta(DetallesConsulta);
                            FILE* IdHistoriaClinica;
                            IdHistoriaClinica = fopen("HistoriasClinicas.dat", "rb+"); ///No me acuerdo si era rb o ab
                            if (IdHistoriaClinica == NULL) {
                                cout << "No se pudo abrir el archivo de historia clinica" << endl;
                                return;
                            }


                            fseek(IdHistoriaClinica, sizeof(HistoriaClinica) * Cont, 0);
                            fwrite(&obj, sizeof(HistoriaClinica), 1, IdHistoriaClinica);
                            //obj.grabarEnDisco(Cont);
                            fclose(IdHistoriaClinica);

                        }

                    }

                }

            }

            system("pause");
            system("cls");
        
    }

}




///ESTA FUNCION PERTENECE AL MENU ADMINISTRADOR
void AgregarUnUsuario()
{

    int DniUsuario = 1, EdadUsusario, LegajoUsuario, TipoEmpleadoUsuario, IdEpleadoUsuario, IdEpleadoUsuarioHorario;
    int NumeroEspecialidadUsuario;
    char Nombres[50];
    char Apellidos[50];
    char ContraseniaUsuario[30];
    char EmailUsuario[50];

    Empleado reg;
    while (DniUsuario != 0)
    {
        //todo: falta validar que los ingresos sean correctos
        //todo: pide datos que no tiene que pedir, y no pide otros que deberia pedir
        cout << "-------------------------Agregar a un usuario-------------------------" << endl;
        cout << "Ingrese los datos del usuario que quiera agregar" << endl;
        cout << "Ingrese el DNI del usuario (Ingrese 0 para volver al menu)" << endl;
        //todo:validar que el dni no exista
        cin >> DniUsuario; ///OK
        cout << endl;
        cin.ignore();


        if (DniUsuario == 0) { return; }
            cout << "Ingrese los nombres del usuario (50 caracteres maximo)" << endl;
            cin.getline(Nombres, 50);///OK
            cout << endl;

            cout << "Ingrese los apellidos del usuario (50 caracteres maximo)" << endl;
            cin.getline(Apellidos, 50); ///OK
            cout << endl;

            cout << "Ingrese la edad del usuario" << endl;
            cin >> EdadUsusario; ///OK
            cout << endl;

            cout << "Ingrese un legajo para el usuario" << endl;
            cin >> LegajoUsuario; ///OK, PERO CREO QUE ESTO DEBERIA SER UN AUTONUMERICO
            cout << endl;

            cout << "Ingrese una contrasenia para el usuario" << endl;
            cin >> ContraseniaUsuario; ///OK
            cout << endl;

            cout << "Ingrese el email del usuario" << endl;
            cin >> EmailUsuario; ///OK
            cout << endl;

            cout << "Ingrese el tipo de empleado del usuario" << endl;
            cout << "99-Administrador  1-Adminitrativo  2-Medico" << endl;
            cin >> TipoEmpleadoUsuario; ///OK
            cout << endl;

            cout << "Ingrese el ID del empleado" << endl;///No estoy muy seguro de esto, revisar bien
            cin >> IdEpleadoUsuario; ///ESTE ES EL ID DE EMPLEADP DE LA ESPECIALIDAD DEL USUARIO
            cout << endl;


            cout << "ingrese la especialidad del empleado: " << endl;
            cout << "0-Administrador  1-Administrativo  2-Pediatria" << endl;
            cout << "3-Kinesiologia   4-Oftalmologia    5-Traumatologia" << endl;
            cout << "6-Obstetricia    7-Psicologia      8-Nutricion" << endl;
            cout << "9-Psiquiatra     10-Oftalmologia   11-Cardiologia" << endl << endl;
            cout << "Ingrese el numero correspondiente a la especialidad del empleado" << endl;
            cin >> NumeroEspecialidadUsuario; ///OK ///No estoy muy seguro de esto, revisar bien
            cout << endl;


            cout << "Ingrese el ID del empleado del horario" << endl;///No estoy muy seguro de esto, revisar bien
            cin >> IdEpleadoUsuarioHorario;
            cout << endl;

            ///ACA SE PODRIAN INGRESAR LOS DIAS A TRABAJAR

            ///ACA SE PODRIAN INGRESAR LA HORA DE ENTRADA DE CADA DIA

            ///ACA SE PODRIAN INGRESAR LA HORA DE SALIDA DE CADA DIA

            reg.setDNI(DniUsuario);
            reg.setNombres(Nombres);
            reg.setApellidos(Apellidos);
            reg.setEdad(EdadUsusario);
            reg.setLegajo(LegajoUsuario);
            reg.setPassword(ContraseniaUsuario);
            reg.setEmail(EmailUsuario);
            reg.setTipoEmpleado(TipoEmpleadoUsuario);
            Especialidad obj;
            obj.setIDEmpleado(IdEpleadoUsuario);
            obj.setNEspecialidades(NumeroEspecialidadUsuario);
            reg.setEspecialidad(obj);
            HorarioEmpleado horita;
            horita.setIDEmpleado(IdEpleadoUsuarioHorario);

            //todo:faltan setear datos

            if (reg.grabarEnDisco(0) == true)
            {
                cout << "El empleado se agrego exitosamente" << endl;
            }

            else
            {
                cout << "No se pudo agregar el empleado" << endl;
            }

            system("pause");
            system("cls");

    }


}

///ESTA FUNCION YA ESTA VALIDADA, REVISAR BIEN POR LAS DUDAS 
void EliminarUsuario()
{

    int DniUsuario = 1;
    Empleado reg;
    while (DniUsuario)
    {
        cout << "-------------------------Eliminar un usuario-------------------------" << endl;
        cout << "Ingrese el dni del usuario que quiera eliminar (Ingrese un 0 para volver al menu): ";
        //todo:cuando ingreso un solo digito me lo toma igual
        cin >> DniUsuario;
        cout << endl;

        ///ESTO VALIDA QUE EL DNI INGRESADO NO PUEDO SER NEGATIVO
        if (DniUsuario == 0) {return;}

        if (existeDNI(DniUsuario) == false) {
         cout << "El dni que ingreso no existe o es incorrecto, ingrese otro dni" << endl;
         system("pause");
         system("cls");
        }

        else
        {
                int Opcion;
                int Posicion = 0;
                int Pos = 0;
                while (reg.leerDeDisco(Pos) == true)
                {
                    if (reg.getEstado() == true && reg.getDNI() == DniUsuario)
                    {
                        Posicion = Pos;
                        reg.Mostrar();
                    }
                    Pos++;
                }

                ///ESTO ES PARA SABER SI SE ENCONTRO ALGUN EMPLEADO CON EL DNI INGRESADO
                if (Posicion != 0)
                {
                    cout << "¿Desea eliminar el usuario? (1-SI 2-NO)" << endl;
                    cout << "Ingrese una opcion" << endl;
                    cin >> Opcion;
                    cout << endl;

                    if (Opcion == 1)
                    {

                        reg.leerDeDisco(Posicion);
                        reg.setEstado(false);
                        //todo:meter todo esto en una funcion
                        FILE* p;

                        p = fopen("Empleados.dat", "rb+");

                        if (p == nullptr)
                        {
                            cout << "NO SE PUDO ABRIR EL ARCHIVO DE EMPLEADOS" << endl;
                        }

                        fseek(p, sizeof(Empleado) * Posicion, 0);
                        fwrite(&reg, sizeof(Empleado), 1, p);

                        //todo:falta el grabar, creo

                        fclose(p);
                    }

                    ///ESTA ES UNA VALIDACION PARA CUANDO EL USUARIO INGRESA UNA OPCION QUE NO EXISTE
                    if (Opcion != 1 && Opcion != 2)
                    {
                        cout << "La opcion que ingreso es incorrecta, ingrese otra opcion" << endl;
                    }
                }

                else
                {
                    cout << "No se encontro ningun usuario con el dni ingresado, ingrese otro dni " << endl;
                }


                system("pause");
                system("cls");

        }



    }
}



void ModificarUsuario()
{
    int DniUsuario = 1, EdadUsusario, LegajoUsuario, TipoEmpleadoUsuario, IdEpleadoUsuario, IdEpleadoUsuarioHorario;
    int NumeroEspecialidadUsuario;
    char Nombres[50];
    char Apellidos[50];
    char ContraseniaUsuario[30];
    char EmailUsuario[50];
    int Posicion = 0;
    Empleado reg;
    while (DniUsuario != 0)
    {
        cout << "-------------------------modificar un usuario-------------------------" << endl;
        cout << "Ingrese el dni del usuario que quiera moficar (Ingrese un 0 para volver al menu): ";
        cin >> DniUsuario;
        cout << endl;

        if (DniUsuario == 0) { return; }
       
        ///ESTO VALIDA QUE EL DNI INGRESADO NO PUEDO SER NEGATIVO
        if (existeDNI(DniUsuario)==false)
        {
            cout << "El dni que ingreso no existe o no es valido, ingrese otro dni" << endl;
            system("pause");
            system("cls");
        }


        else
        {
                int Pos = 0;
                while (reg.leerDeDisco(Pos) == true)
                {
                    if (reg.getEstado() == true && reg.getDNI() == DniUsuario)
                    {
                        Posicion = Pos;
                        reg.Mostrar();
                    }
                    Pos++;
                }

                ///ESTO ES PARA SABER SI SE ENCONTRO ALGUN EMPLEADO CON EL DNI INGRESADO
                if (Posicion != 0)
                {

                    int Opcion;
                    cout << "¿Desea modificar el usuario? (1-SI 2-NO)" << endl;
                    cout << "Ingrese una opcion: ";
                    //todo: falta validar que ingrese un numero que sea 1 o 2
                    cin >> Opcion;
                    cout << endl;
                    cin.ignore();

                    if (Opcion == 1)
                    {
                        //todo:pide datps que no los deberia pedir
                        cout << "Ingrese los nombres del usuario" << endl;
                        cin.getline(Nombres, 50);///OK
                        cout << endl;

                        cout << "Ingrese los apellidos del usuario" << endl;
                        cin.getline(Apellidos, 50); ///OK
                        cout << endl;

                        cout << "Ingrese la edad del usuario" << endl;
                        cin >> EdadUsusario; ///OK
                        cout << endl;

                        cout << "Ingrese un legajo para el usuario" << endl;
                        cin >> LegajoUsuario; ///OK, PERO CREO QUE ESTO DEBERIA SER UN AUTONUMERICO
                        cout << endl;

                        cout << "Ingrese una contrasenia para el usuario" << endl;
                        cin >> ContraseniaUsuario; ///OK
                        cout << endl;

                        cout << "Ingrese el email del usuario" << endl;
                        cin >> EmailUsuario; ///OK
                        cout << endl;

                        cout << "Ingrese el tipo de empleado del usuario" << endl;
                        cout << "99-Administrador  1-Adminitrativo  2-Medico" << endl;
                        cin >> TipoEmpleadoUsuario; ///OK
                        cout << endl;

                        cout << "Ingrese el ID del empleado" << endl;///No estoy muy seguro de esto, revisar bien
                        cin >> IdEpleadoUsuario; ///ESTE ES EL ID DE EMPLEADP DE LA ESPECIALIDAD DEL USUARIO
                        cout << endl;


                        cout << "ingrese la especialidad deñ empleado: " << endl;
                        cout << "0-Administrador  1-Administrativo  2-Pediatria" << endl;
                        cout << "3-Kinesiologia   4-Oftalmologia    5-Traumatologia" << endl;
                        cout << "6-Obstetricia    7-Psicologia      8-Nutricion" << endl;
                        cout << "9-Psiquiatra     10-Oftalmologia   11-Cardiologia" << endl << endl;
                        cout << "Ingrese el numero correspondiente a la especialidad del empleado" << endl;
                        cin >> NumeroEspecialidadUsuario; ///OK ///No estoy muy seguro de esto, revisar bien
                        cout << endl;


                        cout << "Ingrese el ID del empleado del horario" << endl;///No estoy muy seguro de esto, revisar bien
                        cin >> IdEpleadoUsuarioHorario;
                        cout << endl;

                        reg.leerDeDisco(Posicion);
                        reg.setDNI(DniUsuario);
                        reg.setNombres(Nombres);
                        reg.setApellidos(Apellidos);
                        reg.setEdad(EdadUsusario);
                        reg.setLegajo(LegajoUsuario);
                        reg.setPassword(ContraseniaUsuario);
                        reg.setEmail(EmailUsuario);
                        reg.setTipoEmpleado(TipoEmpleadoUsuario);
                        Especialidad obj;
                        obj.setIDEmpleado(IdEpleadoUsuario);
                        obj.setNEspecialidades(NumeroEspecialidadUsuario);
                        reg.setEspecialidad(obj);
                        HorarioEmpleado horita;
                        horita.setIDEmpleado(IdEpleadoUsuarioHorario);

                        FILE* p;

                        p = fopen("Empleados.dat", "rb+");

                        if (p == nullptr)
                        {
                            cout << "NO SE PUDO ABRIR EL ARCHIVO DE EMPLEADOS" << endl;
                        }

                        fseek(p, sizeof(Empleado) * Posicion, 0);
                        fwrite(&reg, sizeof(Empleado), 1, p);

                        //todo:falta el grabar

                        fclose(p);

                    }

                    ///ESTA ES UNA VALIDACION PARA CUANDO EL USUARIO INGRESA UNA OPCION QUE NO EXISTE
                    if (Opcion != 1 && Opcion != 2)
                    {
                        cout << "La opcion que ingreso es incorrecta, ingrese otra opcion" << endl;
                    }
                }

                else
                {
                    cout << "No se encontro ningun usuario con el dni ingresado, ingrese otro dni " << endl;
                }

                system("pause");
                system("cls");
            

        }

    }

}

///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///ESTAS FUNCIONES PERTENECEN A COPIA DE SEGURIDAD
int generarCod() {
    int NRO, MIN = 10000, MAX = 99999;
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX);
    NRO = distr(eng);
    return NRO;
}

void generarNombreBK(string& nombre) {
    int hora, minuto;
    Fecha f;
    Fecha_Hora FH;
    time_t currentTime = time(NULL);
    time(&currentTime);
    struct tm* myTime = localtime(&currentTime);
    hora = myTime->tm_hour;
    minuto = myTime->tm_min;
    cargarFechaHoy(f);
    FH.setFechaHora(hora, minuto, f.getDia(), f.getMes(), f.getAnio());
    //string n("BK_");
    nombre += "BK_";
    nombre += (FH.getFechaHora());
    nombre.replace(nombre.find(" "), 1, "_");
    nombre.replace(nombre.find("/"), 1, "-");
    nombre.replace(nombre.find("/"), 1, "-");
    nombre.replace(nombre.find(":"), 1, "_");
}

void grabarCopiaPacientes(const char* ruta, Paciente& paciente) {
    int pos = 0;
    FILE* p;
    p = fopen(ruta, "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO." << endl;
        return;
    }
    while (paciente.leerDeDisco(pos++))
    {
        fwrite(&paciente, sizeof(Paciente), 1, p);
    }
    fclose(p);
}

void guardarNombreArchivoPacientes(const char* ruta) {
    Archivo reg;
    reg.setNombre(ruta);
    reg.setEstado(true);
    reg.grabarEnDisco("Backup/Pacientes/rutas.dat");
}

void CopiaSeguridadPacientes() {
    int codigo, hora, minuto;
    while (true) {
        system("cls");
        int cod = generarCod();
        cout << "PARA CONTINUAR INGRESE EL SIGUIENTE CODIGO: " << cod << endl;
        cout << "CODIGO DE CONFIRMACION: ";
        cin >> codigo;
        if (cod == codigo) break;
        else {
            cout << "ERROR. VUELVA A INTENTAR." << endl;
            system("pause");
        }
    }
    Paciente paciente;
    string carpeta("Backup/Pacientes/");
    string nombre;
    generarNombreBK(nombre);
    string extension(".dat");
    string r;
    char ruta[41];
    r += carpeta;
    r += nombre;
    r += extension;
    strcpy(ruta, r.c_str());
    grabarCopiaPacientes(ruta, paciente);
    guardarNombreArchivoPacientes(ruta);
}
///----------------------------------------------------------------------------------------------

void grabarCopiaTurnos(const char* ruta, Turno& turno) {
    int pos = 0;
    FILE* p;
    p = fopen(ruta, "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO." << endl;
        return;
    }
    while (turno.leerDeDisco(pos++))
    {
        fwrite(&turno, sizeof(Turno), 1, p);
    }
    fclose(p);
}
void guardarNombreArchivoTurnos(const char* ruta) {
    Archivo reg;
    reg.setNombre(ruta);
    reg.setEstado(true);
    reg.grabarEnDisco("Backup/Turnos/rutas.dat");
}

void CopiaSeguridadTurnos() {
    int codigo, hora, minuto;
    while (true) {
        system("cls");
        int cod = generarCod();
        cout << "PARA CONTINUAR INGRESE EL SIGUIENTE CODIGO: " << cod << endl;
        cout << "CODIGO DE CONFIRMACION: ";
        cin >> codigo;
        if (cod == codigo) break;
        else {
            cout << "ERROR. VUELVA A INTENTAR." << endl;
            system("pause");
        }    
    }
    Turno turno;
    string carpeta("Backup/Turnos/");
    string nombre;
    generarNombreBK(nombre);
    string extension(".dat");
    string r;
    char ruta[41];
    r += carpeta;
    r += nombre;
    r += extension;
    strcpy(ruta, r.c_str());
    grabarCopiaTurnos(ruta, turno);
    guardarNombreArchivoTurnos(ruta);
}
///----------------------------------------------------------------------------------------------

void grabarCopiaPagos(const char* ruta, FacturaConsulta& facturaConsulta) {
    int pos = 0;
    FILE* p;
    p = fopen(ruta, "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO." << endl;
        return;
    }
    while (facturaConsulta.leerDeDisco(pos++))
    {
        fwrite(&facturaConsulta, sizeof(FacturaConsulta), 1, p);
    }
    fclose(p);
}
void guardarNombreArchivoPagos(const char* ruta) {
    Archivo reg;
    reg.setNombre(ruta);
    reg.setEstado(true);
    reg.grabarEnDisco("Backup/Pagos/rutas.dat");
}

void CopiaSeguridadPagos() {
    int codigo, hora, minuto;
    while (true) {
        system("cls");
        int cod = generarCod();
        cout << "PARA CONTINUAR INGRESE EL SIGUIENTE CODIGO: " << cod << endl;
        cout << "CODIGO DE CONFIRMACION: ";
        cin >> codigo;
        if (cod == codigo) break;
        else {
            cout << "ERROR. VUELVA A INTENTAR." << endl;
            system("pause");
        }
    }
    FacturaConsulta facturaConsulta;
    string carpeta("Backup/Pagos/");
    string nombre;
    generarNombreBK(nombre);
    string extension(".dat");
    string r;
    char ruta[41];
    r += carpeta;
    r += nombre;
    r += extension;
    strcpy(ruta, r.c_str());
    grabarCopiaPagos(ruta, facturaConsulta);
    guardarNombreArchivoPagos(ruta);
}
///----------------------------------------------------------------------------------------------

void grabarCopiaHistoriasClinicas(const char* ruta, HistoriaClinica& historiaClinica) {
    int pos = 0;
    FILE* p;
    p = fopen(ruta, "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO." << endl;
        return;
    }
    while (historiaClinica.leerDeDisco(pos++))
    {
        fwrite(&historiaClinica, sizeof(HistoriaClinica), 1, p);
    }
    fclose(p);
}
void guardarNombreArchivoHistoriasClinicas(const char* ruta) {
    Archivo reg;
    reg.setNombre(ruta);
    reg.setEstado(true);
    reg.grabarEnDisco("Backup/Historias Clinicas/rutas.dat");
}

void CopiaSeguridadHC() {
    int codigo, hora, minuto;
    while (true) {
        system("cls");
        int cod = generarCod();
        cout << "PARA CONTINUAR INGRESE EL SIGUIENTE CODIGO: " << cod << endl;
        cout << "CODIGO DE CONFIRMACION: ";
        cin >> codigo;
        if (cod == codigo) break;
        else {
            cout << "ERROR. VUELVA A INTENTAR." << endl;
            system("pause");
        }
    }
    HistoriaClinica historiaClinica;
    string carpeta("Backup/Historias Clinicas/");
    string nombre;
    generarNombreBK(nombre);
    string extension(".dat");
    string r;
    char ruta[41];
    r += carpeta;
    r += nombre;
    r += extension;
    strcpy(ruta, r.c_str());
    grabarCopiaHistoriasClinicas(ruta, historiaClinica);
    guardarNombreArchivoHistoriasClinicas(ruta);
}
///----------------------------------------------------------------------------------------------

void grabarCopiaEmpleados(const char* ruta, Empleado& empleado) {
    int pos = 0;
    FILE* p;
    p = fopen(ruta, "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO." << endl;
        return;
    }
    while (empleado.leerDeDisco(pos++))
    {
        fwrite(&empleado, sizeof(Empleado), 1, p);
    }
    fclose(p);
}
void guardarNombreArchivoEmpleados(const char* ruta) {
    Archivo reg;
    reg.setNombre(ruta);
    reg.setEstado(true);
    reg.grabarEnDisco("Backup/Empleados/rutas.dat");
}

void CopiaSeguridadEmpleados() {
    int codigo, hora, minuto;
    while (true) {
        system("cls");
        int cod = generarCod();
        cout << "PARA CONTINUAR INGRESE EL SIGUIENTE CODIGO: " << cod << endl;
        cout << "CODIGO DE CONFIRMACION: ";
        cin >> codigo;
        if (cod == codigo) break;
        else {
            cout << "ERROR. VUELVA A INTENTAR." << endl;
            system("pause");
        }
    }
    Empleado empleado;
    string carpeta("Backup/Empleados/");
    string nombre;
    generarNombreBK(nombre);
    string extension(".dat");
    string r;
    char ruta[41];
    r += carpeta;
    r += nombre;
    r += extension;
    strcpy(ruta, r.c_str());
    grabarCopiaEmpleados(ruta, empleado);
    guardarNombreArchivoEmpleados(ruta);
}
///----------------------------------------------------------------------------------------------
void CopiaSeguridadTodos() {
    CopiaSeguridadPacientes();
    CopiaSeguridadTurnos();
    CopiaSeguridadPagos();
    CopiaSeguridadHC();
    CopiaSeguridadEmpleados();
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//todo:hacer desde aca..restaurar copias de seguridad

bool existe(Archivo& reg) {
    FILE* p;
    p = fopen(reg.getNombre(), "rb");
    if (p == NULL) return false;
    fclose(p);
    return true;
}

int cantRegistros(const char* ruta) {
    int aux;
    FILE* p;
    p = fopen(ruta, "rb");
    if (p == NULL) return -1;
    fseek(p, 0, 2);
    aux = ftell(p) / sizeof(Archivo);
    fclose(p);
    return aux;
}

bool seRepite(const char* nombre, const char* ruta) {
    Archivo reg;
    int pos = 0, cont = 0;
    while (reg.leerDeDisco(pos++, ruta))
    {
        if (strcmp(reg.getNombre(), nombre) == 0) cont++;
    }
    if (cont > 1) return true;
    return false;
}

int cantRutasOk(const char* ruta) {
    
    Archivo reg;
    int pos = 0, cont = 0;
    int aux = cantRegistros(ruta);
    
    //cout << aux;

    for (int i = 0; i < aux; i++){
        reg.leerDeDisco(i, ruta);
        if (existe(reg)) {
            if (seRepite(reg.getNombre(), ruta)) {
                reg.setEstado(false);
                reg.grabarEnDisco(ruta, pos);
            }
            else if (!reg.getEstado()) {
                reg.setEstado(true);
                reg.grabarEnDisco(ruta, i);
                cont++;
            }
            else cont++;
        }
        else {
            reg.setEstado(false);
            reg.grabarEnDisco(ruta, i);
        }
    }
    /*while (reg.leerDeDisco(pos++, ruta)) {
        if (seRepite(reg.getNombre(), ruta)) {
            reg.setEstado(false);
            reg.grabarEnDisco(ruta, pos);
            cont--;
        }
    }*/

    //system("pause");
    return cont;
}

void cargarVArchivo(Archivo* vA, int cant, const char* ruta) {
    Archivo aux;
    int pos = 0, c = 0;
    for (int i = 0; i < cantRegistros(ruta); i++)
    {
        aux.leerDeDisco(i, ruta);
        if (aux.getEstado()) {
            vA[c] = aux;
            c++;
        }
    }
}

void migrarBKPacientes(Archivo& ruta, int cant, const char* nombre) {
    Paciente reg;
    int pos = 0;
    FILE* p;
    p = fopen("Pacientes.dat", "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
    while (reg.leerCopiaDeDisco(pos++,ruta.getNombre())){
        reg.GrabarEnDisco();
    }
    fclose(p);
}

void RestaurarCopiaSeguridadPacientes() {
    Paciente reg;
    int pos = 0, opcion;
    int cant = cantRutasOk("Backup/Pacientes/rutas.dat");
    if (cant == 0) {
        cout << "No existen copias de seguridad" << endl;
        system("pause");
        return;
    }
    Archivo* vA = new Archivo[cant];
    cargarVArchivo(vA, cant, "Backup/Pacientes/rutas.dat");
    while (true) {
        system("cls");
        for (int i = 1; i <= cant; i++)
        {
            cout << i << ". " << vA[i-1].getNombre() << endl;
        }
        cout << "Ingrese una opcion para restaurar: ";
        cin >> opcion;
        if (opcion > 0 && opcion <= cant) {
            migrarBKPacientes(vA[opcion-1], cant, "Pacientes.dat");
            cout << "El archivo ha sido restaurado" << endl;
            delete[] vA;
            return;
        }
        else {
            cout << "Opcion incorrecta. Vuelva a intentar." << endl;
            system("pause");
        }

    }

    delete[] vA;
}
//-----------------------------------------------------------------------------------------------

void migrarBKTurnos(Archivo& ruta, int cant, const char* nombre) {
    Turno reg;
    int pos = 0;
    FILE* p;
    p = fopen("Turnos.dat", "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
    while (reg.leerCopiaDeDisco(pos++, ruta.getNombre())) {
        reg.grabarEnDisco();
    }
    fclose(p);
}

void RestaurarCopiaSeguridadTurnos() {
    Turno reg;
    int pos = 0, opcion;
    int cant = cantRutasOk("Backup/Turnos/rutas.dat");
    if (cant == 0) {
        cout << "No existen copias de seguridad" << endl;
        system("pause");
        return;
    }
    Archivo* vA = new Archivo[cant];
    cargarVArchivo(vA, cant, "Backup/Turnos/rutas.dat");
    while (true) {
        system("cls");
        for (int i = 1; i <= cant; i++)
        {
            cout << i << ". " << vA[i - 1].getNombre() << endl;
        }
        cout << "Ingrese una opcion para restaurar: ";
        cin >> opcion;
        if (opcion > 0 && opcion <= cant) {
            migrarBKTurnos(vA[opcion - 1], cant, "Turnos.dat");
            cout << "El archivo ha sido restaurado" << endl;
            delete[] vA;
            return;
        }
        else {
            cout << "Opcion incorrecta. Vuelva a intentar." << endl;
            system("pause");
        }

    }

    delete[] vA;
}

//-----------------------------------------------------------------------------------------------

void migrarBKPagos(Archivo& ruta, int cant, const char* nombre) {
    FacturaConsulta reg;
    int pos = 0;
    FILE* p;
    p = fopen("Pagos.dat", "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
    while (reg.leerCopiaDeDisco(pos++, ruta.getNombre())) {
        reg.grabarEnDisco();
    }
    fclose(p);
}

void RestaurarCopiaSeguridadPagos() {
    FacturaConsulta reg;
    int pos = 0, opcion;
    int cant = cantRutasOk("Backup/Pagos/rutas.dat");
    if (cant == 0) {
        cout << "No existen copias de seguridad" << endl;
        system("pause");
        return;
    }
    Archivo* vA = new Archivo[cant];
    cargarVArchivo(vA, cant, "Backup/Pagos/rutas.dat");
    while (true) {
        system("cls");
        for (int i = 1; i <= cant; i++)
        {
            cout << i << ". " << vA[i - 1].getNombre() << endl;
        }
        cout << "Ingrese una opcion para restaurar: ";
        cin >> opcion;
        if (opcion > 0 && opcion <= cant) {
            migrarBKPagos(vA[opcion - 1], cant, "Pagos.dat");
            cout << "El archivo ha sido restaurado" << endl;
            delete[] vA;
            return;
        }
        else {
            cout << "Opcion incorrecta. Vuelva a intentar." << endl;
            system("pause");
        }

    }

    delete[] vA;
}

//-----------------------------------------------------------------------------------------------

void migrarBKHistoriasClinicas(Archivo& ruta, int cant, const char* nombre) {
    HistoriaClinica reg;
    int pos = 0;
    FILE* p;
    p = fopen("HistoriasClinicas.dat", "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
    while (reg.leerCopiaDeDisco(pos++, ruta.getNombre())) {
        reg.grabarEnDisco();
    }
    fclose(p);
}

void RestaurarCopiaSeguridadHC() {
    HistoriaClinica reg;
    int pos = 0, opcion;
    int cant = cantRutasOk("Backup/HistoriasClinicas/rutas.dat");
    if (cant == 0) {
        cout << "No existen copias de seguridad" << endl;
        system("pause");
        return;
    }
    Archivo* vA = new Archivo[cant];
    cargarVArchivo(vA, cant, "Backup/HistoriasClinicas/rutas.dat");
    while (true) {
        system("cls");
        for (int i = 1; i <= cant; i++)
        {
            cout << i << ". " << vA[i - 1].getNombre() << endl;
        }
        cout << "Ingrese una opcion para restaurar: ";
        cin >> opcion;
        if (opcion > 0 && opcion <= cant) {
            migrarBKHistoriasClinicas(vA[opcion - 1], cant, "HistoriasClinicas.dat");
            cout << "El archivo ha sido restaurado" << endl;
            delete[] vA;
            return;
        }
        else {
            cout << "Opcion incorrecta. Vuelva a intentar." << endl;
            system("pause");
        }

    }

    delete[] vA;
}

//-----------------------------------------------------------------------------------------------

void migrarBKEmpleados(Archivo& ruta, int cant, const char* nombre) {
    Empleado reg;
    int pos = 0;
    FILE* p;
    p = fopen("Empleados.dat", "wb");
    if (p == NULL) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
    while (reg.leerCopiaDeDisco(pos++, ruta.getNombre())) {
        reg.grabarEnDisco();
    }
    fclose(p);
}

void RestaurarCopiaSeguridadEmpleados() {
    Empleado reg;
    int pos = 0, opcion;
    int cant = cantRutasOk("Backup/Empleados/rutas.dat");
    if (cant == 0) {
        cout << "No existen copias de seguridad" << endl;
        system("pause");
        return;
    }
    Archivo* vA = new Archivo[cant];
    cargarVArchivo(vA, cant, "Backup/Empleados/rutas.dat");
    while (true) {
        system("cls");
        for (int i = 1; i <= cant; i++)
        {
            cout << i << ". " << vA[i - 1].getNombre() << endl;
        }
        cout << "Ingrese una opcion para restaurar: ";
        cin >> opcion;
        if (opcion > 0 && opcion <= cant) {
            migrarBKEmpleados(vA[opcion - 1], cant, "Empleados.dat");
            cout << "El archivo ha sido restaurado" << endl;
            delete[] vA;
            return;
        }
        else {
            cout << "Opcion incorrecta. Vuelva a intentar." << endl;
            system("pause");
        }

    }

    delete[] vA;
}

//-----------------------------------------------------------------------------------------------
void RestaurarCopiaSeguridadTodos() {
    RestaurarCopiaSeguridadPacientes();
    RestaurarCopiaSeguridadTurnos();
    RestaurarCopiaSeguridadPagos();
    RestaurarCopiaSeguridadHC();
    RestaurarCopiaSeguridadEmpleados();
}

///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------
///ESTA FUNCION YA ESTA, REVISAR BIEN POR LAS DUDAS 
///ESTA FUNCION PERTENECE A Configuracion > ExportarDatos
void ExportarPacientes()
{
    Paciente reg;
    //reg.GrabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo paciente a un archivo de pacientes
    ofstream File;
    
    
    int pos = 0;
    File.open("csv/pacientes.csv"); //Este es el direcctorio adonde se guarda el archivo csv
        if (!File.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
        }
    File << "DNI" << ";" << "Nombres" << ";" << "Apellidos" << ";" << "Edad" << ";";
    File << "ID" << ";" << "Telefono" << ";" << "Email" << ";";
    File << "Dia de nacimiento" << ";" << "Mes de nacimiento" << ";" << "Anio de nacimiento" << ";";
    File << "Calle" << "; " << "Localidad" << "; " << "Partido" << "; " << "Provincia" << "; " << "CodigoPostal" << "; " << "Pais" << "; " << "Estado" << endl;
    
    while (reg.leerDeDisco(pos++)) //Esto carga a un objeto de tipo paciente un registro de un archivo de oacientes
    {
        ///Esto convierte lo que esta cargado en el objeto de tipo paciente a un archivo csv y lo guarda ahi
        File << reg.getDNI() << ";" << reg.getNombres() << ";" << reg.getApellidos() << ";" << reg.getEdad() << ";";
        File << reg.getID() << ";" << reg.getTelefono() << ";" << reg.getEmail() << ";";
        File << reg.getFechaNac().getDia() << ";" << reg.getFechaNac().getMes() << ";" << reg.getFechaNac().getAnio() << ";";
        File << reg.getDireccionPaciente().getCalle() << ";" << reg.getDireccionPaciente().getLocalidad() << ";" << reg.getDireccionPaciente().getPartido() << ";";
        File << reg.getDireccionPaciente().getProvincia() << ";" << reg.getDireccionPaciente().getCodigoPostal() << ";" << reg.getDireccionPaciente().getCodigoPostal() << ";";
        File << reg.getEstado() << endl;
    }

    cout << "Se exporto el archivo de pacientes exitosamente" << endl;
    
    File.flush();
    File.close();
}

//Me lo exporta daniado, revisar bien 
void ExportarTurnos()
{

    Turno reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo Turno a un archivo de Turnos

    ofstream File;
    File.open("csv/Turnos.csv"); //Este es el direcctorio adonde se guarda el archivo csv
    
    if (!File.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }

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

    cout << "Se exporto el archivo de turnos exitosamente" << endl;
    
    File.flush();
    File.close();
}



void ExportarPagosConsultas()
{

    FacturaConsulta reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo FacturaConsulta a un archivo de FacturaConsulta

    ofstream File;
    File.open("csv/FacturasConsultas.csv"); //Este es el direcctorio adonde se guarda el archivo csv
    if (!File.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }


    File << ";" << "ID" << ";" << "PrecioConsulta" << ";" << "IDPaciente" << ";" << "ObraSocial";
    File << ";" << "DiaFactura" << ";" << "MesFactura" << ";" << "AnioFactura";
    File << ";" << "DiaTurno" << ";" << "MesTurno" << ";" << "AnioTurno";
    File << ";" << "LegajoAdmin" << ";" << "FormaPago" << ";" << "LegajoMedico" << endl;

    int Pos = 0;
    while (reg.leerDeDisco(Pos) == true)
    {
        ///Esto convierte lo que esta cargado en el objeto de tipo FacturaConsulta a un archivo csv y lo guarda ahi
        ///Falta el get de precioconsulta
        File << ";" << reg.getID() << ";" << reg.getPrecioConsulta() << ";" << reg.getIDPaciente() << ";" << reg.getObraSocial();
        File << ";" << reg.getFechaFactura().getDia() << ";" << reg.getFechaFactura().getMes() << ";" << reg.getFechaFactura().getAnio();
        File << ";" << reg.getFechaTurno().getDia() << ";" << reg.getFechaTurno().getMes() << ";" << reg.getFechaTurno().getAnio();
        File << ";" << reg.getLegajoAdministrativo() << ";" << reg.getFormaPago() << endl;
        Pos++;
    }

    File.flush();
    File.close();
}



void ExportarHistoriasClinicas()
{

    HistoriaClinica reg;
    //reg.grabarEnDisco(0);  ///Esta linea la use para grabar un objeto de tipo HistoriaClinica a un archivo de HistoriaClinica

    ofstream File;
    File.open("csv/HistoriasClinicas.csv"); //Este es el direcctorio adonde se guarda el archivo csv
    if (!File.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }

    File << ";" << "IDTurno" << ";" << "DetallesConsulta"  << endl;
    int Pos = 0;

    while (reg.leerDeDisco(Pos) == true)
    {

        File << ";" << reg.getIDTurno() << ";" << reg.getDetallesConsulta() << endl;
        Pos++;
    }

    File.flush();
    File.close();
}



void ExportarEmpleados()
{
    int pos = 0;
    Cadena especialidad[3] = { "Administrativo","Medico","Administrador" };
    Cadena especialidades[12] = { "Administrador","Administrativo","Pediatria", "Kinesiologia", "Oftalmologia", 
        "Traumatologia", "Obstetricia", "Psicologia", "Nutricion", "Psiquiatria", "Dermatologia", "Cardiologia" };
    Empleado reg;
    ofstream File;
    File.open("csv/Empleados.csv"); //Este es el direcctorio adonde se guarda el archivo csv
    if (!File.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }
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
    File << "Legajo" << ";" << "Password" << ";" << "Email" << ";" << "Tipo de Empleado";
    File << ";" << "Especialidad" << endl;
    while (reg.leerDeDisco(pos))
    {
        if (reg.getTipoEmpleado() == 99) {
            File << reg.getLegajo() << ";" << reg.getPassword() <<";"<<reg.getEmail()<<";"<< especialidad[2].getCadena()<<";"
                <<especialidades[reg.getEspecialidad().getNEspecialidades()].getCadena() << endl;
        }
        else {
            File << reg.getLegajo() << ";" << reg.getPassword() << ";" << reg.getEmail() << ";" << 
                especialidad[reg.getTipoEmpleado()-1].getCadena() << ";" <<
                especialidades[reg.getEspecialidad().getNEspecialidades()-1].getCadena() << endl;
        }
        pos++;
    }
    File.flush();
    File.close();
}



void ExportarTodosLosArchivos()
{

    ExportarPacientes();

    ExportarTurnos();

    ExportarPagosConsultas();

    ExportarHistoriasClinicas();

    ExportarEmpleados();


}
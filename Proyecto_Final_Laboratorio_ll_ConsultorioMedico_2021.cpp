#include <iostream>
#include "Direccion.h"
#include "Empleado.h"
#include "FacturaConsulta.h"
#include "Fecha.h"
#include "HistoriaClinica.h"
#include "Hora.h"
#include "Paciente.h"
#include "Persona.h"
#include "Turno.h"
#include "FuncionesGlobales.h"
#include "FuncionesGlobalesDeMenus.h"
#include "TemplatesHTML.h"
#include "Fecha_Hora.h"
#include "HorarioEmpleado.h"
#include "Archivo.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main()
{
    //ESTA ES UNA PRUEBA DE MODIFICACION EN GITHUB
    //RestaurarCopiaSeguridadPacientes();
    ///ListadoDePacientesPorApellido();
    /*Archivo reg;
    int pos = 0;
    while (reg.leerDeDisco(pos++, "Backup/Pacientes/rutas.dat"))
    {
        reg.Mostrar();
    }*/
    /*Archivo reg;
    int pos = 0;
    while (reg.leerDeDisco(pos++,"Backup/Pacientes/rutas.dat")) {
        reg.Mostrar();
    }*/
    //CopiaSeguridadPacientes();
    //CopiaSeguridadEmpleados();
    //ExportarEmpleados();
    //char c[2] = { 92 };
    //cout << c;
    //AgregarPaciente();
    //prueba();
    //Fecha f(14,1,2022);
    //f.Mostrar();
    //cout << f.getFeriado();
    //cout<<f.getNumeroDia();
    //Hora v[20];
    //cargarHorarios(v);
    //Fecha_Hora reg;
    //reg.Mostrar();
    //AsignarTurno();
    //ModificarTurno();
    //login();
    //Hora h1(8, 0), h2(18, 0);
    //HorarioEmpleado horaLaboral;
    //horaLaboral.setHoraEntrada(h1);
        
        /*
        Empleado reg;
        Especialidad e;
        reg.setDNI(123456);
        reg.setNombres("Ana");
        reg.setApellidos("Gutierrez");
        reg.setLegajo(3333);
        char pass[30];
        strcpy(pass, "AnaMartinez");
        reg.setPassword(pass);
        reg.setEmail("leandro.gomez3@alumnos.frgp.utn.edu.ar");
        reg.setTipoEmpleado(2);
        e.setNEspecialidades(5);
        reg.setEspecialidad(e);
        reg.grabarEnDisco();
        */
    
        
    /*
    Turno reg;
    Fecha f(5, 12, 2021);
    reg.setFechaTurno(f);
    reg.setLegajoMedico(3333);
    reg.grabarEnDisco(0);
    */


    //Empleado reg(horaEntrada, horaSalida, 123456, "Tobias", "Iaconis", 321, "321", "tobias.iaconis@alumnos.frgp.utn.edu.ar", 1, 0, true);
    //reg.grabarEnDisco(0);
    //obj.grabarEnDisco(0);
    //cout << endl;
    
/*
    Empleado reg;
    int pos = 0;
    
    
    while (reg.leerDeDisco(pos)==true) {
        reg.Mostrar();
        //cout << reg.getEspecialidad().getNEspecialidades() << endl;
        //cout << reg.getLegajoMedico() << endl;
        //cout << reg.getLegajo() << endl;
        cout << endl;
        pos++;
    }
    */
    
    //GestionarPagos();
    //ListadoDeTurnosOrdenadosPorEspecialidad();

    //ConsultaPacientePorDNI();
    //ConsultaDeTurnosPorEspecialidad();
   
    //ConsultaPorCliente();
    //ConsultaPorObraSocial();

    //Consultas();
    //ConsultaPorAdministrativo();

    //CantidadTurnosAsignadosEnMes();

    //t.setFechaAsignacionTurno();
    //t.getFechaAsignacionTurno().Mostrar();*/
    //prueba();

    //RecaudacionAnual();

    //Informes();

/*
Paciente reg;
reg.GrabarEnDisco();
*/

    //ExportarDatos();
    
Listados();

    /*
    HistoriaClinica reg;
    reg.grabarEnDisco(0);
    << ";"
    */

}





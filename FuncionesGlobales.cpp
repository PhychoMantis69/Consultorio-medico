#include "FuncionesGlobales.h"
#include "FuncionesGlobalesDeMenus.h"
#include "TemplatesHTML.h"
#include "Empleado.h"
#include <iostream>
#include <conio.h>
#include "string.h"

using namespace std;

void cargarCadena(char* pal, int tam) {
    int i;
    fflush(stdin);
    for (i = 0; i < tam; i++) {
        pal[i] = cin.get();
        if (pal[i] == '\n') break;
    }
    pal[i] = '\0';
    fflush(stdin);
}
int buscarUsuarioYContrasenia(int usuario, char* password) {
    Empleado reg;
    int pos = 0;
    while (reg.leerDeDisco(pos)) {
        if (reg.getLegajo() == usuario && strcmp(reg.getPassword(), password) == 0) {
            return reg.getTipoEmpleado();
        }
        pos++;
    }
    return 0;
}
void leerPassword(char* password)
{
    int i = 0;
    cout.flush();

    do
    {
        password[i] = (unsigned char)_getch();

        if (password[i] != 8)  // no es retroceso
        {
            cout << '*';  // muestra por pantalla
            i++;
        }
        else if (i > 0)    // es retroceso y hay caracteres
        {
            cout << (char)8 << (char)32 << (char)8;
            i--;  //el caracter a borrar e el backspace
        }
        cout.flush();

    } while (password[i - 1] != 13);  // si presiona ENTER

    password[i - 1] = NULL;
    cout << endl;
}



void login() {
    int usuario;
    char password[30];
    int tipoEmpleado;
    while (true) {
        system("cls");
        cout << "\t\tLOGIN DE USUARIO" << endl;
        cout << "------------------------------------" << endl;
        cout << "Ingrese Usuario: " << endl;
        cin >> usuario;
        cin.ignore();
        cout << "Ingrese Contrasena: " << endl;
        leerPassword(password);
        tipoEmpleado = buscarUsuarioYContrasenia(usuario, password);
        system("cls");

        switch (tipoEmpleado) {
        case 1:
            menuAdministrativo();
            break;
        case 2:
            menuMedico(usuario);
            break;
        case 99:
            menuAdministrador();
            break;
        default:
            cout << "Usuario o contrasenia incorrecto. Ingrese de nuevo" << endl;
            system("pause");
        }
    }
}

void menuAdministrativo() {
    int opc;
    while (true)
    {
        cout << "Bienvenido/a XXXXXXXXXXXXX" << endl;
        cout << "----------------------------------" << endl;
        cout << "1-ASIGNAR TURNO." << endl;
        cout << "2-MODIFICAR TURNO. " << endl;
        cout << "3-ELIMINAR TURNO." << endl;
        cout << "4-AGREGAR PACIENTES AL SISTEMA." << endl;
        cout << "5-GESTIONAR PAGOS." << endl;
        cout << "0-VOLVER AL MENU PRINCIPAL." << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            AsignarTurno();
            break;
        case 2:
            system("cls");
            ModificarTurno();
            break;
        case 3:
            system("cls");
            EliminarTurno();
            break;

        case 4:
            system("cls");
            AgregarPaciente();
            break;

        case 5:
            system("cls");
            GestionarPagos();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }


        system("pause");
        system("cls");
    }

}

void menuMedico(int usuario) {
    int opc;
    while (true)
    {
        cout << "Bienvenido/a XXXXXXXXXXXXX" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "1-VER PACIENTES DEL DIA." << endl;
        cout << "2-AGREGA UN REGISTRO DE HISTORIA CLINICA." << endl;
        cout << "3-MODIFICAR REGISTRO DE HISTORIA CLINICA PARA UN PACIENTE." << endl;
        cout << "0-VOLVER AL MENU PRINCIPAL." << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            VerTurnosDelDia(usuario);
            break;
        case 2:
            system("cls");
            AgregaRegistroDeHistoriaClinica(usuario);
            break;
        case 3:
            system("cls");
            ModificarRegistroDeHistoriaClinica(usuario);
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO." << endl;
            break;
        }

        system("pause");
        system("cls");
    }

}

void menuAdministrador() {
    int opc;
    while (true)
    {
        cout << "Bienvenido/a XXXXXXXXXXXXX" << endl;
        cout << "------------------------------------" << endl;
        cout << "1-AGREGAR UN USUARIO. " << endl;
        cout << "2-ELIMINAR UN USUARIO. " << endl;
        cout << "3-MODIFICAR UN USUARIO. " << endl;
        cout << "4-CONFIGURACIONES." << endl;
        //cout << "5-ASIGNACION DE LIMITE DE TURNOS." << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            AgregarUnUsuario();
            break;
        case 2:
            system("cls");
            EliminarUsuario();
            break;
        case 3:
            system("cls");
            ModificarUsuario();
            break;

        case 4:
            system("cls");
            ConfiguracionesAdministrador();
            break;

        case 5:
            system("cls");
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls");
    }


}

void ConfiguracionesAdministrador() {
    int opc;
    while (true)
    {
        cout << "1-REALIZAR UNA COPIA DE SEGURIDAD" << endl;
        cout << "2-RESTAURAR COPIA DE SEGURIDAD" << endl;
        cout << "3-EXPORTAR DATOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            CopiaSeguridad();///OK
            break;
        case 2:
            system("cls");
            RestaurarCopiasSeguridad();
            break;
        case 3:
            system("cls");
            ExportarDatos();///OK
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }

}

void CopiaSeguridad() {
    int opc;
    while (true)
    {
        cout << "¿DE QUE ARCHIVO DE DESEA REALIZAR LA COPIA?" << endl;
        cout << "1-PACIENTES" << endl;
        cout << "2-TURNOS" << endl;
        cout << "3-PAGOS" << endl;
        cout << "4-HISTORIAS CLINICAS" << endl;
        cout << "5-EMPLEADOS" << endl;
        cout << "6-TODOS LOS ARCHIVOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            CopiaSeguridadPacientes();///OK
            break;
        case 2:
            system("cls");
            CopiaSeguridadTurnos();///OK
            break;
        case 3:
            system("cls");
            CopiaSeguridadPagos();///OK
            break;

        case 4:
            system("cls");
            CopiaSeguridadHC();///OK
            break;

        case 5:
            system("cls");
            CopiaSeguridadEmpleados();///OK
            break;

        case 6:
            system("cls");
            CopiaSeguridadTodos();///OK
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }

}

void RestaurarCopiasSeguridad() {
    int opc;
    while (true)
    {
        cout << "¿DE QUE ARCHIVO DE DESEA RESTAURAR UNA COPIA DE SEGURIDAD?" << endl;
        cout << "1-PACIENTES" << endl;
        cout << "2-TURNOS" << endl;
        cout << "3-PAGOS CONSULTAS" << endl;
        cout << "4-HISTORIAS CLINICAS" << endl;
        cout << "5-EMPLEADOS" << endl;
        cout << "6-TODOS LOS ARCHIVOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            RestaurarCopiaSeguridadPacientes();
            break;
        case 2:
            system("cls");
            RestaurarCopiaSeguridadTurnos();
            break;
        case 3:
            system("cls");
            RestaurarCopiaSeguridadPagos();
            break;

        case 4:
            system("cls");
            RestaurarCopiaSeguridadHC();
            break;

        case 5:
            system("cls");
            RestaurarCopiaSeguridadEmpleados();
            break;

        case 6:
            system("cls");
            RestaurarCopiaSeguridadTodos();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }


}

void ExportarDatos() {
    int opc;
    while (true)
    {
        cout << "¿DE QUE ARCHIVO DE DESEA EXPORTAR DATOS?" << endl;
        cout << "1-PACIENTES" << endl;
        cout << "2-TURNOS" << endl;
        cout << "3-PAGOS CONSULTAS" << endl;
        cout << "4-HISTORIAS CLINICAS" << endl;
        cout << "5-EMPLEADOS" << endl;
        cout << "6-TODOS LOS ARCHIVOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ExportarPacientes();
            break;
        case 2:
            system("cls");
            ExportarTurnos();
            break;
        case 3:
            system("cls");
            ExportarPagosConsultas();
            break;

        case 4:
            system("cls");
            ExportarHistoriasClinicas();
            break;

        case 5:
            system("cls");
            ExportarEmpleados();
            break;

        case 6:
            system("cls");
            ExportarTodosLosArchivos();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }


}

///------------------------------------------------------


void Listados()
{

    int opc;
    while (true)
    {
        cout << "¿QUE LISTADO DESEA VER?" << endl;
        cout << "1-LISTADO DE PACIENTES" << endl;
        cout << "2-LISTADO DE ADMINISTRATIVOS" << endl;
        cout << "3-LISTADO DE ADMINISTRADORES" << endl;
        cout << "4-LISTADO DE MEDICOS" << endl;
        cout << "5-LISTADO DE TURNOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoDePacientes();
            break;
        case 2:
            system("cls");
            ListaDeAdministrativos();
            break;
        case 3:
            system("cls");
            ListadoDeAdministradores();
            break;

        case 4:
            system("cls");
            ListadoDeMedicos();
            break;

        case 5:
            system("cls");
            ListadoDeTurnos();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }
}

///-----------------------------------------------------------------
///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDePacientes()
{

    int opc;
    while (true)
    {
        cout << "¿COMO QUIERE VER LOS LISTADOS DE PACIENTES?" << endl;
        cout << "1-ORDENADOS POR APELLIDO" << endl;
        cout << "2-ORDENADOS POR EDAD" << endl;
        cout << "3-ORDENADOS POR CIUDAD" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoDePacientesPorApellido();
            break;
        case 2:
            system("cls");
            PorEdad();
            break;
        case 3:
            system("cls");
            PorCiudad();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }
}

///----------------------------------------------------------------
///ESTA FUNCION PERTENECE A LISTADOS
void ListaDeAdministrativos()
{

    int opc;
    while (true)
    {
        cout << "¿COMO QUIERE VER LOS LISTADOS DE ADMINISTRATIVOS?" << endl;
        cout << "1-ORDENADOS POR LEGAJO" << endl;
        cout << "2-ORDENADOS POR APELLIDO" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoAdministrativosOrdenadoPorLegajo();
            break;
        case 2:
            system("cls");
            ListadoAdministrativosOrdenadoPorNombre();
            break;
        case 0:
            return;
        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }


}

///--------------------------------------------------------
///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeAdministradores()
{

    int opc;
    while (true)
    {
        cout << "¿COMO QUIERE VER LOS LISTADOS DE ADMINISTRADORES?" << endl;
        cout << "1-ORDENADOS POR LEGAJO" << endl;
        cout << "2-ORDENADOS POR APELLIDO" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoAdministradoresOrdenadoPorLegajo();
            break;
        case 2:
            system("cls");
            ListadoAdministradoresOrdenadoPorApellido();
            break;
        case 0:
            return;
        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }
        system("pause");
        system("cls"); 
    }
}



///--------------------------------------------------------

///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeMedicos()
{

    int opc;
    while (true)
    {
        cout << "¿COMO QUIERE VER LOS LISTADOS DE MEDICOS?" << endl;
        cout << "1-ORDENADOS POR LEGAJO" << endl;
        cout << "2-ORDENADOS POR APELLIDO" << endl;
        cout << "3-ORDENADOS POR ESPECIALIDAD" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoMedicosOrdenadoPorLegajo();
            break;
        case 2:
            system("cls");
            ListadoMedicosOrdenadoPorApellido();
            break;

        case 3:
            system("cls");
            ListadoMedicosOrdenadoPorEspecialidad();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }
}


///---------------------------------------------------------
///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeTurnos()
{

    int opc;
    while (true)
    {
        cout << "¿COMO QUIERE VER LOS LISTADOS DE TURNOS?" << endl;
        cout << "1-ORDENADOS POR FECHA" << endl;
        cout << "2-ORDENADOS POR ESPECIALIDAD" << endl;
        cout << "3-ORDENADOS POR MEDICO TRATANTE" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ListadoDeTurnosOrdenadosPorFecha();
            break;
        case 2:
            system("cls");
            ListadoDeTurnosOrdenadosPorEspecialidad();
            break;

        case 3:
            system("cls");
            //todo:aca hay algo raro..en la funcion de tobias esta ConsultaDePagos();
            //todo: ¿que cosa? (?
            ListadoDeTurnosOrdenadosPorMedicoTratante();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); 
    }
}


///-----------------------------------------------------------

void Consultas()
{

    int opc;
    while (true)
    {
        cout << "¿QUE TIPO DE CONSULTA DESEA HACER?" << endl;
        cout << "1-CONSULTA DE PACIENTES" << endl;
        cout << "2-CONSULTA DE TURNOS" << endl;
        cout << "3-CONSULTA DE PAGOS" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ConsultaDePacientes();
            break;
        case 2:
            system("cls");
            ConsultaDeTurnos();
            break;

        case 3:
            system("cls");
            ConsultaDePagos();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }

}

///--------------------------------------------------------

///ESTA FUNCION PERTENECE A CONSULTAS
void ConsultaDePacientes()
{

    int opc;
    while (true)
    {
        cout << "¿QUE TIPO DE CONSULTA DESEA HACER?" << endl;
        cout << "1-POR DNI" << endl;
        cout << "2-POR RANGO DE EDAD" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ConsultaPacientePorDNI();
            break;
        case 2:
            system("cls");
            ConsultaPacientePorRangoEdad();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); 
    }
}

///-------------------------------------------------------------
///ESTA FUNCION PERTENECE A CONSULTAS
void ConsultaDeTurnos()
{

    int opc;
    while (true)
    {
        cout << "¿QUE TIPO DE CONSULTA DESEA HACER?" << endl;
        cout << "1-POR TURNOS NO ASISTIDOS" << endl;
        cout << "2-POR RANGO DE FECHA" << endl;
        cout << "3-POR ESPECIALIDAD" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ConsultaDeTurnosNoAsistidos();
            break;
        case 2:
            system("cls");
            ConsultaDeTurnosPorRangoDeFecha();
            break;

        case 3:
            system("cls");
            ConsultaDeTurnosPorEspecialidad();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }
}

///--------------------------------------------------------------------------

///ESTA FUNCION PERTENECE A CONSULTAS
void ConsultaDePagos()
{

    int opc;
    while (true)
    {
        cout << "¿QUE TIPO DE CONSULTA DESEA HACER?" << endl;
        cout << "1-POR RANGO DE FECHA" << endl;
        cout << "2-POR CLIENTE" << endl;
        cout << "3-POR OBRA SOCIAL" << endl;
        cout << "4-POR ADMINISTRATIVO QUE TOMA EL PAGO" << endl;
        cout << "0- VOLVER" << endl << endl;
        cout << "INGRESE UNA OPCION ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            ConsultaPorRangoFecha();
            break;
        case 2:
            system("cls");
            ConsultaPorCliente();
            break;

        case 3:
            system("cls");
            ConsultaPorObraSocial();
            break;

        case 4:
            system("cls");
            ConsultaPorAdministrativo();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); ///Se realizan 2 system pause
    }

}

///-------------------------------------------------------------------------

void Informes() {

    int opc;
    while (true)
    {
        cout << "¿QUE INFORNE DESEA VER?" << endl;
        cout << "1-CANTIDAD DE TURNOS ASIGANADOS EN EL MES." << endl;
        cout << "2-CANTIDAD DE PACIENTES QUE FUERON A LOS TURNOS." << endl;
        cout << "3-RECAUDACION MENSUAL." << endl;
        cout << "4-RECAUDACION ANUAL." << endl;
        cout << "5-RECAUDACION POR CLIENTE." << endl;
        cout << "6-RECAUDACION POR ESPECIALIDAD." << endl;
        cout << "0- VOLVER." << endl << endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        cout << endl;

        switch (opc)
        {
        case 1:
            system("cls");
            CantidadTurnosAsignadosEnMes();
            break;
        case 2:
            system("cls");
            AusenciasTurnosMes();
            break;

        case 3:
            system("cls");
            RecaudacionMensual();
            break;

        case 4:
            system("cls");
            RecaudacionAnual();
            break;

        case 5:
            system("cls");
            RecaudacionPorCliente();
            break;


        case 6:
            system("cls");
            RecaudacionPorEspecialidad();
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "LA OPCION INGRESADA NO EXISTE, VUELVA A INTENTARLO" << endl;
            break;
        }

        system("pause");
        system("cls"); 
    }


}
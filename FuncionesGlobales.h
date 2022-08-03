#pragma once
#include "TemplatesHTML.h"
//#include "Empleado.h"

void cargarCadena(char* pal, int tam);
int buscarUsuarioYContrasenia(int usuario, char* password);

void login();
void menuAdministrativo();
void menuMedico(int usuario);
void menuAdministrador();
void Listados();
void Consultas();
void Informes();
void ConfiguracionesAdministrador(); ///ESTA FUNCION PERTENECE A ADMINISTRATIVO
void CopiaSeguridad(); ///ESTA FUNCION PERTENECE A ADMINISTRATIVO
void RestaurarCopiasSeguridad(); ///ESTA FUNCION PERTENECE A ADMINISTRATIVO
void ExportarDatos(); ///ESTA FUNCION PERTENECE A ADMINISTRATIVO
void ExportarPacientes();
void ListadoDePacientes(); ///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDePacientesPorApellido(); ///ESTA FUNCION PERTENECE A ListadoDePacientes
void PorEdad(); ///ESTA FUNCION PERTENECE A ListadoDePacientes
void PorCiudad(); ///ESTA FUNCION PERTENECE A ListadoDePacientes
void ListaDeAdministrativos(); ///ESTA FUNCION PERTENECE A Listados
void ConsultaDePagos(); /// ESTA FUNCION PERTENECE A Consultas
void ConsultaPorRangoFecha(); ///ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorCliente(); /// ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorObraSocial(); /// ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorAdministrativo(); /// ESTA FUNCION PERTENECE A ConsultaDePagos

void ListadoAdministrativosOrdenadoPorLegajo(); ///ESTA FUNCION PERTENECE A Listados
void ListadoAdministrativosOrdenadoPorNombre(); ///ESTA FUNCION PERTENECE A Listados
void ConsultaDePacientes();///ESTA FUNCION PERTENECE A CONSULTAS
void VerTurnosDelDia(int Usuario);
void AgregaRegistroDeHistoriaClinica(int Usuario);
void ModificarRegistroDeHistoriaClinica(int Usuario);
void AgregarUnUsuario();  ///ESTA OPCION PERTENECE AL MENU DE ADMINISTRADOR
void EliminarUsuario();   ///ESTA OPCION PERTENECE AL MENU DE ADMINISTRADOR
void ModificarUsuario();
void GestionarPagos();







void ListadoDeAdministradores(); ///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeMedicos();  ///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeTurnos();   ///ESTA FUNCION PERTENECE A LISTADOS

void ConsultaDeTurnos();   ///ESTA FUNCION PERTENECE A CONSULTAS
void ConsultaDePagos();   ///ESTA FUNCION PERTENECE A CONSULTAS
//void ModificarTurno(); ///Modifica un registro de tipo turno

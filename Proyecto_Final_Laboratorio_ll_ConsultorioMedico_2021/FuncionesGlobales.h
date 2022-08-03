#pragma once

void cargarCadena(char* pal, int tam);
int buscarUsuarioYContrasenia(int usuario, char* password);
void login();
void menuAdministrativo();
void menuMedico(int Usuario);
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
void ListaDeAdministrativos(); ///ESTA FUNCION PERTENECE A LISTADOS
void ConsultaDePagos(); /// ESTA FUNCION PERTENECE A Consultas
void ConsultaPorRangoFecha(); ///ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorCliente(); /// ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorObraSocial(); /// ESTA FUNCION PERTENECE A ConsultaDePagos
void ConsultaPorAdministrativo(); /// ESTA FUNCION PERTENECE A ConsultaDePagos
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------
void RecaudacionAnual();  ///ESTA FUNCION PERTENECE A Informes
void RecaudacionMensual();  ///ESTA FUNCION PERTENECE A Informes
void RecaudacionPorCliente();  ///ESTA FUNCION PERTENECE A Informes
void ListadoAdministrativosOrdenadoPorLegajo();  ///ESTA FUNCION PERTENECE A Listados
void ListadoAdministrativosOrdenadoPorNombre();  ///ESTA FUNCION PERTENECE A Listados
void ListadoDeTurnosOrdenadosPorFecha();
void ListadoDeTurnosOrdenadosPorEspecialidad();
void VerTurnosDelDia(int Usuario);

//void ListadoDeAdministradores(); ///ESTA FUNCION PERTENECE A LISTADOS
//void ListadoDeMedicos();  ///ESTA FUNCION PERTENECE A LISTADOS
void ListadoDeTurnos();   ///ESTA FUNCION PERTENECE A LISTADOS
void ConsultaDePaciente();  ///ESTA FUNCION PERTENECE A CONSULTAS
void ConsultaPorDni();
//void ConsultaDeTurnos();   ///ESTA FUNCION PERTENECE A CONSULTAS
//void ConsultaDePagos();   ///ESTA FUNCION PERTENECE A CONSULTAS
//void ModificarTurno(); ///Modifica un registro de tipo turno

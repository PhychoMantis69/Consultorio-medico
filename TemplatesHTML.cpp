#include "TemplatesHTML.h"
//#include "Empleado.h"
#include "Paciente.h"
#include <iostream>
#include <fstream>


using namespace std;
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
///LISTADOS
//todo: terminar esta funcion..y modificar el css para cambiar lo que dice cuando se vuelve responsive...acomodar la tabla
void MostrarPacientesListadosPorApellidos(Paciente* p, int cantRegistros) {
    ofstream file;
    file.open("Listados\\index.html");
    if (!file.is_open()) {
        cout << "ERROR DE ARCHIVO" << endl;
        return;
    }


	file << "<!DOCTYPE html>" << endl;
	file << "	<html lang=\"en\">" << endl;
	file << "	<head>" << endl;
	file << "	<title>Table V01</title>" << endl;
	file << "	<meta charset=\"UTF-8\">" << endl;
	file << "	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"icon\" type=\"image/png\" href=\"images/icons/favicon.ico\"/>" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/bootstrap/css/bootstrap.min.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href=\"fonts/font-awesome-4.7.0/css/font-awesome.min.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/animate/animate.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/select2/select2.min.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/perfect-scrollbar/perfect-scrollbar.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href =\"css/util.css\">" << endl;
	file << "	<link rel=\"stylesheet\" type=\"text/css\" href =\"css/main.css\">" << endl;
	file << "	<!--============================================================================================== = -->" << endl;
	file << "	</head>" << endl;
	file << "	<body>" << endl;
	file << "	<div class=\"limiter\">" << endl;
	file << "	<div class=\"container-table100\">" << endl;
	file << "	<div class=\"wrap-table100\">" << endl;
	file << "	<div class=\"table100\">" << endl;
	file << "	<table>" << endl;
	file << "	<thead>" << endl;
	file << "	<tr class=\"table100 - head\">" << endl;
	file << "	<th class=\"column1\">Apellido</th>" << endl;
	file << "	<th class=\"column2\">Nombre</th>" << endl;
	file << "	<th class=\"column3\">DNI</th>" << endl;
	file << "	<th class=\"column4\">Edad</th>" << endl;
	file << "	<th class=\"column5\">Telefono</th>" << endl;
	file << "	<th class=\"column6\">Email</th>" << endl;
	file << "	</tr>" << endl;
	file << "	</thead>" << endl;
	file << "	<tbody>" << endl;
    for (int i = 0; i < cantRegistros-1; i++)
    {
        if (strcmp(p[i].getNombres(), " ") == 0) continue;
        file << "	<tr>" << endl;
        file << "	<td class=\"column1\">"<<p[i].getApellidos()<<"</td >" << endl;
        file << "	<td class=\"column2\">"<<p[i].getNombres()<<"</td>" << endl;
        file << "	<td class=\"column3\">"<<p[i].getDNI()<<"</td>" << endl;
        file << "	<td class=\"column4\">"<<p[i].getEdad()<<"</td>" << endl;
        file << "	<td class=\"column5\">"<<p[i].getTelefono()<<"</td>"<<endl;
        file << "	<td class=\"column6\">"<<p[i].getEmail()<<"</td>"<<endl;
        file << "	</tr>" << endl;
    }
	
    file << "	</tbody>"<< endl;
    file << "	</table>"<< endl;
    file << "	</div>"<< endl;
    file << "	</div>"<< endl;
    file << "	</div>"<< endl;
    file << "	</div>"<< endl;
    file << "	<!--============================================================================================== = -->" << endl;
    file << "	<script src=\"vendor/jquery/jquery-3.2.1.min.js\"></script>"<< endl;
        file << "	<!--============================================================================================== = -->" << endl;
        file << "	<script src=\"vendor/bootstrap/js/popper.js\"></script>" << endl;
        file << "	<script src=\"vendor/bootstrap/js/bootstrap.min.js\"></script>" << endl;
        file << "	<!--============================================================================================== = -->" << endl;
        file << "	<script src=\"vendor/select2/select2.min.js\"></script>" << endl;
        file << "	<!--============================================================================================== = -->" << endl;
        file << "	<script src=\"js/main.js\"></script>" << endl;
        file << "	</body>" << endl;
        file << "	</html>" << endl;


    file.flush();
    file.close();
    system("Listados\\index.html");
}





//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
/*void prueba() {
	//char c = { 22 };
    //char c[2] = { 92 };
    //cout << c;
    int pos = 0;
	ofstream prueba;
    Paciente reg;
    reg.setNombres("Angel Simon");
	prueba.open("html/index.html");
    prueba << "<!DOCTYPE html>" << endl;
        prueba << "<html lang=\"en\">" << endl;
        prueba << "<head>" << endl;
        prueba << "<meta charset=\"utf-8\">" << endl;
        prueba << "<title>Example 1</title>" << endl;
        prueba << "<link rel=\"stylesheet\"href=\"style.css\" media=\"all\"/>" << endl;
        prueba << "</head>" << endl;
        prueba << "<body>" << endl;
        prueba << "<header class=\"clearfix\">" << endl;
        prueba << "<div id=\"logo\">" << endl;
        prueba << "<img src=\"images.jpg\">" << endl;
        prueba << "</div>" << endl;
        prueba << "<h1>"<< reg.getNombres() <<"</h1>" << endl;
        prueba << "<div id=\"company\" class=\"clearfix\">" << endl;
        prueba << "<div>Company Name</div>" << endl;
        prueba << "<div>455 Foggy Heights, <br/> AZ 85004, US</div>" << endl;
        prueba << "<div>(602) 519 - 0450 </div>" << endl;
        prueba << "<div><a href=\"mailto:company@example.com\">company@example.com</a></div>" << endl;
        prueba << "</div>" << endl;
        prueba << "<div id=\"project\">" << endl;
        prueba << "<div><span>PROJECT</span> Website development</div>" << endl;
        prueba << "<div><span>CLIENT</span> John Doe</div>" << endl;
        prueba << "<div><span>ADDRESS</span> 796 Silver Harbour, TX 79273, US</div>" << endl;
        prueba << "<div><span>EMAIL</span> <a href=\"mailto:john@example.com\">john@example.com</a></div>" << endl;
        prueba << "<div><span>DATE</span> August 17, 2015 </div>" << endl;
        prueba << "<div><span>DUE DATE</span> September 17, 2015 </div>" << endl;
        prueba << "</div>" << endl;
        prueba << "</header>" << endl;
        prueba << "<main>" << endl;
        prueba << "<table>" << endl;
        prueba << "<thead>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<th class=\"service\">NOMBRE</th>" << endl;
        prueba << "<th class=\"desc\">APELLIDO</th>" << endl;
        prueba << "<th class=\"prueba\">DNI</th>" << endl;
        prueba << "<th>EDAD</th>" << endl;
        prueba << "<th>ID</th>" << endl;
        prueba << "<th>PARTIDO</th>" << endl;
        prueba << "</tr>" << endl;
        prueba << "</thead>" << endl;
        prueba << "<tbody>" << endl;
        while (reg.leerDeDisco(pos++))
        {
            prueba << "<tr>" << endl;
            prueba << "<td class=\"service\">"<<reg.getNombres()<<"</td>" << endl;
            prueba << "<td class=\"desc\">"<<reg.getApellidos()<<"</td>" << endl;
            prueba << "<td class=\"prueba\">"<<reg.getDNI()<<"</td>" << endl;
            prueba << "<td class=\"unit\">"<<reg.getEdad()<<"</td>" << endl;
            prueba << "<td class=\"qty\">"<<reg.getID()<<"</td>" << endl;
            prueba << "<td class=\"total\">"<<reg.getDireccionPaciente().getPartido()<<"</td>" << endl;
            prueba << "</tr>" << endl;
        }
        prueba << "<tr>" << endl;
        prueba << "<td class=\"service\">Development</td>" << endl;
        prueba << "<td class=\"desc\">Developing a Content Management System - based Website</td>" << endl;
        prueba << "<td class=\"prueba\">Esto es una prueba</td>" << endl;
        prueba << "<td class=\"unit\">$40.00</td>" << endl;
        prueba << "<td class=\"qty\">80</td>" << endl;
        prueba << "<td class=\"total\">$3,200.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<td class=\"service\">SEO</td>" << endl;
        prueba << "<td class=\"desc\">Optimize the site for search engines(SEO)</td >" << endl;
        prueba << "<td class=\"prueba\">Esto es una prueba</td>" << endl;
        prueba << "<td class=\"unit\">$40.00 </td>" << endl;
        prueba << "<td class=\"qty\">20</td>" << endl;
        prueba << "<td class=\"total\">$800.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<td class=\"service\">Training</td>" << endl;
        prueba << "<td class=\"desc\">Initial training sessions for staff responsible for uploading web content</td>" << endl;
        prueba << "<td class=\"prueba\">Esto es una prueba</td>" << endl;
        prueba << "<td class=\"unit\">$40.00 </td>" << endl;
        prueba << "<td class=\"qty\">4</td>" << endl;
        prueba << "<td class=\"total\">$160.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<td colspan=\"4\">SUBTOTAL</td>" << endl;
        prueba << "<td class=\"total\">$5,200.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<td colspan=\"4\">TAX 25 %</td>" << endl;
        prueba << "<td class=\"total\">$1,300.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "<tr>" << endl;
        prueba << "<td colspan=\"4\" class=\"grand total\">GRAND TOTAL</td>" << endl;
        prueba << "<td class=\"grand total\">$6,500.00</td>" << endl;
        prueba << "</tr>" << endl;
        prueba << "</tbody>" << endl;
        prueba << "</table>" << endl;
        prueba << "<div id=\"notices\">" << endl;
        prueba << "<div>NOTICE:</div>" << endl;
        prueba << "<div class=\"notice\">A finance charge of 1.5 % will be made on unpaid balances after 30 days.</div>" << endl;
        prueba << "</div>" << endl;
        prueba << "</main>" << endl;
        prueba << "<footer>" << endl;
        prueba << "Invoice was created on a computer and is valid without the signature and seal." << endl;
        prueba << "</footer>" << endl;
        prueba << "</body>" << endl;
        prueba << "</html>" << endl;
        prueba.close();
        system("html\\index.html");
}*/
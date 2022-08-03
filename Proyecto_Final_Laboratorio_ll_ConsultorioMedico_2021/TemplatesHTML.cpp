#include "TemplatesHTML.h"
#include <iostream>
#include <fstream>


using namespace std;

void prueba() {
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
}
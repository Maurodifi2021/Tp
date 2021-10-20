#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#define RUTAPOLIZA "Asegurados.BAK"

using namespace std;
char menu ()
{
    cout << "========= ASEGURADORA BIT =========" << endl;
    cout << "0- Levantar polizas" << endl;
    cout << "1- Cargar una poliza" << endl;
    cout << "2- Buscar una poliza existente" << endl;
    cout << "3- Desactivar una poliza existente" << endl;
    cout << "7- Listar todas las polizas (ordenado por cantidad de accidentes)" << endl;
    cout << "5- Mostrar todas las pólizas que no tengan la cuota al día (En formato CSV y HTML)." << endl;
    cout << "6- Procesar un lote de incidentes" << endl;
    cout << "Para finalizar el dia presiona esc" << endl;
    char opcion;
    do
    {
       opcion=getch();
    } while ((opcion!='0') && (opcion!='1') &&(opcion!='2') && (opcion!='3') && (opcion!='5') && (opcion!='6') && (opcion!='5') && (opcion!='6') && (opcion!='7') && (opcion!='8') && (opcion!=27));
    return opcion;
}
struct Polizas
{
    int poliza ;
    char dni [11];
    char nombre [12];
    char apellido [15];
    bool cuota;
    char patente [8];
    bool activa;
    int accidentes ;
};
struct incidente
{
    int Codigoincidente;
    int Fechahora;
    char DniAsegurado [11];
    char DniotroConductor[11];
    int Nropoliza;
    char Calle [50];
    int Altura;
};
void cargarpolizaprueba ()
{
    FILE *f;
    f= fopen (RUTAPOLIZA, "wb");
    Polizas p;
    if (f)
    {
        strcpy(p.apellido,"DIFILIPPO");
        strcpy(p.nombre,"MAURO");
        strcpy(p.dni,"44544627");
        p.cuota=false;
        strcpy(p.patente,"IGD150");
        p.activa=true;
        p.accidentes=1;
        p.poliza=9999;
        fwrite(&p, sizeof(Polizas),1,f);

        strcpy(p.apellido,"PUCENICZ");
        strcpy(p.nombre,"MATIAS");
        strcpy(p.dni,"76.890.345");
        p.cuota=true;
        strcpy(p.patente,"MMG234");
        p.activa=true;
        p.accidentes=10;
        p.poliza=3456;
        fwrite(&p, sizeof(Polizas),1,f);

        strcpy(p.apellido,"ALEGRE");
        strcpy(p.nombre,"JUAN");
        strcpy(p.dni,"23.456.789");
        p.cuota=false;
        strcpy(p.patente,"IFT560");
        p.activa=false;
        p.accidentes=0;
        p.poliza=1234;
        fwrite(&p, sizeof(Polizas),1,f);
        fclose (f);
    }
    else
        cout << "Error: no se pudo crear el archivo" << endl;
    return;
}
struct Nodopoliza
{
    Polizas info;
    Nodopoliza *sgte;
};
void mostrarpoliza( Nodopoliza *lista )
{
    cout << "Poliza nro: " << lista->info.poliza << endl;
    cout << "DNI: " << lista->info.dni << endl;
    cout << "Nombres: " << lista->info.nombre << endl;
    cout << "Apellidos: " << lista->info.apellido<< endl;
    cout << "Cuota: " << lista->info.cuota << endl;
    cout << "Patente: " << lista->info.patente << endl;
    cout << "Activa: " << lista->info.activa << endl;
    cout << "cantidad de incidentes: " << lista->info.poliza << endl;
    cout << endl;
}
void mostrarpolizas (Nodopoliza *lista)
{
    while (lista)
    {
        cout << "Poliza nro: " << lista -> info.poliza << endl;
        cout << "DNI: " << lista -> info.dni << endl;
        cout << "Nombres: " << lista -> info.nombre << endl;
        cout << "Apellidos: " << lista -> info.apellido<< endl;
        cout << "Cuota: " << lista -> info.cuota << endl;
        cout << "Patente: " << lista -> info.patente << endl;
        cout << "Activa: " << lista -> info.activa << endl;
        cout << "cantidad de incidentes: " << lista -> info.accidentes << endl;
        cout << endl;
        lista = lista->sgte;
    }
}
Nodopoliza *ObtenerSiguiente(Nodopoliza  *n)
{
    if (n)
        return n->sgte;
    else
        return NULL;
}
Nodopoliza* Buscarpoliza(Nodopoliza *raiz, int polizabuscada)
{
    Nodopoliza *p = raiz;
    while (p && (p->info.poliza != polizabuscada))
    {
        p = p->sgte;
    }
    return p;
}
Nodopoliza* BuscarpolizaDNI (Nodopoliza *raiz, char dnibuscado [])
{
    Nodopoliza *p = raiz;
    while (p)
    {
        strcmp(p->info.dni,dnibuscado);
        p = p->sgte;
    }
    return p;
}
Nodopoliza* BuscarNodoAnterior(Nodopoliza * raiz, Nodopoliza * anterior_a)
{
    Nodopoliza *p =NULL;
    if (raiz != anterior_a)
    {
        p = raiz;
        while (p && (p->sgte!= anterior_a) )
        {
            p = p->sgte;
        }
        return p;
    }
    else
        return NULL;
}
Nodopoliza *ListapolizaObtenerSiguiente(Nodopoliza  *n)
{
    if (n)
        return n->sgte;
    else
        return NULL;
}
void ListapolizaborrarLista(Nodopoliza *&lista)
{
    Nodopoliza *anterior;
    Nodopoliza *paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux= lista;
        while (paux && paux->sgte)
        {
            anterior = paux;
            paux= paux->sgte;
        }
        if (paux)
        {
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista =NULL;
        }
    }
    return;
}
void ListaPolizaBorrarSiguiente(Nodopoliza  *n)
{
    Nodopoliza  *borrar = n->sgte;
    Nodopoliza  *sgteborrar;
    if (borrar)
        sgteborrar= borrar->sgte;
    else
        sgteborrar = NULL;
    n->sgte = sgteborrar;
    delete borrar;
    return;
}
void ListaPolizaInsertarSiguiente (Nodopoliza  *&n, Polizas x)
{
    Nodopoliza *nuevo= new Nodopoliza();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }

    return;
}
void insertarOrdenado(Nodopoliza *&lista, Polizas p)
{
    Nodopoliza *paux = lista;
    Nodopoliza *anterior =NULL;
    while (paux && paux->info.accidentes < p.accidentes)
    {
        anterior = paux;
        paux = paux->sgte;
    }
    if ( paux!= lista)
    {
        anterior->sgte = new Nodopoliza();
        anterior->sgte->info = p;
        anterior->sgte->sgte = paux;

    }
    else
    {
        lista = new Nodopoliza();
        lista->sgte = paux;
        lista->info = p;
    }
    return;
}
void levantarPoliza(Nodopoliza *&a)
{
    FILE *pol;
    Polizas p;
    pol=fopen(RUTAPOLIZA,"r");
    fread(&p,sizeof(Polizas),1,pol);
    while (!feof(pol))
    {
        ListaPolizaInsertarSiguiente(a,p);
        fread(&p,sizeof(Polizas),1,pol);
    }
    fclose(pol);
    return;
}
void borrarNodopoliza(Nodopoliza *& raiz, Nodopoliza * aborrar)
{
    if (raiz && aborrar)
    {
        if (aborrar==raiz)
        {
            raiz = raiz->sgte;
            delete aborrar;
        }
        else
        {
            Nodopoliza *x = BuscarNodoAnterior(raiz,aborrar);
            ListaPolizaBorrarSiguiente(x);
        }
    }
    return;
}
void guardarpolizaDisco(Nodopoliza *la)
{
    FILE *pol;
    Nodopoliza *auxpol=NULL;
    if (pol= fopen(RUTAPOLIZA,"wb"))
    {
            auxpol= la;
            while (auxpol)
            {
                fwrite(&(auxpol->info), sizeof(Polizas),1,pol);
                auxpol= ListapolizaObtenerSiguiente(auxpol);
            }
            fclose(pol);
    }
        else
            cout << "ERROR AL INTENTAR GRABAR ARCHIVO DE POLIZAS" << endl;
        fclose(pol);
    return;
}
void mostrarenHTML (Nodopoliza *lista)
{
    FILE *f;
    Polizas p;
    f = fopen ("salidahtml.html","wt");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Polizas que no estan al dia</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Poliza</th><th>Apellido</th><th>Nombre</th><th>Dni</th><th>Patente</th><th>Cantidad de accidentes</th>\n");
    while (lista)
    {
        if (lista->info.cuota == false)
        {
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td>\n",lista->info.poliza,lista->info.apellido,lista->info.nombre,lista->info.dni,lista->info.patente,lista->info.accidentes);
            fprintf(f,"</tr>\n");
        }
        lista=lista->sgte;
    }
    fprintf(f, "</table>");
    fprintf(f, "</body>");
    fprintf(f, "</html>");
    fclose(f);
    return;
}
void mostrarenCSV(Nodopoliza *lista)
{
    FILE *f;
    f = fopen("salidaexcel.csv", "wt");
    fprintf(f,"Poliza;Apellido;Nombre;Dni;Patente;Cdad de Accidentes\n");
    while (lista)
    {
        if (lista->info.cuota==false)
        {
            fprintf(f,"%d;%s;%s;%s;%s;%d\n",lista->info.poliza,lista->info.apellido,lista->info.nombre,lista->info.dni,lista->info.patente,lista->info.accidentes);
        }
        lista = lista->sgte;
    }
    fclose(f);
    return;
}
int main()
{
    Nodopoliza *lista = NULL;
    Nodopoliza *aux=NULL;
    Nodopoliza *x=NULL;
    FILE *pol;
    Polizas p;
    int poliza, poliza2;
    char opcion; char cuota; char activa; char dni [11];
    do
    {
        opcion = menu();
        switch (opcion)
        {
            case '0':
                ListapolizaborrarLista(lista);
                /*cargarpolizaprueba ();*/
                levantarPoliza (lista);
                cout << "Archivos levantados correctamente" << endl;
            case '1':
                Polizas nuevapoliza;
                cout << "Ingrese los datos de la poliza: " << endl;
                cout << "Poliza (9999): " << endl;
                cin >> nuevapoliza.poliza;
                if (Buscarpoliza(lista,nuevapoliza.poliza))
                {
                    cout << "ERROR: YA HAY UNA POLIZA CON EL NRO QUE INTENTA INGRESAR" << endl;
                }
                else
                {
                    cout << "Ingrese el dni (xx.xxx.xxx): " << endl;
                    cin >> nuevapoliza.dni;
                    cout << "Nombre: ";
                    cin >> nuevapoliza.nombre;
                    cout << "Apellido: ";
                    cin >> nuevapoliza.apellido;
                    cout << "¿Cuota al dia? (v,f): ";
                    cin >> cuota;
                    if (cuota == 'v')
                        nuevapoliza.cuota = true;
                    else
                        nuevapoliza.cuota=false;
                    cout << "Patente del auto (AAA999AA o AAA999): ";
                    cin >> nuevapoliza.patente;
                    cout << "¿Esta activa? (v,f): ";
                    cin >> activa;
                    if (activa == 'v')
                        nuevapoliza.activa = true;
                    else
                        nuevapoliza.activa=false;
                    cout << "Cantidad de accidentes: ";
                    cin >> nuevapoliza.accidentes;
                    insertarOrdenado(lista,nuevapoliza);
                }
                break;
            case '2':
                cout << "Ingrese 1 para budcar por numero de poliza o ingrese 2 para buscar polizas por numero de DNI: " << endl;
                char eleccion;
                cin >> eleccion;
                if (eleccion == 49)
                {
                    cout << "Ingrese la poliza a buscar (9999): " << endl;
                    cin >> poliza;
                    x = Buscarpoliza (lista,poliza);
                }
                else if (eleccion == 50)
                {
                    cout << "Ingrese su dni (xx.xxx.xxx): " << endl;
                    cin >> dni;
                    x = BuscarpolizaDNI (lista,dni);
                }
                if (x)
                    mostrarpoliza(x);
                else
                    cout << "La poliza no esta en el archivo." << endl;
                break;
            case '3':
                    cout << "Ingrese legajo de la poliza a desactivar: " << endl;
                    cin >> poliza2;
                    borrarNodopoliza (lista, Buscarpoliza(lista,poliza2));
                    cout << "Se ha borrado correctamente" << endl;
                break;
            case '5':
                mostrarenHTML (lista);
                mostrarenCSV (lista);
                break;
            case '6':

                break;
            case '7':
                x = lista;
                mostrarpolizas (x);
                break;
    }
    }
    while (opcion != 27);
    guardarpolizaDisco (lista);
    ListapolizaborrarLista(lista);
    return 0;
}

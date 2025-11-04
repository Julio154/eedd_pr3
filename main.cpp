#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VDinamico.h"
#include "ListaEnlazada.h"
#include "Laboratorio.h"
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Avl.h"
#include "Farmacia.h"

/**
 * @authors Julio Gallegos Rojas jgr00087@red.ujaen.es
 * @author Silvia Cruz Román scr00043@red.ujaen.es
 */

/**
 * @brief funcion que nos muestra por pantalla un menu de opciones
 */
void menu1(){
    std::cout<<std::endl<<std::endl;
    std::cout<<"------MENU-----Programa de prueba 1: AVL"<<std::endl
    <<"1.Buscar el CIF de esas 500 farmacias en AVL"<<std::endl
    <<"2.Buscar el CIF de esas 500 farmacias en VectorDinamico"<<std::endl
    <<"3.Mostrar comparacion de tiempos de las busquedas anteriores"<<std::endl
    <<"4.Mostrar altura AVL con todas las farmacias"<<std::endl
    <<"5.Mostrar las 100 primeras farmacias en inorden"<<std::endl;
}
/**
 * @brief funcion que nos muestra por pantalla un menu de opciones
 */
void menu2(){
    std::cout<<"------MENU-----Programa de prueba 2: LAS OPCIONES NO CONTEMPLADAS TE PERMITEN SALIR"<<std::endl
            <<"1.Crear un vector tipo buffer con los siguientes CIF de farmacia"<<std::endl
            <<"2.Para todas las farmacias anteriores, buscar si alguna de ellas dispensa el ÓXIDO DE "<<
            "MAGNESIO” con ID=3640, y si no lo venden, hacer el pedido correspondiente. "<<std::endl
            <<"3.Buscar y contar todos los laboratorios con MAGNESIO"<<std::endl
            <<"4.PAREJAS: Localizar todos los laboratorios que suministran a alguna farmacia medicamentos con  VIRUS "<<std::endl;
}
/**
 * @brief funcion que nos muestra la lista de enteros
 * @param lista
 */
void mostrarEnteros(ListaEnlazada<int> *lista){
    int c=0;
    for (ListaEnlazada<int> ::Iterador it= lista->iteradorInicio();c < lista->tam() ; it.siguiente()) {
        std::cout<<" - "<<it.dato()<<"\t";
        c++;
    }
    std::cout<<std::endl;
}

void mostrarLaboratorios(ListaEnlazada<Laboratorio> *lista){
    for (ListaEnlazada<Laboratorio> ::Iterador it= lista->iteradorInicio();!it.fin() ; it.siguiente()) {
        std::cout<<" - "<<it.dato().get_nombre_lab()<<"\t"<<it.dato().get_localidad()<<std::endl;
    }
    std::cout<<std::endl;
}

void mostrarFarmaciasMedicamento(MediExpress medi_express) {
    std::cout<<"Farmacias con medicamentos: "<<std::endl;
    VDinamico<Farmacia*> farmacias = medi_express.get_pharmacy()->recorreInorden();
    for (int i = 0; i < farmacias.getTamlog(); i++) {
        std::cout<<farmacias[i]->get_nombre()<<"  :  "<<std::endl;
        for (int j = 0; j < farmacias[i]->medicamentosDispensados().getTamlog();j++) {
            std::cout<<"     "<<farmacias[i]->medicamentosDispensados()[j]->get_nombre()<<"\n";
        }
    }
}

/**
 * @author Silvia Cruz Roman scr00043@red.ujaen.es
 */
int main(int argc, const char * argv[]) {
    try{

        std::ifstream is;
        std::stringstream  columnas;
        std::string fila;
        Avl<Farmacia> farmacias_avl;

        std::string cif = "";
        std::string provincia="";
        std::string localidad="";
        std::string nombre = "";
        std::string direccion="";
        std::string codPostal="";

        int opcion;
 std::cout<<"Lectura de farmacias en avl"<<std::endl;

        is.open("../farmacias.csv"); //carpeta de proyecto
        clock_t t_ini_avl;

        if ( is.good() ) {
            t_ini_avl = clock();

            while ( getline(is, fila ) ) {

                //¿Se ha leído una nueva fila?
                if (fila!="") {

                    columnas.str(fila);

                    //formato de fila: cif;provincia;localidad;nombre;direccion;codPostal;

                    getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, provincia,';');
                    getline(columnas, localidad,';');
                    getline(columnas, nombre, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, direccion,';');
                    getline(columnas, codPostal,';');

                    fila="";
                    columnas.clear();

                    Farmacia farmacia(cif,provincia,localidad,nombre,direccion,codPostal);
                    farmacias_avl.inserta(farmacia);
                }
            }

            is.close();
        }

        clock_t t_ini_vdinamico;
        std::cout<<"Lectura de farmacias con Vdinamico"<<std::endl;
        VDinamico<Farmacia*> farmacias_vdinamico;

        int contador=0;
        VDinamico<std::string> VdinCif;
        is.open("../farmacias.csv"); //carpeta de proyecto
        if ( is.good() ) {
            t_ini_vdinamico = clock();
            while ( getline(is, fila ) ) {
                //¿Se ha leído una nueva fila?
                if (fila!="") {

                    columnas.str(fila);

                    //formato de fila: cif;provincia;localidad;nombre;direccion;codPostal;

                    getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, provincia,';');
                    getline(columnas, localidad,';');
                    getline(columnas, nombre, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, direccion,';');
                    getline(columnas, codPostal,';');

                    fila="";
                    columnas.clear();

                    if (contador<500) {
                        VdinCif.insertar(cif);
                    }
                    Farmacia farmacia(cif,provincia,localidad,nombre,direccion,codPostal);
                    farmacias_vdinamico.insertar(&farmacia);
                }
            }
            is.close();
        }

        clock_t t_ini_busqueda_vdin, t_fin_busqueda_vdin, t_fin_busqueda_avl, t_ini_busqueda_avl;
        MediExpress mediAuxAvl(farmacias_avl);
        do {
            menu1();
        std::cin>>opcion;

            switch (opcion) {
                case 1: {
                    std::cout <<"1.Buscar el CIF de esas 500 farmacias en AVL"<<std::endl;
                     t_ini_busqueda_avl=clock();
                    for (int i=0;i<500;i++) {
                        mediAuxAvl.buscarFarmacia(VdinCif[i]);
                    }
                     t_fin_busqueda_avl=clock();
                    std::cout << "Tiempo insertar: " << ((double)(t_fin_busqueda_avl - t_ini_busqueda_avl) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

                   }
                    break;
                case 2: {
                    std::cout<<"2.Buscar el CIF de esas 500 farmacias en VectorDinamico"<<std::endl;
                    t_ini_busqueda_vdin=clock();
                    for (int i=0;i<500;i++) {
                        for (int j=0;j<farmacias_vdinamico.getTamlog();j++){
                            if (farmacias_vdinamico[j]->get_cif()==VdinCif[i]) {
                                break;
                            }
                        }
                    }
                     t_fin_busqueda_vdin=clock();

                    std::cout << "Tiempo insertar: " << ((double)(t_fin_busqueda_vdin - t_ini_busqueda_vdin) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
                    break;
                }
                case 3:
                    std::cout<<"3.Mostrar comparacion de tiempos de las busquedas anteriores"<<std::endl;
                    
                    std::cout << "Tiempo busqueda AVL: " << ((double)(t_fin_busqueda_avl - t_ini_busqueda_avl) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
                    std::cout << "Tiempo busqueda Vdin: " << ((double)(t_fin_busqueda_vdin - t_ini_busqueda_vdin) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

                    break;

                case 4: {
                    std::cout<<"4.Mostrar altura AVL con todas las farmacias"<<std::endl;
                    std::cout<<"Altura: "<<farmacias_avl.altura() <<std::endl;
                    break;
                }
                case 5: {
                    std::cout <<"5.Mostrar las 100 primeras farmacias en inorden"<<std::endl;

                    VDinamico<Farmacia*> aux = farmacias_avl.recorreInorden();
                    for (int i=0;i<100;i++) {
                        std::cout<<aux[i]->get_cif() <<std::endl;
                    }
                    std::cout<<std::endl;
                    break;
                }
            }

        }while (opcion > 0 && opcion < 6);



            menu2();

            VDinamico<PaMedicamento> medication;
            ListaEnlazada<Laboratorio> labs;


            std::string id_number = "";
            std::string id_alpha="";

            is.open("../pa_medicamentos.csv"); //carpeta de proyecto
            if ( is.good() ) {
                clock_t t_ini = clock();

                while ( getline(is, fila ) ) {

                    //¿Se ha leído una nueva fila?
                    if (fila!="") {

                        columnas.str(fila);

                        //formato de fila: id_number;id_alpha;nombre;

                        getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                        getline(columnas, id_alpha,';');
                        getline(columnas, nombre,';');

                        fila="";
                        columnas.clear();

                        int idNumber=std::stoi(id_number);
                        PaMedicamento medicamento(idNumber,id_alpha,nombre);
                        medication.insertar(medicamento);
                    }
                }

                is.close();

                std::cout<<"Lectura de Laboratorios:"<<std::endl;
                std::string id;
                std::string nombre_lab;
                std::string direccion;
                std::string codPostal;
                std::string localidad;

                is.open("../lab2.csv"); //carpeta de proyecto
                if ( is.good() ) {

                    while ( getline(is, fila ) ) {

                        //¿Se ha leído una nueva fila?
                        if (fila!="") {

                            columnas.str(fila);

                            //formato de fila: id;nombreLab;direccion;codPostal;localidad;

                            getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                            getline(columnas, nombre_lab,';');
                            getline(columnas, direccion,';');
                            getline(columnas, codPostal,';');
                            getline(columnas, localidad,';');

                            fila="";
                            columnas.clear();

                            int idNumberLabs=std::stoi(id);
                            Laboratorio laboratorio (idNumberLabs,nombre_lab,direccion,codPostal,localidad);
                            labs.insertaFin(laboratorio);
                        }
                    }

                    is.close();
                    std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
                }
            }




            MediExpress medi_express(labs,medication,farmacias_avl);
            medi_express.suministrarMed();

        {
            Avl<Farmacia> *farmacias = medi_express.get_pharmacy();
            VDinamico<Farmacia*> farms = farmacias->recorreInorden();

            int j= 0;
            for (int i = 0; i < farms.getTamlog(); i++) {
                int k = 0;
                while (j < medication.getTamlog() && k < 100) {
                    medi_express.suministrarFarmacia(*farms[i],medication[j].get_id_num());
                    j++;
                    if (j == medication.getTamlog())
                        j=0;
                    k++;
                }
                k=0;
            }
        }

        VDinamico<std::string> bufferCif;
            do {
                std::cin>>opcion;
                switch (opcion) {
                    case 1: {
                        std::cout<<"<1.Crear un vector tipo buffer con los siguientes CIF de farmacia"<<std::endl;
                        std::cout<<"CIF:37656422V, 46316032N, 77092934Q, 33961602D, B62351861, B62351861, "<<
                            "B65828113, 46138599R, 35069965W, 37579913Y, 37682300C, "
                            <<"37643742X, 46112335A, 47980171D, 38116138D, 46315600V, "
                            <<"37640233C, 37931842N, 33964303L, 35022080A, B66046640, "
                            <<"E66748344, 47640201W, B66621954, 46121385Z, X6806622W, "
                            <<"46046390E"<<std::endl;
                        bufferCif.insertar("37656422V");
                        bufferCif.insertar("46316032N");
                        bufferCif.insertar("77092934Q");
                        bufferCif.insertar("33961602D");
                        bufferCif.insertar("B62351861");
                        bufferCif.insertar("B62351861");
                        bufferCif.insertar("37643742X");
                        bufferCif.insertar("46112335A");
                        bufferCif.insertar("47980171D");
                        bufferCif.insertar("38116138D");
                        bufferCif.insertar("46315600V");
                        bufferCif.insertar("37640233C");
                        bufferCif.insertar("37931842N");
                        bufferCif.insertar("33964303L");
                        bufferCif.insertar("35022080A");
                        bufferCif.insertar("B66046640");
                        bufferCif.insertar("E66748344");
                        bufferCif.insertar("47640201W");
                        bufferCif.insertar("B66621954");
                        bufferCif.insertar("46121385Z");
                        bufferCif.insertar("X6806622W");
                        bufferCif.insertar("46046390E");

                    std::cout<<"Datos insertados"<<std::endl;
                        break;
                    }

                        // empezar en esta parte
                    case 2: {
                        std::cout<<"2.Para todas las farmacias anteriores, buscar si alguna de ellas dispensa el ÓXIDO DE "<<
                        "MAGNESIO” con ID=3640, y si no lo venden, hacer el pedido correspondiente. "<<std::endl;

                        for (int i = 0; i < bufferCif.getTamlog(); i++) {
                            Farmacia *farm = medi_express.buscarFarmacia(bufferCif[i]);

                            if (farm == nullptr) {
                                std::cout<<"La farmacia " << bufferCif[i] << " no existe."<<std::endl;
                            }
                            else {
                                PaMedicamento *med = farm->buscaMedicam(3640);
                                if (med == nullptr) {
                                    std::cout<<"La farmacia " << bufferCif[i] << " no vende el medicamento con ID=3640."<<std::endl;
                                    //farm->pedidoMedicam(3640);
                                    medi_express.suministrarFarmacia(*farm, 3640);
                                    std::cout<<"Se ha pedido el medicamento con ID=3640."<<std::endl;
                                }
                                else {
                                    std::cout<<"La farmacia " << bufferCif[i] << " vende el medicamento con ID=3640."<<std::endl;
                                }
                            }
                        }

                        break;
                    }
                    case 3: {
                        std::cout<<"3.Buscar y contar todos los laboratorios con MAGNESIO"<<std::endl;

                        VDinamico<PaMedicamento*> med = medi_express.buscarCompuesto("MAGNESIO");
                        ListaEnlazada<Laboratorio> labs = medi_express.get_labs();
                        ListaEnlazada<Laboratorio> labs_con_magnesio;

                        for (ListaEnlazada<Laboratorio>::Iterador it = labs.iteradorInicio(); !it.fin(); it.siguiente()) {
                            Laboratorio &lab = it.dato();
                            for (int j = 0; j < med.getTamlog(); j++) {
                                PaMedicamento* medi = med[j];
                                if (medi->servidoPor() == lab.get_nombre_lab()) {
                                    std::cout<<lab.get_nombre_lab()<<" tiene "<<medi->get_nombre()<<std::endl;
                                    labs_con_magnesio.insertaFin(lab);
                                }
                            }
                        }

                        mostrarLaboratorios(&labs_con_magnesio);
                        std::cout<<"Son un total de "<<labs_con_magnesio.tam()<<std::endl;

                        break;
                    }
                    case 4: {
                        std::cout<<"4.PAREJAS: Localizar todos los laboratorios que suministran a alguna "
                                   "farmacia medicamentos con VIRUS"<<std::endl;

                        Avl<Farmacia> *farmacias = medi_express.get_pharmacy();
                        VDinamico<Farmacia*> farm = farmacias->recorreInorden();

                        VDinamico<std::string> labs_virus;

                        for (int i = 0; i < farm.getTamlog(); i++) {
                            Farmacia *farm1 = farm[i];
                            VDinamico<PaMedicamento*> med_virus = farm1->buscaMedicam("VIRUS");
                            for (int j = 0; j < med_virus.getTamlog(); j++) {
                                PaMedicamento *medi = med_virus[j];
                                std::cout<<farm1->get_nombre()<<" tiene "<<medi->get_nombre()<<std::endl;

                                std::string inserto = "Farmacia: ";
                                inserto += farm1->get_nombre();
                                inserto += " Medicamento: ";
                                inserto += medi->get_nombre();
                                inserto += " Laboratorio: ";
                                inserto += medi->servidoPor();

                                labs_virus.insertar(inserto);
                            }
                        }

                        for (int i = 0; i < labs_virus.getTamlog(); i++)
                            std::cout<<labs_virus[i]<<std::endl;

                        break;
                    }

                }
        }while(opcion>0 && opcion<5);
        mostrarFarmaciasMedicamento(medi_express);
    } catch (std::exception) {
            std::cerr<<"ERROR";
    }
     return 0;
}
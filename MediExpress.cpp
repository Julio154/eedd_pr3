//
// Created by silvi on 18/10/2025.
//

#include "MediExpress.h"

#include <fstream>
#include <sstream>

MediExpress::MediExpress() {
}

MediExpress::~MediExpress() {
}
MediExpress::MediExpress(const ListaEnlazada<Laboratorio> &labs, const VDinamico<PaMedicamento> &medication):
    labs(labs),
    medication(medication)
{}

MediExpress::MediExpress(const MediExpress &orig):
    labs(orig.labs),
    medication(orig.medication) {

}


void MediExpress::suministrarMed() {
    unsigned int totalMed = medication.getTamlog();
    unsigned int medIndex = 0;

    for (ListaEnlazada<Laboratorio>::Iterador it = labs.iteradorInicio();
         !it.fin() && medIndex < totalMed;
         it.siguiente()) {

        for (int i = 0; i < 2 && medIndex < totalMed; ++i) {
            medication[medIndex].setLab(it.dato());
            ++medIndex;
        }
    }

    std::cout << "Medicamentos enlazados: " << medIndex
              << " | Sin enlazar: " << (totalMed - medIndex) << std::endl;
}

Laboratorio * MediExpress::buscarLab(std::string nombreLab) {
ListaEnlazada<Laboratorio>::Iterador it= labs.iteradorInicio();
    for (ListaEnlazada<Laboratorio>::Iterador it = labs.iteradorInicio(); !it.fin(); it.siguiente()) {
        if (it.dato().get_nombre_lab() == nombreLab) {
            return &it.dato();
        }
    }
    return nullptr;
}

ListaEnlazada<Laboratorio> MediExpress::buscarLabCiudad(std::string nombreCiudad) {
ListaEnlazada<Laboratorio> nuevaLista;
    for (ListaEnlazada<Laboratorio> ::Iterador it= labs.iteradorInicio();!it.fin() ; it.siguiente()) {
        if (it.dato().get_localidad().find(nombreCiudad)!= std::string::npos) {
            nuevaLista.insertaFin(it.dato());
        }
    }
    return nuevaLista;

}
ListaEnlazada<Laboratorio> MediExpress::buscarLabSoloCiudad(std::string nombreCiudad) {
    ListaEnlazada<Laboratorio> nuevaLista;
    for (ListaEnlazada<Laboratorio> ::Iterador it= labs.iteradorInicio();!it.fin() ; it.siguiente()) {
        if (it.dato().get_localidad().find(nombreCiudad) != std::string::npos) {
            nuevaLista.insertaFin(it.dato());
        }
    }
    return nuevaLista;

}

VDinamico<PaMedicamento*> MediExpress::buscarCompuesto(std::string comp) {
    VDinamico<PaMedicamento*> vmedicamento;
    for (unsigned int i = 0; i < medication.getTamlog(); ++i) {
        if (medication[i].get_nombre().find(comp) != std::string::npos) {
            vmedicamento.insertar(&medication[i]);
            std::cout<<"Medicamento encontrado: "<<medication[i].get_nombre()<<std::endl;
        }
    }
    return vmedicamento;
}

VDinamico<PaMedicamento *> MediExpress::getMedicamSinLab() {
    VDinamico<PaMedicamento*> vmedicamento;
    for (unsigned int i = 0; i < medication.getTamlog(); ++i) {
        if (medication[i].servidoPor() == "") {
            vmedicamento.insertar(&medication[i]);
        }
    }
    return vmedicamento;
}

ListaEnlazada<Laboratorio>& MediExpress::get_labs()  {
    return labs;
}


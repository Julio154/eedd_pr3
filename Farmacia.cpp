//
// Created by silvi on 25/10/2025.
//


#include "Farmacia.h"
#include "MediExpress.h"

Farmacia::Farmacia()=default;

Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
                   const std::string &nombre, const std::string &direccion, const std::string &cod_postal)
        :cif(cif),
        provincia(provincia),
        localidad(localidad),
        nombre(nombre),
        direccion(direccion),
        codPostal(cod_postal),
        dispense(),
        linkMedi(nullptr)
{}

Farmacia::Farmacia(const Farmacia &other):
    cif(other.cif),
    provincia(other.provincia),
    localidad(other.localidad),
    nombre(other.nombre),
    direccion(other.direccion),
    codPostal(other.codPostal),
    dispense(other.dispense),
    linkMedi(other.linkMedi)
{}

PaMedicamento *Farmacia::buscaMedicam(int id_num) {

    for (int i = 0; i < dispense.getTamlog(); i++) {
        if (dispense[i]->get_id_num() == id_num) {
            return dispense[i];
        }
    }
    return nullptr;
}

VDinamico<PaMedicamento*> Farmacia::buscaMedicam(std::string nombreMed) {
    VDinamico<PaMedicamento*> medicamentos;
    for (int i = 0; i < dispense.getTamlog(); i++) {
        if (dispense[i]->get_nombre().find(nombreMed) != std::string::npos) {
            medicamentos.insertar(dispense[i]);
        }
    }
    return medicamentos;
}

void Farmacia::pedidoMedicam(int id_num) {
    linkMedi->suministrarFarmacia(*this,id_num);
}

void Farmacia::dispensaMedicam(PaMedicamento *pa) {
    dispense.insertar(pa);
}


std::string Farmacia::get_cif() const {
    return cif;
}

void Farmacia::set_cif(const std::string &cif) {
    this->cif = cif;
}

std::string Farmacia::get_provincia() const {
    return provincia;
}

void Farmacia::set_provincia(const std::string &provincia) {
    this->provincia = provincia;
}

std::string Farmacia::get_localidad() const {
    return localidad;
}

void Farmacia::set_localidad(const std::string &localidad) {
    this->localidad = localidad;
}

std::string Farmacia::get_nombre() const {
    return nombre;
}

void Farmacia::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
}

std::string Farmacia::get_direccion() const {
    return direccion;
}

void Farmacia::set_direccion(const std::string &direccion) {
    this->direccion = direccion;
}

std::string Farmacia::get_cod_postal() const {
    return codPostal;
}

void Farmacia::set_cod_postal(const std::string &cod_postal) {
    codPostal = cod_postal;
}

MediExpress * Farmacia::get_link_medi() const {
    return linkMedi;
}

void Farmacia::set_link_medi(MediExpress *link_medi) {
    linkMedi = link_medi;
}

bool operator<(const Farmacia &lhs, const Farmacia &rhs) {
    return rhs.cif > lhs.cif;
}

bool operator<=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(rhs.cif < lhs.cif);
}

bool operator>(const Farmacia &lhs, const Farmacia &rhs) {
    return rhs.cif < lhs.cif;
}

bool operator>=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(lhs.cif < rhs.cif);
}


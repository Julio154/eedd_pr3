//
// Created by silvi on 25/10/2025.
//


#include "Farmacia.h"
Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
        const std::string &nombre, const std::string &direccion, const std::string &cod_postal)
        : cif(cif),
          provincia(provincia),
          localidad(localidad),
          nombre(nombre),
          direccion(direccion),
          codPostal(cod_postal) {
}

PaMedicamento& Farmacia::buscaMedicam(int id_num) {
}

void Farmacia::pedidoMedicam(int id_num) {

}

void Farmacia::dispensaMedicam(PaMedicamento pa) {

}

bool operator<(const Farmacia &lhs, const Farmacia &rhs) {
}

bool operator<=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(rhs < lhs);
}

bool operator>(const Farmacia &lhs, const Farmacia &rhs) {
    return rhs < lhs;
}

bool operator>=(const Farmacia &lhs, const Farmacia &rhs) {
    return !(lhs < rhs);
}

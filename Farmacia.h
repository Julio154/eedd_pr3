//
// Created by silvi on 25/10/2025.
//

#ifndef PR1_FARMACIA_H
#define PR1_FARMACIA_H
#include <string>
#include "MediExpress.h"

class Farmacia {
private:
    std::string cif;
    std::string provincia;
    std::string localidad;
    std::string nombre;
    std::string direccion;
    std::string codPostal;
    MediExpress *linkMedi;


public:
    Farmacia();
    ~Farmacia() = default;


    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
        const std::string &nombre, const std::string &direccion, const std::string &cod_postal);

    PaMedicamento& buscaMedicam(int id_num);
    void pedidoMedicam(int id_num);
    void dispensaMedicam(PaMedicamento pa);

    friend bool operator<(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator<=(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator>(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator>=(const Farmacia &lhs, const Farmacia &rhs);
};


#endif //PR1_FARMACIA_H

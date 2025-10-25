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


    PaMedicamento& buscaMedicam(int id_num);
    void pedidoMedicam(int id_num);
    void dispensaMedicam(PaMedicamento pa);


};


#endif //PR1_FARMACIA_H

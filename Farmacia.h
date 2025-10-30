//
// Created by silvi on 25/10/2025.
//

#ifndef PR1_FARMACIA_H
#define PR1_FARMACIA_H
class MediExpress;
#include <string>
//#include "MediExpress.h"
#include "PaMedicamento.h"
#include "VDinamico.h"
class Farmacia {
private:
    std::string cif;
    std::string provincia;
    std::string localidad;
    std::string nombre;
    std::string direccion;
    std::string codPostal;
    VDinamico<PaMedicamento*> dispense;
    MediExpress *linkMedi;

public:
    Farmacia();
    ~Farmacia() = default;


    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
        const std::string &nombre, const std::string &direccion, const std::string &cod_postal);

    PaMedicamento& buscaMedicam(int id_num);
    void pedidoMedicam(int id_num);
    void dispensaMedicam(PaMedicamento pa);

    std::string get_cif() const;
    void set_cif(const std::string &cif);
    std::string get_provincia() const;
    void set_provincia(const std::string &provincia);
    std::string get_localidad() const;
    void set_localidad(const std::string &localidad);
    std::string get_nombre() const;
    void set_nombre(const std::string &nombre);
    std::string get_direccion() const;
    void set_direccion(const std::string &direccion);
    std::string get_cod_postal() const;
    void set_cod_postal(const std::string &cod_postal);
    MediExpress * get_link_medi() const;
    void set_link_medi(MediExpress *link_medi);

    friend bool operator<(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator<=(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator>(const Farmacia &lhs, const Farmacia &rhs) ;
    friend bool operator>=(const Farmacia &lhs, const Farmacia &rhs);
};


#endif //PR1_FARMACIA_H

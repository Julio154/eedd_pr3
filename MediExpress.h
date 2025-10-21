//
// Created by silvi on 18/10/2025.
//

#ifndef PR1_MEDIEXPRESS_H
#define PR1_MEDIEXPRESS_H
#include "Laboratorio.h"
#include "ListaEnlazada.h"
#include "PaMedicamento.h"
#include "VDinamico.h"


class MediExpress
{
    private:
        ListaEnlazada<Laboratorio> labs;
        VDinamico<PaMedicamento> medication;
    public:
        MediExpress();
        ~MediExpress();

        MediExpress(const ListaEnlazada<Laboratorio> &labs);

        MediExpress(const ListaEnlazada<Laboratorio> &labs, const VDinamico<PaMedicamento> &medication);

        MediExpress(const MediExpress &orig);

        void suministrarMed();
        Laboratorio* buscarLab(std::string nombreLab);

        ListaEnlazada<Laboratorio> buscarLabCiudad(std::string nombreCiudad);
        ListaEnlazada<Laboratorio> buscarLabSoloCiudad(std::string nombreCiudad);
        VDinamico<PaMedicamento*> buscarCompuesto(std::string comp);
        VDinamico<PaMedicamento*> getMedicamSinLab();

        ListaEnlazada<Laboratorio>& get_labs() ;

        void set_labs(const ListaEnlazada<Laboratorio> &labs);

        VDinamico<PaMedicamento> get_medication() const;

};


#endif //PR1_MEDIEXPRESS_H
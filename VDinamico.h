#ifndef PRACTICA3_VDINAMICO_H
#define PRACTICA3_VDINAMICO_H

#include <math.h>
#include <iostream>
#include <algorithm>
#include <exception>

template <typename T>
class VDinamico{
private:
    unsigned int tamlog, tamfis;
    T *v;

    void potencia2();

public:
    VDinamico();
    VDinamico(unsigned int tamlog);
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T> &orig, unsigned int posinicial,
              unsigned int numelementos);
    ~VDinamico();

    VDinamico<T> &operator=(const VDinamico<T> &orig);
    T &operator[](unsigned int pos);
    void insertar(const T &dato, unsigned int pos = UINT_MAX);
    T borrar(unsigned int pos = UINT_MAX);
    void ordenar();
    void ordenarRev();
    int busquedaBin(const T &dato);
    unsigned int getTamlog(){return this->tamlog;};
    unsigned int getTamfis(){return this->tamfis;};
    void aumenta();
    void disminuye();

    T lee(unsigned pos){ return v[pos]; }
};
template <typename T>
void VDinamico<T>::potencia2() {

    int n=-1;
    do{
        n++;
        this->tamfis=pow(2,n);
    }while(tamfis<tamlog);

}

template <typename T>
VDinamico<T>::VDinamico():
        tamlog(0), tamfis(1)
{
    v = new T[tamfis];
}

template <typename T>
VDinamico<T>::VDinamico(unsigned int tamlog):
        tamlog(tamlog)
{
    v = new T[tamfis];
    potencia2();
}

template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig):
        tamlog(orig.tamlog), tamfis(orig.tamfis)
{
    v = new T[tamfis];
    for(int i = 0; i<orig.tamlog; i++){
        v[i] = orig.v[i];
    }
}

template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig, unsigned int posinicial,
                        unsigned int numelementos):
        tamlog(orig.tamlog)
{
    potencia2();
    v = new T[tamfis];
    for(int i = 0; i<numelementos; i++){
        v[i] = orig.v[posinicial+i];
    }
}

template <typename T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico<T> &orig) {
    if(orig != this){
        delete []v;

        tamlog = orig.tamlog;
        tamfis = orig.tamfis;

        v = new T[tamfis];

        for(int i = 0; i < tamlog; i++){
            v[i] = orig.v[i];
        }}
    return *this;
}

template <typename T>
T& VDinamico<T>::operator[](unsigned int pos) {
    if(pos >= tamlog)
        throw std::out_of_range("VDinamico<T>::operator[], posicion erronea.");
    return v[pos];
}
template <typename T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {

    if (pos == UINT_MAX) {
        if (tamlog == tamfis)
            aumenta();

        v[tamlog++] = dato;

    } else {
        if (pos >= tamlog)
            throw std::out_of_range("VDinamico<T>::insertar, posicion erronea.");

        if (tamlog == tamfis)
            aumenta();

        if (tamlog != 0) {
            for (int i = tamlog - 1; i >= pos; i--) {
                v[i + 1] = v[i];
            }
            v[pos] = dato;
            tamlog++;
        }
    }
}


template <typename T>
void VDinamico<T>::ordenar() {
    std::sort(v,v+tamlog);

}
template <typename T>
void VDinamico<T>::ordenarRev() {
    std::sort(v,v+tamlog);
    std::reverse(v,v+tamlog);
}

template<typename T>
int VDinamico<T>::busquedaBin(const T &dato) {
    int inf = 0;
    int sup = tamlog - 1;
    int curIn;
    while (inf <= sup) {

        curIn = (inf + sup) / 2;

        if (v[curIn] == dato){
            return curIn;
        }

        if (v[curIn] < dato)
            inf = curIn + 1;

        else
            sup = curIn - 1;
    }
    return -1;
}

template<typename T>
T VDinamico<T>::borrar(unsigned int pos) {

    if(tamlog == 0)
        throw std::out_of_range("VDinamico<T>::borrar, no se puede borrar nada.");

    if(pos >= tamlog)
        throw std::out_of_range("VDinamico<T>::borrar, posicion fuera de tamaño logico.");

    if(tamlog < tamfis/3)
        disminuye();

    T aux;
    aux = v[pos];

    for(int i=pos ;i<tamlog;i++){
        v[i]=v[i+1];
    }

    tamlog--;
    return aux;
}

template<typename T>
VDinamico<T>::~VDinamico() {
    delete [] v;
}

template<class T>
void VDinamico<T>::aumenta(){
    T *vaux;
    vaux= new T[tamfis=tamfis*2];
    for(unsigned i=0;i<tamlog;i++)
        vaux[i]=v[i];
    delete []v;
    v=vaux;
};


template<typename T>
void VDinamico<T>::disminuye() {

    tamfis=tamfis/2;
    T* aux = new T[tamfis];
    for(int i=0;i<tamlog;i++){
        aux[i]=v[i];
    }
    delete [] v;
    v=aux;
}

#endif
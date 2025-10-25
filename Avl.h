//
// Created by silvi on 25/10/2025.
//

#ifndef PR1_AVL_H
#define PR1_AVL_H

#include "VDinamico.h"


template <class T>
class Nodo
{
public:
    Nodo<T> *izq;
    Nodo<T> *der;
    char bal;
    T dato;

    Nodo(const T &ele): izq(0), der(0), bal(0), dato(ele){}
    Nodo(const Nodo<T> &orig): izq(orig.izq), der(orig.der), bal(orig.bal), dato(orig.dato){}

};

template <class T>
class Avl {
private:
    Nodo<T> *raiz;

    void inorden(Nodo<T> *p, int nivel, VDinamico<T*> &v);

    Nodo<T> *buscaClave ( T &dato, Nodo<T> *p);
    int insertaDato(Nodo<T>* &c, T &dato);

    void destruyeArbol(Nodo<T>* &p);

    void rotDer(Nodo<T>* &p);
    void rotIzq(Nodo<T>* &p);

    void copiaAvl(Nodo<T>* &q,Nodo<T> *p);
    unsigned int numElementosPr(Nodo<T>* p);
    void alturaPr(Nodo<T>* p, int nivel, int &result);


public:

    Avl() : raiz(0) {}
    Avl(const Avl<T>& orig);
    Avl<T>& operator=(const Avl<T>& orig);

    T* buscaRec ( T &dato);
    T* buscaIt(const T &dato);
    bool inserta( T &dato);

    unsigned int numElementos();
    unsigned int altura();
/**
 * @brief destructor de AVL
 */
    ~Avl(){
        destruyeArbol(raiz);
    };
/**
 * @brief recorre el AVL en inorden
 * @return VDinamico con los datos del AVL colocados en inorden
 */
    VDinamico<T*> recorreInorden() {
        VDinamico<T*> v;
        inorden(raiz,0,v);
        return v;
    };

};
/**
 * @brief metodo privado que se usa en el contructor copia
 * @tparam T class
 * @param q Nodo
 * @param p Nodo
 */
template<class T>
void Avl<T>::copiaAvl(Nodo<T>* &q,Nodo<T> *p){
    if (p){
        q= new Nodo<T> (*p);
        copiaAvl(q->izq,p->izq);
        copiaAvl(q->der,p->der);
    }else
        q=0;
}
/**
 * @brief constructor copia
 * @tparam T class
 * @param orig Avl
 */
template<class T>
Avl<T>::Avl(const Avl<T>& orig){
    copiaAvl(raiz,orig.raiz);
}
/**
 * @brief operador de asignacion
 * @tparam T class
 * @param orig avl
 * @return this
 */
template<class T>
Avl<T>& Avl<T>::operator=(const Avl<T>& orig){
    if (this!=&orig){
        destruyeArbol(raiz);
        copiaAvl(raiz,orig.raiz);
    }
    return *this;
}

/**
 * @brief se encarga de las rotaciones para el balanceo del avl
 * @tparam T class
 * @param nodo Nodo
 */
template<class T>
void Avl<T>::rotIzq(Nodo<T>* &nodo){
    Nodo<T> *q = nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}
/**
 * @brief se encarga de las rotaciones para el balanceo del avl
 * @tparam T class
 * @param nodo Nodo
 */
template<class T>
void Avl<T>::rotDer(Nodo<T>* &nodo){
    Nodo<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}
/**
 * @brief nos calcula el inorden de AVL
 * @tparam T class
 * @param p nodo
 * @param nivel int
 * @param v vector dinamico
 */
template <class T>
void Avl<T>::inorden (Nodo<T> *p, int nivel, VDinamico<T*> &v){
    if (p){
        inorden (p->izq, nivel+1, v);
        v.insertar(&(p->dato));
        inorden (p->der, nivel+1, v);
    }
}
/**
 * @brief busqueda por clave
 * @tparam T class
 * @param dato t
 * @param p nodo
 * @return nodo
 */
template <class T>
Nodo<T> *Avl<T>::buscaClave ( T &dato, Nodo<T> *p){
    if (!p)
        return 0;
    else{
        //T d=dato;
        if (dato < p->dato)
            return buscaClave (dato, p->izq);
        else if (dato > p-> dato)
            return buscaClave (dato, p->der);
        else
            return p;
    }
}
/**
 * @brief busqueda recursiva
 * @tparam T
 * @param dato T
 * @return T
 */
template <class T>
T* Avl<T>::buscaRec ( T &dato){
    Nodo<T> *p = buscaClave (dato, raiz);
    T* result;
    if (p){
        result = &(p->dato);
        return result;
    }
    return 0;
}
/**
 * @brief busqueda iterativa
 * @tparam T class
 * @param dato t
 * @return t
 */
template <class T>
T* Avl<T>::buscaIt (const T &dato){
    Nodo<T> *p = raiz;
    T* result;
    while (p){
        T d=dato;
        if (d < p->dato)
            p=p->izq;
        else
        if (p-> dato < d)
            p=p->der;
        else{
            result = &(p->dato);
            return result;
        }
    }
    return 0;
}

/**
 * @brief inserta dato
 * @tparam T class
 * @param c nodo
 * @param dato t
 * @return int
 */
template<class T>
int Avl<T>::insertaDato( Nodo<T>* &c,  T &dato){
    Nodo<T> *p = c;
    int deltaH = 0;
    T d=dato;
    if (!p){
        p = new Nodo<T>(dato);
        c = p; deltaH=1;
    }else if (p->dato < dato){
        if (insertaDato(p->der, dato)){
            p->bal--;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                rotIzq(c);
            }
        }
    }
    else if (d < p->dato){
        if (insertaDato(p->izq, dato)){
            p->bal++;
            if (p->bal==1) deltaH = 1;
            else if (p->bal == 2){
                if (p->izq->bal == -1) rotIzq(p->izq);
                rotDer(c);
            }
        }
    }
    return deltaH;
}

/**
 * @brief inserta los datos en el avl
 * @tparam T class
 * @param dato t
 * @return bool true si lo inserta correctamente y false si no lo inserta
 */
template <class T>
bool Avl<T>::inserta( T &dato){
    T *result = buscaRec(dato);
    if (!result){
        insertaDato(raiz, dato);
        return true;
    }
    return false;
}
/**
 * @brief destruye el arbol, metodo privado usado en el destructor
 * @tparam T class
 * @param p Nodo
 */
template <class T>
void Avl<T>::destruyeArbol(Nodo<T>* &p){
    if (p){
        destruyeArbol(p->izq);
        destruyeArbol(p->der);
        delete p;
        p=0;
    }
}
/**
 * @brief metodo privado para obtener el numero de elementos
 * @tparam T class
 * @param p nodo
 * @return unsigned int
 */
template <class T>
unsigned int Avl<T>::numElementosPr(Nodo<T>* p){
    if (p)
        return numElementosPr(p->izq)+numElementosPr(p->der)+1;
    else
        return 0;
}
/**
 * @brief nos devuelve el numero de elementos del AVL
 * @tparam T class
 * @return unsigned int
 */
template <class T>
unsigned int Avl<T>::numElementos(){
    return numElementosPr(raiz);
}
/**
 * @brief metodo privado para obtener la altura
 * @tparam T class
 * @param p nodo
 * @param nivel int
 * @param result int
 */
template <class T>
void Avl<T>::alturaPr(Nodo<T>* p, int nivel, int &result){
    if (p){
        alturaPr(p->izq,nivel+1,result);
        if (nivel>result)
            result=nivel;
        alturaPr(p->der,nivel+1,result);
    }
}
/**
 * @brief calcula la altura
 * @tparam T class
 * @return int
 */
template <class T>
unsigned int Avl<T>::altura(){
    int result=0;
    alturaPr(raiz,0,result);
    return result;
}
#endif //PR1_AVL_H
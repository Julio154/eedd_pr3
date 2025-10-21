//
// Created by Portatil on 10/10/2023.
//

#ifndef PR1_LISTAENLAZADA_H
#define PR1_LISTAENLAZADA_H
#include <stdexcept>

template <class T>
class ListaEnlazada{
private:
    template<class X >
    class Nodo{
    public:
        X dato;
        Nodo *sig;

        Nodo( X &aDato, Nodo *aSig = 0):
                dato(aDato), sig(aSig){}
        ~Nodo(){}
    };
    Nodo<T> *cabecera,*cola;
    int tama;

public:
    class Iterador{
    public:
        Nodo<T> *nodo;
        Iterador( Nodo<T> *aNodo=0 ): nodo( aNodo ){}
        bool fin(){ return nodo == 0 ;}
        void siguiente(){
            if (haySiguiente())
                nodo = nodo->sig;}
        bool haySiguiente(){return nodo!= nullptr;};
        T &dato(){ return nodo->dato; }
        Iterador& operator=( const Iterador &orig ){
            nodo=orig.nodo;
            return *this;
        }
        virtual ~Iterador() {}
    };


    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T> &origen);
    ListaEnlazada<T> &operator=(ListaEnlazada<T> const);
    T& inicio();
    T& fin();
    void insertaInicio(T& dato);
    void insertaFin(T& dato);
    void inserta(Iterador &i,T& dato);
    void insertaDetras(Iterador &i,T& dato);
    void borraInicio();
    void borraFinal();
    void borra(Iterador &i);
    int tam();
    ListaEnlazada <T> &concatena(ListaEnlazada &otraLista);
    ListaEnlazada<T> &operator+(ListaEnlazada &otraLista);

    Iterador iteradorInicio(){return Iterador(cabecera);}
    Iterador iteradorFin(){return Iterador(cola);}

    ~ListaEnlazada();
};

/**
 * @brief constructor por defecto
 * @tparam T
 */
template<class T>
ListaEnlazada<T>::ListaEnlazada(): cabecera(0),cola(0), tama(0) {

}

/**
 * @brief constructor copia
 * @tparam T
 * @param origen
 */
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &origen):
cabecera(nullptr), cola(nullptr), tama(0) {
    Nodo<T> *p=origen.cabecera;
    while (p!=nullptr){
        insertaFin(p->dato);
        p=p->sig;
    }
tama=origen.tama;
}

/**
 * @brief operador de asignacion
 * @tparam T
 * @param origen
 * @return
 */
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> origen) {
    while(cabecera!=0)
        borraFinal();
    Nodo<T> *p= origen.cabecera;
    while (p->dato!= nullptr){
        insertaFin(p->dato);
        p=p->sig;
    }
    tama=origen.tama;
    return *this;

}
/**
 * @brief nos devuelve el primer dato de la lista
 * @tparam T
 * @return dato de la cabecera
 */
template<class T>
T &ListaEnlazada<T>::inicio() {
    return cabecera->dato;
}

/**
 * @brief nos devuelve el ultimo dato de la lista
 * @tparam T
 * @return dato que hay en cola
 */
template<class T>
T &ListaEnlazada<T>::fin() {
    return cola->dato;
}

/**
 * @brief inserta datos por el inicio
 * @tparam T
 * @param dato dato de tipo T que se va a insertar
 */
template<class T>
void ListaEnlazada<T>::insertaInicio(T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato, cabecera);
    tama++;
    if (!cabecera)
        cola = nuevo;
    cabecera = nuevo;

}
/**
 * @brief inserta datos por el final
 * @tparam T
 * @param dato dato de tipo T que va a ser insertado en el fin
 */
template<class T>
void ListaEnlazada<T>::insertaFin(T &dato) {
    tama++;
    Nodo<T> *nuevo=new Nodo<T>(dato,0);
    if(cola == 0)
        cabecera = nuevo;
    else
        cola->sig = nuevo;

    cola = nuevo;

}
/**
 * @brief inserta en la posicion que le marque el iterador
 * @tparam T
 * @param i Iterador
 * @param dato dato que se va a insesrta de tipo T
 */
template<class T>
void ListaEnlazada<T>::inserta(Iterador &i, T &dato) {
    Nodo<T> *anterior = 0;

    if( cabecera != cola ){
        anterior = cabecera;
        while( anterior->sig != i.nodo )
            anterior = anterior->sig;
    }
    Nodo<T> *nuevo = new Nodo<T>( dato, anterior );

    anterior->sig = nuevo;
    if( cabecera == 0 )
        cabecera = cola = nuevo;

    tama++;
}
/**
 * @brief insertaDetras del iterador
 * @tparam T
 * @param i
 * @param dato dato de tipo T que se va a insertar
 */
template<class T>
void ListaEnlazada<T>::insertaDetras(Iterador &i, T &dato) {
    Nodo<T> *anterior = 0;
    if( cabecera != cola ){
        anterior = cabecera;
        while( anterior->sig != i.nodo )
            anterior = anterior->sig;
    }
    Nodo<T> *nuevo = new Nodo<T>( dato, anterior );

    anterior->sig = nuevo;
    if( cabecera == 0 )
        cabecera = cola = nuevo;

    tama++;
}
/**
 * @brief borra el dato del inicio
 * @tparam T
 */
template<class T>
void ListaEnlazada<T>::borraInicio() {
    if (cabecera){
        tama--;
        Nodo<T> *borrar=cabecera;
        cabecera=cabecera->sig;
        delete borrar;
    }

}
/**
 * @brief borra el dato del final
 * @tparam T
 */
template<class T>
void ListaEnlazada<T>::borraFinal() {
    // 1. Caso de lista vacía: No hay nada que borrar
    if (cabecera == nullptr) {
        return;
    }

    // El nodo a borrar siempre es 'cola'
    Nodo<T> *aBorrar = cola;

    // 2. Caso de UN SOLO elemento
    if (cabecera == cola) {
        // La lista queda vacía
        cabecera = nullptr;
        cola = nullptr;
    }
    // 3. Caso de MÚLTIPLES elementos (más de uno)
    else {
        // Buscar el penúltimo nodo (el que apunta a 'cola')
        Nodo<T> *anterior = cabecera;
        // Recorrer hasta que 'anterior->sig' sea el nodo 'cola'
        while (anterior->sig != cola) {
            anterior = anterior->sig;
        }

        // El penúltimo nodo se convierte en el nuevo 'cola'
        cola = anterior;
        cola->sig = nullptr; // El nuevo final debe apuntar a nullptr (o 0)
    }

    // 4. Liberar la memoria y actualizar el tamaño
    delete aBorrar;
    tama--;
}
/*void ListaEnlazada<T>::borraFinal() {
    Nodo<T> *anterior= nullptr;
    tama--;
    if (cola!=cabecera){
        anterior=cabecera;
        while(anterior->sig!=cola)
            anterior=anterior->sig;
    }
    delete cola;
    cola=anterior;
    if(anterior){
        anterior->sig=0;
    }else
        cabecera= nullptr;
}

/**
 * @brief borra un dato segun el iterador pasado
 * @tparam T
 * @param i Iterador
 */
template<class T>
void ListaEnlazada<T>::borra(Iterador &i) {
    if (i.nodo == nullptr) {
        throw std::invalid_argument("El iterador no apunta a ningún nodo.");
    }else{
    if (i.haySiguiente()==false){
        borraFinal();
    }


        Nodo<T>* nodoAEliminar = i.nodo;
        if (nodoAEliminar == cabecera) {
            cabecera = cabecera->sig;
        } else {
            Nodo<T>* nodoAnterior = cabecera;
            while (nodoAnterior != nullptr && nodoAnterior->sig != nodoAEliminar) {
                nodoAnterior = nodoAnterior->sig;
            }
            if (nodoAnterior != nullptr) {
                nodoAnterior->sig = nodoAEliminar->sig;
            }
        }

        i.nodo = nodoAEliminar->sig;
        delete nodoAEliminar;
        tama--;}
}

/**
 * @brief devuelve el tamaño de la lista
 * @tparam T
 * @return tamaño de la lista
 */
template<class T>
int ListaEnlazada<T>::tam() {
    return tama;
}

/**
 * @brief concatena 2 listas devolviendo el this
 * @tparam T
 * @param otraLista ListaEnlazada que se concatena
 * @return this , la propia lista unida a la otraLista pasada por parametro
 */
template<class T>
ListaEnlazada<T>& ListaEnlazada<T>::concatena(ListaEnlazada &otraLista) {
Nodo<T> *aux=otraLista.cabecera;
    while (aux){
        this->insertaFin(aux->dato);
        aux=aux->sig;
    }
    return *this;
}

/**
 * @brief operador +
 * @tparam T
 * @param otraLista lista Enlazada que se suma
 * @return una nueva lista
 */
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator+(ListaEnlazada &otraLista) {
    ListaEnlazada nl;
    Nodo<T> *act=nullptr, *nuevo=nullptr;
    int listaAcopiar=1;
    act=this->cabecera;
    while ( listaAcopiar<=2 ) {
        while (act!=nullptr) {
            nuevo = new Nodo<T>( act->dato );
            if (nl.cola==nullptr)
                nl.cabecera=nuevo;
            else {
                nl.cola->siguiente=nuevo;
            }
            nl.cola=nuevo;
            act=act->siguiente;
        }
        listaAcopiar++;
        act=otraLista.cabecera;
    }
    return nl;
}

/**
 * @brief destructor de la ListaEnlazada
 * @tparam T
 */
template<class T>
ListaEnlazada<T>::~ListaEnlazada() {
    Nodo<T> *actual = cabecera;
    Nodo<T> *siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->sig;

        delete actual;
   actual = siguiente;
    }
}
#endif //PR1_LISTAENLAZADA_H

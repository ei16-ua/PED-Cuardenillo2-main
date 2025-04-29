#ifndef _TABBPORO_
#define _TABBPORO_

#include "tporo.h"
#include "tvectorporo.h"
#include <queue>

class TNodoABB; //inicializamos para el nododABB

class TABBPoro{
    friend class TNodoABB;

    private:
        TNodoABB *nodo;

        void InordenAux(TVectorPoro &, int &) const;
        void PreordenAux(TVectorPoro &, int &) const;
        void PostordenAux(TVectorPoro &, int &) const;

        //funciones personales
        TPoro Maximo() const;

    public:
        TABBPoro();
        TABBPoro(const TABBPoro &);
        ~TABBPoro();
        TABBPoro & operator=(const TABBPoro &);

        bool operator==(const TABBPoro &) const;
        bool EsVacio() const;
        bool Insertar(const TPoro &);
        bool Borrar(const TPoro &);
        bool Buscar(const TPoro &) const;
        TPoro Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;

        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
        TVectorPoro Niveles() const;

        TABBPoro operator+(const TABBPoro &) const;
        TABBPoro operator-(const TABBPoro &) const;

        friend ostream & operator<<(ostream &, const TABBPoro &);
};

class TNodoABB{
    friend class TABBPoro;

    private:
        TPoro item;
        TABBPoro iz;
        TABBPoro de;

    public:
        TNodoABB();
        TNodoABB(const TNodoABB &);
        ~TNodoABB();
        TNodoABB & operator=(const TNodoABB &);
};

#endif
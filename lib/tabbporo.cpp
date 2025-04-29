#include "../include/tabbporo.h"

TNodoABB::TNodoABB()
{
    
}

TNodoABB::TNodoABB(const TNodoABB &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
}
TNodoABB::~TNodoABB()
{
    
}

TNodoABB & TNodoABB::operator=(const TNodoABB &nodo)
{
    if (this != &nodo)
    {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
    }
    return *this;
}

TABBPoro::TABBPoro()
{
    nodo = nullptr;
}

TABBPoro::TABBPoro(const TABBPoro &t)
{
    if (t.nodo != nullptr)
    {
        nodo = new TNodoABB(*t.nodo);
    }
    else
    {
        nodo = nullptr;
    }
}

TABBPoro::~TABBPoro()
{
    if (nodo != nullptr)
    {
        delete nodo;
        nodo = nullptr;
    }
}

TABBPoro &TABBPoro::operator=(const TABBPoro &t)
{
    if (this != &t)
    {
        if (nodo != nullptr)
        {
            delete nodo;
        }
        if (t.nodo != nullptr)
        {
            nodo = new TNodoABB(*t.nodo);
        }
        else
        {
            nodo = nullptr;
        }
    }
    return *this;
}

bool TABBPoro::EsVacio() const
{
    return nodo == nullptr;
}

bool TABBPoro::Insertar(const TPoro &t)
{
    if (t.EsVacio())
    {
        return false;
    }
    if(EsVacio()){
        nodo = new TNodoABB();
        nodo->item = t;
        return true;
    }
    
    if(t.Volumen() < nodo->item.Volumen()){
        return nodo->iz.Insertar(t);
    }
    else if(t.Volumen() > nodo->item.Volumen()){
        return nodo->de.Insertar(t);
    }
    else{
        return false;
    }
}

TPoro TABBPoro::Maximo() const {
    if (EsVacio()){
        return TPoro();
    }
    if (nodo->de.EsVacio()){
        return nodo->item;
    }
    else{
        return nodo->de.Maximo();
    }
}


bool TABBPoro::Borrar(const TPoro &t)
{
    if (EsVacio())
    {
        return false;
    }

    if (t.Volumen() < nodo->item.Volumen())
    {
        return nodo->iz.Borrar(t);
    }
    else if (t.Volumen() > nodo->item.Volumen())
    {
        return nodo->de.Borrar(t);
    }
    else
    {
        //Nodo hoja
        if (nodo->iz.EsVacio() && nodo->de.EsVacio())
        {
            delete nodo;
            nodo = nullptr;
        }
        //Nodo con un hijo
        else if (!nodo->iz.EsVacio() && nodo->de.EsVacio())
        {
            TNodoABB *aux = nodo;
            nodo = new TNodoABB(*nodo->iz.nodo);
            delete aux;
        }
        else if (nodo->iz.EsVacio() && !nodo->de.EsVacio())
        {
            TNodoABB *aux = nodo;
            nodo = new TNodoABB(*nodo->de.nodo);
            delete aux;
        }
        else{
            //Nodo con dos hijos
            TNodoABB *aux = nodo->iz.nodo;
            while (aux->de.nodo != nullptr) { 
                aux = aux->de.nodo;
            }
            nodo->item = aux->item;
            nodo->iz.Borrar(aux->item);
        }
        return true;
    }
}

bool TABBPoro::Buscar(const TPoro &t) const
{
    if (EsVacio())
    {
        return false;
    }
    if (nodo->item.Volumen() == t.Volumen())
    {
        return true;
    }
    if (t.Volumen() < nodo->item.Volumen())
    {
        return nodo->iz.Buscar(t);
    }
    else
    {
        return nodo->de.Buscar(t);
    }
}

TPoro TABBPoro::Raiz() const
{
    if (EsVacio())
    {
        return TPoro();
    }
    return nodo->item;
}

int TABBPoro::Altura() const
{
    if (EsVacio())
    {
        return 0;
    }
    int alturaIz = nodo->iz.Altura();
    int alturaDe = nodo->de.Altura();
    return 1 + max(alturaIz, alturaDe);
}

int TABBPoro::Nodos() const
{
    if (EsVacio())
    {
        return 0;
    }
    return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
}

int TABBPoro::NodosHoja() const
{
    if (EsVacio())
    {
        return 0;
    }
    if (nodo->iz.EsVacio() && nodo->de.EsVacio())
    {
        return 1;
    }
    return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

TVectorPoro TABBPoro::Inorden() const
{
    int posicion = 1;
    TVectorPoro v(Nodos());
    InordenAux(v, posicion);
    return v;
}

void TABBPoro::InordenAux(TVectorPoro &v, int &posicion) const
{
    if (!EsVacio())
    {
        nodo->iz.InordenAux(v, posicion);
        v[posicion] = nodo->item;
        posicion++;
        nodo->de.InordenAux(v, posicion);
    }
}

TVectorPoro TABBPoro::Preorden() const
{
    int posicion = 1;
    TVectorPoro v(Nodos());
    PreordenAux(v, posicion);
    return v;
}
void TABBPoro::PreordenAux(TVectorPoro &v, int &posicion) const
{
    if (!EsVacio())
    {
        v[posicion] = nodo->item;
        posicion++;
        nodo->iz.PreordenAux(v, posicion);
        nodo->de.PreordenAux(v, posicion);
    }
}

TVectorPoro TABBPoro::Postorden() const
{
    int posicion = 1;
    TVectorPoro v(Nodos());
    PostordenAux(v, posicion);
    return v;
}
void TABBPoro::PostordenAux(TVectorPoro &v, int &posicion) const
{
    if (!EsVacio())
    {
        nodo->iz.PostordenAux(v, posicion);
        nodo->de.PostordenAux(v, posicion);
        v[posicion] = nodo->item;
        posicion++;
    }
}

TVectorPoro TABBPoro::Niveles() const
{
    TVectorPoro v(Nodos());

    if (EsVacio())
    {
        return v;
    }

    queue<const TABBPoro*> cola;
    cola.push(this);
    int posicion = 1;
    while (!cola.empty())
    {
        const TABBPoro *nodoActual = cola.front();
        cola.pop();
        v[posicion] = nodoActual->Raiz();
        posicion++;
        if (!nodoActual->nodo->iz.EsVacio())
        {
            cola.push(&(nodoActual->nodo->iz));
        }
        if (!nodoActual->nodo->de.EsVacio())
        {
            cola.push(&(nodoActual->nodo->de));
        }
    }
    return v;
}

bool TABBPoro::operator==(const TABBPoro &t) const
{
    if (Nodos() != t.Nodos())
    {
        return false;
    }
    TVectorPoro v1 = Inorden();
    TVectorPoro v2 = t.Inorden();
    for (int i = 1; i <= Nodos(); i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    return true;
}

TABBPoro TABBPoro::operator+(const TABBPoro &t) const
{
    TABBPoro resultado(*this);
    TVectorPoro v = t.Inorden();
    for (int i = 1; i <= t.Nodos(); i++)
    {
        resultado.Insertar(v[i]);
    }
    return resultado;
}

TABBPoro TABBPoro::operator-(const TABBPoro &t) const
{
    TABBPoro resultado;
    TVectorPoro v = Inorden();
    for (int i = 1; i <= t.Nodos(); i++)
    {
        if(!t.Buscar(v[i]))
        {
            resultado.Insertar(v[i]);
        }
    }
    return resultado;
}

ostream &operator<<(ostream &os, const TABBPoro &t)
{
    os << t.Niveles();
    return os;
}
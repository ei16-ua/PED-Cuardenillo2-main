#include "../include/tvectorporo.h"
#include "tvectorporo.h"

TVectorPoro::TVectorPoro()
{
    this->dimension = 0;
    this->datos = NULL;
    this->error = TPoro();
}

TVectorPoro::TVectorPoro(int dimension)
{
    this->dimension = dimension;
    this->datos = new TPoro[dimension];
    this->error = TPoro();
}

TVectorPoro::TVectorPoro(const TVectorPoro &tvectorporo)
{
    this->dimension = tvectorporo.dimension;
    this->datos = new TPoro[tvectorporo.dimension];
    for (int i = 0; i < tvectorporo.dimension; i++) {
        this->datos[i] = tvectorporo.datos[i];
    }
    this->error = tvectorporo.error;
}

TVectorPoro::~TVectorPoro()
{
    delete[] this->datos;
    this->dimension = 0;
    this->datos = nullptr;
}

TVectorPoro &TVectorPoro::operator=(const TVectorPoro &tvectorporo)
{
    if (this != &tvectorporo) {
        delete[] this->datos;
        this->dimension = tvectorporo.dimension;
        this->datos = new TPoro[tvectorporo.dimension];
        for (int i = 0; i < tvectorporo.dimension; i++) {
            this->datos[i] = tvectorporo.datos[i];
        }
        this->error = tvectorporo.error;
    }
    return *this;
}

bool TVectorPoro::operator==(const TVectorPoro &tvectorporo) const
{
    if (this->dimension != tvectorporo.dimension) {
        return false;
    }
    for (int i = 0; i < this->dimension; i++) {
        if (this->datos[i] != tvectorporo.datos[i]) {
            return false;
        }
    }
    return true;
}

bool TVectorPoro::operator!=(const TVectorPoro &tvectorporo) const{
    return !(*this == tvectorporo);
}

TPoro &TVectorPoro::operator[](int i){
    if(i >= 1 && i <= dimension && datos != nullptr){
        return datos[i-1];
    }
    return error;
}

TPoro TVectorPoro::operator[](int i) const{
    if(i >= 1 && i >= dimension){
        return datos[i-1];
    }
    return error;
}

int TVectorPoro::Longitud() const{
    return dimension;
}

int TVectorPoro::Cantidad() const{
    int count = 0;
    for (int i=0; i<dimension; i++){
        if (!datos[i].EsVacio()){
            count++;
        }
    }
    return count;
}

bool TVectorPoro::Redimensionar(int dim){
    if(dim <= 0 || dim == dimension){return false;}

    TPoro *newDatos = new TPoro[dim];
    int minDim = (dim < dimension) ? dim : dimension;
    for (int i=0; i < minDim; i++){
        newDatos[i] = datos[i];
    }
    delete[] datos;
    datos = newDatos;
    dimension = dim;
    return true;
}

ostream &operator<<(ostream &os, const TVectorPoro &tvector)
{
    os << "[";
    for (int i = 0; i < tvector.dimension; i++)
    {
        os << i+1 << " " << tvector.datos[i];
        if (i < tvector.dimension - 1)
        {
            os << " ";
        }
    }
    os << "]";
    return os;
}
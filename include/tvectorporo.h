#pragma once

#include "tporo.h"

class TVectorPoro{

    private:
        int dimension;
        TPoro *datos;
        TPoro error;

    public:
        TVectorPoro();
        TVectorPoro(int);
        TVectorPoro(const TVectorPoro &);
        ~TVectorPoro();
        
        TVectorPoro & operator=(const TVectorPoro &);
        bool operator==(const TVectorPoro &) const;
        bool operator!=(const TVectorPoro &) const;
        TPoro operator[](int) const;
        TPoro & operator[](int);
        int Longitud() const;
        int Cantidad() const;
        bool Redimensionar(int);

        friend ostream &operator<<(ostream &, const TVectorPoro &);
};
#ifndef _TPoro_H_
#define _TPoro_H_
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

class TPoro{
    private:
        int x;
        int y;
        double volumen;
        char* color;
    
        void Copiar(const TPoro &);
        void ConvertirMinusculas(char *);

    public:
        TPoro();
        TPoro(int , int, double);
        TPoro(int, int, double, const char *);
        TPoro(const TPoro &);
        ~TPoro();
        TPoro & operator=(const TPoro & );

        bool operator==(const TPoro & ) const;
        bool operator!=(const TPoro & ) const;
        void Posicion(int, int);
        void Volumen(double);
        void Color(const char *);
        int PosicionX() const;
        int PosicionY() const;
        double Volumen() const;
        char * Color() const;
        bool EsVacio() const;



        friend ostream & operator<< (ostream &, const TPoro &);
};

#endif
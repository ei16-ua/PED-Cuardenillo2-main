#include "../include/tporo.h"
#include "tporo.h"

void TPoro::Copiar(const TPoro &p)
{
    x = p.x;
    y = p.y;
    volumen = p.volumen;
    if (p.color != NULL) {
        color = new char[strlen(p.color) + 1];
        strcpy(color, p.color);
    } else {
        color = NULL;
    }
}

void TPoro::ConvertirMinusculas(char *c)
{
    for (int i = 0; c[i] != '\0'; i++) {
        c[i] = tolower(c[i]);
    }
}

TPoro::TPoro()
{
    this->x = 0;
    this->y = 0;
    this->volumen = 0;
    this->color = nullptr;

}

TPoro::TPoro(int px, int py, double v)
{
    this->x = px;
    this->y = py;
    this->volumen = v;
    this->color = nullptr;
}

TPoro::TPoro(int px, int py, double v, const char* c)
{
    this->x = px;
    this->y = py;
    this->volumen = v;
    if (c != NULL)
    {
        color = new char[strlen(c) + 1];
        strcpy(color, c);
        ConvertirMinusculas(color);
    }
    else{
        color = nullptr;
    }    
}

TPoro::TPoro(const TPoro &tporo ) 
{
    Copiar(tporo);
}

TPoro::~TPoro()
{
    if(color != nullptr){
        delete[] color;
        color = nullptr;
    }
}

TPoro &TPoro::operator=(const TPoro &tporo)
{
    if (this != &tporo)
    {
        int nuevo_x = tporo.x;
        int nuevo_y = tporo.y;
        double nuevo_volumen = tporo.volumen;
        char *nuevo_color = nullptr;

        if (tporo.color != nullptr)
        {
            nuevo_color = new char[strlen(tporo.color) + 1];
            strcpy(nuevo_color, tporo.color);
        }

        delete[] color;

        x = nuevo_x;
        y = nuevo_y;
        volumen = nuevo_volumen;
        color = nuevo_color;
    }
    return *this;
}


/*
bool TPoro::operator==(const TPoro &tporo ) const
{
    return this->x == tporo.x &&
        this->y == tporo.y &&
        this->volumen == tporo.volumen && 
        ((this->color == nullptr && tporo.color == nullptr) || 
        (this->color != nullptr && tporo.color != nullptr && 
            strcmp(this->color, tporo.color) == 0));
}*/
bool TPoro::operator==(const TPoro &tporo) const {
    if (x != tporo.x || y != tporo.y || volumen != tporo.volumen) {
        return false;
    }
    if ((color == nullptr && tporo.color != nullptr) || (color != nullptr && tporo.color == nullptr)) {
        return false;
    }
    if (color != nullptr && tporo.color != nullptr) {
        return strcmp(color, tporo.color) == 0;
    }
    return true;
}


bool TPoro::operator!=(const TPoro &tporo) const
{
    return !(*this == tporo);
}

void TPoro::Posicion(int new_x, int new_y)
{
    this->x = new_x;
    this->y = new_y;
}

void TPoro::Volumen(double new_volumen)
{
    this->volumen = new_volumen;
}

void TPoro::Color(const char *c)
{
    
    if (c != nullptr)
    {
        char *new_color = new char[strlen(c) + 1];
        strcpy(new_color, c);
        ConvertirMinusculas(new_color);

        delete[] color;
        color = new_color;
    }
    else{
        delete[] color;
        color = nullptr;
    }
}

int TPoro::PosicionX() const
{
    return x;
}

int TPoro::PosicionY() const
{
    return y;
}

double TPoro::Volumen() const
{
    return volumen;
}

char *TPoro::Color() const
{
    return color;
}

bool TPoro::EsVacio() const
{
    return x == 0 && y == 0 && volumen == 0 && color == nullptr;
}

ostream &operator<<(ostream &os, const TPoro &obj)
{
    if (obj.EsVacio()) {
        os << "()";
    } else {
        os.setf(ios::fixed);
        os.precision(2);
        os << "(" << obj.x << ", " << obj.y << ") ";

        /*para imprimir los números sin decimales
        if (obj.Volumen() == (int)obj.Volumen()) {
            os << (int)obj.Volumen();
        } else {
            os << obj.Volumen();
        }*/
        os << obj.Volumen();

        if (obj.Color() == nullptr) {
            os << " -";
        }else if(obj.Color()[0] == '\0'){
            os << " -" ;
        } else {
            os << " " << obj.Color();
        }
    }
    return os;
}



#ifndef VECTOR_2D
#define VECTOR_2D

#define FMTCARTESIANAS 1
#define FMTPOLARESG 2
#define FMTPOLARESR 4

#include <iostream>
#include <cmath>
#include "matematicas.h"


class Vector2D {
    private:
        
        double carx, cary;

    public: 
        
        
        enum class Uds {Grados, Radianes};                      

        
        //Constructores de la clase
        
        Vector2D (double x = 0, double y = 0);
        
        Vector2D (double modulo, double angulo, Vector2D::Uds unidad);
                            
        
        //Metodos setter de la clase
        
        void x(double n);

        void y(double n);
    
        void mod(double n);

        void ang(double n, Uds unidad = Uds::Grados);

        void multiplicar(double n);

        void sumar(const Vector2D &V);

        void restar(const Vector2D &V);

        friend std::istream &operator>>(std::istream &is, Vector2D &V);

        friend std::ostream &operator<<(std::ostream &os, const Vector2D &V);

           
        //Metodos getter de la clase
        
        double x() const;

        double y() const;

        double mod() const;

        double ang(Uds unidad = Uds::Grados) const;

        std::string to_string(int fmt=FMTCARTESIANAS|FMTPOLARESG) const;
        
    };

    
        //Funciones que pueden ser necesarias para el uso de la clase
    
    Vector2D sumar(const Vector2D &V1, const Vector2D &V2);

    Vector2D operator+(const Vector2D &V1, const Vector2D &V2);

    Vector2D restar(const Vector2D &V1, const Vector2D &V2);

    Vector2D operator-(const Vector2D &V1, const Vector2D &V2);

    double multiplicar(const Vector2D &V1, const Vector2D &V2);

    double operator*(const Vector2D &V1, const Vector2D &V2);

    Vector2D multiplicar(const Vector2D &V1, double n);

    Vector2D operator*(const Vector2D &V1, double n);

    Vector2D multiplicar(double n, const Vector2D &V1);

    Vector2D operator*(double n, const Vector2D &V1);

    Vector2D operator/(const Vector2D &V1, double n);

    #endif

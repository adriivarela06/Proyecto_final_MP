#include "Vector2D.h"

    //Constructores con valores por defecto
    
    Vector2D::Vector2D(double modulo, double angulo, Vector2D::Uds unidad){
        if(unidad == Vector2D::Uds::Radianes){
            carx = modulo * cos(angulo);
            cary = modulo * sin(angulo);
        }else if(unidad == Vector2D::Uds::Grados){
            carx = modulo * cos(angulo * TO_RAD);
            cary = modulo * sin(angulo * TO_RAD);
        }  
    }

    Vector2D::Vector2D(double x, double y){
        carx = x;
        cary = y;
    }

    // Metodos del tipo set
    
    void Vector2D::x(double n) {
        carx = n;
    }

    void Vector2D::y(double n) {
        cary = n;
    }

    void Vector2D::mod(double modulo){
        double angulo = ang(Vector2D::Uds::Radianes);
        
        x(modulo * cos(angulo));
        y(modulo * sin(angulo));
    }

    void Vector2D::ang(double angulo, Vector2D::Uds unidad){
        double modulo = mod();
        
        if(unidad == Vector2D::Uds::Radianes){
            x(modulo * cos(angulo));
            y(modulo * sin(angulo));
        }
        else{
            x(modulo * cos(angulo * TO_RAD));
            y(modulo * sin(angulo * TO_RAD));
        }
    }

    void Vector2D::multiplicar(double n){
        carx*= n;
        cary*= n;
    }

    void Vector2D::sumar(const Vector2D &V){
        carx += V.x();
        cary += V.y();
    }

    void Vector2D::restar(const Vector2D &V){
        carx -= V.x();
        cary -= V.y();
    }

    //Metodos del tipo get

    double Vector2D::x() const{
        return carx;
    }

    double Vector2D::y() const{
        return cary;
    }

    double Vector2D::mod() const{
        return sqrt(pow(x(),2) + pow(y(),2));
    }

    double Vector2D::ang(Vector2D::Uds unidad) const{
        double angulo = atan2(y(),x());
        
        if (unidad == Vector2D::Uds::Grados)
            angulo *= TO_DEG;

        return angulo;
    }
    
    std::string Vector2D::to_string(int fmt) const{
        std::string cadena;
        
        if((fmt & FMTCARTESIANAS) == FMTCARTESIANAS)
            cadena += "P=(" + std::to_string(x()) + ',' + std::to_string(y()) + ") ";

        if(fmt >= FMTPOLARESG){
            cadena += "# @mod=" + std::to_string(mod()) + ' ';
            
            if((fmt & FMTPOLARESR) == FMTPOLARESR)
                cadena += "@rad=" + std::to_string(ang(Uds::Radianes)) + ' ';

            if ((fmt & FMTPOLARESG) == FMTPOLARESG)
                cadena += "@deg=" + std::to_string(ang());
        }
        
        return cadena;
    }

    //Funciones de sobrecarga de operadores del tipo friend

    std::istream &operator>>(std::istream &is, Vector2D &V){
        double x, y;
        is >> x >> y;
        V.x(x);
        V.y(y);
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const Vector2D &V){
        os << "(" << V.x() << "," << V.y() << ")";
        return os;
    }

    
    //Funciones a parte del class

    Vector2D sumar(const Vector2D &V1, const Vector2D &V2){
       Vector2D V(V1.x() + V2.x(), V1.y() + V2.y());

       return V;
    }

    Vector2D operator+(const Vector2D &V1, const Vector2D &V2){
        return sumar(V1, V2);
    }

    Vector2D restar(const Vector2D &V1, const Vector2D &V2){
        Vector2D V(V1.x() - V2.x(), V1.y() - V2.y());

        return V;
    }

    Vector2D operator-(const Vector2D &V1, const Vector2D &V2){
        return restar(V1, V2);
    }

    double multiplicar(const Vector2D &V1, const Vector2D &V2){
        double prod = V1.x() * V2.x() + V1.y() * V2.y();

        return prod;
    }

    double operator*(const Vector2D &V1, const Vector2D &V2){
        return multiplicar(V1, V2);
    }

    Vector2D multiplicar(const Vector2D &V1, double n){
        Vector2D V(n * V1.x(), n * V1.y());

        return V;
    }

    Vector2D operator*(const Vector2D &V1, double n){
        return multiplicar(V1, n);
    }

    Vector2D multiplicar(double n, const Vector2D &V1){
        Vector2D V(n * V1.x(), n * V1.y());

        return V;
    }

    Vector2D operator*(double n, const Vector2D &V1){
        return multiplicar(V1, n);
    }

    Vector2D operator/(const Vector2D &V1, double n){
        return multiplicar(V1, 1/n);
    }

    //HACER PRODUCTO VECTORIAL NO TE OLVIDES
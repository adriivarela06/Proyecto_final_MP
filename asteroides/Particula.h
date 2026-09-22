#ifndef PARTICULA_H
#define PARTICULA_H

#include "bigs.h"
#include "Vector2D.h"

class Particula {
    private:
        
        Vector2D p, v, a, d;
        double rad, dens, tiempo;
        BiGS::Color c;
        //1 si es nave, 2 si es disparo y 3 si es asteroide
        int objeto;
        bool dif;
    
    public:

        Particula();

        Particula(const Vector2D &pos, const Vector2D &vel);

        Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel);
    
        Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel, const Vector2D &dir, double ra, double de);

        Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel, const Vector2D &dir, double ra, double de, int tipo);

            //Metodos getter

        Vector2D posicion() const;

        Vector2D velocidad() const;

        Vector2D aceleracion() const;

        std::string to_string() const;

        double radio() const;

        double densidad() const;

        double masa() const;

        Vector2D direccion() const;

        bool difunta() const;

        int tipo() const;

        double time() const;

        void dibujar(bool flechas=false) const;

            //Metodos setters
        
        void posicion(const Vector2D &pos);

        void posicion(double carx, double cary);

        void velocidad(const Vector2D &vel);

        void velocidad(double mod, double ang);

        void aceleracion(const Vector2D &acel);

        void aceleracion(double mod, double ang);

        void vmod(double mod);

        void vang(double ang);

        void amod(double mod);

        void aang(double ang);

        void radio(double rad);

        void densidad(double dens);

        void direccion(double a);

        void girar(double ang);

        void tipo(int t);

        void color(const BiGS::Color &c);

        void difunta(bool dif);

        void time(double t);

            //Metodos de movimiento
        
        void avanzaMRU(double dt);

        void avanzaMUA(double dt);

        void rebota(int Ancho, int Alto, bool rebote_paredes = true);
    
};

        void corrige_velocidad(Particula &a1, Particula &a2);

        bool chocan(const Particula &P1, const Particula &P2);
#endif
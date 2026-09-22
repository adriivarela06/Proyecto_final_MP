#include "Particula.h"

    //Constructores

Particula::Particula() : p(0,0), v(0,0), a(0,0), d(0,1), rad(5), dens(1), dif(false), objeto(3), tiempo(0){}
    
Particula::Particula(const Vector2D &pos, const Vector2D &vel) : p(pos), v(vel), a(0,0), d(0,1), rad(5), dens(1), dif(false), objeto(3), tiempo(0){}
    
Particula::Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel) : p(pos), v(vel), a(acel), d(0,1), rad(5), dens(1), dif(false), objeto(3), tiempo(0){}
        
Particula::Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel, const Vector2D &dir, double ra, double de) : p(pos), v(vel), a(acel), d(dir), rad(ra), dens(de), dif(false), objeto(3), tiempo(0){}

Particula::Particula(const Vector2D &pos, const Vector2D &vel, const Vector2D &acel, const Vector2D &dir, double ra, double de, int tipo) : p(pos), v(vel), a(acel), d(dir), rad(ra), dens(de), objeto(tipo), dif(false), tiempo(0){}

    //Metodos getters

Vector2D Particula::posicion() const{
    return p;
}

Vector2D Particula::velocidad() const{
    return v;
}

Vector2D Particula::aceleracion() const{
    return a;
}

std::string Particula::to_string() const{
     std::string cadena;

     cadena += "P=(" + std::to_string(p.x()) + ',' + std::to_string(p.y()) + ") V=(@mod:" + std::to_string(v.mod()) + ",@ang:" + std::to_string(v.ang()) + "d) A=(@mod:" + std::to_string(a.mod()) + ",@ang:" + std::to_string(a.ang()) + ")" + " @rad:" + std::to_string(radio()) ;

     return cadena;
} 

double Particula::radio() const{
    return rad;
}

double Particula::densidad() const{
    return dens;
}

double Particula::masa() const{
    return dens * PI * pow(rad,2);
}

Vector2D Particula::direccion() const{
    return d;
}

bool Particula::difunta() const{
    return dif;
}

int Particula::tipo() const{
    return objeto;
}

double Particula::time() const{
    return tiempo;
}

void Particula::dibujar(bool flechas) const{
    BiGS::drawCircle(posicion().x(), posicion().y(), rad, c, c);
    if(flechas){
        if(objeto == 1)
            BiGS::drawArrow(posicion().x(),
                            posicion().y(),
                            posicion().x() + radio(),
                            posicion().y() + radio(),
                            radio() / 5,
                            10,
                            BiGS::colorRGB(0, 100, 0));
        BiGS::drawArrow(posicion().x(),
                        posicion().y(),
                        posicion().x() + velocidad().x(),
                        posicion().y() + velocidad().y(),
                        radio() / 10,
                        5,
                        BiGS::CYellow);
        BiGS::drawArrow(posicion().x(),
                        posicion().y(),
                        posicion().x() +  aceleracion().x(),
                        posicion().y() + aceleracion().y(),
                        radio() / 10,
                        5,
                        BiGS::CRed);
    }
}

    //Metodos setters

void Particula::posicion(const Vector2D &pos){
    p = pos;
}

void Particula::posicion(double carx, double cary){
    p.x(carx);
    p.y(cary);
}

void Particula::velocidad(const Vector2D &vel){
    v = vel;
}

void Particula::velocidad(double mod, double ang){
    v.x(mod * cos(ang * TO_RAD));
    v.y(mod * sin(ang * TO_RAD));
}

void Particula::aceleracion(const Vector2D &acel){
    a = acel;
}

void Particula::aceleracion(double mod, double ang){
    a.x(mod * cos(ang * TO_RAD));
    a.y(mod * sin(ang * TO_RAD));
}

void Particula::vmod(double mod){
    v.mod(mod);
}

void Particula::vang(double ang){
    v.ang(ang);
}

void Particula::amod(double mod){
    a.mod(mod);
}

void Particula::aang(double ang){
    a.ang(ang);
}

void Particula::radio(double rad){
    this->rad = rad;
}

void Particula::densidad(double d){
    dens = d;
}

void Particula::direccion(double a){
    d.ang(a);
}

void Particula::girar(double ang){
    d.ang(d.ang() + ang);
}

void Particula::tipo(int t){
    objeto = t;
}

void Particula::color(const BiGS::Color &c){
    this->c = c;
}


void Particula::difunta(bool estado){
    dif = estado;
}

void Particula::time(double t){
    tiempo = t;
}

    //Metodos de movimiento

void Particula::avanzaMRU(double dt){
    Vector2D nuevo = velocidad();
    
    nuevo.multiplicar(dt);
    p.sumar(nuevo);
}

void Particula::avanzaMUA(double dt){
    Vector2D nuevo = velocidad();
    nuevo.multiplicar(dt);
    p.sumar(nuevo);

    nuevo = aceleracion();
    nuevo.multiplicar(dt*dt/2);
    p.sumar(nuevo);

    nuevo = aceleracion();
    nuevo.multiplicar(dt);
    v.sumar(nuevo);
}

void Particula::rebota(int Ancho, int Alto, bool rebote_paredes){
    bool colhor = false, colver = false;
    if(rebote_paredes){
        // Izquierda
        if(posicion().x() - radio() < 0){
            colhor = true;
            posicion(radio(), posicion().y());
        }
        // Derecha
        if(posicion().x() + radio() >= Ancho){
            colhor = true;
            posicion(Ancho - radio(), posicion().y());
        }
        // Arriba
        if(posicion().y() - radio() < 0){
            colver = true;
            posicion(posicion().x(), radio());
        }
        // Abajo
        if(posicion().y() + radio() >= Alto){
            colver = true;
            posicion(posicion().x(), Alto - radio());
        }
        // Si hay colisión: corregir rumbo
        if(colhor)
            vang(180 - velocidad().ang());
        if(colver)
            vang(360 - velocidad().ang());
    }else{
        if(posicion().x() + radio() < 0)
            posicion(Ancho + radio(), posicion().y());
        if(posicion().x() - radio() > Ancho)
            posicion(-radio(), posicion().y());
        if(posicion().y() + radio() < 0)
            posicion(posicion().x(), Alto + radio());
        if(posicion().y() - radio() > Alto)
            posicion(posicion().x(), -radio());
    }
}

void corrige_velocidad(Particula &a1, Particula &a2) {
    Vector2D v1 = a1.velocidad();
    Vector2D v2 = a2.velocidad();
    if ((v1.x()-v2.x())*(a2.posicion().x()-a1.posicion().x()) + (v1.y()-v2.y())*(a2.posicion().y()-a1.posicion().y()) >= 0){
        double sum = a1.masa() + a2.masa();
        Vector2D difp12 = a1.posicion() - a2.posicion();
        Vector2D difp21 = a2.posicion() - a1.posicion();
        double dot1 = difp12 * (v1-v2);
        double dot2 = (v2-v1) * difp21;
        double norma1 = difp12.mod();
        norma1 *= norma1; 
        double norma2 = difp21.mod();
        norma2 *= norma2;
        Vector2D nueva_v1 = v1 - (2*a2.masa()/sum) * dot1 * (1.0/norma1) * difp12;
        Vector2D nueva_v2 = v2 - (2*a1.masa()/sum) * dot2 * (1.0/norma2) * difp21;
        a1.velocidad(nueva_v1);
        a2.velocidad(nueva_v2);
    }
}

//Implemento una nueva funcion para comprobar si dos particulas chocan
bool chocan(const Particula &P1, const Particula &P2){
    bool superpuestas = false;
    Vector2D une_centros(P1.posicion().x() - P2.posicion().x(),
                         P1.posicion().y() - P2.posicion().y());
    if(une_centros.mod() <= P1.radio() + P2.radio())
        superpuestas = true;
    return superpuestas;
}

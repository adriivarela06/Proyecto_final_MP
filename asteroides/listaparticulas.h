#ifndef LISTAPARTICULAS_H
#define LISTAPARTICULAS_H
#include "Particula.h"

class ListaParticulas {
    private:
        Particula *lista;
        int num;
    public:
        ListaParticulas();

        ~ListaParticulas();

        ListaParticulas(const ListaParticulas &orig);

        ListaParticulas &operator=(const ListaParticulas &orig);

        int size() const;

        void set(const Particula &p, int pos);

        Particula get(int pos) const;

        void borra(int pos);

        void inserta(const Particula &p, int pos=-1);

        void colisiones(int Ancho, int Alto, bool rebote_paredes = true);

        bool son_difuntas(const BiGS::Audio &Exp, const BiGS::Audio &Navexp, const BiGS::Audio &Reload, int &Marcador, int &balas_en_pantalla);

        void comprueba_teclas(int &balas_en_pantalla, const BiGS::Audio &Shot, const BiGS::Audio &No_Ammo, bool &rebote_paredes);
};

#endif
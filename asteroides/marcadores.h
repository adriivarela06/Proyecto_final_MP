#ifndef MARCADORES_H
#define MARCADORES_H
#include <fstream>

class Ranking{
    private:
        int *puntos, tam;
        std::string *nombres;
    public:
        ~Ranking();
        Ranking();

        int get_n(int i) const;
        std::string get_s(int i) const;
        std::string to_string() const;
        int size() const;
    
        void inserta(std::string cad);
        void suma_puntos(std::string cad, int pts);
};

#endif
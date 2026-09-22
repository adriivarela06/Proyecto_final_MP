#include "marcadores.h"

Ranking::~Ranking(){
    if(tam > 0){
        delete [] puntos;
        delete [] nombres;
    }
    puntos = nullptr;
    nombres = nullptr;
    tam = 0;
}
//Constructor
Ranking::Ranking() : puntos(nullptr), nombres(nullptr), tam(0) {}
//Metodos getter
int Ranking::get_n(int i) const{
    return puntos[i];
}
std::string Ranking::get_s(int i) const{
    return nombres[i];
}
std::string Ranking::to_string() const{
    std::string cad = "El ranking de los jugadores es el siguiente:\n";
    if(tam > 0)
        for(int i = 0; i < tam; ++i)
            cad += nombres[i] + " - " + std::to_string(puntos[i]) + " puntos\n";
    else
        cad += "No hay jugadores en el ranking\n";
    return cad;
}
int Ranking::size() const{
    return tam;
}
//Metodos setter
void Ranking::inserta(std::string cad){
        int *naux = new int [tam+1];
        std::string *saux = new std::string [tam+1];
        for(int i = 0; i < tam; ++i){
            naux[i] = puntos[i];
            saux[i] = nombres[i];
        }
        naux[tam] = 0;
        saux[tam] = cad;
        delete [] puntos;
        delete [] nombres;
        puntos = naux;
        nombres = saux;
        tam++;
}    
void Ranking::suma_puntos(std::string cad, int pts){
    bool encontrado = false;
    for(int i = 0; i < tam && !encontrado; ++i){
        if(cad == nombres[i]){
            encontrado = true;
                puntos[i] += pts;
        }
    }
    //Reordenamos el vector en caso de que cambie el orden
    for(int i = 0; i < tam; ++i){
        int max = i;
        for(int j = i + 1; j < tam; ++j)
            if(puntos[j] > puntos[max])
                max = j;
        if(max != i){
            int naux;
            std::string saux;
            naux = puntos[max];
            saux = nombres[max];
            puntos[max] = puntos[i];
            nombres[max] = nombres[i];
            puntos[i] = naux;
            nombres[i] = saux;
        }
    }
}

#include <iostream>
#include <fstream>
#include "marcadores.h"
using namespace std;

int main(int argc, char **argv){
    Ranking Rank;
    string n_fich;
    if(argc > 1)
        n_fich += argv[1];
    ifstream fichero(n_fich);
    bool fin = false;

    if(fichero.fail())
        fin = true;
    if(!fin){
        int num;
        string nombre;
        while(fichero >> num){
            fichero.ignore();
            getline(fichero, nombre);
            bool inserta = true;
            for(int i = 0; i < Rank.size(); ++i)
                if(nombre == Rank.get_s(i))
                    inserta = false;
            if(inserta)
                Rank.inserta(nombre);
            Rank.suma_puntos(nombre, num);
        }
        cout << Rank.to_string();
    }
    else
        cout << "No se ha podido abrir el fichero" << endl;
}
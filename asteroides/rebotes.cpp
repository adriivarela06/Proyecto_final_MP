#include "listaparticulas.h"
#include "bigs.h"

int main (int argc, char **argv){
    srand(time(0));
    double v[9];
    bool fin = false;
    if(argc == 10){
        for(int i = 0; i < 9 && !fin; i++){
            if(!cad2num(argv[i+1], v[i]))
                fin = true;
        }
    }else
        fin = true;
    
    if(!fin){
        BiGS::windowOpen(v[0],v[1],"Partículas rebotando",true,DRAWMODE_DELAYED);
        ListaParticulas particulas;
        int tam = 0;
        while(tam < v[2]){
            bool superpuestas = false;
            double radio = aleatorio(v[3],v[4]);
            Particula P(Vector2D (aleatorio(radio,v[0] - radio), aleatorio(radio,v[1] - radio)),
                        Vector2D (aleatorio(v[5], v[6]), aleatorio(0,359), Vector2D::Uds::Grados),
                        Vector2D (aleatorio(v[7], v[8]), aleatorio(0, 359), Vector2D::Uds::Grados),
                        Vector2D (0,0),
                        radio,
                        aleatorio(1,10));
            P.color(BiGS::colorRandom());
            for(int j = 0; j < tam; ++j)
                if(chocan(particulas.get(j), P))
                    superpuestas = true;
            if(!superpuestas){
                particulas.inserta(P);
                tam++;
            }
        }
        while (!BiGS::closeRequested()){
            // Calcular tiempo transcurrido desde la anterior iteración
            double dift = BiGS::timeFromLastCall();
            // Detectar colisiones con bordes de la ventana
            particulas.colisiones(v[0], v[1]);
            //Hacemos un bucle anidado para comprobar que particulas chocan entre ellas y cambiamos su rumbo
            for(int j = 0; j < v[2]; ++j){
                for(int k = j + 1; k < tam; ++k){
                    if(chocan(particulas.get(j), particulas.get(k))){
                        Particula P1 = particulas.get(j),
                                  P2 = particulas.get(k);
                        corrige_velocidad(P1, P2);
                        particulas.set(P1, j);
                        particulas.set(P2, k);
                    }
                }
            }
            
            for(int j = 0; j < tam; ++j){
                Particula P = particulas.get(j);
                P.avanzaMUA(dift);
                particulas.set(P,j);
            }
            BiGS::clear(BiGS::CBlack);
            for(int j = 0; j < v[2]; ++j)
                particulas.get(j).dibujar(false);
            BiGS::refresh();
        }
    }else{
        std::cout << "La sintaxis para llamar a este programa es:" << std::endl << "  ./rebotes ancho largo N Rmin Rmax Vmin Vmax Amin Amax" << std::endl << "       Ancho y largo: son las dimensiones de la ventana que se va a abrir" << std::endl << "       N: es el numero de particulas que se van a crear" << std::endl << "       Rmin y Rmax: es el rango del que se saca el radio de las particulas" << std::endl << "       Vmin y Vmax: es el rango del que se saca el modulo de la velocidad de las particulas" << std::endl << "       Amin Amax: es el rango del que se saca el modulo de la aceleracion de las particulas" << std::endl << "Todos los datos han de ser numéricos" << std::endl;
    }
}
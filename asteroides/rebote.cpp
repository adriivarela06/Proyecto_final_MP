#include "Particula.h"

int main(int argc, char **argv) {
    srand(time(0));
    const int height=200, width=200;
    BiGS::windowOpen(width,height,"Partícula rebotando",true,DRAWMODE_DELAYED);
    // Crear partícula aleatoria p
    Particula p(Vector2D (aleatorio(0,width), aleatorio(0,height)),
                Vector2D (aleatorio(10, 40), aleatorio(0,360), Vector2D::Uds::Grados),
                Vector2D (aleatorio(0, 20), aleatorio(0, 360), Vector2D::Uds::Grados));
    p.radio(aleatorio(10,30));
    p.color(BiGS::colorRandom());
    // Esperamos a que el usuario pulse Cerrar Ventana (X)
    while (!BiGS::closeRequested()){
        // Calcular tiempo transcurrido desde la anterior iteración
        double dift = BiGS::timeFromLastCall();
        // Detectar colisiones con bordes de la ventana
        p.rebota(width, height);
        p.avanzaMUA(dift);
        BiGS::clear(BiGS::CBlack);
        p.dibujar(true);
        BiGS::refresh();
        BiGS::timeDelay(5);
    }
    return 0;
}    
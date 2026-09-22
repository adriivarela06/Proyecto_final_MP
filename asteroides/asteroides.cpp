#include "listaparticulas.h"
#include <fstream>

///////////////////////////////////////////////////////////////////   Funciones para modularizar el codigo   ///////////////////////////////////////////////////////////////////

void dibuja_marcadores(int Ancho, int Alto, int Marcador, std::string jugador, std::string rebotes, int disp, int velocidad, int aceleracion, BiGS::Font Letras, BiGS::Font Numeros){
    //Arriba
    BiGS::txtDraw("Marcador", 10, 10, BiGS::colorRGB(0,250,154), Letras);
    BiGS::txtDraw(std::to_string(Marcador).c_str(), 10 + BiGS::txtTextWidth("Marcador", Letras) / 2, 35, BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
    BiGS::txtDraw("Jugador", Ancho / 2, 10, BiGS::colorRGB(0,250,154), Letras, ALIGN_CENTRE);
    BiGS::txtDraw(jugador.c_str(), Ancho / 2, 35, BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
    BiGS::txtDraw("Municion", Ancho - 10, 10, BiGS::colorRGB(0,250,154), Letras, ALIGN_RIGHT);
    BiGS::txtDraw(std::to_string(disp).c_str(), Ancho - 10 - BiGS::txtTextWidth("Municion", Letras) / 2, 35, BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
    //Abajo
    BiGS::txtDraw("Velocidad", 10, Alto - BiGS::txtLineHeight(Letras), BiGS::colorRGB(0,250,154), Letras);
    BiGS::txtDraw(std::to_string(velocidad).c_str(),10 + BiGS::txtTextWidth("Marcador", Letras) / 2, Alto - 35 - BiGS::txtLineHeight(Letras), BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
    BiGS::txtDraw("Rebotes", Ancho / 2, Alto - BiGS::txtLineHeight(Letras), BiGS::colorRGB(0,250,154), Letras, ALIGN_CENTRE);
    BiGS::txtDraw(rebotes.c_str(), Ancho / 2, Alto - 35 - BiGS::txtLineHeight(Letras), BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
    BiGS::txtDraw("Aceleracion", Ancho - 10 , Alto - BiGS::txtLineHeight(Letras), BiGS::colorRGB(0,250,154), Letras, ALIGN_RIGHT);
    BiGS::txtDraw(std::to_string(aceleracion).c_str(), Ancho - 10 - BiGS::txtTextWidth("Municion", Letras) / 2, Alto - 35 - BiGS::txtLineHeight(Letras), BiGS::colorRGB(123,104,238), Numeros, ALIGN_CENTRE);
}

void dibujar(const ListaParticulas &lista, const BiGS::Image &Halcon, const BiGS::Image &Asteroide){
    for(int i = 0; i < lista.size(); ++i){    
        if(lista.get(i).tipo() == 1)
            BiGS::imageDrawR(Halcon,
                            lista.get(i).posicion().x() - lista.get(i).radio() - 10, 
                            lista.get(i).posicion().y() - lista.get(i).radio() - 10,
                            lista.get(i).posicion().x() + lista.get(i).radio() + 10, 
                            lista.get(i).posicion().y() + lista.get(i).radio() + 10,
                            (lista.get(i).direccion().ang() + 90) * TO_RAD);
        if(lista.get(i).tipo() == 2)
                lista.get(i).dibujar();
        if(lista.get(i).tipo() == 3)
            BiGS::imageDrawR(Asteroide,
                            lista.get(i).posicion().x() - lista.get(i).radio() - 3, 
                            lista.get(i).posicion().y() - lista.get(i).radio() - 3,
                            lista.get(i).posicion().x() + lista.get(i).radio() + 3, 
                            lista.get(i).posicion().y() + lista.get(i).radio() + 3,
                            (lista.get(i).direccion().ang() + 90) * TO_RAD);
    }
}

void inicializa_ast(ListaParticulas &particulas, int max, int Ancho, int Alto){
    while(particulas.size() < max){
        bool cumple = true;
        double radio = aleatorio(AstRMin, AstRMax);
        Particula P(Vector2D (aleatorio(radio, Ancho - radio),aleatorio(radio, Alto - radio)),
                    Vector2D (aleatorio(AstVMin, AstVMax), aleatorio(0,359), Vector2D::Uds::Grados),
                    Vector2D (0, 0),
                    Vector2D (1, aleatorio(0,359), Vector2D::Uds::Grados),
                    radio,
                    aleatorio(AstDMin, AstDMax));
        if((P.posicion().x() > 100 && P.posicion().x() < Ancho - 100) || (P.posicion().y() > 100 && P.posicion().y() < Alto - 100))
            cumple = false;
        for(int i = 0; i < particulas.size() && cumple; ++i)
            if(chocan(particulas.get(i), P))
                cumple = false;
        if(cumple)
            particulas.inserta(P);
    }
}

///////////////////////////////////////////////////////////////////   Main asteroides   ///////////////////////////////////////////////////////////////////

int main (int argc, char **argv){
    srand(time(0));
    int Ancho = 800,
        Alto = 600,
        x1 = 100,
        y1 = 218,
        x2 = Ancho - 100,
        y2 = Alto - 218,
        balas_en_pantalla = 0,
        Marcador = 0;
    double astn,
           dispmax,
           disptvida;
    std::string jugador,
                ranking;
    bool astnb = false,
         dispmaxb = false,
         disptvidab = false,
         jugadorb = false,
         rankingb = false,
         game_over = false,
         victoria = false,
         crece = true,
         out_of_ammo = false,
         rebote_paredes = true,
         salir = false;
    ListaParticulas particulas;

///////////////////////////////////////////////////////////////////   Carga de elementos audiovisuales   ///////////////////////////////////////////////////////////////////                
    
    BiGS::windowOpen(Ancho, Alto, "ASTEROIDES", true, DRAWMODE_DELAYED);
    BiGS::Audio Shot = BiGS::audioLoad("./data/SHOT.ogg"),
                No_Ammo = BiGS::audioLoad("./data/OUT_OF_AMMO.ogg"),
                Loose = BiGS::audioLoad("./data/LOOSE.ogg"),
                Win = BiGS::audioLoad("./data/WIN.ogg"),
                Exp = BiGS::audioLoad("./data/EXPLOSION.ogg"),
                Navexp = BiGS::audioLoad("./data/NAVE_EXP.ogg"),
                Reload = BiGS::audioLoad("./data/RELOAD.ogg"),
                Arcade = BiGS::audioLoad("./data/ARCADE.ogg"); 
    BiGS::Image Asteroide = BiGS::imageLoad("./data/ASTEROIDE.png"),
                Final = BiGS::imageLoad("./data/FINAL.png"),
                Fondo = BiGS::imageLoad("./data/FONDO.jpg"),
                Halcon = BiGS::imageLoad("./data/HALCON.png"),
                Inicio = BiGS::imageLoad("./data/INICIO.png"),
                Victoria = BiGS::imageLoad("./data/VICTORIA.png");
    BiGS::Font Letras = BiGS::txtLoadFont("./data/LETRAS.ttf", 25),
               Numeros = BiGS::txtLoadFont("./data/NUMEROS.ttf", 30);

///////////////////////////////////////////////////////////////////   Comprobacion de los argumentos de la consola   ///////////////////////////////////////////////////////////////////
    
    for(int i = 1; i < argc; i += 2){
        if(cad2min(argv[i]) == "-astn"){
            if(cad2num(argv[i+1],astn))
                astnb = true;
            else
                astn = 0;
        }
        if(cad2min(argv[i]) == "-dispmax"){
            if(cad2num(argv[i+1],dispmax))
                dispmaxb = true;
            else
                dispmax = 0;
        } 
        if(cad2min(argv[i]) == "-disptvida"){
            if(cad2num(argv[i+1],disptvida))
                disptvidab = true;
            else
                disptvida = 0;
        }
        if(cad2min(argv[i]) == "-jugador"){
            jugador = argv[i+1];
            jugadorb = true;
        }
        if(cad2min(argv[i]) == "-ranking"){
            ranking = argv[i+1];
            rankingb = true;
        }
    }

///////////////////////////////////////////////////////////////////   Inicializacion de las particulas   ///////////////////////////////////////////////////////////////////

    Particula Nave(Vector2D (Ancho/2, Alto/2), Vector2D (0,0), Vector2D (0,0), Vector2D (1,270,Vector2D::Uds::Grados), NaveR, 1, 1);
    particulas.inserta(Nave);

    if(!astnb)
        astn = AstN;
    if(!dispmaxb)
        dispmax = DispMax;
    if(!disptvidab)
        disptvida = DispTVida;
    if(!jugadorb)
        jugador = "Han Solo";
   
    inicializa_ast(particulas, astn + 1, Ancho, Alto);

///////////////////////////////////////////////////////////////////   Algoritmo para la imagen inicial   ///////////////////////////////////////////////////////////////////

    BiGS::audioPlay(Arcade, 5, 0.1, 0, 1, ALLEGRO_PLAYMODE_LOOP);
    BiGS::Event E;
    while(!salir && !BiGS::closeRequested()){
        if(BiGS::eventNext(E))
            if(E.type == BiGS::KEY_DOWN)
                salir = true;
        BiGS::clear();
        BiGS::imageDrawR(Fondo, -135, 0, 935, 600);
        dibujar(particulas, Halcon, Asteroide);
        BiGS::imageDrawR(Inicio, x1, y1, x2, y2);
        BiGS::refresh();
        if(x1 == 100)
            crece = true;
        if(x1 == 50)
            crece = false;
        if(crece){
            x1--;
            y1--;
            x2++;
            y2++;
        }
        if(!crece){
            x1++;
            y1++;
            x2--;
            y2--;
        }
        BiGS::timeDelay(30);
    }

///////////////////////////////////////////////////////////////////   Algoritmo principal de juego   ///////////////////////////////////////////////////////////////////

    while (!BiGS::closeRequested() && !victoria && !game_over){
        double dift = BiGS::timeFromLastCall();

        // Deteccion de colisiones con los bordes de la ventana
        particulas.colisiones(Ancho, Alto, rebote_paredes);

        //Bucle para sumar el tiempo transcurrido a las balas
        for(int i = 1; i < particulas.size(); ++i){
            if(particulas.get(i).tipo() == 2){
                Particula P = particulas.get(i);
                P.time(P.time() + dift);
                particulas.set(P,i);
            }
        }

        //Bucle anidado para comprobar los choques entre particulas y tiempo de balas
        for(int i = 0; i < particulas.size(); ++i){
            if(particulas.get(i).tipo() == 2 && particulas.get(i).time() >= DispTVida){
                Particula P = particulas.get(i);
                P.difunta(true);
                particulas.set(P,i);
            }
            for(int j = i + 1; j < particulas.size(); ++j){
                if(chocan(particulas.get(i), particulas.get(j)) && particulas.get(i).difunta() == false && particulas.get(j).difunta() == false){
                    Particula P1 = particulas.get(i),
                              P2 = particulas.get(j);
                    if(P1.tipo() == 3 &&  P2.tipo() == 3)
                        corrige_velocidad(P1, P2);
                    else {
                            P1.difunta(true);
                            P2.difunta(true);
                    }
                    particulas.set(P1, i);
                    particulas.set(P2, j);
                }
            }
        }
        
        //Lectura de las teclas
        particulas.comprueba_teclas(balas_en_pantalla, Shot, No_Ammo, rebote_paredes);

        //Hacemos los cambios si son difuntas
        if(particulas.son_difuntas(Exp, Navexp, Reload, Marcador, balas_en_pantalla))
            game_over = true;

        //Comprobacion de si quedan asteroides
        victoria = true;
        for(int i = 0; i < particulas.size() && !game_over; ++i)
            if(particulas.get(i).tipo() == 3)
                victoria = false;

        //MUA a todas las particulas
        for(int i = 0; i < particulas.size() && !game_over && !victoria; ++i){
            Particula P = particulas.get(i);
            P.avanzaMUA(dift);
            particulas.set(P,i);
        }

        //Se dibuja todo
        BiGS::clear();
        BiGS::imageDrawR(Fondo, -135, 0, 935, 600);
        dibujar(particulas, Halcon, Asteroide);
        if(!game_over && !victoria){
            int disp = dispmax - balas_en_pantalla,
                velocidad = particulas.get(0).velocidad().mod(),
                aceleracion = particulas.get(0).aceleracion().mod();
            std::string rebote = "Si";
            if(!rebote_paredes)
                rebote = "No";
            dibuja_marcadores(Ancho, Alto, Marcador, jugador, rebote, disp, velocidad, aceleracion, Letras, Numeros);
        }
        BiGS::refresh();
        BiGS::timeDelay(5);
    }

///////////////////////////////////////////////////////////////////   Ranking   ///////////////////////////////////////////////////////////////////

    if(rankingb){
        std::ofstream fichero(ranking, std::ios::app);
        fichero << std::to_string(Marcador) << " " << jugador << std::endl;
        fichero.close();
    }

///////////////////////////////////////////////////////////////////   Final del juego   ///////////////////////////////////////////////////////////////////
    
    BiGS::clear();
    BiGS::imageDrawR(Fondo, -135, 0, 935, 600);
    BiGS::refresh();
    BiGS::audioStop(5);
    BiGS::Color C;
    if(game_over){
        BiGS::timeDelay(1000);
        BiGS::audioPlay(Loose, 0);
        BiGS::imageDrawR(Final, 0, 200, 800, 400);
        C = BiGS::colorRGB(128, 0, 0);
    }
    else{
        BiGS::timeDelay(200);
        BiGS::audioPlay(Win, 0);
        BiGS::imageDrawR(Victoria, 0, 200, 800, 400);
        C = BiGS::colorRGB(100, 30, 22);
    }
    BiGS::txtDraw("Pulse una tecla para cerrar el juego", Ancho / 2, Alto - 200, C, Letras, ALIGN_CENTRE);
    BiGS::refresh();
    BiGS::timeDelay(5000);
    BiGS::eventWaitKeyboard();
}
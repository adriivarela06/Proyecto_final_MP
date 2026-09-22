#include "listaparticulas.h"
#include "bigs.h"

ListaParticulas::ListaParticulas() : lista(nullptr), num(0){}

ListaParticulas::~ListaParticulas(){
    if(num > 0)
    delete [] lista;
    lista = nullptr;
    num = 0;
}

ListaParticulas::ListaParticulas(const ListaParticulas &orig){
    if(orig.num > 0){
        num = orig.num;
        lista = new Particula [orig.num];
        for(int i = 0; i < orig.num; ++i){
            lista[i] = orig.lista[i];
        } 
    }
}

ListaParticulas & ListaParticulas::operator=(const ListaParticulas &orig){
    if(this != &orig){
        if(lista != nullptr)
            delete [] lista;
        if(orig.num > 0){
            num = orig.num;
            lista = new Particula [num];
            for(int i = 0; i < num; ++i)
                lista[i] = orig.lista[i];
        }else{
            lista = nullptr;
            num = 0;
        }
    }
    return *this;
}


int ListaParticulas::size() const{
    return num;
}

void ListaParticulas::set(const Particula &p, int pos){
        lista[pos] = p;
}

Particula ListaParticulas::get(int pos) const{
        return lista[pos];
}

void ListaParticulas::borra(int pos){
    if(num > 1){
        Particula *vec = new Particula [num - 1];
        for(int i = 0; i < pos; ++i)
            vec[i] = lista[i];
        for(int i = pos; i < num - 1; ++i)
            vec[i] = lista[i + 1];
        delete [] lista;
        lista = vec;
        num--;
    }else if(num == 1){
        delete [] lista;
        lista = nullptr;
        num = 0;
    }
}

void ListaParticulas::inserta(const Particula &p, int pos){
    Particula *vec = new Particula [num + 1];
    if(pos == -1 || pos > num)
        pos = num;
    for(int i = 0; i < pos; ++i)
        vec[i] = lista[i];
    vec[pos] = p;   
    for(int i = pos; i < num; ++i)
        vec[i + 1] = lista[i];
    num++;
    delete [] lista;
    lista = vec;
}

void ListaParticulas::colisiones(int Ancho, int Alto, bool rebote_paredes){
    for(int i = 0; i < num; ++i)
        lista[i].rebota(Ancho, Alto, rebote_paredes);
}
//Metodo que devuelve false si no es game over y true si lo es
bool ListaParticulas::son_difuntas(const BiGS::Audio &Exp, const BiGS::Audio &Navexp, const BiGS::Audio &Reload, int &Marcador, int &balas_en_pantalla){
    int i = 0;
    bool game_over = false;
    while(i < num && !game_over){
        if(lista[i].difunta()){
            //Si es nave
            if(lista[i].tipo() == 1){
                game_over = true;
                BiGS::audioPlay(Navexp, 0);
            }
            //Si es bala
            if(lista[i].tipo() == 2){
                balas_en_pantalla--;
                BiGS::audioPlay(Reload, 0, 0.25);
            }
            //Si es asteroide
            if(lista[i].tipo() == 3){
                Marcador += lista[i].radio();
                if(lista[i].radio() > AstRDestruido){
                    double radio = lista[i].radio() / 2;
                    if(radio < AstRDestruido)
                        radio = AstRDestruido;
                    Vector2D vel1(lista[i].velocidad().mod(), lista[i].velocidad().ang() + 45, Vector2D::Uds::Grados),
                             vel2(lista[i].velocidad().mod(), lista[i].velocidad().ang() - 45, Vector2D::Uds::Grados);
                    Particula A1(Vector2D (lista[i].posicion().x() + (radio + lista[i].radio()) * cos(vel1.ang(Vector2D::Uds::Radianes)), 
                                           lista[i].posicion().y() + (radio + lista[i].radio()) * sin(vel1.ang(Vector2D::Uds::Radianes))),
                                 vel1,
                                 Vector2D (0,0),
                                 Vector2D (1,aleatorio(0,359),Vector2D::Uds::Grados),
                                 radio, 1, 3),
                              A2(Vector2D (lista[i].posicion().x() + (radio + lista[i].radio()) * cos(vel2.ang(Vector2D::Uds::Radianes)), 
                                           lista[i].posicion().y() + (radio + lista[i].radio()) * sin(vel2.ang(Vector2D::Uds::Radianes))),
                                 vel2,
                                 Vector2D (0,0),
                                 Vector2D (1,aleatorio(0,359),Vector2D::Uds::Grados),
                                 radio, 1, 3);
                    inserta(A1);
                    inserta(A2);
                }
                BiGS::audioPlay(Exp, 0);
            }
            borra(i);
        }
        else
            ++i;
    }
    return game_over;
}

void ListaParticulas::comprueba_teclas(int &balas_en_pantalla, const BiGS::Audio &Shot, const BiGS::Audio &No_Ammo, bool &rebote_paredes){
    if(BiGS::isKeyPressed(ALLEGRO_KEY_UP)){
        if(lista[0].aceleracion().mod() < NaveAMax){
            lista[0].amod(lista[0].aceleracion().mod() + NaveAInc);
            lista[0].aang(lista[0].direccion().ang());
        }
    }else if(!BiGS::isKeyPressed(ALLEGRO_KEY_DOWN))
        lista[0].amod(0);
    if(BiGS::isKeyPressed(ALLEGRO_KEY_DOWN)){
        if(lista[0].velocidad().mod() > 0.9){
            lista[0].amod(NaveAMax);
            lista[0].aang(lista[0].velocidad().ang() - 180);
        }
        else{
            lista[0].vmod(0);
            lista[0].amod(0);
        }
    }else if(!BiGS::isKeyPressed(ALLEGRO_KEY_UP))
        lista[0].amod(0);
    if(BiGS::isKeyPressed(ALLEGRO_KEY_RIGHT))
        lista[0].girar(2);
    if(BiGS::isKeyPressed(ALLEGRO_KEY_LEFT))
        lista[0].girar(-2);
    BiGS::Event Ev;
    bool cond = false;
    if(BiGS::eventNext(Ev))
        cond = true;
    if(cond && Ev.type == BiGS::KEY_DOWN){
        if(Ev.keyboard.keycode == ALLEGRO_KEY_SPACE){    
            if(balas_en_pantalla < DispMax){
                Particula P(Vector2D (lista[0].posicion().x() + (lista[0].radio() + 5) * cos(lista[0].direccion().ang(Vector2D::Uds::Radianes)),
                                    lista[0].posicion().y() + (lista[0].radio() + 5) * sin(lista[0].direccion().ang(Vector2D::Uds::Radianes))),
                            Vector2D (max(DispVMin, lista[0].velocidad().mod() * 1.2),
                                      lista[0].direccion().ang(), Vector2D::Uds::Grados),
                            Vector2D (0,0), 
                            Vector2D (0,0),
                            2, 1, 2);
                P.color(BiGS::CYellow);
                inserta(P);
                balas_en_pantalla++;
                BiGS::audioPlay(Shot, 1, 0.25);
            }
            else
                BiGS::audioPlay(No_Ammo, 1, 0.25);
        }
        if(Ev.keyboard.keycode == ALLEGRO_KEY_B)
            rebote_paredes = !rebote_paredes;
    }
    if(lista[0].velocidad().mod() > NaveVMax)
        lista[0].vmod(NaveVMax);
}
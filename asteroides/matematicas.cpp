#include <cstring> 
#include <cmath>  
#include <cstdlib>   
#include <cctype>    
#include <string>    
#include "matematicas.h"

bool cad2num(const char *c, double &n){
    bool es_numero = true, es_negativo = false, es_decimal = false;
    int i = 0, ent = 0, tam = strlen(c);
    
    //Eliminamos los posibles espacios que haya al principio
    while(c[i] == ' '){
        i++;
    }

    //Comprobamos si es negativo o positivo
    if(c[i] == '-'){
        es_negativo = true;
        i++;
    }
    if(c[i] == '+')
        i++;
        
    //Contamos cuantos digitos hay antes del . que hay en la cadena excepto los espacios
    for(int cont = i; cont < tam && !es_decimal && es_numero; cont++){
        if(c[cont] >= '0' && c[cont] <= '9')
            ent++;
        else if(c[cont] == '.'){
            es_decimal = true;
        }else if((c[cont] > '9' || c[cont] < '0'))
            es_numero = false;
    }

    if(es_numero){
        //Leemos la parte entera del numero
        n = 0;
        double elev = pow(10, ent-1);

        while(c[i] != '.' && i < tam){
            n += (c[i] - '0') * elev;
            elev /= 10;
            i++;
        }
        
        //Leemos la parte decimal si esque la hay
        if(es_decimal){ 
            i++;
            double dec = 0.1;

            while(i < tam && c[i] >= '0' && c[i] <= '9' && c[i] != ' '){ 
                n += (c[i] - '0') * dec;
                dec *= 0.1;
                i++;
            }
        }

        //Aqui se comprueba si despues de que termine el numero hay algo mas a parte de espacios
        while(i < tam)
            if(c[i] != ' ')
                es_numero = false;

        //Si es decimal le cambiamos el signo
        if(es_negativo)
            n = -n;
    }


    return es_numero;
}

double aleatorio(int min, int max){
    double random = rand(); 

    random = random * (max - min) / RAND_MAX + min;
    return random;
}

std::string cad2min(const char *c){
    std::string devuelto;

    for(int i = 0; i < strlen(c); ++i)
            devuelto += tolower(c[i]);

    return devuelto;
}

double max(double n1, double n2){
    double maximo;
    if(n1 > n2)
        maximo = n1;
    else    
        maximo = n2;
    return maximo;
}
#ifndef MATEMATICAS_H
#define MATEMATICAS_H

#define PI 3.14159265359

#define PI2 1.57079632679

#define TO_RAD 0.01745329251

#define TO_DEG 57.2957795131

#define AstN 3

#define AstRMin 10

#define AstRMax 40

#define AstRDestruido 10

#define AstVMin 10

#define AstVMax 100

#define AstDMin 1

#define AstDMax 5

#define NaveR 20

#define NaveVMax 300

#define NaveAMax 300

#define NaveAInc 10

#define DispMax 5

#define DispVMin 150

#define DispTVida 10

#define SpawnBulletsX 900

bool cad2num(const char *c, double &n);

double aleatorio(int min, int max);

std::string cad2min(const char *c);

double max(double n1, double n2);

#endif
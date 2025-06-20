#ifndef ARIEL_MARQUEZ_H_INCLUDED
#define ARIEL_MARQUEZ_H_INCLUDED

#include "funciones_grupo.h"

#define FACTOR_REDUCIR 1
#define FACTOR_AUMENTAR 2

#define IMG_REDUCIR_CONTRASTE "SODA_reducir-contraste_"
#define IMG_AUMENTAR_CONTRASTE "SODA_aumentar-contraste_"
#define IMG_ACHICAR "SODA_achicar_"
#define IMG_RECORTAR "SODA_recortar_"
#define IMG_COMODIN "SODA_comodin_"

int aumentarOReducirContraste(Header header, Pixel **imagen, char nombre[], int factor, float porcentaje);
int recortar(Header header, Pixel **imagen, char nombre[], float porcentaje);
int achicar(Header header, Pixel **imagen, char nombre[], float porcentaje);
int comodin(Header header, Pixel **imagen, char nombre[]);

#endif // ARIEL_MARQUEZ_H_INCLUDED

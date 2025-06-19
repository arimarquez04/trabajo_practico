#ifndef funciones_stivala_H_INCLUDED
#define funciones_stivala_H_INCLUDED

#include "funciones_grupo.h"

int imagenRGB(const char *nomArch, Header header, Pixel **imagen, int color, int porcentaje);
int imagenGrises(const char *nomArch, Header header, Pixel **imagen);
int imagenEspejarH(const char *nomArch, Header header, Pixel **imagen);
int imagenEspejarV(const char *nomArch, Header header, Pixel **imagen);

#endif // ALUMNO_1_H_INCLUDED

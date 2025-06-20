#ifndef FACUNDO_PAZ_H_INCLUDED
#define FACUNDO_PAZ_H_INCLUDED

#include "funciones_grupo.h"

int rotarDerecha (const char* nombreArchivo,  Header cabeceraOriginal,  Pixel **imagenOriginal);
int rotarIzquierda (const char* nombreArchivo, Header cabeceraOriginal, Pixel **imagenOriginal);
int concatenarVertical ( const char* nombreArchivo1, Header cabecera1, Pixel **imagen1, const char* nombreArchivo2, Header cabecera2, Pixel **imagen2);
int concatenarHorizontal ( const char* nombreArchivo1, Header cabecera1, Pixel **imagen1, const char* nombreArchivo2, Header cabecera2, Pixel **imagen2);
int llenarImagenHorizontal(Header *header, Pixel ***imagen, int difAncho);
int llenarImagenVertical(Header *header, Pixel ***imagen, int difAlto);


#endif // FACUNDO_PAZ_H_INCLUDED

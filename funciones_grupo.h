//
// Created by arima on 10/6/2025.
//

#ifndef funciones_grupo_H
#define funciones_grupo_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define ERR_NO_IMAGEN 3
#define INVALID_ARGUMENT 4

#define ROJO 0
#define VERDE 1
#define AZUL 2

typedef struct
{
    unsigned short int bm;
    unsigned int tamArchivo;
    unsigned short int reservado1;
    unsigned short int reservado2;
    unsigned int inicioImagen;
    unsigned int tamHeader;
    unsigned int ancho;
    unsigned int alto;
    unsigned short int numPlanos;
    unsigned short int tamPunto;
    unsigned int compresion;
    unsigned int tamImagen;
    unsigned int resHorizontal;
    unsigned int resVertical;
    unsigned int tamTablacolor;
    unsigned int contColores;
    unsigned char *bloqueExtra;
} Header;

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;

int grabarCabeceraArchivo(const char *nomArch, Header *header);
void mostrarCabeceraArchivoHexa(Header *header);

int grabarImagenMemoria(const char *nomArch, Header *header, Pixel ***imagen);
int liberarImagen(Header *header, Pixel ***imagen);
void mostrarImagen(Header *header, Pixel ***imagen);
int crearImagen(const char *nomArch, Header header, Pixel **imagen);
int copiaImagen(Header headerOriginal, Pixel **imagenOriginal, Header *headerCopia, Pixel ***imagenCopia);
char* buscaNombreArchivo(int argc, char *argv[]);

#endif //HEADER_H

//
// Created by arima on 10/6/2025.
//

#ifndef HEADER_H
#define HEADER_H

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define ERR_NO_IMAGEN 3

typedef struct{
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

typedef struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

int grabarCabeceraArchivo(const char *nomArch, Header *header);
void mostrarCabeceraArchivoHexa(Header *header);
int grabarImagenMemoria(const char *nomArch, Header *header, Pixel ***imagen);
int liberarImagen(Header *header, Pixel ***imagen);
void mostrarImagen(Header *header, Pixel ***imagen);
int crearImagen(const char *nomArch, Header header, Pixel **imagen);

#endif //HEADER_H

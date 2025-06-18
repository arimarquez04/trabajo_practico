#include <stdio.h>
#include <stdlib.h>

#include "funciones_marquez.h"
#include "funciones_grupo.h"


float calcularFactorContraste(float porcentaje, int factor);
unsigned char  aplicarContraste(unsigned char valor, float factorContraste);

int aumentarOReducirContraste(Header header, Pixel **imagen, char nombre[], int factor, float porcentaje) {
    if (porcentaje < 0 || porcentaje > 100) {
        printf("El argumento porcentaje posee un valor invalido.\n");
        return INVALID_ARGUMENT;
    }

    if (factor != FACTOR_AUMENTAR && factor != FACTOR_REDUCIR) {
        printf("El argumento factor posee un valor invalido.\n");
        return INVALID_ARGUMENT;
    }

    float factorContraste = calcularFactorContraste(porcentaje, factor);

    Header headerNew;
    Pixel **imagenNew;
    copiaImagen(header, imagen, &headerNew, &imagenNew);

    for (int i = 0; i < headerNew.alto; i++) {
        for (int j = 0; j < headerNew.ancho; j++) {
            imagenNew[i][j].red   = aplicarContraste(imagenNew[i][j].red, factorContraste);
            imagenNew[i][j].green = aplicarContraste(imagenNew[i][j].green, factorContraste);
            imagenNew[i][j].blue  = aplicarContraste(imagenNew[i][j].blue, factorContraste);
        }
    }

    char nombreArchivo[256];
    strcpy(nombreArchivo, IMG_REDUCIR_CONTRASTE);
    strcat(nombreArchivo, nombre);

    crearImagen(nombreArchivo, headerNew, imagenNew);
    liberarImagen(&headerNew, &imagenNew);

    return TODO_OK;
}
float calcularFactorContraste(float porcentaje, int factor) {
    if (factor == FACTOR_AUMENTAR) {
        return 1 + (porcentaje / 100.0f);
    } else if (factor == FACTOR_REDUCIR) {
        return 1 - (porcentaje / 100.0f);
    }

    return 1.0f;
}
unsigned char aplicarContraste(unsigned char valor, float factorContraste) {
    float calculado = (valor - 128) * factorContraste + 128;

    if (calculado < 0) calculado = 0;
    if (calculado > 255) calculado = 255;

    return (unsigned char)(calculado + 0.5f);
}

int recortar(Header header, Pixel **imagen, char nombre[], float porcentaje) {
    if(porcentaje<0 || porcentaje>100){
        printf("El argumento porcentaje posee un valor invalido.\n");
        return INVALID_ARGUMENT;
    }

    int cantAlto, cantAncho;
    cantAncho = header.ancho - (int)(header.ancho * (porcentaje / 100.0));
    cantAlto = header.alto - (int)(header.alto * (porcentaje / 100.0));

    Header headerNew;
    Pixel **imagenNew;
    grabarCabeceraArchivo(nombre, &headerNew);
    headerNew.alto=cantAlto;
    headerNew.ancho=cantAncho;

    int resultado = grabarImagenMemoria(nombre, &header, &imagenNew);
    if(resultado == ERR_MEMORIA){
        printf("Ocurrio un error de memoria al intentar recortar la imagen");
        return resultado;
    }
    if(resultado == ERR_ARCHIVO){
        printf("Ocurrio un error al leer el archivo al intentar recortar la imagen");
        return resultado;
    }

    char nombreArchivo[256];
    strcpy(nombreArchivo, IMG_RECORTAR);
    strcat(nombreArchivo, nombre);

    crearImagen(nombreArchivo, headerNew, imagenNew);
    liberarImagen(&headerNew, &imagenNew);
    return TODO_OK;
}

int achicar(Header header, Pixel **imagen, char nombre[], float porcentaje){
    if(porcentaje<0 || porcentaje>100){
        printf("El argumento porcentaje posee un valor invalido.\n");
        return INVALID_ARGUMENT;
    }
    int cantAlto, cantAncho;
    cantAncho = header.ancho - (int)(header.ancho * (porcentaje / 100.0));
    cantAlto = header.alto - (int)(header.alto * (porcentaje / 100.0));

    Header headerNew;
    Pixel **imagenNew;
    grabarCabeceraArchivo(nombre, &headerNew);
    headerNew.alto=cantAlto;
    headerNew.ancho=cantAncho;

    int resultado = grabarImagenMemoria(nombre, &header, &imagenNew);
    if(resultado == ERR_MEMORIA){
        printf("Ocurrio un error de memoria al intentar recortar la imagen");
        return resultado;
    }
    if(resultado == ERR_ARCHIVO){
        printf("Ocurrio un error al leer el archivo al intentar recortar la imagen");
        return resultado;
    }

    float escalaX = (float)header.ancho / headerNew.ancho;
    float escalaY = (float)header.alto / headerNew.alto;

    for (int i = 0; i < headerNew.alto; i++) {
        for (int j = 0; j < headerNew.ancho; j++) {
            int startY = (int)(i * escalaY);
            int endY   = (int)((i + 1) * escalaY);
            int startX = (int)(j * escalaX);
            int endX   = (int)((j + 1) * escalaX);

            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int y = startY; y < endY && y < header.alto; y++) {
                for (int x = startX; x < endX && x < header.ancho; x++) {
                    sumR += imagen[y][x].red;
                    sumG += imagen[y][x].green;
                    sumB += imagen[y][x].blue;
                    count++;
                }
            }

            if (count == 0) count = 1;

            imagenNew[i][j].red   = sumR / count;
            imagenNew[i][j].green = sumG / count;
            imagenNew[i][j].blue  = sumB / count;
        }
    }

    char nombreArchivo[256];
    strcpy(nombreArchivo, IMG_ACHICAR);
    strcat(nombreArchivo, nombre);

    crearImagen(nombreArchivo, headerNew, imagenNew);
    liberarImagen(&headerNew, &imagenNew);
    return TODO_OK;
}

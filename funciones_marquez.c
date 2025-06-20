#include <stdio.h>
#include <stdlib.h>

#include "funciones_marquez.h"
#include "funciones_grupo.h"


float calcularFactorContraste(float porcentaje, int factor);
unsigned char  aplicarContraste(unsigned char valor, float factorContraste);
void calcularPixelPromedio(Pixel **imagen, int startX, int endX, int startY, int endY, int anchoOriginal, int altoOriginal, Pixel *destino);

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
    if(factor == FACTOR_AUMENTAR){
        strcpy(nombreArchivo, IMG_AUMENTAR_CONTRASTE);
    }
    if(factor == FACTOR_REDUCIR){
        strcpy(nombreArchivo, IMG_REDUCIR_CONTRASTE);
    }
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

        calcularPixelPromedio(imagen, startX, endX, startY, endY, header.ancho, header.alto, &imagenNew[i][j]);
    }
}


    char nombreArchivo[256];
    strcpy(nombreArchivo, IMG_ACHICAR);
    strcat(nombreArchivo, nombre);

    crearImagen(nombreArchivo, headerNew, imagenNew);
    liberarImagen(&headerNew, &imagenNew);
    return TODO_OK;
}
void calcularPixelPromedio(Pixel **imagen, int startX, int endX, int startY, int endY, int anchoOriginal, int altoOriginal, Pixel *destino) {
    int sumR = 0, sumG = 0, sumB = 0;
    int count = 0;

    for (int y = startY; y < endY && y < altoOriginal; y++) {
        for (int x = startX; x < endX && x < anchoOriginal; x++) {
            sumR += imagen[y][x].red;
            sumG += imagen[y][x].green;
            sumB += imagen[y][x].blue;
            count++;
        }
    }

    if (count == 0) count = 1;

    destino->red   = sumR / count;
    destino->green = sumG / count;
    destino->blue  = sumB / count;
}


int comodin(Header header, Pixel **imagen, char nombre[]) {
    Header headerNew;
    Pixel **imagenNew;
    copiaImagen(header, imagen, &headerNew, &imagenNew);

    for (int i = 0; i < headerNew.alto; i++) {
        for (int j = 0; j < headerNew.ancho; j++) {
            float r = 0.393 * imagenNew[i][j].red + 0.769 * imagenNew[i][j].green + 0.189 * imagenNew[i][j].blue;
            float g = 0.349 * imagenNew[i][j].red + 0.686 * imagenNew[i][j].green + 0.168 * imagenNew[i][j].blue;
            float b = 0.272 * imagenNew[i][j].red + 0.534 * imagenNew[i][j].green + 0.131 * imagenNew[i][j].blue;

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;

            imagenNew[i][j].red   = (unsigned char)r;
            imagenNew[i][j].green = (unsigned char)g;
            imagenNew[i][j].blue  = (unsigned char)b;
        }
    }

    char nombreArchivo[256];
    strcpy(nombreArchivo, IMG_COMODIN);
    strcat(nombreArchivo, nombre);

    crearImagen(nombreArchivo, headerNew, imagenNew);
    liberarImagen(&headerNew, &imagenNew);

    return TODO_OK;
}

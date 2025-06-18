#include <stdio.h>
#include <stdlib.h>

#include "funciones_marquez.h"
#include "funciones_grupo.h"


float calcularFactorContraste(float porcentaje, int factor);
unsigned char  aplicarContraste(unsigned char valor, float factorContraste);

int aumentarOReducirContraste(Header header, Pixel **imagen, char nombre[], int factor, float porcentaje) {
    if (porcentaje < 0 || porcentaje > 100) {
        printf("El argumento porcentaje posee un valor inválido.\n");
        return INVALID_ARGUMENT;
    }

    if (factor != FACTOR_AUMENTAR && factor != FACTOR_REDUCIR) {
        printf("El argumento factor posee un valor inválido.\n");
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

    return 1.0f; // Valor neutro por defecto si el factor es inválido
}
unsigned char aplicarContraste(unsigned char valor, float factorContraste) {
    float calculado = (valor - 128) * factorContraste + 128;

    if (calculado < 0) calculado = 0;
    if (calculado > 255) calculado = 255;

    return (unsigned char)(calculado + 0.5f); // redondeo al más cercano
}


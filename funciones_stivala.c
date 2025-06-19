#include "funciones_grupo.h"

int imagenRGB(const char *nomArch, Header header, Pixel **imagen, int color, int porcentaje)
{
    Header headerL;
    Pixel **imagenL;

    copiaImagen(header, imagen, &headerL, &imagenL);

    if(porcentaje < 0 || porcentaje > 100)
    {
        printf("El argumento porcentaje posee un valor inválido.");
        return INVALID_ARGUMENT;
    }

    float factorIncr = 1 + (float)porcentaje/100;
    unsigned int nuevoPixel;

    char nombreArchivo[256];
    switch(color)
    {
        case ROJO:
            strcpy(nombreArchivo, "SODA_tonalidad-roja_");
        break;
        case VERDE:
            strcpy(nombreArchivo, "SODA_tonalidad-verde_");
        break;
        case AZUL:
            strcpy(nombreArchivo, "SODA_tonalidad-azul_");
        break;
    }
    strcat(nombreArchivo, nomArch);

    for(int i = 0 ; i < headerL.alto ; i++)
    {
        for(int j = 0 ; j < headerL.ancho ; j++)
        {
            switch(color)
            {
                case ROJO:
                    nuevoPixel = imagenL[i][j].red * factorIncr;
                    imagenL[i][j].red = (nuevoPixel > 255) ? 255 : nuevoPixel;
                break;
                case VERDE:
                    nuevoPixel = imagenL[i][j].green* factorIncr;
                    imagenL[i][j].green = (nuevoPixel > 255) ? 255 : nuevoPixel;
                    break;
                case AZUL:
                    nuevoPixel = imagenL[i][j].blue * factorIncr;
                    imagenL[i][j].blue = (nuevoPixel > 255) ? 255 : nuevoPixel;
                break;
            }
        }
    }

    crearImagen(nombreArchivo, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}

int imagenGrises(const char *nomArch, Header header, Pixel **imagen)
{
    Header headerL;
    Pixel **imagenL;

    copiaImagen(header, imagen, &headerL, &imagenL);

    for(int i = 0 ; i < headerL.alto ; i++)
    {
        for(int j = 0 ; j < headerL.ancho ; j++)
        {
            unsigned char gris = (imagenL[i][j].red + imagenL[i][j].green + imagenL[i][j].blue) / 3;
            imagenL[i][j].red = gris;
            imagenL[i][j].green = gris;
            imagenL[i][j].blue = gris;
        }
    }
    char nombreArchivo[256];
    strcpy(nombreArchivo, "SODA_escala-de-grises_");
    strcat(nombreArchivo, nomArch);

    crearImagen(nombreArchivo, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}

int imagenEspejarH(const char *nomArch, Header header, Pixel **imagen)
{
    Header headerL;
    Pixel **imagenL;

    copiaImagen(header, imagen, &headerL, &imagenL);

    Pixel pixel;

    for (int i = 0 ; i < headerL.alto ; i++)
    {
        for (int j = 0 ; j < headerL.ancho / 2 ; j++)
        {
            pixel = imagenL[i][j];
            imagenL[i][j] = imagenL[i][headerL.ancho - 1 - j];
            imagenL[i][headerL.ancho - 1 - j] = pixel;
        }
    }

    char nombreArchivo[256];
    strcpy(nombreArchivo, "SODA_espejar-horizontal_");
    strcat(nombreArchivo, nomArch);

    crearImagen(nombreArchivo, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}


int imagenEspejarV(const char *nomArch, Header header, Pixel **imagen)
{
    Header headerL;
    Pixel **imagenL;

    copiaImagen(header, imagen, &headerL, &imagenL);

    Pixel pixel;

    for(int i = 0; i < headerL.alto / 2; i++)
    {
        for(int j = 0; j < headerL.ancho; j++)
        {
            pixel = imagenL[i][j];
            imagenL[i][j] = imagenL[headerL.alto - 1 - i][j];
            imagenL[headerL.alto - 1 - i][j] = pixel;
        }
    }
    char nombreArchivo[256];
    strcpy(nombreArchivo, "SODA_espejar-vertical_");
    strcat(nombreArchivo, nomArch);

    crearImagen(nombreArchivo, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}

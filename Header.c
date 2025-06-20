#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int grabarCabeceraArchivo(const char *nomArch, Header *header)
{
    FILE *arch = fopen(nomArch, "rb");

    if(!arch)
    {
        puts("Error al abrir el archivo2.");
        return ERR_ARCHIVO;
    }

    fread(&header->bm, sizeof(short int), 1, arch);
    fread(&header->tamArchivo, sizeof(int), 1, arch);
    fread(&header->reservado1, sizeof(short int), 1, arch);
    fread(&header->reservado2, sizeof(short int), 1, arch);
    fread(&header->inicioImagen, sizeof(int), 1, arch);
    fread(&header->tamHeader, sizeof(int), 1, arch);
    fread(&header->ancho, sizeof(int), 1, arch);
    fread(&header->alto, sizeof(int), 1, arch);
    fread(&header->numPlanos, sizeof(short int), 1, arch);
    fread(&header->tamPunto, sizeof(short int), 1, arch);
    fread(&header->compresion, sizeof(int), 1, arch);
    fread(&header->tamImagen, sizeof(int), 1, arch);
    fread(&header->resHorizontal, sizeof(int), 1, arch);
    fread(&header->resVertical, sizeof(int), 1, arch);
    fread(&header->tamTablacolor, sizeof(int), 1, arch);
    fread(&header->contColores, sizeof(int), 1, arch);

    int posActual = ftell(arch);
    int bytesExtra = header->inicioImagen - posActual;

    if (bytesExtra > 0)
    {
        header->bloqueExtra = (unsigned char *)malloc(bytesExtra);
        if (!header->bloqueExtra)
        {
            fclose(arch);
            return ERR_MEMORIA;
        }
        fread(header->bloqueExtra, 1, bytesExtra, arch);
    }
    else
    {
        header->bloqueExtra = NULL;
    }



    fclose(arch);

    return TODO_OK;
}

void mostrarCabeceraArchivoHexa(Header *header)
{
    printf("%X ", header->bm);
    printf("%X ", header->tamArchivo);
    printf("%X ", header->reservado1);
    printf("%X ", header->reservado2);
    printf("%X ", header->inicioImagen);
    printf("%X ", header->tamHeader);
    printf("%X ", header->ancho);
    printf("%X ", header->alto);
    printf("%X ", header->numPlanos);
    printf("%X ", header->tamPunto);
    printf("%X ", header->compresion);
    printf("%X ", header->tamImagen);
    printf("%X ", header->resHorizontal);
    printf("%X ", header->resVertical);
    printf("%X ", header->tamTablacolor);
    printf("%X ", header->contColores);

    putchar('\n');
}

int grabarImagenMemoria(const char *nomArch, Header *header, Pixel ***imagen)
{
    FILE *arch = fopen(nomArch, "rb");

    if(!arch)
    {
        puts("Error al abrir el archivo3.");
        return ERR_ARCHIVO;
    }

    int alto = header->alto;
    int ancho = header->ancho;
    int inicio = header->inicioImagen;
    int padding = (4 - (ancho * 3) % 4) % 4;

    *imagen = (Pixel **)malloc(alto * sizeof(Pixel *));

    if (!*imagen)
    {
        return ERR_MEMORIA;
    }

    for(int i = 0 ; i < alto ; i++)
    {
        (*imagen)[i] = (Pixel *)malloc(ancho * sizeof(Pixel));

        if (!(*imagen)[i])
        {
            //AGREGAR CODIGO PARA LIBERAR LAS FILAS QUE SE CREARON HASTA ESE MOMENTO EN CASO DE FALLAR
            return ERR_MEMORIA;
        }
    }

    fseek(arch, inicio, SEEK_SET);

    for(int i = alto - 1 ; i >= 0 ; i--)
    {
        fread((*imagen)[i], sizeof(Pixel), ancho, arch);
        fseek(arch, padding, SEEK_CUR); // saltar el padding
    }

    fclose(arch);

    return TODO_OK;
}

int liberarImagen(Header *header, Pixel ***imagen)
{
    if (!imagen || !*imagen)
    {
        return ERR_NO_IMAGEN;
    }

    int alto = header->alto;

    for (int i = 0 ; i < alto ; i++)
    {
        free((*imagen)[i]);
    }

    free(*imagen);
    *imagen = NULL;

    if (header->bloqueExtra)
    {
        free(header->bloqueExtra);
        header->bloqueExtra = NULL;
    }


    return TODO_OK;
}

void mostrarImagen(Header *header, Pixel ***imagen)
{
    int alto = header->alto;
    int ancho = header->ancho;

    for(int i = 0 ; i < alto ; i++)
    {
        for(int j = 0 ; j < ancho ; j++)
        {
            printf("%x ", (*imagen)[i][j].red);
            printf("%x ", (*imagen)[i][j].green);
            printf("%x ", (*imagen)[i][j].blue);
            //putchar('\n');
        }
        putchar('\n');
    }
}

int crearImagen(const char *nomArch, Header header, Pixel **imagen)
{
    FILE *arch = fopen(nomArch, "wb");

    if(!arch)
    {
        puts("Error al abrir el archivo.");
        return ERR_ARCHIVO;
    }

    fwrite(&header.bm, sizeof(short), 1, arch);
    fwrite(&header.tamArchivo, sizeof(int), 1, arch);
    fwrite(&header.reservado1, sizeof(short), 1, arch);
    fwrite(&header.reservado2, sizeof(short), 1, arch);
    fwrite(&header.inicioImagen, sizeof(int), 1, arch);
    fwrite(&header.tamHeader, sizeof(int), 1, arch);
    fwrite(&header.ancho, sizeof(int), 1, arch);
    fwrite(&header.alto, sizeof(int), 1, arch);
    fwrite(&header.numPlanos, sizeof(short), 1, arch);
    fwrite(&header.tamPunto, sizeof(short), 1, arch);
    fwrite(&header.compresion, sizeof(int), 1, arch);
    fwrite(&header.tamImagen, sizeof(int), 1, arch);
    fwrite(&header.resHorizontal, sizeof(int), 1, arch);
    fwrite(&header.resVertical, sizeof(int), 1, arch);
    fwrite(&header.tamTablacolor, sizeof(int), 1, arch);
    fwrite(&header.contColores, sizeof(int), 1, arch);

    int posActual = ftell(arch);
    int bytesExtra = header.inicioImagen - posActual;

    if (bytesExtra > 0 && header.bloqueExtra != NULL)
    {
        fwrite(header.bloqueExtra, 1, bytesExtra, arch);
    }

    int padding = (4 - (header.ancho * 3) % 4) % 4;
    unsigned char pad[3] = {0, 0, 0};

    for (int i = header.alto - 1; i >= 0; i--)
    {
        for (int j = 0; j < header.ancho; j++)
        {
            fwrite(&imagen[i][j], sizeof(Pixel), 1, arch);
        }
        fwrite(pad, padding, 1, arch);
    }

    fclose(arch);

    return TODO_OK;
}

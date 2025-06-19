#include <stdio.h>
#include "funciones_grupo.h"

int rotarDerecha (const char* nombreArchivo, Header cabeceraOriginal, Pixel **imagenOriginal)
{
    Header cabeceraCopia;
    Pixel **imagenCopia;
    copiaImagen(cabeceraOriginal, imagenOriginal, &cabeceraCopia, &imagenCopia);

    imagenCopia = (Pixel **)malloc(cabeceraOriginal.ancho * sizeof(Pixel *));

    for (int i = 0; i < cabeceraOriginal.ancho; i++)
    {
        imagenCopia[i] = (Pixel *)malloc(cabeceraOriginal.alto * sizeof(Pixel));
        if (!imagenCopia[i])
        {
            for (int j = 0; j < i; j++)
            {
                free(imagenCopia[j]);
            }
            free(imagenCopia);
            imagenCopia = NULL;
            return ERR_MEMORIA;
        }
    }

    for (int i = 0; i < cabeceraOriginal.alto; i++)
    {
        for (int j = 0; j < cabeceraOriginal.ancho; j++)
        {
            imagenCopia[j][cabeceraOriginal.alto - 1 - i] = imagenOriginal[i][j];
        }
    }

    cabeceraCopia.ancho = cabeceraOriginal.alto;
    cabeceraCopia.alto = cabeceraOriginal.ancho;
    cabeceraCopia.resHorizontal = cabeceraOriginal.resVertical;
    cabeceraCopia.resVertical = cabeceraOriginal.resHorizontal;

    char nombreaImagenNueva [255] = nombreGrupo;
    strcat( nombreaImagenNueva, "_rotar-derecha_");
    strcat(nombreaImagenNueva, nombreArchivo);

    crearImagen(nombreaImagenNueva, cabeceraCopia, imagenCopia);

    liberarImagen(&cabeceraCopia, &imagenCopia);

    return TODO_OK;
}
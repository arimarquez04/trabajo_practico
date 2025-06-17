#include <stdio.h>
#include "funciones_grupo.h"

int rotarDerecha (const char* nombreArchivo, Header cabecera, Pixel **imagen)
{
    Header cabeceraCopia;
    Pixel **imagenCopia;

    // Copiar la imagen original
    copiaImagen(cabecera, imagen, &cabeceraCopia, &imagenCopia);

    // Rotar la imagen 90 grados a la derecha
    Pixel **imagenRotada = (Pixel **)malloc(cabeceraCopia.ancho * sizeof(Pixel *));
    for (int i = 0; i < cabeceraCopia.ancho; i++)
    {
        imagenRotada[i] = (Pixel *)malloc(cabeceraCopia.alto * sizeof(Pixel));
    }

    for (int i = 0; i < cabeceraCopia.alto; i++)
    {
        for (int j = 0; j < cabeceraCopia.ancho; j++)
        {
            imagenRotada[j][cabeceraCopia.alto - 1 - i] = imagenCopia[i][j];
        }
    }

    // Actualizar las dimensiones de la cabecera
    cabeceraCopia.ancho = cabecera.alto;
    cabeceraCopia.alto = cabecera.ancho;

    // Crear el archivo de imagen rotada
    crearImagen(nombreArchivo, cabeceraCopia, imagenRotada);

    // Liberar memoria
    liberarImagen(&cabeceraCopia, &imagenRotada);
    liberarImagen(&cabecera, &imagenCopia);

    return TODO_OK;
}
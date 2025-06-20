#include <stdio.h>
#include "funciones_grupo.h"

int rotarDerecha (const char* nombreArchivo, Header cabeceraOriginal, Pixel **imagenOriginal)
{
    Header cabeceraCopia;
    Pixel **imagenCopia;
    if(copiaImagen(cabeceraOriginal, imagenOriginal, &cabeceraCopia, &imagenCopia) != TODO_OK)
    {
        puts("Error al copiar la imagen original para rotarla.");
        return ERR_MEMORIA;
    }

    imagenCopia = (Pixel **)malloc(cabeceraOriginal.ancho * sizeof(Pixel *));

    if (!imagenCopia)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al asignar memoria para la imagen rotada.");
        return ERR_MEMORIA;
    }

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
            puts("Error al asignar memoria para la imagen rotada.");
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

    if(crearImagen(nombreaImagenNueva, cabeceraCopia, imagenCopia) != TODO_OK)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al crear la imagen rotada.");
        return ERR_ARCHIVO;
    }

    liberarImagen(&cabeceraCopia, &imagenCopia);

    return TODO_OK;
}

int rotarIzquierda (const char* nombreArchivo, Header cabeceraOriginal, Pixel **imagenOriginal)
{
    Header cabeceraCopia;
    Pixel **imagenCopia;
    if(copiaImagen(cabeceraOriginal, imagenOriginal, &cabeceraCopia, &imagenCopia) != TODO_OK)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al copiar la imagen original para rotarla.");
        return ERR_MEMORIA;
    }

    imagenCopia = (Pixel **)malloc(cabeceraOriginal.ancho * sizeof(Pixel *));
    if( !imagenCopia)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al asignar memoria para la imagen rotada.");
        return ERR_MEMORIA;
    }
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
            puts("Error al asignar memoria para la imagen rotada.");
            return ERR_MEMORIA;
        }
    }

    for (int i = 0; i < cabeceraOriginal.alto; i++)
    {
        for (int j = 0; j < cabeceraOriginal.ancho; j++)
        {
            imagenCopia[cabeceraOriginal.ancho - 1 - j][i] = imagenOriginal[i][j];
        }
    }

    cabeceraCopia.ancho = cabeceraOriginal.alto;
    cabeceraCopia.alto = cabeceraOriginal.ancho;
    cabeceraCopia.resHorizontal = cabeceraOriginal.resVertical;
    cabeceraCopia.resVertical = cabeceraOriginal.resHorizontal;

    char nombreaImagenNueva [255] = nombreGrupo;
    strcat( nombreaImagenNueva, "_rotar-izquierda_");
    strcat(nombreaImagenNueva, nombreArchivo);

    if(crearImagen(nombreaImagenNueva, cabeceraCopia, imagenCopia) != TODO_OK)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al crear la imagen rotada.");
        return ERR_ARCHIVO;
    }

    liberarImagen(&cabeceraCopia, &imagenCopia);

    return TODO_OK;
}

int concatenarVertical ( const char* nombreArchivo1, Header cabecera1, Pixel **imagen1, const char* nombreArchivo2, Header cabecera2, Pixel **imagen2)
{
    Header cabeceraCopia;
    Pixel **imagenCopia, **imagenTmp;
    int difAncho;

    char nombreSinExtension [255];
    char *puntoExtension = strrchr(nombreArchivo1, '.');
    strncpy(nombreSinExtension, nombreArchivo1, puntoExtension - nombreArchivo1);
    nombreSinExtension[puntoExtension - nombreArchivo1] = '\0';

    char nombreImagenNueva [255];
    strcpy(nombreImagenNueva, nombreGrupo);
    strcat(nombreImagenNueva, "_concatenar-vertical_");
    strcat(nombreImagenNueva, nombreSinExtension);
    strcat(nombreImagenNueva, "_");
    strcat(nombreImagenNueva, nombreArchivo2);

    if(cabecera1.ancho > cabecera2.ancho)
    {
        difAncho = cabecera1.ancho - cabecera2.ancho;
        if(llenarImagenHorizontal(&cabecera2, &imagen2, difAncho) != TODO_OK)
        {
                puts("Error al ampliar la imagen 2 horizontalmente.");
                return ERR_MEMORIA;
        }

    }
    if (cabecera1.ancho < cabecera2.ancho)
    {
        difAncho = cabecera2.ancho - cabecera1.ancho;
        if(llenarImagenHorizontal(&cabecera1, &imagen1, difAncho) != TODO_OK)
        {
            puts("Error al ampliar la imagen 1 horizontalmente.");
            return ERR_MEMORIA;
        }

    }

    copiaImagen(cabecera1, imagen1, &cabeceraCopia, &imagenCopia);
    imagenTmp = (Pixel **)realloc(imagenCopia, (cabecera1.alto + cabecera2.alto) * sizeof(Pixel *));

    if (imagenTmp != NULL)
    {
        imagenCopia = imagenTmp;
        //free(imagenTmp);
    }
    else
    {
        puts("Error al asignar memoria para la imagen concatenada verticalmente.");
        liberarImagen(&cabeceraCopia, &imagenCopia);
        return ERR_MEMORIA;
    }
    for( int i = cabecera1.alto; i < (cabecera1.alto + cabecera2.alto); i++)
    {
        imagenCopia[i] = (Pixel *)malloc(cabecera1.ancho * sizeof(Pixel));
        if (!imagenCopia[i])
        {
            puts("Error al asignar memoria para la nueva fila de la imagen concatenada verticalmente.");
            for(int j = i; j > cabecera1.alto; j--)
            {
                free(imagenCopia[j]);
            }
            liberarImagen(&cabeceraCopia, &imagenCopia);
            return ERR_MEMORIA;
        }
        for( int j = 0; j < cabecera1.ancho; j++)
        {
            imagenCopia[i][j] = imagen2[i - cabecera1.alto][j];
        }
    }

    cabeceraCopia.alto = cabecera1.alto + cabecera2.alto;
    cabeceraCopia.tamImagen = cabeceraCopia.alto * cabeceraCopia.ancho * sizeof(Pixel);


    if(crearImagen(nombreImagenNueva, cabeceraCopia, imagenCopia) != TODO_OK)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al crear la imagen concatenada verticalmente.");
        return ERR_ARCHIVO;
    }

    liberarImagen(&cabeceraCopia, &imagenCopia);
    return TODO_OK;
}

int concatenarHorizontal ( const char* nombreArchivo1, Header cabecera1, Pixel **imagen1, const char* nombreArchivo2, Header cabecera2, Pixel **imagen2)
{
    Header cabeceraCopia;
    Pixel **imagenCopia, *filaTmp;
    int difAlto;

    char nombreSinExtension [255];
    char *puntoExtension = strrchr(nombreArchivo1, '.');
    strncpy(nombreSinExtension, nombreArchivo1, puntoExtension - nombreArchivo1);
    nombreSinExtension[puntoExtension - nombreArchivo1] = '\0';

    char nombreImagenNueva [255];
    strcpy(nombreImagenNueva, nombreGrupo);
    strcat(nombreImagenNueva, "_concatenar-horizontal_");
    strcat(nombreImagenNueva, nombreSinExtension);
    strcat(nombreImagenNueva, "_");
    strcat(nombreImagenNueva, nombreArchivo2);

    if(cabecera1.alto > cabecera2.alto)
    {
        difAlto = cabecera1.alto - cabecera2.alto;
        if(llenarImagenVertical(&cabecera2, &imagen2, difAlto) != TODO_OK)
        {
            puts("Error al ampliar la imagen 2 verticalmente.");
            return ERR_MEMORIA;
        }
    }
    if (cabecera1.alto < cabecera2.alto)
    {
        difAlto = cabecera2.alto - cabecera1.alto;
        if(llenarImagenVertical(&cabecera1, &imagen1, difAlto) != TODO_OK)
        {
            puts("Error al ampliar la imagen 1 verticalmente.");
            return ERR_MEMORIA;
        }
    }

    copiaImagen(cabecera1, imagen1, &cabeceraCopia, &imagenCopia);
    for( int i = 0; i < cabeceraCopia.alto; i++)
    {
        filaTmp = (Pixel *)realloc(imagenCopia[i], (cabecera1.ancho + cabecera2.ancho) * sizeof(Pixel ));
        if (filaTmp != NULL)
        {
            imagenCopia[i] = filaTmp;
            //free(imagenTmp);
        }
        else
        {
            puts("Error al asignar memoria para la imagen concatenada horizontalmente.");
            liberarImagen(&cabeceraCopia, &imagenCopia);
            return ERR_MEMORIA;
        }
        for( int j = cabeceraCopia.ancho; j < (cabecera1.ancho + cabecera2.ancho); j++)
        {
            imagenCopia[i][j] = imagen2[i][j - cabeceraCopia.ancho];
        }

    }

    cabeceraCopia.ancho = cabecera1.ancho + cabecera2.ancho;
    cabeceraCopia.tamImagen = cabeceraCopia.alto * cabeceraCopia.ancho * sizeof(Pixel);

    if(crearImagen(nombreImagenNueva, cabeceraCopia, imagenCopia) != TODO_OK)
    {
        liberarImagen(&cabeceraCopia, &imagenCopia);
        puts("Error al crear la imagen concatenada horizontalmente.");
        return ERR_ARCHIVO;
    }
    liberarImagen(&cabeceraCopia, &imagenCopia);
    return TODO_OK;
}

int llenarImagenHorizontal(Header *cabecera, Pixel ***imagen, int difAncho)
{
    int alto = cabecera->alto;
    int ancho = cabecera->ancho + difAncho;
    Pixel *filaTmp;
    for (int i = 0; i < alto; i++)
    {
        filaTmp = (Pixel *)realloc((*imagen)[i], ancho * sizeof(Pixel));
        if (filaTmp != NULL)
        {
            (*imagen)[i] = filaTmp;
        }
        else
        {
            puts("Error al asignar memoria para la imagen ampliada horizontalmente.");
            for (int j = 0; j < i; j++)
            {
                free((*imagen)[j]);
            }
            free(*imagen);
            *imagen = NULL;
            return ERR_MEMORIA;
        }
        for (int j = cabecera->ancho; j < ancho; j++)
        {
            (*imagen)[i][j].blue = 125;
            (*imagen)[i][j].green = 125;
            (*imagen)[i][j].red = 125;
        }
    }

    cabecera->ancho = ancho;
    cabecera->tamImagen = cabecera->alto * cabecera->ancho * sizeof(Pixel);

    return TODO_OK;
}


int llenarImagenVertical(Header *cabecera, Pixel ***imagen, int difAlto)
{
    int ancho = cabecera->ancho;
    int alto = cabecera->alto + difAlto;
    Pixel **nuevaImagen = (Pixel **)realloc(*imagen, alto * sizeof(Pixel *));
    if (nuevaImagen != NULL)
    {
        *imagen = nuevaImagen;
    }
    else
    {
        puts("Error al asignar memoria para la imagen ampliada verticalmente.");
        return ERR_MEMORIA;
    }
    for ( int i = 0; i < difAlto; i++)
    {
        (*imagen)[cabecera->alto + i] = (Pixel *)malloc(ancho * sizeof(Pixel));
        if (!(*imagen)[cabecera->alto + i])
        {
            puts("Error al asignar memoria para la nueva fila de la imagen ampliada verticalmente.");
            for(int j = i; j > 0; j--)
            {
                free((*imagen)[j]);
            }
            return ERR_MEMORIA;
        }
        for (int j = 0; j < ancho; j++)
        {
            (*imagen)[cabecera->alto + i][j].blue = 125;
            (*imagen)[cabecera->alto + i][j].green = 125;
            (*imagen)[cabecera->alto + i][j].red = 125;
        }
    }

    cabecera->alto = alto;
    cabecera->tamImagen = cabecera->alto * cabecera->ancho * sizeof(Pixel);

    return TODO_OK;
}

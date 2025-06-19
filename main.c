#include <stdio.h>
#include "funciones_grupo.h"
#include "funciones_marquez.h"
#include "funciones_paz.h"
#include "funciones_stivala.h"

int main(int argc, char *argv[])
{
    Header header, header2;
    Pixel **imagen, **imagen2;
    char *nomArch1, *nomArch2;

    nomArch1 = buscaNombreArchivo(argc, argv);
    //nomArch2 = buscaNombreArchivo(argc, argv);

    printf("%s\n", nomArch1);
    //printf("%s\n", nomArch2);

    grabarCabeceraArchivo("unlam_1.bmp", &header);
    mostrarCabeceraArchivoHexa(&header);
    grabarImagenMemoria("unlam_1.bmp", &header, &imagen);

    liberarImagen(&header, &imagen);
    liberarImagen(&header2, &imagen2);
    return 0;
}

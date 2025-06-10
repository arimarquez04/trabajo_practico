#include <stdio.h>
#include "Header.h"
int main(void) {
    Header header;
    Pixel **imagen;

    grabarCabeceraArchivo("unlam_359.bmp", &header);
    mostrarCabeceraArchivoHexa(&header);
    grabarImagenMemoria("unlam_359.bmp", &header, &imagen);

    mostrarImagen(&header, &imagen);

    crearImagen("PRUEBA_359.bmp", header, imagen);

    liberarImagen(&header, &imagen);

    return 0;
}
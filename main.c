#include <stdio.h>
#include "funciones_grupo.h"
#include "funciones_stivala.h"

int main()
{
    pruebaPaz(); // Llamada a la función de prueba de Facundo Paz
    Header header;
    Pixel **imagen;

    grabarCabeceraArchivo("unlam_1.bmp", &header);
    mostrarCabeceraArchivoHexa(&header);
    grabarImagenMemoria("unlam_1.bmp", &header, &imagen);

    imagenEspejarH("1INVERTIR_H.bmp", header, imagen);
    imagenGrises("2GRIS.bmp", header, imagen);
    imagenRGB("3VERDE.bmp", header, imagen, VERDE, 20);
    imagenRGB("4AZUL.bmp", header, imagen, AZUL, 20);
    imagenRGB("5ROJO.bmp", header, imagen, ROJO, 50);

    liberarImagen(&header, &imagen);
    return 0;
}

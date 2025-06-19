//entorno de pruebas

#include <stdio.h>
#include "funciones_grupo.h"
#include "funciones_marquez.h"
#include "funciones_paz.h"
#include "funciones_stivala.h"
<<<<<<< HEAD

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

=======
#include "funciones_marquez.h"
int main()
{
    Header header;
    Pixel **imagen;
    grabarCabeceraArchivo("unlam_1.bmp", &header);
    mostrarCabeceraArchivoHexa(&header);
    grabarImagenMemoria("unlam_1.bmp", &header, &imagen);
    rotarDerecha("Rotarderecha.bmp", header, imagen);
    imagenEspejarH("1INVERTIR_H.bmp", header, imagen);
    imagenGrises("2GRIS.bmp", header, imagen);
    imagenRGB("3VERDE.bmp", header, imagen, VERDE, 20);
    imagenRGB("4AZUL.bmp", header, imagen, AZUL, 20);
    imagenRGB("5ROJO.bmp", header, imagen, ROJO, 50);
    aumentarOReducirContraste(header, imagen, "unlam_1.bmp", FACTOR_REDUCIR, 50);
>>>>>>> 644b70e1865aad8a07d7f705a6fab1f4b69c5d79
    liberarImagen(&header, &imagen);
    liberarImagen(&header2, &imagen2);
    return 0;
}

#include <stdio.h>
#include "funciones_grupo.h"
#include "funciones_stivala.h"
#include "funciones_marquez.h"
#include "funciones_paz.h"

int main(int argc, char *argv[])
{
    Header header1, header2;
    Pixel **imagen1, **imagen2;

    char *archivo1 = NULL;
    char *archivo2 = NULL;
    int cntArchivos = 0;

    buscaNombreArchivo(argc, argv, &archivo1, &archivo2, &cntArchivos);

    if(!archivo1)
    {
        printf("No se especific� una imagen por par�metro");
        return INVALID_ARGUMENT;
    }

    grabarCabeceraArchivo(archivo1, &header1);
    grabarImagenMemoria(archivo1, &header1, &imagen1);

    if(archivo2)
    {
        grabarCabeceraArchivo(archivo2, &header2);
        grabarImagenMemoria(archivo2, &header2, &imagen2);
    }

    for(int i = 1 ; i < argc ; i++)
    {
        if(strcmpi(argv[i], "--escala-de-grises") == 0)
            imagenGrises(archivo1, header1, imagen1);
        else if(strcmpi(argv[i], "--espejar-horizontal") == 0)
            imagenEspejarH(archivo1, header1, imagen1);
        else if(strcmpi(argv[i], "--espejar-vertical") == 0)
            imagenEspejarV(archivo1, header1, imagen1);
        else if(_strnicmp(argv[i], "--tonalidad-roja=", 17) == 0)
            imagenRGB(archivo1, header1, imagen1, ROJO, obtenerValorParametro(argv[i]));
        else if(_strnicmp(argv[i], "--tonalidad-verde=", 18) == 0)
            imagenRGB(archivo1, header1, imagen1, VERDE, obtenerValorParametro(argv[i]));
        else if(_strnicmp(argv[i], "--tonalidad-azul=", 17) == 0)
            imagenRGB(archivo1, header1, imagen1, AZUL, obtenerValorParametro(argv[i]));
        else if(strcmpi(argv[i], "--rotar-derecha") == 0)
            rotarDerecha(archivo1, header1, imagen1);
        else if(strcmpi(argv[i], "--rotar-izquierda") == 0)
            rotarIzquierda(archivo1, header1, imagen1);
        else if(strcmpi(argv[i], "--concatenar-vertical") == 0)
            if(cntArchivos < 2)
                printf("Falta una imagen para concatenar verticalmente.\n");
            else
            concatenarVertical(archivo1, header1, imagen1, archivo2, header2, imagen2);
        else if(strcmpi(argv[i], "--concatenar-horizontal") == 0)
            if(cntArchivos < 2)
                printf("Falta una imagen para concatenar horizontalmente.\n");
            else
                concatenarHorizontal(archivo1, header1, imagen1, archivo2, header2, imagen2);
        else if (strncmp(argv[i], "--aumentar-contraste", 20) == 0) {
            int parametro = obtenerValorParametro(argv[i]);
            if(parametro >0){
                aumentarOReducirContraste(header1, imagen1, archivo1, FACTOR_AUMENTAR, (float) parametro);
            } else {
                printf("Falta el valor para --aumentar-contraste\n");
            }
        }
        else if (strncmp(argv[i], "--reducir-contraste", 19) == 0) {
            int parametro = obtenerValorParametro(argv[i]);
            if(parametro >0){
                aumentarOReducirContraste(header1, imagen1, archivo1, FACTOR_REDUCIR, (float) parametro);
            } else {
                printf("Falta el valor para --reducir-contraste\n");
            }
        }
        else if (strncmp(argv[i], "--recortar", 10) == 0) {
            int parametro = obtenerValorParametro(argv[i]);
            if(parametro >0){
                recortar(header1, imagen1, archivo1, (float) parametro);
            } else {
                printf("Falta el valor para --recortar\n");
            }
        }
        else if (strncmp(argv[i], "--achicar", 9) == 0) {
            int parametro = obtenerValorParametro(argv[i]);
            if(parametro >0){
                achicar(header1, imagen1, archivo1, parametro);
            } else {
                printf("Falta el valor para --achicar\n");
            }
        }
        else if (strncmp(argv[i], "--comodin", 9) == 0) {
            comodin(header1, imagen1, archivo1);
        }
        else if(strstr(argv[i], ".bmp") == NULL)
        {
            printf("%s NO es una funcionalidad valida.\n", argv[i]);
        }
    }

    liberarImagen(&header1, &imagen1);
    if(archivo2)
        liberarImagen(&header2, &imagen2);

    return 0;
}

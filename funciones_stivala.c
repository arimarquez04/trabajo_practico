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

    crearImagen(nomArch, headerL, imagenL);
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

    crearImagen(nomArch, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}

int imagenEspejarH(const char *nomArch, Header header, Pixel **imagen)
{
    Header headerL;
    Pixel **imagenL;

    copiaImagen(header, imagen, &headerL, &imagenL);

    Pixel pixel;

    for(int i = 0 ; i < headerL.alto ; i++)
    {
        for(int j = 0 ; j < headerL.ancho / 2 ; j++)
        {
            pixel = imagenL[i][j];
            imagenL[i][j] = imagenL[i][headerL.ancho - 1 - j];
            imagenL[i][headerL.ancho - 1 - j] = pixel;
        }
    }

    crearImagen(nomArch, headerL, imagenL);
    liberarImagen(&headerL, &imagenL);

    return TODO_OK;
}

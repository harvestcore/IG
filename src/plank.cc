//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: plank.cc
//
//####################################################

#include "plank.h"

Plank::Plank() {
    height = 10;
    width = 10;
    cubes = 1;
}

Plank::Plank(double height, double width, double cubes) {
    init(height, width, cubes);
}

void Plank::init(double height, double width, double cubes) {
    this->height = height;
    this->width = width;
    this->cubes = cubes;
}

CoordenadasIMG Plank::getCoordenadas() {
    return img;
}

int Plank::getCubes() {
    return (int) cubes;
}

void Plank::incrementHeight() {
    height += 1;
}

void Plank::decrementHeight() {
    height -= 1;
}

void Plank::incrementWidth() {
    width += 1;
}

void Plank::decrementWidth() {
    width -= 1;
}

void Plank::incrementSide() {
    cubes += 1;
}

void Plank::decrementSide() {
    cubes -= 1;
}

void Plank::generatePlank() {
    double ancho = width / cubes;
    double alto = height / cubes;

    double auxAncho = 0;
    double auxAlto = 0;

    int ind = 2;
    cube = new Cube();


    if (cubes == 1) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(width,height,0.5);
        cube->drawChess();
        glPopMatrix();
    } else {
        for (int i = 0; i < cubes; ++i) {
            for (int j = 0; j < cubes; ++j) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glTranslatef(-((cubes-1)*width)/(2*cubes),-((cubes-1)*height)/(2*cubes),0);
                glTranslatef(auxAncho,auxAlto,0);
                glScalef(ancho,alto,0.5);
                cube->drawChess();
                glPopMatrix();
                auxAncho += ancho;
            }
            auxAncho = 0;
            auxAlto += alto;
        }
    }

    img.X_00 = -width/2;
    img.Y_00 = -height/2;
    img.X_01 = -width/2;
    img.Y_01 = height/2;
    img.X_10 = width/2;
    img.Y_10 = -height/2;
    img.X_11 = width/2;
    img.Y_11 = height/2;
    img.thicc = 0.5/2;
}

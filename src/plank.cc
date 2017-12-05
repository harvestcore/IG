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

    cube.calculateNormalTriangles();
    cube.calculateNormalPoints();
    cube.setMaterial(1);
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

void Plank::drawCube(ViewMode mode) {
    switch (mode) {
        case MESH:
            cube.drawMesh();
            break;
        case EDGES:
            cube.drawEdges();
            break;
        case SOLID:
            cube.drawSolid();
            break;
        case CHESS:
            cube.drawChess();
            break;
        case FLAT:
            cube.drawFlatSmoothing();
            break;
        case SMOOTH:
            cube.drawGouraudSmoothing();
            break;
    }
}

void Plank::generatePlank(ViewMode mode) {
    double ancho = width / cubes;
    double alto = height / cubes;
    anchoCubo = ancho;
    altoCubo = alto;

    double auxAncho = 0;
    double auxAlto = 0;

    int ind = 2;

    if (cubes == 1) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(width,height,0.5);
        drawCube(mode);
        glPopMatrix();
    } else {
        for (int i = 0; i < cubes; ++i) {
            for (int j = 0; j < cubes; ++j) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glTranslatef(-((cubes-1)*width)/(2*cubes),-((cubes-1)*height)/(2*cubes),0);
                glTranslatef(auxAncho,auxAlto,0);
                glScalef(ancho,alto,0.5);
                drawCube(mode);
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

void incrementTop() {

}

void decrementTop() {

}

void incrementBottom() {

}

void decrementBottom() {

}

void incrementLeft() {

}

void decrementLeft() {

}

void incrementRight() {

}

void decrementRight() {

}

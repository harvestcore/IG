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

Plank::Plank(double height, double width, int cubes) {
    init(height, width, cubes);
}

void Plank::init(double height, double width, int cubes) {
    this->height = height;
    this->width = width;
    this->cubes = cubes;
}

CoordenadasIMG Plank::getCoordenadas() {
    return img;
}

int Plank::getCubes() {
    return cubes;
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

void Plank::generatePlank(ViewMode mode, CoordenadasIMG coords) {
    double ancho = width / cubes;
    double alto = height / cubes;

    double auxAncho = 0;
    double auxAlto = 0;

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

    double auxWidth = width / 2;
    double auxHeight = height / 2;

    img.X_00 = -auxWidth + (auxWidth * coords.X_00);
    img.Y_00 = -auxHeight + (auxHeight * coords.Y_00);
    img.X_01 = -auxWidth + (auxWidth * coords.X_01);
    img.Y_01 = (height * coords.Y_01) - auxHeight;
    img.X_10 = (width * coords.X_10) - auxWidth;
    img.Y_10 = -auxHeight + (auxHeight * coords.Y_10);
    img.X_11 = (width * coords.X_11) - auxWidth;
    img.Y_11 = (height * coords.Y_11) - auxHeight;
    img.thicc = coords.thicc / 2;
}

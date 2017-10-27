//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: 3DObject.cc
//
//####################################################

#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "3DObject.h"
#include "vertex.h"
#include "models.h"
#include "machine.h"

using namespace std;

Box::Box() {
}

Box::Box(double newHeight, double newWidth, double newThickness) {
    height = newHeight;
    width = newWidth;
    thickness = newThickness;
}

void Box::setHeight(double newHeight) {
    height = newHeight;
}

void Box::setWidth(double newWidth) {
    width = newWidth;
}

void Box::setThickness(double newThickness) {
    thickness = newThickness;
}

void Box::setParameters(double newHeight, double newWidth, double newThickness) {
    setHeight(newHeight);
    setWidth(newWidth);
    setThickness(newThickness);
}

void Box::generateBox() {
    float h = (float) height / 2;
    float w = (float) width / 2;
    float t = (float) thickness / 2;
    float THICC = (float) thickness;

    points = {{-w,0,w},{-w + THICC,0,w},{w - THICC,0,w},{w,0,w},
    {w,0,w + THICC},
    {w,0,-w + THICC},
    {w,0,-w},
    {w - THICC,0,-w},
    {w,0,-w},
    {-w,0,-w},
    {-w,0,-w + THICC},
    {-w,0,w - THICC}};

}

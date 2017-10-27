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
#include "articulatedArm.h"

using namespace std;

Arm::Arm() {
}

Arm::Arm(double newTopRadius, double newBottomRadius, double newHeight) {
    topRadius = newTopRadius;
    bottomRadius = newBottomRadius;
    height = newHeight;
}

void Arm::createArm() {
}

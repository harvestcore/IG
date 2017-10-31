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
#include "wattRegulator.h"

using namespace std;


WattRegulator::WattRegulator() {
}

void WattRegulator::draw() {
  glMatrixMode(GL_MODELVIEW);
  glTranslate(0,4,0);
  glScale(10,4,10);
  base.drawMesh();
}

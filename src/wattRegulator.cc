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


Disco::Disco() {
}

void Disco::draw() {
  disco1.generateByRevolution('y', false);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0,13,0);
  glScalef(3,2,3);
  disco1.drawMesh();
  disco1.drawEdges();
  glPopMatrix();
}

BrazoPrincipal::BrazoPrincipal() {
}

void BrazoPrincipal::draw() {
  brazo.generateByRevolution('y', false);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0,7,0);
  glScalef(2,10,2);
  brazo.drawMesh();
  brazo.drawEdges();
  glPopMatrix();

  //disco_sup.draw();
}

WattRegulator::WattRegulator() {
}

void WattRegulator::draw() {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0,1,0);
  glScalef(5,2,5);
  base.drawMesh();
  base.drawEdges();
  glPopMatrix();

  brazo.draw();
}

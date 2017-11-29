//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: sceneText.cc
//
//####################################################

#include <GL/glut.h>
#include "sceneText.h"
#include <string>

string dts(double i){
	stringstream out;
	out << i;
	return out.str();
}

void printText(int x, int y, string text) {
    glRasterPos2f(x,y);

    for (int i=0; i<text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
}

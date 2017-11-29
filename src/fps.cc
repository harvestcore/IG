//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: fps.cc
//
//####################################################

#include <GL/glut.h>
#include "fps.h"

FPScounter::FPScounter(){
}

void FPScounter::incrementFrames() {
    frames +=1;
}

void FPScounter::calculateFPS() {
    elapsed_time = glutGet(GLUT_ELAPSED_TIME);
	if ((elapsed_time - base_time) > 1000.0) {
		fps=frames*1000.0/(elapsed_time - base_time);
		base_time = elapsed_time;
		frames = 0;
	}
}

double FPScounter::getFPS() {
    return fps;
}

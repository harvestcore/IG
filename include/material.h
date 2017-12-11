//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: material.cc
//
//####################################################

#ifndef __MATERIAL__H__
#define	__MATERIAL__H__

#include <GL/glut.h>
#include "vertex.h"
#include "texture.h"

using namespace std;

class Material {
    private:
        _vertex4f ambient;
        _vertex4f specular;
        _vertex4f diffuse;
        GLfloat brightness;

    public:
        Material();
        void setAmbient(_vertex4f ambient);
        void setSpecular(_vertex4f specular);
        void setDiffuse(_vertex4f diffuse);
        void setBrightness(GLfloat brightness);
        _vertex4f getAmbient();
        _vertex4f getSpecular();
        _vertex4f getDiffuse();
        GLfloat getBrightness();
        void enable();
        void disable();
};

#endif

//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: light.h
//
//####################################################

#ifndef __LIGHT__H__
#define	__LIGHT__H__

#include <GL/glut.h>
#include "vertex.h"
#include "3DObject.h"

class Light {
    private:
        GLenum ID;

        _vertex4f position;
        _vertex4f ambient;
        _vertex4f specular;
        _vertex4f diffuse;
        GLfloat alpha, beta;
        bool directional;
        ALLFIGURE sphere;

    public:
        Light();
        void setID(GLenum ID);
        void setPosition(_vertex4f position);
        void setAmbient(_vertex4f ambient);
        void setSpecular(_vertex4f specular);
        void setDiffuse(_vertex4f diffuse);
        void setDirectional(bool dir);
        void setAlpha(GLfloat alpha);
        void setBeta(GLfloat beta);
        void enable();
        void disable();
};

#endif

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

class Light {
    private:
        GLenum ID;

        _vertex3f position;
        _vertex4f ambient;
        _vertex4f specular;
        _vertex4f diffuse;

        GLfloat alfa, beta;

        bool directional;

    public:
        Light();

        void setID(GLenum ID);
        void setPosition(_vertex3f position);
        void setAmbient(_vertex4f ambient);
        void setSpecular(_vertex4f specular);
        void setDiffuse(_vertex4f diffuse);
        void setDirection(GLfloat alfa, GLfloat beta);
        void setDirectional(bool dir);

        void activate();
        void dactivate();
};

#endif

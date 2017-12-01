//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: texture.h
//
//####################################################

#ifndef __TEXTURE__H__
#define	__TEXTURE__H__

#include <GL/glut.h>
#include <vector>
#include "CImg.h"

using namespace cimg_library;

class Texture {
    private:
        GLuint ID;
        CImg<unsigned char> image;
        vector<unsigned char> data;

        unsigned int tamx;
        unsigned int tamy;
        unsigned char * texels;
        unsigned int id;
        bool automatico;

    public:
        Texture(const char *file);
        void loadTexture(const char *file);
        void enable();
        void disable();
};

#endif

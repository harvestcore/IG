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

#define TWOPI 6.283185308

#include <GL/glut.h>
#include <vector>
#include "CImg.h"
#include "types.h"
#include "vertex.h"

using namespace std;
using namespace cimg_library;

class Texture {
    private:
        GLuint ID;
        //GLenum ID;
        CImg<unsigned char> image;
        vector<unsigned char> data;
        unsigned int height;
        unsigned int width;


    public:
        Texture();
        Texture(const char *file);
        void loadTexture(const char *file);
        unsigned int getHeight();
        unsigned int getWidth();
        void drawTexture(CoordenadasIMG img);
        void drawTextureRevolution(vector<_vertex2f> map, vector<_vertex3f> points);
        void removeTexture();
};

#endif

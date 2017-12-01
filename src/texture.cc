//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: texture.cc
//
//####################################################

#include "texture.h"

void Texture::loadTexture(const char *file) {
    image.load(file);

    for (long y = 0; y < image.height(); y ++) {
        for (long x = 0; x < image.width(); x ++) {
            unsigned char *r = image.data(x, y, 0, 0);
            unsigned char *g = image.data(x, y, 0, 1);
            unsigned char *b = image.data(x, y, 0, 2);
            data.push_back(*r);
            data.push_back(*g);
            data.push_back(*b);
        }
    }
}

void Texture::enable() {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, textura_id);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // TRASFIERE LOS DATOS A GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
         0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void Texture::disable() {
    glDeleteTextures(1, &ID);
}

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

Texture::Texture() {
}

Texture::Texture(const char *file) {
    loadTexture(file);
}

void Texture::loadTexture(const char *file) {
     image.load(file);
     height = image.height();
     width = image.width();

     for (long i = 0; i < image.height(); ++i)
        for (long j = 0; j < image.width(); ++j) {
           unsigned char *r = image.data(j, i, 0, 0);
           unsigned char *g = image.data(j, i, 0, 1);
           unsigned char *b = image.data(j, i, 0, 2);
           data.push_back(*r);
           data.push_back(*g);
           data.push_back(*b);
        }

     glGenTextures(1, &ID);

}

unsigned int Texture::getHeight() {
    return height;
}

unsigned int Texture::getWidth() {
    return width;
}

void Texture::drawTexture(CoordenadasIMG img) {
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);         glVertex3f(img.X_10, img.Y_10, img.thicc + 0.015);
        glTexCoord2f(1, 1);         glVertex3f(img.X_00, img.Y_00, img.thicc + 0.015);
        glTexCoord2f(1, 0);         glVertex3f(img.X_01, img.Y_01, img.thicc + 0.015);
        glTexCoord2f(0, 0);         glVertex3f(img.X_11, img.Y_11, img.thicc + 0.015);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Texture::removeTexture() {
    glDeleteTextures(1, &ID);
}
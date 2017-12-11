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

void Texture::drawTexture(CoordenadasIMG cubo, CoordenadasIMG text) {
    double x00 = 1 / text.X_00;
    double y00 = 1 / text.Y_00;
    double x01 = 1 / text.X_01;
    double y01 = 1 / text.Y_01;
    double x10 = 1 / text.X_10;
    double y10 = 1 / text.Y_10;
    double x11 = 1 / text.X_11;
    double y11 = 1 / text.Y_11;

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
        glTexCoord2f(text.X_11, text.Y_11);         glVertex3f(cubo.X_10, cubo.Y_10, cubo.thicc + 0.015);
        glTexCoord2f(text.X_01, text.Y_01);         glVertex3f(cubo.X_00, cubo.Y_00, cubo.thicc + 0.015);
        glTexCoord2f(text.X_00, text.Y_00);         glVertex3f(cubo.X_01, cubo.Y_01, cubo.thicc + 0.015);
        glTexCoord2f(text.X_10, text.Y_10);         glVertex3f(cubo.X_11, cubo.Y_11, cubo.thicc + 0.015);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Texture::drawTextureRevolution(vector<_vertex2f> map, vector<_vertex3f> points) {
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);
    for (unsigned int i = 0; i < map.size(); ++i) {
        glTexCoord2f(map[i].s,map[i].t);
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }

    for (unsigned int i = 0; i < map.size(); ++i) {
        glTexCoord2f(map[i].s,map[i].t);
        glVertex3f(points[i].x, points[i].y, -points[i].z);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Texture::removeTexture() {
    glDeleteTextures(1, &ID);
}

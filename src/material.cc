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

#include "material.h"

Material::Material() {
    texture = null;
}

void Material::setAmbient(_vertex4f ambient) {
    this->ambient = ambient;
}

void Material::setSpecular(_vertex4f specular) {
    this->specular = specular;
}

void Material::setDiffuse(_vertex4f diffuse) {
    this->diffuse = diffuse;
}

void Material::setBrightness(GLfloat brightness) {
    this->brightness = brightness;
}

bool Material::gotTexture() {
    return texture == null;
}

void Material::enable() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, brightness);

    if(gotTexture())
        textura->activar();
    else
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Material::disable() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

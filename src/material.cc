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

_vertex4f Material::getAmbient() {
    return ambient;
}

_vertex4f Material::getSpecular() {
    return specular;
}

_vertex4f Material::getDiffuse() {
    return diffuse;
}

GLfloat Material::getBrightness() {
    return brightness;
}

bool Material::gotTexture() {
    return texture != nullptr;
}

void Material::loadTexture(const char *file) {
    texture = new Texture(file);
}

Texture Material::getTexture() {
    return *texture;
}

void Material::enableTexture() {
    //texture->drawTexture();
}

void Material::disableTexture() {
    //texture->disable();
}

void Material::enable() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) &ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) &diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, brightness);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glPopMatrix();
}

void Material::disable() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

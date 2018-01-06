//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: camera.cc
//
//####################################################

#include "camera.h"

Camera::Camera() {
}

void Camera::setType(CameraType type) {
    this->type = type;
}

void Camera::setPosition(_vertex3f position) {
    this->position = position;
}

void Camera::setCenter(_vertex3f center) {
    this->center = center;
}

void Camera::setObserverAngle(_vertex2f observerAngle) {
    this->observerAngle = observerAngle;
}

void Camera::setObserverDistance(GLfloat observerDistance) {
    this->observerDistance = observerDistance;
}

void Camera::setPlanes(GLfloat frontplane, GLfloat backplane) {
    this->frontplane = frontplane;
    this->backplane = backplane;
}

void Camera::setCoordinates(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
    this->top = top;
    this->bottom = bottom;
    this->left = left;
    this->right = right;
}

void Camera::setOffset(_vertex3f offset) {
    this->offset = offset;
}

CameraType Camera::getType() {
    return type;
}

void Camera::projectPerspective() {
    glFrustum(left, right, bottom, top, frontplane, backplane);
}

void Camera::projectOrthogonal() {
    glOrtho(left, right, bottom, top, frontplane, backplane);
}

void Camera::lookAt() {
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    //gluLookAt(position.x, position.y, position.z, center.x, center.y, center.z, 0, 1, 0);
}

void Camera::move() {
    glTranslatef(0,0,-observerDistance);
	glRotatef(observerAngle.x,1,0,0);
	glRotatef(observerAngle.y,0,1,0);
    glTranslatef(offset.x,offset.y,offset.z);
}

void Camera::project() {
    if (type == PERSPECTIVE)
        projectPerspective();
    else if (type == ORTHOGONAL)
        projectOrthogonal();
}

void Camera::moveForward() {
    position.z -= 0.5;
}

void Camera::moveBackward() {
    position.z += 0.5;
}

void Camera::moveLeft() {
    position.x -= 0.5;
}

void Camera::moveRight() {
    position.x += 0.5;
}

void Camera::moveUp() {
    position.y += 0.5;
}

void Camera::moveDown() {
    position.y -= 0.5;
}

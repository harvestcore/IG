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

Camera::Camera(CameraType newtype, CameraPosition3 pos, CameraPosition3 center, CameraPosition3 vector, CameraPosition3 observer, CameraPosition6 window) {
    setType(newtype);  
    setCameraPosition(pos);
    setCameraCenter(center);
    setCameraVector(vector);
    setObserver(observer);
    setWindow(window);
}

void Camera::setType(CameraType newtype) {
    type = newtype;
}

void Camera::setCameraPosition(CameraPosition3 pos) {
    cameraPosX = pos.x;
    cameraPosY = pos.y;
    cameraPosZ = pos.z;
}

void Camera::setCameraCenter(CameraPosition3 center) {
    cameraCenterPosX = center.x;
    cameraCenterPosY = center.y;
    cameraCenterPosZ = center.z;
}

void Camera::setCameraVector(CameraPosition3 vector) {
    vectorX = vector.x;
    vectorY = vector.y;
    vectorZ = vector.z;
}

void Camera::setObserver(CameraPosition3 observer) {
    observerAngleX = observer.x;
    observerAngleY = observer.y;
    observerDistance = observer.z;
}

void Camera::setWindow(CameraPosition6 window) {
    left = window.x;
    right = window.y;
    up = window.z;
    down = window.t;
    backPlane = window.u;
    frontPlane = window.v;
}

CameraType Camera::getType() {
    return type;
}

void Camera::projectPerspective() {
    glFrustum(left,right,down,up,frontPlane,backPlane);
}

void Camera::projectOrthogonal() {
    glOrtho(left,right,down,up,frontPlane,backPlane);
}

void Camera::lookAt() {
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraCenterPosX, cameraCenterPosY, cameraCenterPosZ, vectorX, vectorY, vectorZ);
}

void Camera::project() {
    if (type == PERSPECTIVE)
        projectPerspective();
    else if (type == ORTHOGONAL)
        projectOrthogonal();
}

void Camera::moveForward() {
    cameraPosZ -= 0.5;
}

void Camera::moveBackward() {
    cameraPosZ += 0.5;
}

void Camera::moveLeft() {
    cameraPosX -= 0.5;
}

void Camera::moveRight() {
    cameraPosX += 0.5;
}

void Camera::moveUp() {
    cameraPosY += 0.5;
}

void Camera::moveDown() {
    cameraPosY -= 0.5;
}

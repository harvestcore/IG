//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: camera.h
//
//####################################################

#ifndef __CAMERA__H__
#define	__CAMERA__H__

#include <GL/glut.h>
#include "types.h"

class Camera {
    private:
        CameraType type;

        
        GLfloat left;
        GLfloat right;
        GLfloat up;
        GLfloat down;
        GLfloat backPlane;
        GLfloat frontPlane;
        
        GLfloat observerDistance;
        GLfloat observerAngleX;
        GLfloat observerAngleY;

        GLfloat cameraPosX;
        GLfloat cameraPosY;
        GLfloat cameraPosZ;

        GLfloat cameraCenterPosX;
        GLfloat cameraCenterPosY;
        GLfloat cameraCenterPosZ;

        GLfloat vectorX;
        GLfloat vectorY;
        GLfloat vectorZ;

        void projectPerspective();
        void projectOrthogonal();

    public:
        Camera();
        Camera(CameraType newtype, CameraPosition3 pos, CameraPosition3 center, CameraPosition3 vector, CameraPosition3 observer, CameraPosition6 window);
        CameraType getType();
        void setType(CameraType newtype);
        void setCameraPosition(CameraPosition3 pos);
        void setCameraCenter(CameraPosition3 center);
        void setCameraVector(CameraPosition3 vector);
        void setObserver(CameraPosition3 observer);
        void setWindow(CameraPosition6 window);
        void lookAt();
        void project();
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();


};

#endif
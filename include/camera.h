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
#include "vertex.h"

class Camera {
    private:
        CameraType type;
        
        GLfloat left;
        GLfloat right;
        GLfloat top;
        GLfloat bottom;
        GLfloat backplane;
        GLfloat frontplane;

        GLfloat scale;
        
        GLfloat observerDistance;
        _vertex2f observerAngle;
        _vertex3f position;
        _vertex3f center;

        _vertex3f offset;

        void projectPerspective();
        void projectOrthogonal();

    public:
        Camera();

        void setType(CameraType newtype);
        void setPosition(_vertex3f pos);
        void setCenter(_vertex3f center);
        void setObserverAngle(_vertex2f angle);
        void setObserverDistance(GLfloat observerDistance);
        void setPlanes(GLfloat frontplane, GLfloat backplane);
        void setCoordinates(GLfloat top, GLfloat bottom, GLfloat left, GLfloat right);
        void setOffset(_vertex3f offset);
        void setScale(GLfloat scale);

        CameraType getType();

        void lookAt();
        void move();
        void project();
        void zoomIn();
        void zoomOut();

    //  Unused
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
};

#endif
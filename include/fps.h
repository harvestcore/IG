//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: fps.h
//
//####################################################

#ifndef __FPS__H__
#define	__FPS__H__

#include <GL/glut.h>

class FPScounter {
    private:
        double elapsed_time = 0.0;
        int frames = 0;
        int fps = 0;
        int base_time = 0;

    public:
        FPScounter();
        void incrementFrames();
        void calculateFPS();
        double getFPS();
};

#endif

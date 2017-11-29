//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: fps.h
//
//####################################################

#include <GL/glut.h>

class FPScounter {
    private:
        double elapsed_time;
        int frames = 0;
        int fps = 0;
        int base_time = 0;

    public:
        FPScounter();
        void incrementFrames();
        void calculateFPS();
        int getFPS();
};

//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: plank.h
//
//####################################################

#ifndef __PLANK__H__
#define	__PLANK__H__

#include <GL/glut.h>
#include "models.h"
#include "types.h"

class Plank {
    private:
        Cube cube;
        double height;
        double width;
        double cubes;
        CoordenadasIMG img;
        double anchoCubo;
        double altoCubo;
        bool calculado = false;

    public:
        Plank();
        Plank(double height, double width, double cubes);
        void init(double height, double width, double cubes);
        CoordenadasIMG getCoordenadas();
        int getCubes();
        void incrementHeight();
        void decrementHeight();
        void incrementWidth();
        void decrementWidth();
        void incrementSide();
        void decrementSide();
        void drawCube(ViewMode mode);
        void generatePlank(ViewMode mode);
};

#endif

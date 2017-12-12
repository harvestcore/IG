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
#include <utility>
#include "models.h"
#include "types.h"

class Plank {
    private:
        Cube cube;
        double height;
        double width;
        int cubes;

        int cubesx, cubesy;

        CoordenadasIMG img;
        double anchoCubo;
        double altoCubo;
        bool calculado = false;

    public:
        Plank();
        Plank(double height, double width, int cubesx, int cubesy);
        void init(double height, double width, int cubesx, int cubesy);
        CoordenadasIMG getCoordenadas();
        int getCubesx();
        int getCubesy();
        void incrementHeight();
        void decrementHeight();
        void incrementWidth();
        void decrementWidth();
        void incrementSide();
        void decrementSide();
        void drawCube(ViewMode mode);
        void generatePlank(ViewMode mode, CoordenadasIMG);
};

#endif

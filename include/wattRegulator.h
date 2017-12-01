//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//	GII - ETSIIT
//
//  file: wattRegulator.h
//
//####################################################

#ifndef __WATT__H__
#define	__WATT__H__

#include <thread>
#include <chrono>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "models.h"
#include "types.h"
#include "3DObject.h"
#include "vertex.h"

class Laterales {
    private:
        Cylinder tubo;
        Sphere bola;
        Ply_Static beethoven;

        double angulo_superior = 35;
        double angulo_inferior = 41;

        double altura_disco_central = 6;

    public:
        Laterales();
        void draw(ViewMode mode);
        void show(ViewMode mode, TypeObject type);

        void incrementarAnguloSuperior(double velocidad);
        void reducirAnguloSuperior(double velocidad);

        void incrementarAnguloInferior(double velocidad);
        void reducirAnguloInferior(double velocidad);

        void incrementarDiscoCentral(double velocidad);
        void decrementarDiscoCentral(double velocidad);

        void comprobarMovimiento();
};

class Brazo_Disco {
    private:
      Cylinder brazo_disco;

    public:
        Brazo_Disco();
        void draw(ViewMode mode);
        void show(ViewMode mode);
};

class Pie {
    private:
        Cube pie;

    public:
        Pie();
        void draw(ViewMode mode);
        void show(ViewMode mode);
};

class Watt {
    private:
        Pie pie;
        Brazo_Disco brazo_disco;
        Laterales laterales;

        double angulo_giro;
        double velocidad = 1;

        bool girando = false;

    public:
        Watt();
        void draw(ViewMode mode);

        void incrementarAngulo();
        void decrementarAngulo();

        void incrementarAnguloInf();
        void decrementarAnguloInf();

        void aumentarVelocidad();
        void decrementarVelocidad();

        void control();
        void giro();

        void toggleSpinning();
        bool isSpinning();
        double getSpeed();
};


#endif

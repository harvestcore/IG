#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class SoporteLateral {
    private:

    public:
        SoporteLateral();
        void draw();
};

class BrazosLaterales {
    private:
        Cylinder brazo_izq;
        Cylinder brazo_der;
        //Sphere bola;

    public:
        BrazosLaterales();
        void draw();
};

class Disco {
    private:
        Cylinder disco_sup;
        BrazosLaterales laterales;

    public:
        Disco();
        void draw();
};

class BrazoPrincipal {
    private:
        Cylinder brazo;
        Disco disco_sup;

    public:
        BrazoPrincipal();
        void draw();
};

class WattRegulator {
    private:
        Cube base;
        BrazoPrincipal brazo;

    public:
        WattRegulator();
        void draw();
};

#endif

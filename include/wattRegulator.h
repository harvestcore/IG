#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class Soportes {
    private:
        Cylinder soporte_izq;
        Cylinder soporte_der;

    public:
        Soportes();
        void draw();
};

class Anillo {
    private:
        Cylinder anillo_central;
        Cylinder varilla;
        Soportes soportes_laterales;

    public:
        Anillo();
        void draw();
};

class Esferas {
    private:
        Sphere bola_izq;
        Sphere bola_der;
        Anillo anillo_central;

    public:
        Esferas();
        void draw();
};

class BrazosLaterales {
    private:
        Cylinder brazo_izq;
        Cylinder brazo_der;
        Esferas bolas;

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

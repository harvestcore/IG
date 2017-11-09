#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class Laterales {
    private:
        Cylinder tubo;
        Sphere bola;

        double angulo_superior = 35;
        double angulo_inferior = 41;

        double altura_disco_central = 6;

    public:
        Laterales();
        void draw();

        void incrementarAnguloSuperior();
        void reducirAnguloSuperior();

        void incrementarAnguloInferior();
        void reducirAnguloInferior();

        void incrementarDiscoCentral();
        void reducirDiscoCentral();

        void comprobarMovimiento();
};

class Brazo_Disco {
    private:
      Cylinder brazo_disco;

    public:
        Brazo_Disco();
        void draw();
};

class Pie {
    private:
        Cube pie;

    public:
        Pie();
        void draw();
};

class Watt {
    private:
        Pie pie;
        Brazo_Disco brazo_disco;
        Laterales laterales;

        double angulo_giro;
        double velocidad = 1;

    public:
        Watt();
        void draw();

        void incrementarAngulo();
        void decrementarAngulo();

        void incrementarAnguloInf();
        void decrementarAnguloInf();

        void incrementarDisco();
        void decrementarDisco();

        void giro();
};


#endif

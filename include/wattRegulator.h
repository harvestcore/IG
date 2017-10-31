#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class Disco {
  private:
    Cylinder disco1;

  public:
    Disco();
    void draw();
};

class SoporteLateral {
  private:

  public:
    SoporteLateral();
    void draw();

};

class BrazoLateral {
  private:
    Cylinder brazo;
    SoporteLateral soporte;
    Sphere esfera;

  public:
    BrazoLateral();
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

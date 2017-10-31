#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class WattRegulator {
  private:
    Cube base;
    Cylinder cilindro1;

  public:
    WattRegulator();
    void draw();
};

#endif

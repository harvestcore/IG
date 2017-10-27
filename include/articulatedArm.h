#ifndef __ARM__H__
#define	__ARM__H__

#include "models.h"
#include "3DObject.h"

class Finger: public ComplexObject {
};

class Hand: public ComplexObject {
};

class Arm: public RevolutionModel {
    private:
    public:
        Arm();
        Arm(double newTopRadius, double newBottomRadius, double newHeight);
        void createArm();
};

class ArticulatedArm {
    private:
        bool armGenerated = false;

    public:
};

#endif

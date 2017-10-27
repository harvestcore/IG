#ifndef __MACHINE__H__
#define	__MACHINE__H__

#include "models.h"
#include "3DObject.h"

class Box: public ComplexObject{
    private:
        double height;
        double width;
        double thickness;

    public:
        Box();
        Box(double newHeight, double newWidth, double newThickness);
        void setHeight(double newHeight);
        void setWidth(double newWidth);
        void setThickness(double newThickness);
        void setParameters(double newHeight, double newWidth, double newThickness);
        void generateBox();
};

class Maquina {
    private:
        bool machineGenerated = false;
    public:
};

#endif

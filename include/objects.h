//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//	GII - ETSIIT
//
//  file: objects.h
//
//####################################################

#ifndef __OBJECTS__H__
#define	__OBJECTS__H__

#include <GL/glut.h>
#include <vector>
#include "3DObject.h"
#include "vertex.h"
#include "types.h"
#include "models.h"
#include "wattRegulator.h"
#include "file_ply_stl.h"


/**
*   Clase que encapsula todas las anteriores para así solo tener un objeto
*   Models en el main.
*/
class Models {
    private:
        bool areModelsGenerated = false;
    public:
        Cube v_Cube;
        Tetrahedron v_Tetrahedron;
        Ply_Static v_Ply_Static;
        Ply_Revolution v_Ply_Revolution;
        Cylinder v_Cylinder;
        Glass v_Glass;
        Glass_Inverted v_Glass_Inverted;
        Cone v_Cone;
        Tube v_Tube;
        Sphere v_Sphere;
        Watt v_Watt;

        Models();
        void setModelsAreGenerated(bool mod);
        bool getModelsAreGenerated();
        void initializeModels();
        void addStep(TypeObject object);
        void reduceStep(TypeObject object);
        void addStepALL();
        void reduceStepALL();
        void regenerate(TypeObject object);
        void setAnguloInicioAnguloFinal(double inicio, double final);
};


#endif

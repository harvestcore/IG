//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//	GII - ETSIIT
//
//  file: objects.cc
//
//####################################################

#include <vector>
#include "objects.h"
#include "vertex.h"

Models::Models() {
}

void Models::setModelsAreGenerated(bool mod) {
    areModelsGenerated = mod;
}

bool Models::getModelsAreGenerated() {
    return areModelsGenerated;
}

void Models::initializeModels() {
    Cube aux_cube(2);
    v_Cube = aux_cube;

    Tetrahedron aux_tetrahedron(2);
    v_Tetrahedron = aux_tetrahedron;

    Ply_Static aux_ply_static("/home/angel/Dropbox/Universidad/Tercero/P2_2/ply/beethoven.ply");
    v_Ply_Static = aux_ply_static;

    Ply_Revolution aux_ply_revolution("/home/angel/Dropbox/Universidad/Tercero/P2_2/ply/peon.ply");
    v_Ply_Revolution = aux_ply_revolution;
    v_Ply_Revolution.generateByRevolution('y', false);

    Cylinder aux_cylinder(4, 6);
    v_Cylinder = aux_cylinder;
    v_Cylinder.generateByRevolution('y', false);

    Glass aux_glass(5, 3, 6);
    v_Glass = aux_glass;
    v_Glass.generateByRevolution('y', false);

    Glass_Inverted aux_glass_inverted(5, 3, 6);
    v_Glass_Inverted = aux_glass_inverted;
    v_Glass_Inverted.generateByRevolution('y', false);

    Cone aux_cone(4, 6);
    v_Cone = aux_cone;
    v_Cone.generateByRevolution('y', false);

    Tube aux_tube(4, 6);
    v_Tube = aux_tube;
    v_Tube.generateByRevolution('y', false);

    vector<_vertex3f> points = {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},
              {-0.5,0.5,0.5},{0.5,0.5,0.5},
              {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},
              {-0.5,0.5,-0.5},{0.5,0.5,-0.5}};

    vector<_vertex3i> triangles = {{0,1,2},{1,2,3},{1,3,5},{5,3,7},
                 {5,7,4},{4,7,6},{4,6,0},{0,6,2},
                 {4,0,1},{4,1,5},{2,6,3},{3,6,7}};

}

void Models::addStep(TypeObject object) {
    switch (object) {
        case PLY_REVOLUTION:
           v_Ply_Revolution.moreSteps();
           regenerate(object);
           break;

         case CYLINDER:
            v_Cylinder.moreSteps();
            regenerate(object);
            break;

        case GLASS:
            v_Glass.moreSteps();
            regenerate(object);
            break;

        case GLASS_INVERTED:
            v_Glass_Inverted.moreSteps();
            regenerate(object);
            break;

        case CONE:
            v_Cone.moreSteps();
            regenerate(object);
            break;

        case TUBE:
            v_Tube.moreSteps();
            regenerate(object);
            break;
    }
}

void Models::reduceStep(TypeObject object) {
    switch (object) {
        case PLY_REVOLUTION:
           v_Ply_Revolution.lessSteps();
           regenerate(object);
           break;

         case CYLINDER:
            v_Cylinder.lessSteps();
            regenerate(object);
            break;

        case GLASS:
            v_Glass.lessSteps();
            regenerate(object);
            break;

        case GLASS_INVERTED:
            v_Glass_Inverted.lessSteps();
            regenerate(object);
            break;

        case CONE:
            v_Cone.lessSteps();
            regenerate(object);
            break;

        case TUBE:
            v_Tube.lessSteps();
            regenerate(object);
            break;
    }
}

void Models::addStepALL() {
    v_Ply_Revolution.moreSteps();
    regenerate(PLY_REVOLUTION);

    v_Cylinder.moreSteps();
    regenerate(CYLINDER);

    v_Glass.moreSteps();
    regenerate(GLASS);

    v_Glass_Inverted.moreSteps();
    regenerate(GLASS_INVERTED);

    v_Cone.moreSteps();
    regenerate(CONE);

    v_Tube.moreSteps();
    regenerate(TUBE);
}

void Models::reduceStepALL() {
    v_Ply_Revolution.lessSteps();
    regenerate(PLY_REVOLUTION);

    v_Cylinder.lessSteps();
    regenerate(CYLINDER);

    v_Glass.lessSteps();
    regenerate(GLASS);

    v_Glass_Inverted.lessSteps();
    regenerate(GLASS_INVERTED);

    v_Cone.lessSteps();
    regenerate(CONE);

    v_Tube.lessSteps();
    regenerate(TUBE);
}

void Models::regenerate(TypeObject object) {
    switch (object) {
        case PLY_REVOLUTION:
           v_Ply_Revolution.generateByRevolution('y', false);
           break;

         case CYLINDER:
            v_Cylinder.generateByRevolution('y', false);
            break;

        case GLASS:
            v_Glass.generateByRevolution('y', false);
            break;

        case GLASS_INVERTED:
            v_Glass_Inverted.generateByRevolution('y', false);
            break;

        case CONE:
            v_Cone.generateByRevolution('y', false);
            break;

        case TUBE:
            v_Tube.generateByRevolution('y', false);
            break;
    }
}

void Models::setAnguloInicioAnguloFinal(double inicio, double final) {
    v_Ply_Revolution.setAnguloInicio(inicio);
    v_Ply_Revolution.setAnguloFinal(final);

    v_Cylinder.setAnguloInicio(inicio);
    v_Cylinder.setAnguloFinal(final);

    v_Glass.setAnguloInicio(inicio);
    v_Glass.setAnguloFinal(final);

    v_Glass_Inverted.setAnguloInicio(inicio);
    v_Glass_Inverted.setAnguloFinal(final);

    v_Cone.setAnguloInicio(inicio);
    v_Cone.setAnguloFinal(final);

    v_Tube.setAnguloInicio(inicio);
    v_Tube.setAnguloFinal(final);
}

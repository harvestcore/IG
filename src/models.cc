//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: models.cc
//
//####################################################

#include <vector>
#include "models.h"
#include "vertex.h"
#include "types.h"

using namespace std;

StaticModel::StaticModel() {
}

StaticModel::StaticModel(double newSide) {
    setSide(newSide);
}

void StaticModel::setSide(double newSide) {
    side = (GLfloat) newSide * 0.5;
}

double StaticModel::getSide() const {
    return (double) side;
}

RevolutionModel::RevolutionModel() {
}

RevolutionModel::RevolutionModel(double newTopRadius, double newBottomRadius, double newHeight) {
    setTopRadius(newTopRadius);
    setBottomRadius(newBottomRadius);
    setHeight(newHeight);
}

void RevolutionModel::setTopRadius(double newTopRadius) {
    topRadius = newTopRadius * 0.5;
}

void RevolutionModel::setBottomRadius(double newBottomRadius) {
    bottomRadius = newBottomRadius * 0.5;
}

void RevolutionModel::setHeight(double newHeight) {
    height = newHeight * 0.5;
}

double RevolutionModel::getTopRadius() const {
    return (double) topRadius;
}

double RevolutionModel::getBottomRadius() const {
    return (double) bottomRadius;
}

double RevolutionModel::getHeight() const {
    return (double) height;
}

void RevolutionModel::Status() {
    cout << "steps: " << steps << endl;
    cout << "height: " << height << endl;
    cout << "topRadius: " << topRadius << endl;
    cout << "bottomRadius: " << bottomRadius << endl;
}

Cube::Cube() {
  setSide(1);
  createCube();
}

Cube::Cube(double newSide) {
    setSide(newSide);
    createCube();
}

void Cube::createCube() {
    points = {{-side,-side,side},{side,-side,side},
              {-side,side,side},{side,side,side},
              {-side,-side,-side},{side,-side,-side},
              {-side,side,-side},{side,side,-side}};

    triangles = {{0,1,2},{1,2,3},{1,3,5},{5,3,7},
                 {5,7,4},{4,7,6},{4,6,0},{0,6,2},
                 {4,0,1},{4,1,5},{2,6,3},{3,6,7}};
}

Tetrahedron::Tetrahedron() {
    setSide(1);
    createTetrahedron();
}

Tetrahedron::Tetrahedron(double newSide) {
    setSide(newSide);
    createTetrahedron();
}

void Tetrahedron::createTetrahedron() {
    points = {{0,side,0},{-side,-side,-side},{side,-side,-side},{0,-side,side}};
    triangles = {{1,0,2},{2,0,3},{0,1,3},{1,2,3}};
}

Ply_Static::Ply_Static() {
}

Ply_Static::Ply_Static(const string &filename) {
    createPly_Static(filename);
}

void Ply_Static::createPly_Static(const string &filename) {
    readPly(filename);
}

Ply_Revolution::Ply_Revolution() {
}

Ply_Revolution::Ply_Revolution(const string &filename) {
    createPly_Revolution(filename);
}

void Ply_Revolution::createPly_Revolution(const string &filename) {
    readPly(filename);
    setProfile(getVectorPoints());
}

Cylinder::Cylinder() {
    setTopRadius(1);
    setBottomRadius(1);
    setHeight(1);
    createCylinder();
}

Cylinder::Cylinder(double newRadius, double newHeight) {
    setTopRadius(newRadius);
    setBottomRadius(newRadius);
    setHeight(newHeight);
    createCylinder();
}

void Cylinder::createCylinder() {
    profile = {{0,-height,0},{bottomRadius,-height,0},{topRadius,height,0},{0,height,0}};
}

Glass::Glass() {
    setTopRadius(1);
    setBottomRadius(0.5);
    setHeight(1);
    createGlass();
}

Glass::Glass(double newTopRadius, double newBottomRadius, double newHeight) {
    setTopRadius(newTopRadius);
    setBottomRadius(newBottomRadius);
    setHeight(newHeight);
    createGlass();
}

void Glass::createGlass() {
    profile = {{0,-height,0},{bottomRadius,-height,0},{topRadius,height,0}};
}

Glass_Inverted::Glass_Inverted() {
    setTopRadius(0.5);
    setBottomRadius(1);
    setHeight(1);
    createGlass_Inverted();
}

Glass_Inverted::Glass_Inverted(double newTopRadius, double newBottomRadius, double newHeight) {
    setTopRadius(newTopRadius);
    setBottomRadius(newBottomRadius);
    setHeight(newHeight);
    createGlass_Inverted();
}

void Glass_Inverted::createGlass_Inverted() {
    profile = {{topRadius,-height,0},{bottomRadius,height,0},{0,height,0}};
}

Cone::Cone() {
    setTopRadius(0.5);
    setBottomRadius(0.5);
    setHeight(1);
    createCone();
}

Cone::Cone(double newRadius, double newHeight) {
    setTopRadius(newRadius);
    setBottomRadius(newRadius);
    setHeight(newHeight);
    createCone();
}

void Cone::createCone() {
    profile = {{0,-height,0},{bottomRadius,-height,0},{0,height,0}};
}

Tube::Tube() {
    setTopRadius(0.5);
    setBottomRadius(0.5);
    setHeight(1);
    createTube();
}

Tube::Tube(double newRadius, double newHeight) {
    setTopRadius(newRadius);
    setBottomRadius(newRadius);
    setHeight(newHeight);
    createTube();
}

void Tube::createTube() {
    profile = {{bottomRadius,-height,0},{topRadius,height,0}};
}

Sphere::Sphere() {
    radius = 0.5;
}

Sphere::Sphere(int newSteps, int newRadius) {
    steps = newSteps;
    radius = newRadius;
}

void Sphere::setRadius(double newRadius){
    radius = (GLfloat) newRadius;
}

void Sphere::createProfileSphere(char axis){
    vector<_vertex3f> bola(1);
    vector<_vertex3f> test(steps);

    _vertex3f point;
    point.x = 0;
    point.y = -radius;
    point.z = 0;

    bola[0] = point;

    //Revolution3DObject aux;
    //aux.addSinglePoint(point);
    profile = points = bola;
    //aux.drawMesh();
    //aux.generateByRevolution('y', false);
    //profile = points;

    double ini = (PI / 180) * 0;
    double fin = (PI / 180) * 180;

    double to_rotate = fin - ini;

    double rotationAngle = to_rotate / (steps-1);

    _vertex3f rotar = profile[0];

    for (int i = 0; i < steps; ++i) {
        switch (axis) {
            case 'x':
                for (unsigned int i = 0; i < profile.size(); ++i)
                    test[i] = rotate_X(rotar, rotationAngle);
                break;

            case 'y':
                for (unsigned int i = 0; i < profile.size(); ++i)
                    test[i] = rotate_Y(rotar, rotationAngle);
                break;

            case 'z':
                for (unsigned int i = 0; i < profile.size(); ++i)
                    test[i] = rotate_Z(rotar, rotationAngle);
                break;
        }
        rotar = test[i];
    }

    points = test;
}

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

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
    cout << "Steps: " << steps << endl;
    cout << "Height: " << height << endl;
    cout << "TopRadius: " << topRadius << endl;
    cout << "BottomRadius: " << bottomRadius << endl;
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
    Ply_Static aux("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/sphere.ply");
    points = aux.getVectorPoints();
    triangles = aux.getVectorTriangles();
}

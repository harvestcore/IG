//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: 3DObject.cc
//
//####################################################

#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "3DObject.h"
#include "vertex.h"

using namespace std;

Simple3DObject::Simple3DObject() {
    points.clear();
}

Simple3DObject::Simple3DObject (vector<_vertex3f> toConstruct) {
    points.clear();
    points = toConstruct;
}

Simple3DObject::Simple3DObject (const Simple3DObject &otherObject) {
    points.clear();
    points = otherObject.getVectorPoints();
}

void Simple3DObject::addSinglePoint(_vertex3f toAdd) {
    points.push_back(toAdd);
}

void Simple3DObject::addPoints(vector<_vertex3f> toAdd) {
    for (unsigned int i = 0; i < toAdd.size(); ++i)
        points.push_back(toAdd[i]);
}

_vertex3f Simple3DObject::getPoint(int position) const {
    return points[position];
}

vector<_vertex3f> Simple3DObject::getVectorPoints() const {
    return points;
}

int Simple3DObject::sizeMesh() const {
    return (int) points.size();
}

void Simple3DObject::drawMesh() {
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < points.size(); ++i)
        glVertex3fv((GLfloat *) &points[i]);
    glEnd();
}

Object3D::Object3D() {
    triangles.clear();
    points.clear();
}

Object3D::Object3D(vector<_vertex3i> newTriangles, vector<_vertex3f> newMesh) {
    points.clear();
    points = newMesh;
    triangles.clear();
    triangles = newTriangles;
}

Object3D::Object3D(vector<_vertex3i> newTriangles, Simple3DObject newMesh) {
    points.clear();
    points = newMesh.getVectorPoints();
    triangles.clear();
    triangles = newTriangles;
}

Object3D::Object3D(const Object3D &otherObject) {
    points.clear();
    points = otherObject.getVectorPoints();

    triangles.clear();
    triangles = otherObject.getVectorTriangles();
}

void Object3D::addSingleTriangle(_vertex3i toAdd) {
    triangles.push_back(toAdd);
}

void Object3D::addTriangles(vector<_vertex3i> toAdd) {
    for (unsigned int i = 0; i < toAdd.size(); ++i)
        triangles.push_back(toAdd[i]);
}

_vertex3i Object3D::getTriangle(int position) const {
    return triangles[position];
}

vector<_vertex3i> Object3D::getVectorTriangles() const {
    return triangles;
}

int Object3D::sizeTriangles() const {
    return (int) triangles.size();
}

void Object3D::drawEdges() {
    glColor3f(0.5,0,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size(); ++i) {
        glVertex3fv((GLfloat *) &points[triangles[i]._0]);
        glVertex3fv((GLfloat *) &points[triangles[i]._1]);
        glVertex3fv((GLfloat *) &points[triangles[i]._2]);
    }
    glEnd();
}

void Object3D::drawSolid() {
    glColor3f(0,0.5,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size(); ++i) {
        glVertex3fv((GLfloat *) &points[triangles[i]._0]);
        glVertex3fv((GLfloat *) &points[triangles[i]._1]);
        glVertex3fv((GLfloat *) &points[triangles[i]._2]);
    }
    glEnd();
}

void Object3D::drawChess() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size(); ++i) {
        switch(i % 2) {
            case 0:
                glColor3f(1,0,0);
                break;
            case 1:
                glColor3f(0,1,0);
                break;
        }
        glVertex3fv((GLfloat *) &points[triangles[i]._0]);
        glVertex3fv((GLfloat *) &points[triangles[i]._1]);
        glVertex3fv((GLfloat *) &points[triangles[i]._2]);
    }
    glEnd();
}

PlyObject::PlyObject() {}

PlyObject::PlyObject(const string &filename) {
    readPly(filename);
}

void PlyObject::readPly(const string &filename) {
    _file_ply aux;
    aux.open(filename);
    aux.read(points, triangles);
    aux.close();
}

Revolution3DObject::Revolution3DObject() {
}

Revolution3DObject::Revolution3DObject(vector<_vertex3f> newProfile, int newSteps) {
    steps = newSteps;
    profile = newProfile;
}

void Revolution3DObject::setProfile(vector<_vertex3f> newProfile) {
    profile = newProfile;
}

vector<_vertex3f> Revolution3DObject::getProfile() const {
    return profile;
}

void Revolution3DObject::setSteps(int newSteps) {
    steps = newSteps;
}

int Revolution3DObject::getSteps() const {
    return steps;
}

void Revolution3DObject::setAnguloInicio(double newAngulo_inicio) {
    angulo_inicio = newAngulo_inicio;
}

void Revolution3DObject::setAnguloFinal(double newAngulo_final) {
    angulo_final = newAngulo_final;
}

void Revolution3DObject::moreSteps() {
    ++steps;
}

void Revolution3DObject::lessSteps() {
    if (steps > 1)
        --steps;
}

void Revolution3DObject::generateByRevolution(char axis, bool addCovers) {
    bool bottomCover = false;
    bool topCover = false;
    int aux = -1;
    int aux_cover = -1;
    int num_triangs = 0;

    /*

    double ini = (PI / 180) * angulo_inicio;
    double fin = (PI / 180) * angulo_final;

    double to_rotate = fin - ini;

    double rotationAngle = to_rotate / (steps-1);

    vector<_vertex3f> profile_original = profile;

    switch (axis) {
        case 'x':
            for (unsigned int i = 0; i < profile.size(); ++i)
                profile[i] = rotate_X(profile[i], ini);
            break;

        case 'y':
            for (unsigned int i = 0; i < profile.size(); ++i)
                profile[i] = rotate_Y(profile[i], ini);
            break;

        case 'z':
            for (unsigned int i = 0; i < profile.size(); ++i)
                profile[i] = rotate_Z(profile[i], ini);
            break;
    }

    */

    /**
    *   Angulo de rotacion de los puntos
    */
    double rotationAngle = 2 * PI / steps;

    /**
    *   Si quiero añadir tapas añado los puntos que necesito.
    */
    if (addCovers) {
       int aux_size = (int) profile.size();

       if (axis == 'x') {
          if (profile[0].z != 0) {
             _vertex3f aux(profile[0].x, 0, 0);
             profile.insert(profile.begin(), aux);
          }
       } else if (axis == 'y') {
          if (profile[0].x != 0) {
             _vertex3f aux(0, profile[0].y, 0);
             profile.insert(profile.begin(), aux);
          }
       } else if (axis == 'z') {
          if (profile[0].y != 0) {
             _vertex3f aux(0, 0, profile[0].z);
             profile.insert(profile.begin(), aux);
          }
       }

       if (axis == 'x') {
          if (profile[profile.size()].z != 0) {
             _vertex3f aux(profile[aux_size].x, 0, 0);
             profile.push_back(aux);
          }
       } else if (axis == 'y') {
          if (profile[profile.size()].x != 0) {
             _vertex3f aux(0, profile[aux_size].y, 0);
             profile.push_back(aux);
          }
       } else if (axis == 'z') {
          if (profile[profile.size()].y != 0) {
             _vertex3f aux(0, 0, profile[aux_size].z);
             profile.push_back(aux);
          }
       }
    }

    /**
    *   Contador de puntos
    */
    int counter = (int) profile.size();

    /**
    *   Comprobamos si tiene tapa superior o inferior.
    */
    switch (axis) {
        case 'x':
            if(profile[0].z == 0)
                bottomCover = true;
            if(profile[profile.size()-1].z == 0)
                topCover = true;
            break;

        case 'y':
            if(profile[0].x == 0)
                bottomCover = true;
            if(profile[profile.size()-1].x == 0)
                topCover = true;
            break;

        case 'z':
            if(profile[0].y == 0)
                bottomCover = true;
            if(profile[profile.size()-1].y == 0)
                topCover = true;
            break;
    }


    /**
    *   Actualizo el contador de puntos en funcion de las tapas
    */
    if(bottomCover)
        --counter;
    if(topCover)
        --counter;

    /**
    *   Numero de puntos que va a tener el objeto revolucionado
    */
    int dots = counter * steps;

    /**
    *   Numero de vertices de la parte interior del objeto
    */
    int interior_dots = counter * steps;

    /**
    *   Numero de triangulos que va a tener el objeto revolucionado
    */
    int triang = 2 * steps * (counter - 1);

    /**
    *   Actualizo los contadores en funcion de las tapas
    */
    if(bottomCover) {
        ++dots;
        triang += steps;
    }
    if(topCover) {
        ++dots;
        triang += steps;
    }

    /**
    *   Vector auxiliar para almacenar los puntos.
    */
    vector<_vertex3f> auxPoints(dots);

    /**
    *   Comprueba los cuatro posibles casos de tapas y calcula los puntos del nuevo objeto revolucionado.
    *
    *   Casos:
    *       tapa superior   &&  tapa inferior
    *       tapa superior   &&  !tapa inferior
    *       !tapa superior  &&  tapa inferior
    *       !tapa superior  &&  !tapa inferior
    */
    switch (bottomCover) {
        case true:
            switch (topCover) {

                /**
                *   tapa superior   &&  tapa inferior
                */
                case true:
                    for(unsigned int i = 0; i < profile.size() - 2; ++i)
                        auxPoints[i] = profile[i+1];

                    for(int i = 1; i < steps; ++i)
                        for(unsigned int j = 0; j < profile.size() - 1; ++j)
                            switch (axis) {
                                case 'x':
                                    auxPoints[i * counter + j] = rotate_X(profile[j + 1], rotationAngle * i);
                                    break;
                                case 'y':
                                    auxPoints[i * counter + j] = rotate_Y(profile[j + 1], rotationAngle * i);
                                    break;
                                case 'z':
                                    auxPoints[i * counter + j] = rotate_Z(profile[j + 1], rotationAngle * i);
                                    break;
                            }

                    auxPoints[dots - 2] = profile[0];
                    auxPoints[dots - 1] = profile[profile.size() - 1];
                    break;

                /**
                *   !tapa superior   &&  tapa inferior
                */
                case false:
                    for(unsigned int i = 0; i<profile.size() - 1; ++i)
                        auxPoints[i] = profile[i + 1];

                    for(int i = 1; i < steps; ++i)
                        for(unsigned int j = 0; j < profile.size(); ++j)
                            switch (axis) {
                                case 'x':
                                    auxPoints[i * counter + j] = rotate_X(profile[j + 1], rotationAngle * i);
                                    break;
                                case 'y':
                                    auxPoints[i * counter + j] = rotate_Y(profile[j + 1], rotationAngle * i);
                                    break;
                                case 'z':
                                    auxPoints[i * counter + j] = rotate_Z(profile[j + 1], rotationAngle * i);
                                    break;
                            }

                    auxPoints[dots - 1] = profile[0];
                    break;
            }
            break;

        case false:
            switch (topCover) {

                /**
                *   tapa superior   &&  !tapa inferior
                */
                case true:
                    for(unsigned int i = 0; i < profile.size() - 1; ++i)
                        auxPoints[i] = profile[i];

                    for(int i = 1; i < steps; ++i) {
                        for(unsigned int j = 0; j < profile.size() - 1; ++j)
                            switch (axis) {
                                case 'x':
                                    auxPoints[i * counter + j] = rotate_X(profile[j], rotationAngle * i);
                                    break;
                                case 'y':
                                    auxPoints[i * counter + j] = rotate_Y(profile[j], rotationAngle * i);
                                    break;
                                case 'z':
                                    auxPoints[i * counter + j] = rotate_Z(profile[j], rotationAngle * i);
                                    break;
                            }

                        auxPoints[dots - 1] = profile[profile.size() - 1];
                    }
                    break;

                /**
                *   !tapa superior   &&  !tapa inferior
                */
                case false:
                    for(unsigned int i = 0; i < profile.size(); ++i)
                        auxPoints[i] = profile[i];

                    for(int i = 1; i < steps; ++i)
                        for(unsigned int j = 0; j < counter; ++j)
                            switch (axis) {
                                case 'x':
                                    auxPoints[i * counter + j] = rotate_X(profile[j], rotationAngle * i);
                                    break;
                                case 'y':
                                    auxPoints[i * counter + j] = rotate_Y(profile[j], rotationAngle * i);
                                    break;
                                case 'z':
                                    auxPoints[i * counter + j] = rotate_Z(profile[j], rotationAngle * i);
                                    break;
                            }
                    break;
            }
    }

    points.clear();
    //points = profile;
    points = auxPoints;

    /**
    *   Vector auxiliar para almacenar los triangulos
    */
    vector<_vertex3i> auxTriangles(triang);

    /**
    *   Creo los triangulos intermedios
    */
    for(int i = 0; i < (counter - 1); ++i)
        for(int j = 0 ; j < steps; ++j) {
            aux = counter * j + i;

            auxTriangles[num_triangs].x = aux % interior_dots;
            auxTriangles[num_triangs].y = (aux + counter) % interior_dots;
            auxTriangles[num_triangs].z = (aux + 1)% interior_dots;

            auxTriangles[num_triangs+1].x = (aux + counter) % interior_dots;
            auxTriangles[num_triangs+1].y = (aux + counter + 1) % interior_dots;
            auxTriangles[num_triangs+1].z = (aux + 1) % interior_dots;
            num_triangs += 2;
        }

    /**
    *   Si hay tapa inferior se crean los triangulos
    */
    if (bottomCover) {
        if (topCover)
            aux_cover = dots - 2;
        else
            aux_cover = dots - 1;

        for(int i = 0; i < steps ; i++) {
            aux = i * counter;
            auxTriangles[num_triangs].x = aux_cover;
            auxTriangles[num_triangs].y = (aux + counter) % interior_dots;
            auxTriangles[num_triangs].z = aux % interior_dots;
            num_triangs++;
        }
    }

    if (topCover) {
        aux_cover = dots - 1;

        for(int i = 0; i < steps ; i++) {
            aux = i * counter + counter - 1;
            auxTriangles[num_triangs].x = aux % interior_dots;
            auxTriangles[num_triangs].y = (aux + counter) % interior_dots;
            auxTriangles[num_triangs].z = aux_cover;
            num_triangs++;
        }
    }

    triangles.clear();
    triangles = auxTriangles;
}

_vertex3f Revolution3DObject::rotate_X(_vertex3f point, double angle) {
    _vertex3f aux;
    aux.x = point.x;
    aux.y = cos(angle) * point.y - sin(angle) * point.z;
    aux.z = sin(angle) * point.y + cos(angle) * point.z;

    return aux;
}

_vertex3f Revolution3DObject::rotate_Y(_vertex3f point, double angle) {
    _vertex3f aux;
    aux.x = cos(angle) * point.x + sin(angle) * point.z;
    aux.y = point.y;
    aux.z = -sin(angle) * point.x + cos(angle) * point.z;

    return aux;
}

_vertex3f Revolution3DObject::rotate_Z(_vertex3f point, double angle) {
    _vertex3f aux;
    aux.x = cos(angle) * point.x - sin(angle) * point.y;
    aux.y = sin(angle) * point.x + cos(angle) * point.y;
    aux.z = point.z;

    return aux;
}

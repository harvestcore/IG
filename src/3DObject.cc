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

#include "3DObject.h"

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
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size(); ++i) {
        glVertex3fv((GLfloat *) &points[triangles[i]._0]);
        glVertex3fv((GLfloat *) &points[triangles[i]._1]);
        glVertex3fv((GLfloat *) &points[triangles[i]._2]);
    }
    glEnd();
}

void Object3D::drawChess() {
    glPolygonMode(GL_FRONT,GL_FILL);
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

void Object3D::drawFlatSmoothing() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);

    if (gotMaterial()) {
        _vertex4f amb = material->getAmbient();
        _vertex4f spec = material->getSpecular();
        _vertex4f dif = material->getDiffuse();
        GLfloat br = material->getBrightness();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &dif);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, br);
    }

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< triangles.size();i++){
        glNormal3f(normalTriangles[i].x, normalTriangles[i].y, normalTriangles[i].z);
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._0].s,map[triangles[i]._0].t);
        }
        glVertex3f(points[triangles[i]._0].x, points[triangles[i]._0].y, points[triangles[i]._0].z);
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._1].s,map[triangles[i]._1].t);
        }
        glVertex3f(points[triangles[i]._1].x, points[triangles[i]._1].y, points[triangles[i]._1].z);
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._2].s,map[triangles[i]._2].t);
        }
        glVertex3f(points[triangles[i]._2].x, points[triangles[i]._2].y, points[triangles[i]._2].z);
    }
    glEnd();
}

void Object3D::drawGouraudSmoothing() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    if (gotMaterial()) {
        _vertex4f amb = material->getAmbient();
        _vertex4f spec = material->getSpecular();
        _vertex4f dif = material->getDiffuse();
        GLfloat br = material->getBrightness();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &dif);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, br);
    }

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< triangles.size();i++){
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._0].s,map[triangles[i]._0].t);
        }
        glNormal3f(normalPoints[triangles[i]._0].x, normalPoints[triangles[i]._0].y, normalPoints[triangles[i]._0].z);
        glVertex3f(points[triangles[i]._0].x, points[triangles[i]._0].y, points[triangles[i]._0].z);
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._1].s,map[triangles[i]._1].t);
        }
        glNormal3f(normalPoints[triangles[i]._1].x, normalPoints[triangles[i]._1].y, normalPoints[triangles[i]._1].z);
        glVertex3f(points[triangles[i]._1].x, points[triangles[i]._1].y, points[triangles[i]._1].z);
        if(!map.empty()) {
            glTexCoord2f(map[triangles[i]._2].s,map[triangles[i]._2].t);
        }
        glNormal3f(normalPoints[triangles[i]._2].x, normalPoints[triangles[i]._2].y, normalPoints[triangles[i]._2].z);
        glVertex3f(points[triangles[i]._2].x, points[triangles[i]._2].y, points[triangles[i]._2].z);
    }
    glEnd();
}


void Object3D::mapping(unsigned int a, unsigned int b) {
    vector<_vertex2f> aux_points(points.size());
    float var = 1.0 / a;
    vector<float> dist(b);
    float suma = 0.0;
    dist[0] = suma;

    for (unsigned int i = 1; i < b; ++i) {
        suma += sqrt(pow(points[i].x - points[i - 1].x,2) + pow(points[i].y - points[i - 1].y,2));
        dist[i] = suma;
    }

    for (unsigned int i = 0; i < b; ++i) {
        dist[i] /= suma;
    }

    for (unsigned int i = 0; i < a + 1; ++i) {
        for (unsigned int j = 0; j < b; ++j) {
            aux_points[i * b + j].s = 1 - i * var;
            aux_points[i * b + j].t = 1 - dist[j];
        }
    }

    map.clear();
    map = aux_points;
}

void Object3D::calculateNormalTriangles() {
    vector<_vertex3f> v_aux(triangles.size());

    _vertex3f P, Q, N;

    for(unsigned int i=0; i<v_aux.size(); i++) {
        P = points[triangles[i]._1] - points[triangles[i]._0];

        Q = points[triangles[i]._2] - points[triangles[i]._0];

        N.x = P.y*Q.z - P.z*Q.y;
        N.y = P.z*Q.x - P.x*Q.z;
        N.z = P.x*Q.y - P.y*Q.x;

        N.normalize();
        v_aux[i] = N;
    }
    normalTriangles = v_aux;
}

void Object3D::calculateNormalPoints() {
    vector<_vertex3f> v_aux(points.size());

    vector<int> num_triangulos(points.size(),0);
    unsigned int id0, id1, id2;

    for(unsigned int i=0; i<triangles.size(); i++) {
        id0 = triangles[i]._0;
        id1 = triangles[i]._1;
        id2 = triangles[i]._2;

        v_aux[id0] += normalTriangles[i];
        num_triangulos[id0]++;

        v_aux[id1] += normalTriangles[i];
        num_triangulos[id1]++;

        v_aux[id2] += normalTriangles[i];
        num_triangulos[id2]++;
    }

    for(unsigned int i = 0; i < v_aux.size(); ++i) {
        v_aux[i] /= num_triangulos[i];
        v_aux[i].normalize();
    }

    normalPoints = v_aux;
}

void Object3D::initMaterial() {
    material = new Material();
}

bool Object3D::gotMaterial() {
    return material != nullptr;
}

void Object3D::changeMaterial(Materials mat) {
    switch (mat) {
        case EMERALD:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0215, 0.1745, 0.0215, 1.0));
            material->setDiffuse(_vertex4f(0.07568, 0.61424, 0.07568, 1.0));
            material->setSpecular(_vertex4f(0.633, 0.727811, 0.633, 1.0));
            material->setBrightness(0.6 * 128);
            break;

        case JADE:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.135, 0.2225, 0.1575, 1.0));
            material->setDiffuse(_vertex4f(0.54, 0.89, 0.63, 1.0));
            material->setSpecular(_vertex4f(0.316228, 0.316228, 0.316228, 1.0));
            material->setBrightness(0.1 * 128);
            break;

        case OBSIDIAN:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.05375, 0.05, 0.06625, 1.0));
            material->setDiffuse(_vertex4f(0.18275, 0.17, 0.22525, 1.0));
            material->setSpecular(_vertex4f(0.332741, 0.328634, 0.346435, 1.0));
            material->setBrightness(0.3 * 128);
            break;

        case PEARL:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0215, 0.1745, 0.0215, 1.0));
            material->setDiffuse(_vertex4f(0.07568, 0.61424, 0.07568, 1.0));
            material->setSpecular(_vertex4f(0.633, 0.727811, 0.633, 1.0));
            material->setBrightness(0.088 * 128);
            break;

        case RUBY:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.25,	0.20725,	0.20725, 1.0));
            material->setDiffuse(_vertex4f(1.0,	0.829,	0.829, 1.0));
            material->setSpecular(_vertex4f(0.296648,	0.296648,	0.296648, 1.0));
            material->setBrightness(0.6 * 128);
            break;

        case TURQUOISE:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.1,	0.18725,	0.1745, 1.0));
            material->setDiffuse(_vertex4f(0.396,	0.74151,	0.69102, 1.0));
            material->setSpecular(_vertex4f(0.297254,	0.30829,	0.306678, 1.0));
            material->setBrightness(0.1 * 128);
            break;

        case BRASS:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.329412,	0.223529,	0.027451, 1.0));
            material->setDiffuse(_vertex4f(0.780392,	0.568627,	0.113725, 1.0));
            material->setSpecular(_vertex4f(0.992157,	0.941176,	0.807843, 1.0));
            material->setBrightness(0.21794872 * 128);
            break;

        case BRONCE:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.2125,	0.1275,	0.054, 1.0));
            material->setDiffuse(_vertex4f(0.714,	0.4284,	0.18144, 1.0));
            material->setSpecular(_vertex4f(0.393548,	0.271906,	0.166721, 1.0));
            material->setBrightness(0.2 * 128);
            break;

        case CHROME:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.25,	0.25,	0.25, 1.0));
            material->setDiffuse(_vertex4f(0.4,	0.4,	0.4, 1.0));
            material->setSpecular(_vertex4f(0.774597,	0.774597,	0.774597, 1.0));
            material->setBrightness(0.6 * 128);
            break;

        case COPPER:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.19125,	0.0735,	0.0225, 1.0));
            material->setDiffuse(_vertex4f(0.7038,	0.27048,	0.0828, 1.0));
            material->setSpecular(_vertex4f(0.256777,	0.137622,	0.086014, 1.0));
            material->setBrightness(0.1 * 128);
            break;

        case GOLD:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.24725, 0.1995, 0.0745, 1.0));
            material->setDiffuse(_vertex4f(0.75164, 0.60648, 0.22648, 1.0));
            material->setSpecular(_vertex4f(0.628281, 0.555802, 0.366065, 1.0));
            material->setBrightness(0.4 * 128);
            break;

        case SILVER:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.19225,	0.19225,	0.19225, 1.0));
            material->setDiffuse(_vertex4f(0.50754,	0.50754,	0.50754, 1.0));
            material->setSpecular(_vertex4f(0.508273,	0.508273,	0.508273, 1.0));
            material->setBrightness(0.4 * 128);
            break;

        case BLACK_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.0,	0.0, 1.0));
            material->setDiffuse(_vertex4f(0.01,	0.01,	0.01, 1.0));
            material->setSpecular(_vertex4f(0.50,	0.50,	0.50, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case CYAN_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.1,	0.06, 1.0));
            material->setDiffuse(_vertex4f(0.0,	0.50980392,	0.50980392, 1.0));
            material->setSpecular(_vertex4f(0.50196078,	0.50196078,	0.50196078, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case GREEN_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.0,	0.0, 1.0));
            material->setDiffuse(_vertex4f(0.1,	0.35,	0.1, 1.0));
            material->setSpecular(_vertex4f(0.45,	0.55,	0.45, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case RED_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.0,	0.0, 1.0));
            material->setDiffuse(_vertex4f(0.5,	0.0,	0.0, 1.0));
            material->setSpecular(_vertex4f(0.7,	0.6,	0.6, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case WHITE_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.0,	0.0, 1.0));
            material->setDiffuse(_vertex4f(0.55,	0.55,	0.55, 1.0));
            material->setSpecular(_vertex4f(0.70,	0.70,	0.70, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case YELLOW_PLASTIC:
            delete material;
            initMaterial();
            material->setAmbient(_vertex4f(0.0,	0.0,	0.0, 1.0));
            material->setDiffuse(_vertex4f(0.5,	0.5,	0.0, 1.0));
            material->setSpecular(_vertex4f(0.60,	0.60,	0.50, 1.0));
            material->setBrightness(0.25 * 128);
            break;

        case NULL_MATERIAL:
            delete material;
            break;
    }
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


void Revolution3DObject::generateByRevolutionWithTexture() {
    float rotationAngle = 2 * PI / steps;
    unsigned int counter = points.size();
    unsigned int num_points = counter * (steps + 1);
    vector<_vertex3f> aux_points(num_points);

    for (unsigned int i = 0; i < points.size(); ++i) {
        aux_points[i] = points[i];
    }

    for (unsigned int i = 1; i < steps + 1; ++i) {
        for (unsigned int j = 0; j < counter; ++j) {
            aux_points[i * counter + j] = rotate_Y(points[j], rotationAngle);
        }
    }

    points.clear();
    points = aux_points;

    unsigned int index;
    unsigned int vi = 0;
    unsigned int num_triangles = 2 * steps * (counter-1);
    vector<_vertex3i> aux_triangles(num_triangles);

    for (unsigned int i = 0; i< (counter - 1); ++i) {
        for (unsigned int j = 0; j < steps; ++j) {
            index = counter * j + i;

            aux_triangles[vi]._0 = (index + 1) % num_points;
            aux_triangles[vi]._1 = (index + counter) % num_points;
            aux_triangles[vi]._2 = index % num_points;

            aux_triangles[vi + 1]._0 = (index + 1) % num_points;
            aux_triangles[vi + 1]._1 = (index + counter + 1) % num_points;
            aux_triangles[vi + 1]._2 = (index + counter) % num_points;
            vi += 2;
        }
    }

    triangles.clear();
    triangles = aux_triangles;

    //***** 3. COORDS. TEXTURA *********************************************
    mapping(steps , counter);
}

void Revolution3DObject::regenerate() {
    this->generateByRevolution('y', false);
}

ALLFIGURE::ALLFIGURE() {
}

void ALLFIGURE::createCube() {
    points.clear();
    triangles.clear();

    points = {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},
              {0.5,0.5,0.5},{-0.5,0.5,0.5},
              {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},
              {0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    triangles = {{0,1,2},{2,3,0},{1,5,6},{6,2,1},
                 {7,6,5},{5,4,7},{4,0,3},{3,7,4},
                 {4,5,1},{1,0,4},{3,2,6},{6,7,3}};
}

void ALLFIGURE::createTetrahedron() {
    points.clear();
    triangles.clear();
    points = {{0,1,0},{-1,-1,-1},{1,-1,-1},{0,-1,1}};
    triangles = {{1,0,2},{2,0,3},{0,1,3},{1,2,3}};
}

void ALLFIGURE::createPly_Static(const string &filename) {
    points.clear();
    triangles.clear();
    readPly(filename);
}

void ALLFIGURE::createPly_Revolution(const string &filename) {
    points.clear();
    triangles.clear();
    profile.clear();
    readPly(filename);
    setProfile(getVectorPoints());
    generateByRevolution('y', false);
}

void ALLFIGURE::createCylinder() {
    points.clear();
    triangles.clear();
    profile.clear();
    profile = {{0,-1,0},{1,-1,0},{1,1,0},{0,1,0}};
    generateByRevolution('y', false);
}

void ALLFIGURE::createGlass() {
    points.clear();
    triangles.clear();
    profile.clear();
    profile = {{0,-1,0},{0.5,-1,0},{1,1,0}};
    generateByRevolution('y', false);
}

void ALLFIGURE::createGlass_Inverted() {
    points.clear();
    triangles.clear();
    profile.clear();
    profile = {{0.5,-1,0},{1,1,0},{0,1,0}};
    generateByRevolution('y', false);
}

void ALLFIGURE::createCone() {
    points.clear();
    triangles.clear();
    profile.clear();
    profile = {{0,-1,0},{0.5,-1,0},{0,1,0}};
    generateByRevolution('y', false);
}

void ALLFIGURE::createTube() {
    points.clear();
    triangles.clear();
    profile.clear();
    profile = {{0.5,-1,0},{0.5,1,0}};
    generateByRevolution('y', false);
}

void ALLFIGURE::createSphere() {
    readPly("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/sphere.ply");
}

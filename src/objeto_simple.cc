#include <GL/glew.h>
#include <vector>
#include <math.h>
#include "objeto_simple.h"
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
#ifndef __TYPES__
#define __TYPES__

#include <GL/glut.h>

enum ViewMode {
    MESH,
    EDGES,
    SOLID,
    CHESS,
    FLAT,
    SMOOTH,
    NULL_
};

enum TypeObject {
    CUBE,
    TETRAHEDRON,
    PLY_STATIC,
    PLY_REVOLUTION,
    CYLINDER,
    GLASS,
    GLASS_INVERTED,
    CONE,
    TUBE,
    SPHERE,
    WATT,
    _NULL
};

enum Materials {
    EMERALD,
    JADE,
    OBSIDIAN,
    PEARL,
    RUBY,
    TURQUOISE,
    BRASS,
    BRONCE,
    CHROME,
    COPPER,
    GOLD,
    SILVER,
    BLACK_PLASTIC,
    CYAN_PLASTIC,
    GREEN_PLASTIC,
    RED_PLASTIC,
    WHITE_PLASTIC,
    YELLOW_PLASTIC,
    NULL_MATERIAL
};

enum MaterialManagemement {
    ADD,
    SUBTRACT
};

enum CameraType {
    PERSPECTIVE,
    ORTHOGONAL
};

struct ColorRGB {
    GLint r;
    GLint g;
    GLint b;
};

struct CameraPosition3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct CameraPosition6 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat t;
    GLfloat u;
    GLfloat v;
};

struct CoordenadasIMG {
    float X_00;
    float Y_00;
    float X_01;
    float Y_01;
    float X_10;
    float Y_10;
    float X_11;
    float Y_11;

    float thicc;
};

struct DrawMode {
    bool mesh = false;
    bool edges = false;
    bool solid = false;
    bool chess = false;
    bool flat = false;
    bool smooth = false;

    void allFalse() {
        mesh = false;
        edges = false;
        solid = false;
        chess = false;
        flat = false;
        smooth = false;
    }
};

#endif

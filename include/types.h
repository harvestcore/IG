#ifndef __TYPES__
#define __TYPES__

enum ViewMode {
    MESH,
    EDGES,
    SOLID,
    CHESS,
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
    TEST,
    _NULL
};

enum Transformations {
    SCALE,
    ROTATION,
    TRANSLATION
};

#endif

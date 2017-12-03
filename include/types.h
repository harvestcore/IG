#ifndef __TYPES__
#define __TYPES__

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

#endif

//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: manageView.cc
//
//####################################################

#include "manageView.h"

ViewMode currentMode(ViewMode actual, ViewMode nuevo) {
    if (actual == NULL_)
        actual = nuevo;
    else if (actual == nuevo)
        actual = NULL_;
    else if (actual != nuevo)
        actual = nuevo;

    return actual;
}

ALLFIGURE* changeObject(ALLFIGURE* oldObject, ALLFIGURE* newObject) {
    if (oldObject == nullptr)
        oldObject = newObject;
    else if (oldObject == newObject)
        oldObject = nullptr;
    else if (oldObject != newObject)
        oldObject = newObject;

    return oldObject;
}

TypeObject changeCurrentObject(TypeObject oldObject, TypeObject newObject) {
    if (oldObject == _NULL)
        oldObject = newObject;
    else if (oldObject == newObject)
        oldObject = _NULL;
    else if (oldObject != newObject)
        oldObject = newObject;

    return oldObject;
}

string objectToString(TypeObject obj) {
    switch (obj) {
        case CUBE:
        return "Cubo";
        case TETRAHEDRON:
        return "Tetraedro";
        case PLY_STATIC:
        return "Beethoven";
        case PLY_REVOLUTION:
        return "Peon";
        case CYLINDER:
        return "Cilindro";
        case GLASS:
        return "Vaso";
        case GLASS_INVERTED:
        return "Vaso Inv";
        case CONE:
        return "Cono";
        case TUBE:
        return "Tubo";
        case SPHERE:
        return "Esfera";
        case WATT:
        return "Watt";
        case _NULL:
        return "Off";
    }
}


string modotoString(ViewMode mode) {
    switch (mode) {
        case MESH:
        return "Puntos";
        case EDGES:
        return "Lineas";
        case SOLID:
        return "Solido";
        case CHESS:
        return "Ajedrez";
        case FLAT:
        return "Flat";
        case SMOOTH:
        return "Smooth";
        case NULL_:
        return "Off";
    }
}

string booltostring(bool bts) {
    if (bts)
        return "On";
    else
        return "Off";
}

string materialIDtostring(int mat) {
    switch (mat) {
        case 0:
            return "Off";
        case 1:
            return "EMERALD";
        case 2:
            return "JADE";
        case 3:
            return "OBSIDIAN";
        case 4:
            return "PEARL";
        case 5:
            return "RUBY";
        case 6:
            return "TURQUOISE";
        case 7:
            return "BRASS";
        case 8:
            return "BRONCE";
        case 9:
            return "CHROME";
        case 10:
            return "COPPER";
        case 11:
            return "GOLD";
        case 12:
            return "SILVER";
        case 13:
            return "BLACK_PLASTIC";
        case 14:
            return "CYAN_PLASTIC";
        case 15:
            return "GREEN_PLASTIC";
        case 16:
            return "RED_PLASTIC";
        case 17:
            return "WHITE_PLASTIC";
        case 18:
            return "YELLOW_PLASTIC";
    }
}

string unsignedtostring(unsigned int num) {
    if (num == 0)
        return "" + 0;
    else
        return "" + (int) num;
}

string cameratypetostring(CameraType type) {
    if (type == ORTHOGONAL)
        return "ORTHOGONAL";
    if (type == PERSPECTIVE)
        return "PERSPECTIVE";
}
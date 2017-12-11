//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: manageView.h
//
//####################################################

#ifndef __MANAGE__VIEW__H__
#define	__MANAGE__VIEW__H__

#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <string>
#include "3DObject.h"
#include "vertex.h"
#include "models.h"
#include "objects.h"
#include "types.h"
#include "plank.h"
#include "wattRegulator.h"

//  Maneja el modo de visión y el objeto actual.
ViewMode currentMode(ViewMode actual, ViewMode nuevo);
TypeObject changeObject(TypeObject oldObject, TypeObject newObject);

//  Texto en pantalla.
string objectToString(TypeObject obj);
string modotoString(ViewMode mode);
string booltostring(bool bts);
string materialIDtostring(int mat);

#endif

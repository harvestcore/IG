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
#include "3DObject.h"
#include "vertex.h"
#include "models.h"
#include "types.h"

vector<ViewMode> changeMode(vector<ViewMode> oldMode, ViewMode newMode, int  i);
TypeObject changeObject(TypeObject oldObject, TypeObject newObject);
void drawModels(Models mods, TypeObject object, vector<ViewMode> mode);

#endif

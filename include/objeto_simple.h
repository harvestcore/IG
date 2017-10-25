#ifndef __OBJETO__SIMPLE__H__
#define	__OBJETO__SIMPLE__H__


#include <GL/glut.h>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"

#define PI 3.1415927

using namespace std;

/**
*   Clase para crear y mostrar objetos 3D sencillos usando puntos.
*/
class Simple3DObject {
	protected:
		/**
		*	Almacena los puntos de un objeto 3D sencillo.
		*/
        vector<_vertex3f> points;

	public:
		/**
		*	Constructor por defecto de la clase. Hace un clear del vector de puntos.
		*/
        Simple3DObject();

        /**
		*	Constructor de clase. Crea un objeto a partir de un vector
		*	de puntos que se le pasa como argumento.
		*/
        Simple3DObject (vector<_vertex3f> toConstruct);

        /**
		*	Constructor de copia de la clase.
		*/
        Simple3DObject (const Simple3DObject &otherObject);

        /**
		*	Añade un punto al objeto.
		*/
        void addSinglePoint(_vertex3f toAdd);

        /**
		*	Añade un conjunto de puntos, pasados como argumento, al objeto.
		*/
        void addPoints(vector<_vertex3f> toAdd);

        /**
		*	Devuelve un punto situado en una posición del vector.
		*/
        _vertex3f getPoint(int position) const;

        /**
        *   Devuelve el vector de puntos.
        */
        vector<_vertex3f> getVectorPoints() const;

        /**
		*	Devuelve el número de puntos que tiene el objeto.
		*/
        int sizeMesh() const;

        /**
		*	Dibuja la malla de puntos que forma el objeto.
		*/
        void drawMesh();
};

#endif

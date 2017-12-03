//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//	GII - ETSIIT
//
//  file: 3DObject.h
//
//####################################################

#ifndef __3D__OBJECT__H__
#define	__3D__OBJECT__H__

#include <GL/glut.h>
#include <vector>
#include <utility>
#include <math.h>
#include "vertex.h"
#include "file_ply_stl.h"
#include "material.h"
#include "types.h"

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

/**
*   Clase para crear y mostrar objetos 3D usando puntos y polígonos.
*/
class Object3D: public Simple3DObject {
	protected:
        vector<_vertex3i> triangles;
        vector<_vertex3f> normalTriangles;
        vector<_vertex3f> normalPoints;
        vector<_vertex2f> map;

	public:
        Material *material;

		/**
		*	Constructor por defecto de la clase. Hace un clear del vector de triángulos.
		*/
        Object3D();

		/**
		*	Constructor de clase. Crea un objeto a partir de un vector de triángulos y
		*	otro de puntos.
		*/
        Object3D(vector<_vertex3i> newTriangles, vector<_vertex3f> newMesh);

		/**
		*	Constructor de clase. Crea un objeto a partir de un vector de triángulos y
		*	un objeto 3D sencillo.
		*/
        Object3D(vector<_vertex3i> newTriangles, Simple3DObject newMesh);

		/**
		*	Constructor de copia de la clase.
		*/
        Object3D(const Object3D &otherObject);

		/**
		*	Añade un triángulo al objeto.
		*/
        void addSingleTriangle(_vertex3i toAdd);

		/**
		*	Añade un conjunto de triángulos, pasados como argumento, al objeto.
		*/
        void addTriangles(vector<_vertex3i> toAdd);

		/**
		*	Devuelve un triángulo situado en una posición del vector.
		*/
        _vertex3i getTriangle(int position) const;

        /**
        *   Devuelve el vector de triángulos.
        */
        vector<_vertex3i> getVectorTriangles() const;

		/**
		*	Devuelve el número de triángulos que tiene el objeto.
		*/
        int sizeTriangles() const;

		/**
		*	Dibuja las aristas que forman el objeto.
		*/
        void drawEdges();

		/**
		*	Dibuja el sólido (conjunto de todos los triángulos) que forman
		*	el objeto.
		*/
        void drawSolid();

		/**
		*	Dibuja el modelado ajedrez del objeto.
		*/
        void drawChess();

        void drawFlatSmoothing();
        void drawGouraudSmoothing();

        void mapping(unsigned int a, unsigned int b);
        void calculateNormalTriangles();
        void calculateNormalPoints();
        void initMaterial();
        bool gotMaterial();
        void changeMaterial(Materials mat);

};

/**
*   Clase para crear y mostrar objetos 3D a partir de archivos .ply.
*/
class PlyObject: public Object3D {
    protected:

    public:

        /**
        *   Constructor de la clase.
        */
        PlyObject();

        /**
        *   Constructor con parámetros.
        */
        PlyObject(const string &filename);

        /**
        *   Función para leer un archivo ply y cargar los puntos y triángulos
        *   a los vectores.
        */
        void readPly(const string &filename);
};

/**
*   Clase para crear y mostrar objetos 3D de revolución.
*/
class Revolution3DObject: public PlyObject {
    protected:

        /**
        *   Divisiones del objeto.
        */
        int steps = 30;

        /**
        *   Perfil del objeto, nunca se modifica.
        */
        vector<_vertex3f> profile;

        double angulo_inicio = 0.0;
        double angulo_final = 0.0;

	public:

        /**
        *   Constructor de la clase.
        */
        Revolution3DObject();

        /**
        *   Constructor con parámetros.
        */
        Revolution3DObject(vector<_vertex3f> newProfile, int newSteps);

        /**
		*   Funciones para rotar un punto sobre los ejes.
		*/
		_vertex3f rotate_X(_vertex3f point, double angle);
		_vertex3f rotate_Y(_vertex3f point, double angle);
		_vertex3f rotate_Z(_vertex3f point, double angle);

        /**
        *   Funciones set y get.
        */
        void setProfile(vector<_vertex3f> newProfile);
        vector<_vertex3f> getProfile() const;
        void setSteps(int newSteps);
        int getSteps() const;

        void setAnguloInicio(double newAngulo_inicio);
        void setAnguloFinal(double newAngulo_final);

        /**
        *   Aumenta las diviones del objeto.
        */
        void moreSteps();

        /**
        *   Disminuye las diviones del objeto.
        */
        void lessSteps();

        /**
        *   Revoluciona el perfil tantas veces como steps indique.
        */
        void generateByRevolution(char axis, bool addCovers);

        /**
        *   Solo eje y.
        */
        void generateByRevolutionWithTexture();

        void regenerate();
};

class ALLFIGURE: public Revolution3DObject {
    private:
    public:
        ALLFIGURE();
        void createCube();
        void createTetrahedron();
        void createPly_Static(const string &filename);
        void createPly_Revolution(const string &filename);
        void createCylinder();
        void createGlass();
        void createGlass_Inverted();
        void createCone();
        void createTube();
        void createSphere();

};

#endif

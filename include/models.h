//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: models.h
//
//  Contiene clases con todos los objetos necesarios
//  para la práctica:
//      -   Cubo
//      -   Tetraedro
//      -   Ply Estático
//      -   Ply Revolución
//      -   Cilindro
//      -   Vaso
//      -   Vaso invertido
//      -   Cono
//      -   Tubo
//
//####################################################

#ifndef __MODELS__H__
#define	__MODELS__H__

#include <GL/glut.h>
#include "3DObject.h"
#include "vertex.h"
#include "types.h"
#include "file_ply_stl.h"

using namespace std;

/**
*   Encapsula todos los objetos estáticos y añade un lado para crearlos según
*   tamaño deseado.
*/
class StaticModel : public Object3D{
    protected:
        GLfloat side;
    public:
        StaticModel();
        StaticModel(double newSide);
        void setSide(double newSide);
        double getSide() const;
};

/**
*   Encapsula todos los objetos de recolución y añade una altura y radios para
*   crear objetos según deseemos.
*/
class RevolutionModel : public Revolution3DObject{
    protected:
        GLfloat height;
        GLfloat topRadius;
        GLfloat bottomRadius;
    public:
        RevolutionModel();
        RevolutionModel(double newTopRadius, double newBottomRadius, double newHeight);
        void setTopRadius(double newTopRadius);
        void setBottomRadius(double newBottomRadius);
        void setHeight(double newHeight);
        double getTopRadius() const;
        double getBottomRadius() const;
        double getHeight() const;
};

/**
*   Clase para crear cubos.
*/
class Cube : public StaticModel {
	private:
	public:
		Cube();
        Cube(double newSide);
        void createCube();
};

/**
*   Clase para crear tetraedros.
*/
class Tetrahedron : public StaticModel {
	private:
	public:
		Tetrahedron();
        Tetrahedron(double newSide);
        void createTetrahedron();
};

/**
*   Clase para crear ply estáticos.
*/
class Ply_Static: public PlyObject {
    private:
    public:
        Ply_Static();
        Ply_Static(const string &filename);
        void createPly_Static(const string &filename);
};

/**
*   Clase para crear ply de revolución.
*/
class Ply_Revolution: public RevolutionModel {
    private:
    public:
        Ply_Revolution();
        Ply_Revolution(const string &filename);
        void createPly_Revolution(const string &filename);
};

/**
*   Clase para crear cilindros.
*/
class Cylinder: public RevolutionModel {
    private:
    public:
        Cylinder();
        Cylinder(double radius, double height);
        void createCylinder();
};


/**
*   Clase para crear vasos.
*/
class Glass: public RevolutionModel {
    private:
    public:
        Glass();
        Glass(double newTopRadius, double newBottomRadius, double newHeight);
        void createGlass();
};

/**
*   Clase para crear vasos invertidos.
*/
class Glass_Inverted: public RevolutionModel {
    private:
    public:
        Glass_Inverted();
        Glass_Inverted(double newTopRadius, double newBottomRadius, double newHeight);
        void createGlass_Inverted();
};

/**
*   Clase para crear conos.
*/
class Cone: public RevolutionModel {
    private:
    public:
        Cone();
        Cone(double radius, double height);
        void createCone();
};

/**
*   Clase para crear tubos.
*/
class Tube: public RevolutionModel {
    private:
    public:
        Tube();
        Tube(double radius, double height);
        void createTube();
};

class Sphere: public Revolution3DObject {
    private:
    public:
        Sphere();
        Sphere(double radius);
};

#endif

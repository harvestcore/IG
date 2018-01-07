Práctica 5

Lista de modificaciones respecto a la práctica 4:

    Se han añadido los siguientes archivos:
        camera.h
        camera.cc

    Cámaras:
        Los archivos anteriores encapsulan una cámara y permiten trabajar con ella en diferentes modos de visualización (GL_PERSPECTIVE, GL_ORTHOGONAL)
        Se ha sustituído la cámara original del programa por una instancia de esta nueva clase "Camera".
        En modo selección de objetos se crea una segunda cámara que permite orbitar al objeto seleccionado.

    Botones (glut):
        Se han añadido los botones necesarios (generados con glut) para realizar las acciones necesarias.

    Menú:
        He añadido un menú secundario accionado con el ratón que permite realizar casi (no todas) las mismas acciones que los botones.
        Se activa con el botón derecho del ratón.
        Está programado con glut.

    Mouse:
        Se puede controlar la cámara y el zoom con el ratón. Funciona tanto en modo perspectiva como en ortogonal.
        Mantener click izquierdo para mover la cámara.
        Rueda del ratón para aumentar o disminuir el zoom.
        Mantener pulsado el botón de la rueda del ratón para mover la luz 1 (tiene que estar activada).

    Selección:
        He implementado la selección de OpenGL.
        Para probar el funcionamiento: Modo selección (se muestran 9 objetos que podemose seleccionar).
        Además he implementado una selección por color, que permite añadir y eliminar objetos. Se encuentra desactivada pues no era objetivo de la práctica.


SETUP BÁSICO PARA VER EL FUNCIONAMIENTO.

Modo objetos:
    Este modo sirve para visualizar los objetos (podría decirse que es un "modo prácticas 1-4").
    1- Iniciar el programa.
    2- Seleccionar el modo "Objetos".
    3- Seleccionar una figura (cubo, esfera, ...)
    4- Seleccionar un modo de visualización (puntos, sólido, flat, ...)

Modo selección:
    Este modo sirve para probar la funcionalidad de la selección (podría decirse que es un "modo práctica 5").
    1- Iniciar el programa.
    2- Seleccionar el modo "Seleccion".
    3- Seleccionar una figura (cubo, esfera, ...)
    4- Seleccionar un modo de visualización (puntos, sólido, flat, ...)
    5- Seleccionar un objeto de los que se muestran en pantalla.


Otras funcionalidades/aclaraciones del programa:
    Importante:
        El botón "Proyec" sirve para cambiar el tipo de proyección de las cámaras. Por defecto se muestra en perspectiva. Este boton cambia de perspectiva a ortogonal y viceversa.
        Casi todas las acciones descritas abajo se puedes realizar tanto con los botones de la segunda ventana como con el menú desplegable secundario (click derecho del ratón).

    Para ver correctamente una figura en modo de visualización flat o smooth tienes que activar como mínimo una luz.
    La luz en el infinito se puede mover, pero no se puede acercar o alejar. La otra luz sí puede acercarse/alejarse, además de moverse.
    Si estas visualizando una figura de revolución (ply rev, cono, esfera, ...) puedes aumentar o disminuir el número de divisiones de la figura.
    En modo de visualización flat o smooth puedes cambiar el material de la figura con los botones.
    Si deseas ver el tablero, pulsa el botón "Tablero", y si además quieres aplicarle una textura pulsa en el botón "Img".
    Puedes cambiar el alto y ancho del tablero con los botones "++W / --W / ++H / --H".
    El botón "Leer Tab" te permite introducir las coordenadas de la zona del tablero donde se mostrará la textura.
    El botón "Leer Tex" te permite introducir las coordenadas de la textura que se mostraran en el tablero.
    El botón "Spin" te permite activar la animacion del Watt, es decir, que gire.
    Los botones "++V / --V" te permiten cambiar la velocidad de giro del Watt.
    En la parte superior izquierda de la ventana principal se muestra información actual de lo que se encuentra en pantalla.
    En el botón "Help" puedes ver rápidamente los controles básicos.


Resumen de los archivos que componen la práctica:

    3DObject:
        Contiene 5 clases en su interior:
            Simple3DObject: Clase para crear y mostrar objetos 3D sencillos usando puntos.
            Object3D: Clase para crear y mostrar objetos 3D usando puntos y polígonos.
            PlyObject: Clase para crear y mostrar objetos 3D a partir de archivos .ply.
            Revolution3DObject: Clase para crear y mostrar objetos 3D de revolución.
            ALLFIGURE: Permite crear las figuras básicas.

    button:
        Usado para crear los botones de la segunda ventana.
        Creado por Glenn G. Chappell.

    CImg:
        Se usa para cargar imágenes/texturas.
        Creado por David Tschumperle.

    Camera:
        Encapsula una cámara y permite trabajar con ella.

    file_ply_stl:
        Permite cargar archivos .ply
        Creado por Domingo Martín Perandrés.

    fps:
        Permite añadir un contador de fps.

    light:
        Encapsula una luz y permite trabajar con ella.

    manageView:
        Pequeño cajón de sastre. Contiene funciones varias que he necesitado en el programa.

    material:
        Encapsula un material y permite trabajar con él.

    models:
        Contiene clases para crear todos los tipos de figuras (cubo, tetraedro, esfera...)

    objects:
        Contiene una clase "Models" que tiene en su interior un objeto de cada tipo.

    plank:
        Encapsula un tablero y permite trabajar con él.

    texture:
        Encapsula una textura y permite trabajar con ella.

    vertex:
        Contiene los tipos básicos usados en toda la estructura de la práctica.
        Creado por Domingo Martín Perandrés.

    wattRegulator:
        Crea y encapsula un regulador de Watt.


COMPILACIÓN Y EJECUCIÓN:
    Ejecutar "make" en el directorio principal del programa.
    En caso de error instalar lo siguiente (necesario para cargar las texturas):
        sudo apt-get install magic
        sudo apt-get install imagemagick
    
    Para ejecutar: ./bin/main

    
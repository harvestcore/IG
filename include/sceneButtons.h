//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: scenaButtons.h
//
//####################################################


#include "button.h"
#include <vector>

class sceneButtons {
    private:
        Button mesh, lines, solid, chess, masDiv, menosDiv, masVel, menosVel, spin;
        Button cubo, tetraedro, ply_estatico, ply_revolucion, cilindro, vaso, vaso_invertido, cono, tubo, esfera, watt;
        Button flecha_up, flecha_down, flecha_left, flecha_right;
        Button zoom_in, zoom_out;
        Button exit;

        void generateButtons_models();
        void generateButtons_zoom();
        void generateButtons_arrows();
        void generateButtons_viewModes();

        void exit_program();

        void toggle_cube();
        void toggle_tetrahedron();
        void toggle_ply_static();
        void toggle_ply_revolution();
        void toggle_cylinder();
        void toggle_glass();
        void toggle_glass_inverted();
        void toggle_cone();
        void toggle_tube();
        void toggle_sphere();
        void toggle_watt();

        void toggle_zoom_in();
        void toggle_zoom_out();

        void toggle_up();
        void toggle_down();
        void toggle_left();
        void toggle_right();

        void toggle_mesh();
        void toggle_edges();
        void toggle_solid();
        void toggle_chess();
        void toggle_masDiv();
        void toggle_menosDiv();
        void toggle_masVel();
        void toggle_menosVel();
        void toggle_spin();

        bool buttons_generated = false;

    public:
        sceneButtons();
        void generateButtons();
        void draw_buttons();
        void handle_motion(int x, int y);
        void handle_mouse(int button, int state, int x, int y);
        bool getButtonsGenerated();
        void setButtonsGenerated(bool set);
};

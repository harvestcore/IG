//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: sceneButtons.cc
//
//####################################################

#include "sceneButtons.h"

sceneButtons::sceneButtons() {
}

void sceneButtons::generateButtons_models() {
    cubo.setpos(-0.95,0.80);
	cubo.setsize(0.4,0.15);
	cubo.setlabel("Cubo");
	cubo.setaction(toggle_cube);
	cubo.setactive(true);

	tetraedro.setpos(-0.95,0.6);
	tetraedro.setsize(0.4,0.15);
	tetraedro.setlabel("Tetraedro");
	tetraedro.setaction(toggle_tetrahedron);
	tetraedro.setactive(true);

	ply_estatico.setpos(-0.95,0.4);
	ply_estatico.setsize(0.4,0.15);
	ply_estatico.setlabel("Ply Est");
	ply_estatico.setaction(toggle_ply_static);
	ply_estatico.setactive(true);

	ply_revolucion.setpos(-0.95,0.2);
	ply_revolucion.setsize(0.4,0.15);
	ply_revolucion.setlabel("Ply Rev");
	ply_revolucion.setaction(toggle_ply_revolution);
	ply_revolucion.setactive(true);

	cilindro.setpos(-0.95,0);
	cilindro.setsize(0.4,0.15);
	cilindro.setlabel("Cilindro");
	cilindro.setaction(toggle_cylinder);
	cilindro.setactive(true);

	vaso.setpos(-0.95,-0.2);
	vaso.setsize(0.4,0.15);
	vaso.setlabel("Vaso");
	vaso.setaction(toggle_glass);
	vaso.setactive(true);

	vaso_invertido.setpos(-0.95,-0.4);
	vaso_invertido.setsize(0.4,0.15);
	vaso_invertido.setlabel("Vaso Inv");
	vaso_invertido.setaction(toggle_glass_inverted);
	vaso_invertido.setactive(true);

	cono.setpos(-0.95,-0.6);
	cono.setsize(0.4,0.15);
	cono.setlabel("Cono");
	cono.setaction(toggle_cone);
	cono.setactive(true);

	tubo.setpos(-0.95,-0.8);
	tubo.setsize(0.4,0.15);
	tubo.setlabel("Tubo");
	tubo.setaction(toggle_tube);
	tubo.setactive(true);

	esfera.setpos(-0.95,-1);
	esfera.setsize(0.4,0.15);
	esfera.setlabel("Esfera");
	esfera.setaction(toggle_sphere);
	esfera.setactive(true);

	watt.setpos(-0.5,-0.6);
	watt.setsize(0.4,0.15);
	watt.setlabel("Watt");
	watt.setaction(toggle_watt);
	watt.setactive(true);
}

void sceneButtons::generateButtons_zoom() {
    zoom_in.setpos(0.1,-1);
	zoom_in.setsize(0.25,0.15);
	zoom_in.setlabel("++Z");
	zoom_in.setaction(toggle_zoom_in);
	zoom_in.setactive(true);

	zoom_out.setpos(-0.35,-1);
	zoom_out.setsize(0.25,0.15);
	zoom_out.setlabel("--Z");
	zoom_out.setaction(toggle_zoom_out);
	zoom_out.setactive(true);
}

void sceneButtons::generateButtons_arrows() {
    flecha_up.setpos(-0.1,-0.75);
    flecha_up.setsize(0.2,0.15);
    flecha_up.setlabel("^");
    flecha_up.setaction(toggle_up);
    flecha_up.setactive(true);

    flecha_down.setpos(-0.1,-0.90);
    flecha_down.setsize(0.2,0.15);
    flecha_down.setlabel("v");
    flecha_down.setaction(toggle_down);
    flecha_down.setactive(true);

    flecha_left.setpos(-0.3,-0.825);
    flecha_left.setsize(0.2,0.15);
    flecha_left.setlabel("<");
    flecha_left.setaction(toggle_left);
    flecha_left.setactive(true);

    flecha_right.setpos(0.1,-0.825);
    flecha_right.setsize(0.2,0.15);
    flecha_right.setlabel(">");
    flecha_right.setaction(toggle_right);
    flecha_right.setactive(true);
}

void sceneButtons::generateButtons_viewModes() {
    salir.setpos(0.55,-0.95);
	salir.setsize(0.4,0.2);
	salir.setlabel("Salir");
	salir.setaction(exit_program);
	salir.setactive(true);

	mesh.setpos(-0.3,0.6);
	mesh.setsize(0.4,0.2);
	mesh.setlabel("Puntos");
	mesh.setaction(toggle_mesh);
	mesh.setactive(true);

	lines.setpos(0.3,0.6);
	lines.setsize(0.4,0.2);
	lines.setlabel("Lineas");
	lines.setaction(toggle_edges);
	lines.setactive(true);

	solid.setpos(-0.3,0.3);
	solid.setsize(0.4,0.2);
	solid.setlabel("Solido");
	solid.setaction(toggle_solid);
	solid.setactive(true);

	chess.setpos(0.3,0.3);
	chess.setsize(0.4,0.2);
	chess.setlabel("Ajedrez");
	chess.setaction(toggle_chess);
	chess.setactive(true);

	masDiv.setpos(-0.3,0);
	masDiv.setsize(0.4,0.2);
	masDiv.setlabel("++Div");
	masDiv.setaction(toggle_masDiv);
	masDiv.setactive(true);

	menosDiv.setpos(-0.3,-0.3);
	menosDiv.setsize(0.4,0.2);
	menosDiv.setlabel("--Div");
	menosDiv.setaction(toggle_menosDiv);
	menosDiv.setactive(true);

	masVel.setpos(0.3,0);
	masVel.setsize(0.4,0.2);
	masVel.setlabel("++Vel");
	masVel.setaction(toggle_masVel);
	masVel.setactive(true);

	menosVel.setpos(0.3,-0.3);
	menosVel.setsize(0.4,0.2);
	menosVel.setlabel("--Vel");
	menosVel.setaction(toggle_menosVel);
	menosVel.setactive(true);

	spin.setpos(0.3,-0.6);
	spin.setsize(0.4,0.2);
	spin.setlabel("Spin");
	spin.setaction(toggle_spin);
	spin.setactive(true);
}

void sceneButtons::generateButtons() {
    generateButtons_models();
    generateButtons_zoom();
    generateButtons_arrow();
    generateButtons_viewModes();
}

void sceneButtons::exit_program() {
	exit(0);
}

void sceneButtons::toggle_mesh() {
	modos = changeMode(modos, MESH, 0);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_edges() {
	modos = changeMode(modos, EDGES, 1);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_solid() {
	modos = changeMode(modos, SOLID, 2);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_chess() {
	modos = changeMode(modos, CHESS, 3);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_masDiv() {
	sumar = true;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_menosDiv() {
	restar = true;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_masVel() {
	modelos.v_Watt.aumentarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_menosVel() {
	modelos.v_Watt.decrementarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_spin() {
	modelos.v_Watt.toggleSpinning();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

////////////

void sceneButtons::toggle_cube() {
	objeto = changeObject(objeto, CUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_tetrahedron() {
	objeto = changeObject(objeto, TETRAHEDRON);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_ply_static() {
	objeto = changeObject(objeto, PLY_STATIC);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_ply_revolution() {
	objeto = changeObject(objeto, PLY_REVOLUTION);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_cylinder() {
	objeto = changeObject(objeto, CYLINDER);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_glass() {
	objeto = changeObject(objeto, GLASS);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_glass_inverted() {
	objeto = changeObject(objeto, GLASS_INVERTED);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_cone() {
	objeto = changeObject(objeto, CONE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_tube() {
	objeto = changeObject(objeto, TUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_sphere() {
	objeto = changeObject(objeto, SPHERE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_watt() {
	objeto = changeObject(objeto, WATT);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

	/////////////////

void sceneButtons::toggle_up() {
	Observer_angle_x--;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_down() {
	Observer_angle_x++;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_left() {
	Observer_angle_y--;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_right() {
	Observer_angle_y++;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

	////////////////////

void sceneButtons::toggle_zoom_in() {
	Observer_distance/=1.2;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::toggle_zoom_out() {
	Observer_distance*=1.2;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void sceneButtons::draw_buttons() {
	salir.display();
	mesh.display();
	lines.display();
	solid.display();
	chess.display();
	masDiv.display();
	menosDiv.display();
	masVel.display();
	menosVel.display();
	spin.display();

	cubo.display();
	tetraedro.display();
	ply_estatico.display();
	ply_revolucion.display();
	cilindro.display();
	vaso.display();
	vaso_invertido.display();
	cono.display();
	tubo.display();
	esfera.display();
	watt.display();

	flecha_up.display();
	flecha_down.display();
	flecha_left.display();
	flecha_right.display();

	zoom_in.display();
	zoom_out.display();
}

void sceneButtons::handle_motion(int x, int y) {
	salir.handlemotion(x,y);
	mesh.handlemotion(x,y);
	lines.handlemotion(x,y);
	solid.handlemotion(x,y);
	chess.handlemotion(x,y);
	masDiv.handlemotion(x,y);
	menosDiv.handlemotion(x,y);
	masVel.handlemotion(x,y);
	menosVel.handlemotion(x,y);
	spin.handlemotion(x,y);

	cubo.handlemotion(x,y);
	tetraedro.handlemotion(x,y);
	ply_estatico.handlemotion(x,y);
	ply_revolucion.handlemotion(x,y);
	cilindro.handlemotion(x,y);
	vaso.handlemotion(x,y);
	vaso_invertido.handlemotion(x,y);
	cono.handlemotion(x,y);
	tubo.handlemotion(x,y);
	esfera.handlemotion(x,y);
	watt.handlemotion(x,y);

	flecha_up.handlemotion(x,y);
	flecha_down.handlemotion(x,y);
	flecha_left.handlemotion(x,y);
	flecha_right.handlemotion(x,y);

	zoom_in.handlemotion(x,y);
	zoom_out.handlemotion(x,y);
}

void sceneButtons::handle_mouse(int button, int state, int x, int y) {
	salir.handlemouse(button,state,x,y);
	mesh.handlemouse(button,state,x,y);
	lines.handlemouse(button,state,x,y);
	solid.handlemouse(button,state,x,y);
	chess.handlemouse(button,state,x,y);
	masDiv.handlemouse(button,state,x,y);
	menosDiv.handlemouse(button,state,x,y);
	masVel.handlemouse(button,state,x,y);
	menosVel.handlemouse(button,state,x,y);
	spin.handlemouse(button,state,x,y);

	cubo.handlemouse(button,state,x,y);
	tetraedro.handlemouse(button,state,x,y);
	ply_estatico.handlemouse(button,state,x,y);
	ply_revolucion.handlemouse(button,state,x,y);
	cilindro.handlemouse(button,state,x,y);
	vaso.handlemouse(button,state,x,y);
	vaso_invertido.handlemouse(button,state,x,y);
	cono.handlemouse(button,state,x,y);
	tubo.handlemouse(button,state,x,y);
	esfera.handlemouse(button,state,x,y);
	watt.handlemouse(button,state,x,y);

	flecha_up.handlemouse(button,state,x,y);
	flecha_down.handlemouse(button,state,x,y);
	flecha_left.handlemouse(button,state,x,y);
	flecha_right.handlemouse(button,state,x,y);

	zoom_in.handlemouse(button,state,x,y);
	zoom_out.handlemouse(button,state,x,y);
}

bool sceneButtons::getButtonsGenerated() {
    return buttons_generated;
}

void sceneButtons::setButtonsGenerated(bool set) {
    buttons_generated = set;
}

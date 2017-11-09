/*

Anillo::Anillo() {
}

void Anillo::draw() {
    anillo_central.generateByRevolution('y', false);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,8,0);
    glScalef(3,0.8,3);
    anillo_central.drawChess();
    glPopMatrix();

    varilla.generateByRevolution('y', false);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(1,5.8,0);
    glScalef(0.2,4,0.2);
    varilla.drawChess();
    glPopMatrix();
}

Esferas::Esferas() {
}

void Esferas::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-8.5,12,0);
    glScalef(0.009,0.009,0.009);
    esfera.drawChess();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(8.5,12,0);
    glScalef(0.009,0.009,0.009);
    esfera.drawChess();
    glPopMatrix();
}

Soportes::Soportes() {
}

void Soportes::draw() {
    soporte.generateByRevolution('y', false);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,8,0);
    glRotatef(315,0,0,1);
    glTranslatef(1.5,-8,0);     // origen

    glTranslatef(-4.5,8,0);     // sitio
    glRotatef(90,0,0,1);
    glScalef(0.3,4,0.3);
    soporte.drawChess();
    glPopMatrix();

    soporte.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,8,0);
    glRotatef(45,0,0,1);
    glTranslatef(-1.5,-8,0);     // origen

    glTranslatef(4.5,8,0);
    glRotatef(270,0,0,1);
    glScalef(0.3,4,0.3);
    soporte.drawChess();
    glPopMatrix();

    anillo_central.draw();
}

BrazosLaterales::BrazosLaterales() {
}

void BrazosLaterales::draw() {
    brazo.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,12,0);
    glRotatef(0,0,0,1);
    glTranslatef(1.5,-12,0);     // origen

    glTranslatef(-5.5,12,0);
    glRotatef(90,0,0,1);
    glScalef(0.3,8,0.3);
    brazo.drawChess();
    glPopMatrix();

    brazo.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,12,0);
    glRotatef(0,0,0,1);
    glTranslatef(-1.5,-12,0);     // origen


    glTranslatef(5.5,12,0);
    glRotatef(270,0,0,1);
    glScalef(0.3,8,0.3);
    brazo.drawChess();
    glPopMatrix();

    bolas.draw();
    soportes_laterales.draw();
}

Disco::Disco() {
}

void Disco::draw() {
    disco_sup.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,12,0);
    glScalef(3,0.8,3);
    disco_sup.drawChess();
    glPopMatrix();

    laterales.draw();
}

BrazoPrincipal::BrazoPrincipal() {
}

void BrazoPrincipal::draw() {
    brazo.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(0.5,10,0.5);
    brazo.drawChess();
    glPopMatrix();

    disco_sup.draw();
}

WattRegulator::WattRegulator() {
}

void WattRegulator::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(7,2,7);
    //base.drawChess();
    glPopMatrix();

    brazo.draw();
}

*/


/*

class Anillo{
    private:
        Cylinder anillo_central;
        Cylinder varilla;


    public:
        Anillo();
        void draw();
};

class Esferas : public Anillo {
    private:
        Sphere esfera;

    public:
        Esferas();
        void draw();
};

class Soportes : public Esferas {
    private:
        Cylinder soporte;
        Anillo anillo_central;

    public:
        Soportes();
        void draw();
};

class BrazosLaterales : public Soportes {
    private:
        Cylinder brazo;
        Esferas bolas;
        Soportes soportes_laterales;

    public:
        BrazosLaterales();
        void draw();
};

class Disco : public BrazosLaterales {
    private:
        Cylinder disco_sup;
        BrazosLaterales laterales;

    public:
        Disco();
        void draw();
};

class BrazoPrincipal : public Disco {
    private:
        Cylinder brazo;
        Disco disco_sup;

    public:
        BrazoPrincipal();
        void draw();
};

class WattRegulator : public BrazoPrincipal {
    private:
        Cube base;
        BrazoPrincipal brazo;

    public:
        void masAngulo();
        void menosAngulo();

        WattRegulator();
        void draw();
};



*/

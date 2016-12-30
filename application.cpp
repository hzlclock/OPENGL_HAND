#include "application.h"

#include <iostream>
#include <cassert>

using namespace std;

#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>

void draw_grid();

void draw_cube(GLfloat diameter, GLfloat height);

void draw_finger(GLfloat offset,
                 GLfloat firstLength,
                 GLfloat secondLength,
                 GLfloat thirdLength,
                 GLfloat firstDeg,
                 GLfloat secondDeg) {
    glPushMatrix();

    glTranslatef(offset, 0, -2);
    glRotatef(-firstDeg, 1, 0, 0);
    glTranslatef(0, 0, -firstLength / 2);
    glScalef(0.9, 0.5, firstLength);
    glColor3f(0, 1, 1);
    glutSolidCube(1);

    glScalef(1, 2, 1.0f / firstLength);
    glTranslatef(0, 0, -firstLength / 2.0f);
    glRotatef(-secondDeg, 1, 0, 0);
    glTranslatef(0, 0, -secondLength / 2.0f);
    glScalef(1, 0.5, secondLength);
    glColor3f(0, 0.8, 1);
    glutSolidCube(1);

    glScalef(1, 2, 1.0f / secondLength);
    glTranslatef(0, 0, -secondLength / 2.0f);
    glRotatef(-secondDeg / 2.0f, 1, 0, 0);
    glTranslatef(0, 0, -thirdLength / 2.0f);
    glScalef(1, 0.5, thirdLength);
    glColor3f(0, 0.6, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_thumb(GLfloat rootRotate,
                GLfloat rootDeg,
                GLfloat secondDeg) {
    glPushMatrix();
    glTranslatef(2.5, 0, 2);

    glRotatef(-rootRotate, 0, 0, 1);
    glRotatef(-rootDeg, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, -1.0f);
    glScalef(0.9f, 0.5f, 2.0f);
    glutSolidCube(1);

    glScalef(1, 2, 0.5f);
    glTranslatef(0, 0, -1.0f);
    glRotatef(-secondDeg, 1, 0, 0);
    glTranslatef(0, 0, -0.7f);
    glScalef(1, 0.5, 1.4f);
    glutSolidCube(1);
    glPopMatrix();
}

application::application()
        : solid(true) {
}

application::~application() {
}

// triggered once after the OpenGL context is initialized
void application::init_event() {

    cout << "CAMERA CONTROLS: \n  LMB: Rotate \n  MMB: Move \n  RMB: Zoom" << endl;
    cout << "KEYBOARD CONTROLS: \n  '=': Toggle wireframe mode" << endl;

    const GLfloat ambient[] = {0.15, 0.15, 0.15, 1.0};
    const GLfloat diffuse[] = {0.6, 0.6, 0.6, 1.0};
    const GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    // enable a light
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);


    // enable depth-testing, colored materials, and lighting
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // normalize normals so lighting calculations are correct
    // when using GLUT primitives
    glEnable(GL_NORMALIZE);

    // enable smooth shading
    glShadeModel(GL_SMOOTH);

    set_camera_for_box(vec3(-10, -10, -10), vec3(10, 10, 10));

    t.reset();
}

inline void application::begin_RotateAroundTheSun(float speed, float rad, int startPos) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 36; i++) {
        glVertex3f(0 + (rad * cos(i * 6.282 / 36)), 0,
                   0 + (rad * sin(i * 6.282 / 36)));
    }
    glEnd();
    glPushMatrix();

    glTranslatef(rad, 0, 0);
    glRotatef(speed * t.elapsed() * 180 + startPos, 0, 1, 0);


}


inline void application::end_RotateAroundTheSun() {


    glPopMatrix();

}

// triggered each time the application needs to redraw
void application::draw_event() {
    // apply our camera transformation
    apply_gl_transform();

    // set the position of the light
    const GLfloat light_pos1[] = {0.0, 1.0, 0.0, 1};
    const GLfloat light_pos2[] = {-9.0, 7.0, 5.0, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);

    // draws the grid and frame at the origin
    //draw_grid();

    //
    // create some various objects in the world
    //

    /*begin_RotateAroundTheSun(1, 5);
    glColor3f(1, 0, 0);
    glutSolidSphere(1, 20, 20);
    end_RotateAroundTheSun();*/

    //for(int i=0;i<8;i++){
    //
    //    glColor3f(getRed(color[i]), getGreen(color[i]), getBlue(color[i]));
    //    begin_RotateAroundTheSun(speed[i], rad[i]*3, startDeg[i]);
    //    glutSolidSphere(size[i]*0.3 , 20, 20);
    //
    //    glRotatef(t.elapsed()*180*size[i], 1, 0, 0);
    //    glTranslatef(0, 0, 2);
    //    glutSolidSphere(0.3, 20, 20);
    //
    //    end_RotateAroundTheSun();
    //}

    /*glPushMatrix();
    glColor3f(1, 0, 0);
    
    glRotatef(t.elapsed()*180, 0, 1, 0);
    glTranslatef(5, 1, -5);
    
    solid ? glutSolidSphere(1, 20, 20) : glutWireSphere(1, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);
    glTranslatef(-5, 1, 5);
    solid ? glutSolidTorus(0.5, 1, 20, 20) : glutWireTorus(0.5, 1, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(-5, 1, -5);
    solid ? glutSolidCone(1, 2, 10, 10) : glutWireCone(1, 2, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(5, 0.5, 5);
    solid ? glutSolidCube(1) : glutWireCube(1);
    glPopMatrix();*/

    //glPushMatrix();
    //glColor3f(1, 1, 0);
    //glTranslatef(0, 2, 0);
    //// rotate 180 degrees/second about the y-axis
    //glRotatef(t.elapsed()*180, 0, 1, 0);
    //glScalef(0.5, 0.5, 0.5);
    //solid ? glutSolidDodecahedron() : glutWireDodecahedron();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(0.01f, 0.01f, 0.01f);
    char que_mono[] = "Somos inteligente!";
    for (char *p = que_mono; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glRotatef(30, 0, 0, 1);
    glTranslatef(-4, 3, 0);

    glPushMatrix();
    glScalef(1, 0.125f, 1);
    glColor3f(0, 1, 0);
    glutSolidCube(4);
    glPopMatrix();

    draw_finger(-1.5f, 1.4, 1.0, 0.5, 10, 0);
    draw_finger(-0.5f, 2.0, 1.4, 1.0, 15, 0);
    draw_finger(0.5f, 2.5, 1.4, 1.4, 20, 0);
    draw_finger(1.5f, 2.1, 1.4, 1.0, 80, 80);
    draw_thumb(90, 45, 45);


    glPopMatrix();

}

// triggered when mouse is clicked
void application::mouse_click_event(int button, int button_state, int x, int y) {
}

// triggered when mouse button is held down and the mouse is
// moved
void application::mouse_move_event(
        int x, int y
) {
}

// triggered when a key is pressed on the keyboard
void application::keyboard_event(unsigned char key, int x, int y) {
}

void draw_grid() {
    glDisable(GL_LIGHTING);
    glLineWidth(2.0);

    //
    // Draws the coordinate frame at origin
    //
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBegin(GL_LINES);

    // x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    // y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    // z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();

    //
    // Draws a grid along the x-z plane
    //
    glLineWidth(1.0);
    glColor3f(.20, .20, .20);
    glBegin(GL_LINES);

    int ncells = 20;
    int ncells2 = ncells / 2;

    for (int i = 0; i <= ncells; i++) {
        int k = -ncells2;
        k += i;
        glVertex3f(ncells2, 0, k);
        glVertex3f(-ncells2, 0, k);
        glVertex3f(k, 0, ncells2);
        glVertex3f(k, 0, -ncells2);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void draw_cube(GLfloat diameter, GLfloat height) {
    glBegin(GL_QUADS);
    glVertex3f(diameter, diameter, 0);
    glVertex3f(-diameter, diameter, 0);
    glVertex3f(diameter, -diameter, 0);
    glVertex3f(-diameter, -diameter, 0);

    glVertex3f(diameter, diameter, height);
    glVertex3f(-diameter, diameter, height);
    glVertex3f(diameter, -diameter, height);
    glVertex3f(-diameter, -diameter, height);
    glEnd();
}


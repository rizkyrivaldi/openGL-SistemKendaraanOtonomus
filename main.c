#include <stdio.h> 
#include <stdlib.h> 
#include <GL/glut.h> // Header File For The GLUT Library
#include <GL/gl.h> // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> // Header file for sleeping.
#include <math.h> 
#include <fcntl.h>			/* File control definitions */
#include <errno.h>			/* Error number definitions */
#include <termios.h>		/* POSIX terminal control definitions */
#include <sys/time.h>

// Monitor window
int window;

// Camera transformation
GLfloat x_cam_transform = 0;
GLfloat y_cam_transform = 0;
GLfloat z_cam_transform = 0;

GLfloat z_rotate_robot = 0;

#include "constants.c"
#include "keyboard.c"
#include "objects.c"
#include "animate.c"

void  lighting(void) {
    GLfloat light_ambient[] =  {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] =  {0.4, 0.4, 0.4, 1.0};
    GLfloat light_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_position[] = {2, 0.1, 7,1.0};
    GLfloat spot_direction[] = {0.0, -0.1, -1.0, 1.0};

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 4);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void init_camera(GLfloat x, GLfloat y, GLfloat z){
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, // Point of View
                    2,    // Aspect Ratio (Width:Height)
                    0.2,  // Near Z (The nearest plane from center of camera)
                    8);   // Far Z (How far the camera view is)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x + 0.0, y + 0.1, z + 0.3,     // Eye location (x, y, z)
                0.0, 0.1, 0.0,    // Object of Interest (x, y, z)
                0.0, 1.0, 0.0);   // Up Vector to determine which way is up from the camera prespective
    lighting();
    glShadeModel(GL_SMOOTH) ;
}

void render_scene(void){
    init_camera(x_cam_transform, y_cam_transform, z_cam_transform);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_floor();

    glPushMatrix();
        glRotatef(z_rotate_robot, 0.0, 0.0, 1.0);
        draw_robot();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit (&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(800,400);
    glutInitWindowPosition (40, 100);

    /* Open a window */  
    window = glutCreateWindow ("Simple Window");

    // Initialize callbacks
    glutDisplayFunc(render_scene);

    /* Register the function to do all our OpenGL drawing. */
    glutIdleFunc(render_scene);

    // Register the keyboard function
    glutKeyboardFunc(keyboardKeys);
    glutSpecialFunc(processSpecialKeys);

    // glEnable(GL_DEPTH_TEST); // Enables Depth Testing

    // glutTimerFunc(500, animate, 0);

    /* Start Event Processing Engine */ 
    glutMainLoop () ;
    return 0 ;
}         
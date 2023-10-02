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

extern GLfloat z_rotate_robot;
GLint current_step = 0;
GLint step_size = 36;
GLfloat degree_per_step = 360.0/(GLfloat)step_size;

void animate_rotate(int k){
    if (current_step < step_size){
        z_rotate_robot = z_rotate_robot + degree_per_step;
    }
    else{
        z_rotate_robot = 0;
        current_step = 0;
    }
    // glutPostRedisplay();
    // glutTimerFunc(100.0, animate, 0); // Rotate the bot for each 100 ms
}

void animate_movement(int k){
    
}
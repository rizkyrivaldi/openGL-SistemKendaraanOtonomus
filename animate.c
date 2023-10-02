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
#include "constants.c"

extern GLfloat z_rotate_robot, z_rotate_robot_offset;
extern GLfloat x_translate_robot, y_translate_robot, z_translate_robot;
extern GLfloat movement_speed;
extern GLubyte ir1, ir2, ir3, ir4, ir5, ir6, ir7, ir8;
GLint current_step = 0;
GLint step_size = 360;
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
    if (current_step < step_size){
        z_rotate_robot = z_rotate_robot + degree_per_step;
    }
    else{
        z_rotate_robot = 0;
        current_step = 0;
    }
    // x_translate_robot = x_translate_robot + movement_speed;

    GLfloat dx = movement_speed*cos(z_rotate_robot*DTR);
    GLfloat dy = movement_speed*sin(z_rotate_robot*DTR);

    x_translate_robot = x_translate_robot + dx;
    y_translate_robot = y_translate_robot + dy;
}

void animate_line_follower(int k){

    // Sensor calculation
    int sensor = (ir1)?-4:0 + (ir2)?-3:0 + (ir3)?-2:0 + (ir4)?-1:0 + (ir5)?1:0 + (ir6)?2:0 + (ir7)?3:0 + (ir8)?4:0;

    if(sensor == 0){
        //do nothing
    }
    else if(sensor < 0){
        z_rotate_robot = z_rotate_robot + 3.0;
    }
    else if(sensor > 0){
        z_rotate_robot = z_rotate_robot -3.0;
    }

    // Move forward with z-axis rotation
    GLfloat dx = movement_speed*cos(z_rotate_robot*DTR);
    GLfloat dy = movement_speed*sin(z_rotate_robot*DTR);

    x_translate_robot = x_translate_robot + dx;
    y_translate_robot = y_translate_robot + dy;
}
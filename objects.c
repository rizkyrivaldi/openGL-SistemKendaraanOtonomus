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

/* define color */  
GLfloat green1[4]  ={0.8, 1.0, 0.8, 1.0};
GLfloat blue1[4]  ={0.1, 0.1, 1.0, 1.0};
GLfloat blue2[4]  ={0.2, 0.2, 1.0, 1.0};
GLfloat blue3[4]  ={0.3, 0.3, 1.0, 1.0};
GLfloat yellow1[4]={0.1, 0.1, 0.0, 1.0};
GLfloat yellow2[4]={0.2, 0.2, 0.0, 1.0};
GLfloat pink6[4] ={0.8, 0.55, 0.6, 1.0};
GLfloat yellow5[4]={0.8, 0.8, 0.0, 1.0};
GLfloat abu2[4]={0.5,0.5,0.5,1.0};
GLfloat gray1[4]  ={0.1, 0.1, 0.1, 1.0};
GLfloat gray2[4]  ={0.2, 0.2, 0.2, 1.0};
GLfloat gray3[4]  ={0.3, 0.3, 0.3, 1.0};
GLfloat gray4[4]  ={0.4, 0.4, 0.4, 1.0};
GLfloat gray5[4]  ={0.5, 0.5, 0.5, 1.0};
GLfloat gray6[4]  ={0.6, 0.6, 0.6, 1.0};
GLfloat gray7[4]  ={0.7, 0.7, 0.7, 1.0};
GLfloat gray8[4]  ={0.8, 0.8, 0.7, 1.0};
GLfloat gray9[4]  ={0.9, 0.9, 0.7, 1.0};

void model_box(GLfloat width, GLfloat depth, GLfloat height, GLfloat *color1, GLfloat *color2, GLfloat *color3, int color);
void model_cylinder();
void drawOneLine();
void draw_box(GLdouble x_length, GLdouble y_length, GLdouble z_length);
void draw_cylinder(GLdouble radius, GLdouble height, GLdouble slices);
void draw_cone(GLdouble radius, GLdouble height, GLdouble slices);
void draw_arena(unsigned int textureNumber);
int loadGLTexture(const char* filename, int width, int height);

// Additional pointer for texture
unsigned char* data = NULL;

// file datatype
FILE *fileimage;

void draw_robot(void){
    /*
    ROBOT DRAWING
                    WLF               WRF
                    ///---A1-A-A2---///
                          |     |
                          |     |
                          |     |
                          |     |
                          |     |
                    //----B1-B-B2----//
                    WLR               WRR

                            y
                            |
                            |
                            --------- x
                            /
                            z

    O = Center of Robot

    A = Center of front heel
    B = Center of back heel

    A1 & B1 = Support on left side
    A2 & B2 = Support on right side
    
    WLF = Wheel Left Front
    WRF = Wheel Right Front
    WLR = Wheel Left Rear
    WRR = Wheel Right Rear

    All the robot parts will be referenced to the origin point of the robot (B)
    */
    GLUquadricObj *obj;
    
    // All values are written in meter (m)
    // Initialize Parameters
    GLfloat param_w = 0.4;
    GLfloat param_d = 0.3;
    GLfloat param_h = 0.15;

    GLfloat front_width = 0.09;
    GLfloat front_thickness_y = 0.02;
    GLfloat front_thickness_z = 0.01;

    GLfloat rear_width = 0.18;
    GLfloat rear_thickness_y = 0.02;
    GLfloat rear_thickness_z = 0.01;

    GLfloat body_length = 0.15;

    GLfloat link_length = 0.2;
    GLfloat link_thickness = 0.01;
    GLfloat link_gap = 0.07;

    // Initialize origin point
    GLfloat x_origin = 0.0;
    GLfloat y_origin = 0.0;
    GLfloat z_origin = 0.0;
    GLfloat B[] = {x_origin, y_origin, z_origin};

    // Initialize Wheel points
    GLfloat WLF[] = {B[0] - front_width/2, B[1] + body_length, B[2]};
    GLfloat WRF[] = {B[0] + front_width/2, B[1] + body_length, B[2]};
    GLfloat WLR[] = {B[0] - rear_width/2, B[1], B[2]};
    GLfloat WRR[] = {B[0] + rear_width/2, B[1], B[2]};

    // Initialize Link points
    GLfloat A[] = {B[0], B[1] + body_length, B[2]};
    GLfloat A1[] = {B[0] - link_gap/2, B[1] + body_length, B[2]};
    GLfloat A2[] = {B[0] + link_gap/2, B[1] + body_length, B[2]};

    GLfloat B1[] = {B[0] - link_gap/2, B[1], B[2]};
    GLfloat B2[] = {B[0] + link_gap/2, B[1], B[2]};

    // Draw points
    glPointSize(7.0f);
    glBegin(GL_POINTS);
        glVertex3f(B[0], B[1], B[2]);
        glVertex3f(B1[0], B1[1], B1[2]);
        glVertex3f(B2[0], B2[1], B2[2]);
        glVertex3f(A[0], A[1], A[2]);
        glVertex3f(A1[0], A1[1], A1[2]);
        glVertex3f(A2[0], A2[1], A2[2]);
        glVertex3f(WLF[0], WLF[1], WLF[2]);
        glVertex3f(WRF[0], WRF[1], WRF[2]);
        glVertex3f(WLR[0], WLR[1], WLR[2]);
        glVertex3f(WRR[0], WRR[1], WRR[2]);
    glEnd();

    // Set coloring for the whole robot
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue1);
        // Draw the front body
        glPushMatrix();
            glTranslatef(B[0], B[1] + body_length, B[2]);
            draw_box(front_width, front_thickness_y, front_thickness_z);
        glPopMatrix();

        // Draw the rear body
        draw_box(rear_width, rear_thickness_y, rear_thickness_z);

        // Draw the left link
        glPushMatrix();
            glTranslatef(B1[0], (B1[1] + A1[1]) / 2, B1[2]);
            draw_box(link_thickness, A1[1] - B1[1], link_thickness);
        glPopMatrix();

        // Draw the right link
        glPushMatrix();
            glTranslatef(B2[0], (B2[1] + A2[1]) / 2, B2[2]);
            draw_box(link_thickness, A2[1] - B2[1], link_thickness);
        glPopMatrix();

        // Draw the Wheel Left Rear
        glPushMatrix();
            glTranslatef(WLR[0], WLR[1], WLR[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cylinder(rear_thickness_y * 1.5, rear_thickness_z * 0.8, 12);
        glPopMatrix();

        // Draw the Wheel Right Rear
        glPushMatrix();
            glTranslatef(WRR[0], WRR[1], WRR[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cylinder(rear_thickness_y * 1.5, rear_thickness_z * 0.8, 12);
        glPopMatrix();

        // Draw the Wheel Right Front
        glPushMatrix();
            glTranslatef(WRF[0], WRF[1], WRF[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cylinder(front_thickness_z * 1.5, front_thickness_z * 0.8, 12);
        glPopMatrix();

        // Draw the Wheel Left Front
        glPushMatrix();
            glTranslatef(WLF[0], WLF[1], WLF[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cylinder(front_thickness_z * 1.5, front_thickness_z * 0.8, 12);
        glPopMatrix();

        // EXTRAS
        // Draw a gun :D
        GLfloat gun_height = 0.08;
        GLfloat gun_length = 0.03;
        GLfloat support_thickness = 0.01;
        GLfloat support_width = link_gap;

        // Left support
        glPushMatrix();
            glTranslatef(B1[0], (A1[1] - B1[1])/2.0 + B1[1], B1[2] + gun_height/2.0);
            draw_box(support_thickness, support_thickness, gun_height);
        glPopMatrix();

        // Right support
        glPushMatrix();
            glTranslatef(B2[0], (A2[1] - B2[1])/2.0 + B2[1], B2[2] + gun_height/2.0);
            draw_box(support_thickness, support_thickness, gun_height);
        glPopMatrix();

        // Bar suport
        glPushMatrix();
            glTranslatef(B[0], (A[1] - B[1])/2.0 + B[1], B[2] + gun_height);
            draw_box(support_width, support_thickness, support_thickness);
        glPopMatrix();

        // The gun
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green1);
            glTranslatef(B[0], (A[1] - B[1])/2.0 + B[1], B[2] + gun_height);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            draw_cylinder(support_thickness, gun_length, 12);
        glPopMatrix();

        // ANOTHER EXTRAS
        // Draw Spikes on each wheels

        // Draw the Wheel Left Rear
        glPushMatrix();
            glTranslatef(WLR[0] - (rear_thickness_y * 1.5), WLR[1], WLR[2]);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            draw_cone(rear_thickness_y * 0.8, rear_thickness_z * 3, 12);
        glPopMatrix();

        // Draw the Wheel Right Rear
        glPushMatrix();
            glTranslatef(WRR[0] + (rear_thickness_y * 1.5), WRR[1], WRR[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cone(rear_thickness_y * 0.8, rear_thickness_z * 3, 12);
        glPopMatrix();

        // Draw the Wheel Right Front
        glPushMatrix();
            glTranslatef(WRF[0] + (front_thickness_z * 1.5), WRF[1], WRF[2]);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            draw_cone(front_thickness_z * 0.8, front_thickness_z * 3, 12);
        glPopMatrix();

        // Draw the Wheel Left Front
        glPushMatrix();
            glTranslatef(WLF[0] - (front_thickness_z * 1.5), WLF[1], WLF[2]);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            draw_cone(front_thickness_z * 0.8, front_thickness_z * 3, 12);
        glPopMatrix();

    glPopMatrix();
}

void draw_box(GLdouble x_length, GLdouble y_length, GLdouble z_length){
    GLdouble length = x_length/2;
    GLdouble width = y_length/2;
    GLdouble height = z_length/2;

    glBegin(GL_QUADS); // Top portion of the box
        glVertex3f(-length, -width, height);
        glVertex3f(-length, width, height);
        glVertex3f(length, width, height);
        glVertex3f(length, -width, height);
    glEnd();
    glBegin(GL_QUADS); // Bottom portion of the box
        glVertex3f(-length, -width, -height);
        glVertex3f(-length, width, -height);
        glVertex3f(length, width, -height);
        glVertex3f(length, -width, -height);
    glEnd();
    glBegin(GL_QUAD_STRIP); // Sides of the box
        glVertex3f(-length, -width, height);
        glVertex3f(-length, -width, -height);
        glVertex3f(-length, width, height);
        glVertex3f(-length, width, -height);
        glVertex3f(length, width, height);
        glVertex3f(length, width, -height);
        glVertex3f(length, -width, height);
        glVertex3f(length, -width, -height);
        glVertex3f(-length, -width, height);
        glVertex3f(-length, -width, -height);
    glEnd();
}

void draw_cylinder(GLdouble radius, GLdouble height, GLdouble slices){
    GLUquadricObj *object;
    object = gluNewQuadric();

    // Draw the cylinder
    // Obj, base radius, top radius, height, number of slices on cylinder edge, number of slices of the stacks
    
    glPushMatrix();
        glTranslatef(0, 0, -height/2);
        gluCylinder(object, radius, radius, height, slices, 4);
    glPopMatrix();

    // Draw the circles
    // Obj, lower radius, upper radius, edge vertices slices, between outer/inner slices (rings)
    glPushMatrix();
        glTranslatef(0, 0, height/2);
        gluDisk(object, 0, radius, slices, 4);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -height/2);
        gluDisk(object, 0, radius, slices, 4);
    glPopMatrix();
    gluDeleteQuadric(object);
}

void draw_cone(GLdouble radius, GLdouble height, GLdouble slices){
    GLUquadricObj *object;
    object = gluNewQuadric();

    // Draw the cone sides
    gluCylinder(object, radius, 0, height, slices, 4);

    // Draw the circle
    gluDisk(object, 0, radius, slices, 4);

    gluDeleteQuadric(object);
}

void drawOneLine(double x1, double y1, double x2, double y2){
    glBegin(GL_LINES);
    glVertex3f((x1),(y1),0.0);
    glVertex3f((x2),(y2),0.0);
    glEnd();
}
   
void model_cylinder(GLUquadricObj * object, GLdouble lowerRadius, GLdouble upperRadius, GLdouble length, GLint res, GLfloat *color1, GLfloat *color2) {
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
        glTranslatef(0,0,-length/2);
        gluCylinder(object, lowerRadius, upperRadius, length, 20, res);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
        gluDisk(object, 0.01, lowerRadius, 20, res); 
        glTranslatef(0, 0, length);
        gluDisk(object, 0.01, upperRadius, 20, res); 
    glPopMatrix();
}

void draw_floor(void)
{
  int i,j,flagc=1;

  glPushMatrix();
  
  GLfloat dx=4.5,dy=4.5;
  GLint amount=15;
  GLfloat x_min=-dx/2.0, x_max=dx/2.0, x_sp=(GLfloat) dx/amount, y_min=-dy/2.0, y_max=dy/2.0, y_sp=(GLfloat) dy/amount;

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green1);
  for(i = 0; i<=48; i++){
     drawOneLine(-2.4+0.1*i, -2.4,       -2.4+0.1*i,  2.4);
     drawOneLine(-2.4,       -2.4+0.1*i,  2.4,       -2.4+0.1*i);
  }

  glPopMatrix();
}

void draw_arena(unsigned int textureNumber){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureNumber);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glBegin(GL_POLYGON);
        glTexCoord2f(0,1);
        glVertex3f(-1.0f, -1.0f, 0);
        glTexCoord2f(0,0);
        glVertex3f(-1.0f, 1.0f, 0);
        glTexCoord2f(1,0);
        glVertex3f(1.0f, 1.0f, 0);
        glTexCoord2f(1,1);
        glVertex3f(1.0f, -1.0f, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

int loadGLTexture(const char* filename, int width, int height){
    free(data);

    // Make sure the file is 500x500 pixel
    fileimage = fopen(filename, "r");
    if(fileimage == NULL){
        return 0;
    }

    // Allocate buffer
    data = (unsigned char*) malloc(width * height * 3);

    // Read texture data to buffer
    fread(data, width * height * 3, 1, fileimage);
    fclose(fileimage);

    // Initiate GL Texture
    unsigned int textureID;
    int border = 0;
    int depth = width * height * 3;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    return textureID;
}
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
int mainCamera;
int secondCamera;
int thirdCamera;
int fourthCamera;

// Camera transformation
GLfloat x_cam_transform = 0;
GLfloat y_cam_transform = 0;
GLfloat z_cam_transform = 0;

GLfloat x_cam_translate = 0;
GLfloat y_cam_translate = 0;
GLfloat z_cam_translate = 0;

GLfloat cam_rotate_x = 0;
GLfloat cam_rotate_y = 0;
GLfloat cam_rotate_z = 0;

// Robot Transformation
GLfloat x_transpose_robot = 0;
GLfloat y_transpose_robot = 0;
GLfloat z_transpose_robot = 0;

GLfloat x_rotate_robot = 0.0;
GLfloat y_rotate_robot = 0.0;
GLfloat z_rotate_robot = -90.0;

#include "constants.c"
#include "keyboard.c"
#include "objects.c"
#include "animate.c"

// Arena Texture ID
int textureID = 0;

// Sensor readings
// unsigned int image_raw[100][500];
GLubyte image_raw[100][500];
GLubyte ir1, ir2, ir3, ir4, ir5, ir6, ir7, ir8;
int sens1 = (500/8)*(1) - (500/16);
int sens2 = (500/8)*(2) - (500/16);
int sens3 = (500/8)*(3) - (500/16);
int sens4 = (500/8)*(4) - (500/16);
int sens5 = (500/8)*(5) - (500/16);
int sens6 = (500/8)*(6) - (500/16);
int sens7 = (500/8)*(7) - (500/16);
int sens8 = (500/8)*(8) - (500/16);

// Function prototypes
void lighting(void);
void init_camera(GLfloat x, GLfloat y, GLfloat z);
void init_main_window(void);
void init_second_window(void);
void init_third_window(void);
void init_fourth_window(void);
void render_scene1(void);
void render_scene2(void);
void render_scene3(void);
void render_scene4(void);
void main_sim(void);
void draw_scene(GLfloat x_camera_center, GLfloat y_camera_center, GLfloat z_camera_center, GLfloat x_camera_rotate, GLfloat y_camera_rotate, GLfloat z_camera_rotate);
void draw_sensor_scene(GLfloat x_camera_center, GLfloat y_camera_center, GLfloat z_camera_center, GLfloat x_camera_rotate, GLfloat y_camera_rotate, GLfloat z_camera_rotate);
void update_reading(void);


void lighting(void) {
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

void init_main_camera(GLfloat x, GLfloat y, GLfloat z){
    // glutSetWindow(window);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, // Point of View
                    2,    // Aspect Ratio (Width:Height)
                    0.2,  // Near Z (The nearest plane from center of camera)
                    8);   // Far Z (How far the camera view is)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x + 0.0, y + 0.1, z + 2.0,     // Eye location (x, y, z)
                0.0, 0.1, 0.0,    // Object of Interest (x, y, z)
                0.0, 1.0, 0.0);   // Up Vector to determine which way is up from the camera prespective
    lighting();
    glShadeModel(GL_SMOOTH) ;
}

void init_second_camera(GLfloat x, GLfloat y, GLfloat z){
    // glutSetWindow(secondCamera);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, // Point of View
                    2,    // Aspect Ratio (Width:Height)
                    0.2,  // Near Z (The nearest plane from center of camera)
                    8);   // Far Z (How far the camera view is)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, -0.32, 0.20,     // Eye location (x, y, z)
                0.0, 0.25, 0.0,    // Object of Interest (x, y, z)
                0.0, 1.0, 0.0);   // Up Vector to determine which way is up from the camera prespective
    lighting();
    glShadeModel(GL_SMOOTH) ;
}

void init_third_camera(GLfloat x, GLfloat y, GLfloat z){
    // glutSetWindow(secondCamera);
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(     -0.05, // Left
                    0.05,    // Right
                    -0.01,  // Bottom
                    0.01,   // top
                    0.19, // nearVal
                    1); // farVal
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // gluLookAt(0.0, 0.15, 0.20,     // Eye location (x, y, z)
    //             0.0, 0.15, 0.19,    // Object of Interest (x, y, z)
    //             0.0, 0.0, 1.0);   // Up Vector to determine which way is up from the camera prespective

    gluLookAt(0.0, 0.15, 0.20,     // Eye location (x, y, z)
            0.0, 0.15, 0.19,    // Object of Interest (x, y, z)
            0.0, 1.0, 0.0);   // Up Vector to determine which way is up from the camera prespective
    lighting();
    glShadeModel(GL_SMOOTH) ;
}

void init_main_window(void){
    glutInitWindowSize(800,400);
    glutInitWindowPosition (40, 100);

    /* Open a window */  
    mainCamera = glutCreateWindow ("Rizky Rivaldi Ramadhan");

    // Initialize callbacks
    glutDisplayFunc(&render_scene1);

    // Register the keyboard function
    glutKeyboardFunc(&keyboardKeys);
    glutSpecialFunc(&processSpecialKeys);

    // Load Arena Texture
    textureID = loadGLTexture("assets/ArenaPath.ppm", 500, 500);
}

void init_second_window(void){
    glutInitWindowSize(800,400);
    glutInitWindowPosition(300, 100);
    secondCamera = glutCreateWindow("Second Cam");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(&render_scene2);
    glutKeyboardFunc(&keyboardKeys);
    glutSpecialFunc(&processSpecialKeys);
    // Load Arena Texture
    textureID = loadGLTexture("assets/ArenaPath.ppm", 500, 500);
}

void init_third_window(void){
    glutInitWindowSize(500,100);
    glutInitWindowPosition(700, 100);
    thirdCamera = glutCreateWindow("Third Cam");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(&render_scene3);
    glutKeyboardFunc(&keyboardKeys);
    glutSpecialFunc(&processSpecialKeys);
    // Load Arena Texture
    textureID = loadGLTexture("assets/ArenaPath.ppm", 500, 500);
}

void init_fourth_window(void){
    glutInitWindowSize(500,100);
    glutInitWindowPosition(900, 100);
    fourthCamera = glutCreateWindow("Fourth Cam");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(&render_scene4);
    glutKeyboardFunc(&keyboardKeys);
    glutSpecialFunc(&processSpecialKeys);
    // Load Arena Texture
    textureID = loadGLTexture("assets/ArenaPath.ppm", 500, 500);
}

void render_scene1(void){
    
    // init_main_camera(x_cam_transform, y_cam_transform, z_cam_transform);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glPushMatrix();
    //     // Frame rotation and translation
    //     glTranslatef(x_cam_translate, y_cam_translate, z_cam_translate);
    //     glRotatef(cam_rotate_x, 1, 0, 0);
    //     glRotatef(cam_rotate_y, 0, 1, 0);
    //     glRotatef(cam_rotate_z, 0, 0, 1);

    //     // Draw the objects
    //     // draw_floor();
    //     draw_arena(textureID);

    //     glPushMatrix();
    //         glRotatef(z_rotate_robot, 0.0, 0.0, 1.0);
    //         draw_robot();
    //     glPopMatrix();

    // glPopMatrix();

    // glutSwapBuffers();
}

void render_scene2(void){
    // init_second_camera(x_cam_transform, y_cam_transform, z_cam_transform);

    // draw_robot();
    // draw_floor();
    
    // glutSwapBuffers();
}

void render_scene3(void){

}

void render_scene4(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(500, 100, GL_LUMINANCE, GL_UNSIGNED_BYTE, image_raw);
    glutSwapBuffers();
}

void main_sim(void){

    unsigned int count = 0;
    animate_rotate(count);

    // Draw the first window (sky perspective)
    glutSetWindow(mainCamera);
    init_main_camera(x_cam_transform, y_cam_transform, z_cam_transform);
    draw_scene(x_cam_translate, y_cam_translate, z_cam_translate, cam_rotate_x, cam_rotate_y, cam_rotate_z);

    // Draw the second window (third person car persepective)
    glutSetWindow(secondCamera);
    init_second_camera(0.0, 0.0, 0.0);
    draw_scene(x_transpose_robot, y_transpose_robot, z_transpose_robot, x_rotate_robot, y_rotate_robot, z_rotate_robot);

    // Draw the third window (sensor)
    glutSetWindow(thirdCamera);
    init_third_camera(x_cam_transform, y_cam_transform, z_cam_transform);
    draw_sensor_scene(x_transpose_robot, y_transpose_robot, z_transpose_robot, x_rotate_robot, y_rotate_robot, z_rotate_robot);
    update_reading();

    // Draw the fourth window (ir sensor detection)
    glutSetWindow(fourthCamera);
    render_scene4();

    usleep(200000);
}

void draw_scene(GLfloat x_camera_center, GLfloat y_camera_center, GLfloat z_camera_center, GLfloat x_camera_rotate, GLfloat y_camera_rotate, GLfloat z_camera_rotate){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        // Frame rotation and translation
        glTranslatef(-x_camera_center, -y_camera_center, -z_camera_center);
        glRotatef(-x_camera_rotate, 1, 0, 0);
        glRotatef(-y_camera_rotate, 0, 1, 0);
        glRotatef(-z_camera_rotate, 0, 0, 1);

        // Draw the objects
        draw_floor();
        draw_arena(textureID);

        glPushMatrix();
            glRotatef(z_rotate_robot, 0.0, 0.0, 1.0);
            draw_robot();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void draw_sensor_scene(GLfloat x_camera_center, GLfloat y_camera_center, GLfloat z_camera_center, GLfloat x_camera_rotate, GLfloat y_camera_rotate, GLfloat z_camera_rotate){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        // Frame rotation and translation
        glTranslatef(-x_camera_center, -y_camera_center, -z_camera_center);
        glRotatef(-x_camera_rotate, 1, 0, 0);
        glRotatef(-y_camera_rotate, 0, 1, 0);
        glRotatef(-z_camera_rotate, 0, 0, 1);

        // Draw the objects
        draw_floor();
        draw_arena(textureID);

    glPopMatrix();

    glutSwapBuffers();
    update_reading();
}

void update_reading(void){
    glPixelTransferf(GL_RED_SCALE, 0.3333*0.2);
    glPixelTransferf(GL_GREEN_SCALE, 0.3334*0.2);
    glPixelTransferf(GL_BLUE_SCALE, 0.3333*0.2);

    glReadPixels(0, 0, 500, 100, GL_LUMINANCE, GL_UNSIGNED_BYTE, image_raw);

    ir8 = image_raw[50][sens8]<50 ? 1:0;
    ir7 = image_raw[50][sens7]<50 ? 1:0;
    ir6 = image_raw[50][sens6]<50 ? 1:0;
    ir5 = image_raw[50][sens5]<50 ? 1:0;
    ir4 = image_raw[50][sens4]<50 ? 1:0;
    ir3 = image_raw[50][sens3]<50 ? 1:0;
    ir2 = image_raw[50][sens2]<50 ? 1:0;
    ir1 = image_raw[50][sens1]<50 ? 1:0;

    image_raw[50][sens8]=ir8*255;
    image_raw[50][sens7]=ir7*255;
    image_raw[50][sens6]=ir6*255;
    image_raw[50][sens5]=ir5*255;
    image_raw[50][sens4]=ir4*255;
    image_raw[50][sens3]=ir3*255;
    image_raw[50][sens2]=ir2*255;
    image_raw[50][sens1]=ir1*255;
    
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit (&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );

    init_main_window();
    init_second_window();
    init_third_window();
    init_fourth_window();

    /* Register the function to do all our OpenGL drawing. */
    glutIdleFunc(&main_sim);

    // glEnable(GL_DEPTH_TEST); // Enables Depth Testing

    // glutTimerFunc(500, animate, 0);

    /* Start Event Processing Engine */ 
    glutMainLoop () ;
    return 0 ;
}         
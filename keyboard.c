#include "constants.c"
#define ESCkey	27

extern GLfloat y_cam_transform;
extern GLfloat x_cam_transform;
extern GLfloat z_cam_transform;

void keyboardKeys(unsigned char key, int i, int j)
{
    switch(key){
        case ESCkey:
            exit(1);
            break;
        case 'w':
            y_cam_transform = y_cam_transform + 0.01;
            break;
        case 'a':
            x_cam_transform = x_cam_transform - 0.01;
            break;
        case 's':
            y_cam_transform = y_cam_transform - 0.01;
            break;
        case 'd':
            x_cam_transform = x_cam_transform + 0.01;
            break;
   }
}

void processSpecialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            z_cam_transform = z_cam_transform + 0.01;
            break;
        case GLUT_KEY_LEFT : 
            break;
        case GLUT_KEY_DOWN: 
            z_cam_transform = z_cam_transform - 0.01;
            break;
        case GLUT_KEY_RIGHT:
            break;
    }
}
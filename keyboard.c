#include "constants.c"
#define ESCkey	27

extern GLfloat y_cam_transform;
extern GLfloat x_cam_transform;
extern GLfloat z_cam_transform;

extern GLfloat x_cam_translate;
extern GLfloat y_cam_translate;
extern GLfloat z_cam_translate;

extern GLfloat cam_rotate_x;
extern GLfloat cam_rotate_y;
extern GLfloat cam_rotate_z;

void keyboardKeys(unsigned char key, int i, int j)
{
    switch(key){
        // Normal camera movement
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

        // Required camera movement (tugas)
        case 'u':
            x_cam_translate = x_cam_translate + 0.1;
            break;
        case 'U':
            x_cam_translate = x_cam_translate - 0.1;
            break;
        case 'i':
            y_cam_translate = y_cam_translate + 0.1;
            break;
        case 'I':
            y_cam_translate = y_cam_translate - 0.1;
            break;
        case 'o':
            z_cam_translate = z_cam_translate + 0.1;
            break;
        case 'O':
            z_cam_translate = z_cam_translate - 0.1;
            break;
        case 'j':
            cam_rotate_x = cam_rotate_x + 10;
            break;
        case 'J':
            cam_rotate_x = cam_rotate_x - 10;
            break;
        case 'k':
            cam_rotate_y = cam_rotate_y + 10;
            break;
        case 'K':
            cam_rotate_y = cam_rotate_y - 10;
            break;
        case 'l':
            cam_rotate_z = cam_rotate_z + 10;
            break;
        case 'L':
            cam_rotate_z = cam_rotate_z - 10;
            break;
        case 'p':
            x_cam_translate = 0;
            y_cam_translate = 0;
            z_cam_translate = 0;
            cam_rotate_x = 0;
            cam_rotate_y = 0;
            cam_rotate_z = 0;
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
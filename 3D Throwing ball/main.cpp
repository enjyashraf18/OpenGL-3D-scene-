#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;
static float cameraDistance = -5.0; // Start the camera closer to the scene


const int window_width = 800;
const int window_height = 600;


void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
    glLoadIdentity();  // Reset the modelview matrix

    // Translate the camera closer to the room (adjusting the camera distance)
    glTranslatef(0.0, 0.0, cameraDistance);

    // Apply rotations
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    // Draw the floor
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);  // Gray floor
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    glPopMatrix();

    // Draw the ceiling
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);  // Light gray ceiling
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    glPopMatrix();


    // Draw the left wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.6);  // Blue left wall
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glPopMatrix();

    // Draw the right wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.2, 0.2);  // Red right wall
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    glPopMatrix();

    // Draw the front wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.6, 0.2);  // Green front wall
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();  // Swap buffers for double buffering
}


void setup(void)
{
    glClearColor(0.9, 0.9, 0.9, 1.0);  // Set the background color
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
}

// Function to handle window resizing
void resize(int w, int h)
{
    glViewport(0, 0, w, h);  // Set the viewport to the new window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set perspective projection using the aspect ratio of the window
    float aspectRatio = (float)w / (float)h;

    // Use a perspective projection matrix
    gluPerspective(45.0, aspectRatio, 1.0, 100.0);  // Adjust FOV as needed

    glMatrixMode(GL_MODELVIEW);
}

// Function to handle keyboard input for rotation and camera zoom
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:  // Escape key
        exit(0);
        break;

    case 'x':  // Rotate around X-axis (clockwise)
        Xangle += 5.0;
        if (Xangle > 360.0) Xangle -= 360.0;
        glutPostRedisplay();
        break;

    case 'X':  // Rotate around X-axis (counter-clockwise)
        Xangle -= 5.0;
        if (Xangle < 0.0) Xangle += 360.0;
        glutPostRedisplay();
        break;

    case 'y':  // Rotate around Y-axis (clockwise)
        Yangle += 5.0;
        if (Yangle > 360.0) Yangle -= 360.0;
        glutPostRedisplay();
        break;

    case 'Y':  // Rotate around Y-axis (counter-clockwise)
        Yangle -= 5.0;
        if (Yangle < 0.0) Yangle += 360.0;
        glutPostRedisplay();
        break;

    case 'z':  // Rotate around Z-axis (clockwise)
        Zangle += 5.0;
        if (Zangle > 360.0) Zangle -= 360.0;
        glutPostRedisplay();
        break;

    case 'Z':  // Rotate around Z-axis (counter-clockwise)
        Zangle -= 5.0;
        if (Zangle < 0.0) Zangle += 360.0;
        glutPostRedisplay();
        break;

    case '+':  // Zoom in (move the camera closer)
        cameraDistance += 0.5;
        glutPostRedisplay();
        break;

    case '-':  // Zoom out (move the camera farther)
        cameraDistance -= 0.5;
        if (cameraDistance < -10.0) cameraDistance = -10.0;  // Set a minimum distance
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

// Main function to initialize GLUT and start the rendering loop
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // Enable depth buffer
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Throwing ball scne");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}

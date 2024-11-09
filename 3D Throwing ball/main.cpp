#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

static float bodyAngle = 0.0f;
static float handSwing = 0.0f;
static float walkAngle = 0.0f;
static float walkBack = 0.0f;
static float throwAngle = 0.0f;
static float bowAngle = 0.0f;
static float rotateAngle = 0.0f;
static float walkForward = 0.0f;
static int forward = 0;
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;
static float cameraDistance = -5.0; // Start the camera closer to the scene
int lastTime = 0;  // Store the last time when the scene started
bool isPlaying = true;  // Control the scene playback state

const int window_width = 800;
const int window_height = 600;

// Timer function to track the time elapsed and stop the scene after 3 seconds
void update(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    // body rotation
    if (isPlaying && 500 < currentTime - lastTime && currentTime - lastTime < 1500) {
        bodyAngle += 0.5f;  
    }
    if (isPlaying && 2000 < currentTime - lastTime && currentTime - lastTime < 4000) {
        walkBack += 0.01f;
        if (forward)
        {
            walkAngle -= 1;
        }
        else
        {
            walkAngle += 1;
        }

        if (walkAngle >= 30.0) forward = 1;
        else if (walkAngle <= -30.0) forward = 0;
    }
    // hand swing
    if (isPlaying && 4500 < currentTime - lastTime && currentTime - lastTime < 5500) {
        handSwing += 1.0f;  
    }
    // throw the ball
    if (isPlaying && 5600 < currentTime - lastTime && currentTime - lastTime < 6600) {
        throwAngle += 1.0f;
    }
    // taking a bow
    if (isPlaying && 7000 < currentTime - lastTime && currentTime - lastTime < 8000) {
        walkForward += 1.0 / 75;

        if (forward) walkAngle -= 2;
        else  walkAngle += 2;

        if (walkAngle >= 30.0) forward = 1;
        else if (walkAngle <= -30.0) forward = 0;
        
    }
    if (isPlaying && 8000 < currentTime - lastTime && currentTime - lastTime < 9000) {
        rotateAngle += 0.5f;
    }
    if (isPlaying && 9000 < currentTime - lastTime && currentTime - lastTime < 10000) {
        bowAngle += 0.5f;
    }
    if (isPlaying && 11000 < currentTime - lastTime && currentTime - lastTime < 12000) {
        bowAngle -= 0.5f;
    }
    if (isPlaying && currentTime - lastTime > 120000) {  
        isPlaying = false;
        std::cout << "Time is up, press space to restart" << std::endl;
    }

    // Continuously call the timer function
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // 16 ms -> ~60 FPS
}

void drawHuman() {
    //glPushMatrix();

    // Position of the human
    //float a = 70;
    glTranslatef(0, -0.8, 0.0);

    glRotatef(3 * bodyAngle - 3 * rotateAngle, 0.0, 1.0, 0.0);

    glTranslatef(0, +0.3, 0);
    glRotatef(3 * bowAngle, 1, 0, 0);
    glTranslatef(0, -0.3, 0);

    glTranslatef(0, 0, handSwing / 300 + throwAngle / 300 - walkBack + walkForward);

    // head
    glColor3f(1.0, 0.87, 0.68);
    glPushMatrix();
    //glRotatef(70.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 1.03, 0.0);
    glutSolidSphere(0.13, 20, 20);
    glPopMatrix();

    // body (just a rectangle)
    glColor3f(1.0, 1.0, 0.0); // yellow shirt
    glPushMatrix();
    //glRotatef(70.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.6, 0.0);
    glScalef(0.35, 0.6, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // left arm
    glColor3f(0.5, 0.25, 0.2);
    glPushMatrix();
    glTranslatef(-0.225, 0.67, 0.0);

    // swing
    glTranslatef(0.075 / 2, 0.45 / 2, 0.05 / 2);
    glRotatef(-3.5*handSwing + 3.5 * throwAngle - walkAngle, 1, 0, 0);
    glTranslatef(-0.075 / 2, -0.45 / 2, -0.05 / 2);

    glScalef(0.075, 0.45, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //right arm
    glPushMatrix();
    //glRotatef(70.0, 0.0, 1.0, 0.0);
    glTranslatef(0.225, 0.67, 0.0);
    
    // walking back
    glTranslatef(0.075 / 2, 0.45 / 2, 0.05 / 2);
    glRotatef(walkAngle, 1, 0, 0);
    glTranslatef(-0.075 / 2, -0.45 / 2, -0.05 / 2);

    glScalef(0.075, 0.45, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //left leg
    glColor3f(0.0, 0.0, 0.0); // Black pants
    glPushMatrix();
    glTranslatef(0, 0.3, 0);
    glRotatef(-3 * bowAngle, 1, 0, 0);
    glTranslatef(0, -0.3, 0);

    glTranslatef(-0.07, 0.08, 0.0);
    
    // swing
    glTranslatef(0.08 / 2, 0.5 / 2, 0.05 / 2);
    glRotatef(0.3 * handSwing - 0.3 * throwAngle + walkAngle, 1, 0, 0);
    glTranslatef(-0.08 / 2, -0.5 / 2, -0.05 / 2);

    glScalef(0.08, 0.5, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // right leg
    glPushMatrix();

    glTranslatef(0, 0.3, 0);
    glRotatef(-3 * bowAngle, 1, 0, 0);
    glTranslatef(0, -0.3, 0);

    glTranslatef(0.07, 0.08, 0.0);

    // swing
    glTranslatef(0.08 / 2, 0.5 / 2, 0.05 / 2);
    glRotatef(-0.5 * handSwing + 0.5 * throwAngle - walkAngle, 1, 0, 0);
    glTranslatef(-0.08 / 2, -0.5 / 2, -0.05 / 2);

    glScalef(0.08, 0.5, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //glPopMatrix();
}

void drawRoom() {
    // Draw the floor
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);  // Gray floor
    glVertex3f(-2, -1.0, -1.0);
    glVertex3f(2, -1.0, -1.0);
    glVertex3f(2, -1.0, 1.0);
    glVertex3f(-2, -1.0, 1.0);
    glEnd();
    glPopMatrix();

    // Draw the ceiling
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);  // Light gray ceiling
    glVertex3f(-2, 1.0, -1.0);
    glVertex3f(2, 1.0, -1.0);
    glVertex3f(2, 1.0, 1.0);
    glVertex3f(-2, 1.0, 1.0);
    glEnd();
    glPopMatrix();


    // Draw the left wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.6);  // Blue left wall
    glVertex3f(-2, -1.0, -1.0);
    glVertex3f(-2, -1.0, 1.0);
    glVertex3f(-2, 1.0, 1.0);
    glVertex3f(-2, 1.0, -1.0);
    glEnd();
    glPopMatrix();

    // Draw the right wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.2, 0.2);  // Red right wall
    glVertex3f(2, -1.0, -1.0);
    glVertex3f(2.0, -1.0, 1.0);
    glVertex3f(2.0, 1.0, 1.0);
    glVertex3f(2.0, 1.0, -1.0);
    glEnd();
    glPopMatrix();

    // Draw the front wall
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.6, 0.2);  // Green front wall
    glVertex3f(-2, -1.0, -1.0);
    glVertex3f(2, -1.0, -1.0);
    glVertex3f(2, 1.0, -1.0);
    glVertex3f(-2, 1.0, -1.0);
    glEnd();
    glPopMatrix();
}
    
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

    drawRoom();

    drawHuman();

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
    case ' ':
        isPlaying = true;
        bodyAngle = 0.0f;
        handSwing = 0.0f;
        walkAngle = 0.0f;
        walkBack = 0.0f;
        throwAngle = 0.0f;
        bowAngle = 0.0f;
        rotateAngle = 0.0f;
        walkForward = 0.0f;
        lastTime = glutGet(GLUT_ELAPSED_TIME);
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

    glewInit();  // Initialize GLEW to handle OpenGL extensions
    setup();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    // Start the timer
    lastTime = glutGet(GLUT_ELAPSED_TIME);

    // Set the timer function to update the scene
    glutTimerFunc(16, update, 0);  // 16 ms -> 60 FPS

    glutMainLoop();
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void draw_circle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
void draw_window(int polygon_params[4][2], int lines_params[4][2]);
void draw_door();

int main() {
    GLFWwindow *window;

    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "House", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glMatrixMode(GL_PROJECTION);

    // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glLoadIdentity();

    // essentially set coordinate system
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);

    // (default matrix mode) modelView matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glMatrixMode(GL_MODELVIEW);

    // same as above comment
    glLoadIdentity();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //main body
        glColor3f(0.1, 0.7, 0.5);
        glBegin(GL_LINE_LOOP);
        glVertex2i(200, 100);
        glVertex2i(200, 350);
        glVertex2i(100, 350);
        glVertex2i(100, 400);
        glVertex2i(700, 400);
        glVertex2i(700, 350);
        glVertex2i(600, 350);
        glVertex2i(600, 100);
        glEnd();

        // Left window
        int left_p[4][2] = {{230, 320}, {350, 320}, {350, 230}, {230, 230}};
        int left_l[4][2] = {{290, 320}, {290, 230}, {230, 273}, {350, 273}};
        draw_window(left_p, left_l);

        // Right window
        int right_p[4][2] = {{430, 320}, {550, 320}, {550, 230}, {430, 230}};
        int right_l[4][2] = {{490, 320}, {490, 230}, {430, 273}, {550, 273}};
        draw_window(right_p, right_l);

        // Front Door
        draw_door();

        // render OpenGL here
        glColor3f(255, 140, 0);
        draw_circle(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0, 30, 360);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle((SCREEN_WIDTH / 2.0f) + 10, (SCREEN_HEIGHT / 2.0f) + 10, 0, 30, 360);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void draw_circle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
    GLint numberOfVertices = numberOfSides + 2;

    GLfloat twicePi = 2.0f * M_PI;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;

    for (int i = 1; i < numberOfVertices; i++) {
        circleVerticesX[i] = x + (radius * std::cos((float) i * twicePi / (float) numberOfSides));
        circleVerticesY[i] = y + (radius * std::sin((float) i * twicePi / (float) numberOfSides));
        circleVerticesZ[i] = z;
    }

    GLfloat allCircleVertices[(numberOfVertices) * 3];

    for (int i = 0; i < numberOfVertices; i++) {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
        allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_window(int polygon_params[4][2], int lines_params[4][2]){
    // Window
    glColor3f(0.1, 0.1, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(polygon_params[0][0], polygon_params[0][1]);
    glVertex2i(polygon_params[1][0], polygon_params[1][1]);
    glVertex2i(polygon_params[2][0], polygon_params[2][1]);
    glVertex2i(polygon_params[3][0], polygon_params[3][1]);
    glEnd();

    // lines on the window
    glColor3f(0.1, 0.7, 0.5);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(lines_params[0][0], lines_params[0][1]);
    glVertex2i(lines_params[1][0], lines_params[1][1]);
    glVertex2i(lines_params[2][0], lines_params[2][1]);
    glVertex2i(lines_params[3][0], lines_params[3][1]);
    glEnd();
}

void draw_door() {
    // Front Door
    glColor3f(0.1, 0.1, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(350, 200);
    glVertex2i(425, 200);
    glVertex2i(425, 100);
    glVertex2i(350, 100);
    glEnd();


    // Front Door handle
    glColor3f(0.1, 0.7, 0.5);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(400, 150);
    glEnd();
}
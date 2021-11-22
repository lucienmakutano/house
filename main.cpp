#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void draw_circle(GLint moon_radius, GLint moon_center_x, GLint moon_center_y, GLint moon_steps, GLfloat color_points[]);

void draw_window(int polygon_params[4][2], int lines_params[4][2]);

void draw_door();

void draw_roof();

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
        glClearColor(1.0, 1.0, 1.0, 1.0);
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
        int left_p[4][2] = {{230, 320},
                            {350, 320},
                            {350, 230},
                            {230, 230}};
        int left_l[4][2] = {{290, 320},
                            {290, 230},
                            {230, 273},
                            {350, 273}};
        draw_window(left_p, left_l);

        // Right window
        int right_p[4][2] = {{430, 320},
                             {550, 320},
                             {550, 230},
                             {430, 230}};
        int right_l[4][2] = {{490, 320},
                             {490, 230},
                             {430, 273},
                             {550, 273}};
        draw_window(right_p, right_l);

        // Front Door
        draw_door();

        // Roof
        draw_roof();

        // render OpenGL here
        GLfloat c1_color[] = {255, 140, 0};
        draw_circle(50, 700, 500, 100, c1_color);

        GLfloat c2_color[] = {1.0, 1.0, 1.0};
        draw_circle(50, 725, 525, 100, c2_color);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void
draw_circle(GLint moon_radius, GLint moon_center_x, GLint moon_center_y, GLint moon_steps, GLfloat color_points[]) {
    float circle_angle = M_PI * 2.0f;
    glColor3f(color_points[0], color_points[1], color_points[2]);
    glBegin(GL_TRIANGLE_FAN);
    for (int a = 0; a <= moon_steps; a++) {
        float angle = circle_angle * float(a) / float(moon_steps);//get the current angle
        float moon_x = (float) moon_radius * cosf(angle);//calculate the x component
        float moon_y = (float) moon_radius * sinf(angle);//calculate the y component
        glVertex2f(moon_x + (float) moon_center_x, moon_y + (float) moon_center_y);//output vertex
    }
    glEnd();
}

void draw_window(int polygon_params[4][2], int lines_params[4][2]) {
    // Window
    glColor3f(0.1, 0.7, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(polygon_params[0][0], polygon_params[0][1]);
    glVertex2i(polygon_params[1][0], polygon_params[1][1]);
    glVertex2i(polygon_params[2][0], polygon_params[2][1]);
    glVertex2i(polygon_params[3][0], polygon_params[3][1]);
    glEnd();

    // lines on the window
    glColor3f(0.1, 0.1, 0.3);
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
//    glColor3f(0.1, 0.1, 0.3);
    glColor3f(0.1, 0.7, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(350, 200);
    glVertex2i(425, 200);
    glVertex2i(425, 100);
    glVertex2i(350, 100);
    glEnd();


    // Front Door handle
    glColor3f(0.1, 0.1, 0.3);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(400, 150);
    glEnd();
}

void draw_roof() {
    //semi-circle roof
    glColor3f(1.0, 1.0, 1.0);
    int center_x = 400; //x axis center
    int center_y = 400; //y axis center
    int roof_r = 100; //radius
    // int roof_d = 200; //diameter
    float semi_circle_angle = M_PI * 1.0f;
    int steps = 360;
    glColor3f(0.1, 0.7, 0.5);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < steps; i++) {
        float theta = semi_circle_angle * float(i) / float(steps);//get the current angle
        float x = (float) roof_r * cosf(theta);//calculate the x component
        float y = (float) roof_r * sinf(theta);//calculate the y component
        glVertex2f(x + (float) center_x, y + (float) center_y);//output vertex
    }
    glEnd();
}
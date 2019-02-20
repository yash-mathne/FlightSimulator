#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball, ball2;
Sea sea;

double camera_rotation_angle = 100, camera_y = 4, camera_zoom = 0, camera_look_x = -170, camera_look_y = 60;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, screen_center_z = 0;
float eye_x, eye_y, eye_z;
float tar_x, tar_y, tar_z; 
float up_x, up_y, up_z;
bool camera_ortho = false;
camera_view_t camera_view;

bool view[] = {
    false,  //origin cam
    true,   //plane view
    false,  //top view
    false,  //montain
    false,  //follow cam 
};

double xpos, ypos;
double xpos_old, ypos_old;

bool fired = false, jumped = false, camera_changed = false, game_over = false;


Timer t60(1.0 / 60);

void draw() {

    // origin
    if (view[0]) {
        eye_x = 0;
        eye_y = 2;
        eye_z = 0; 

        tar_x = 0; 
        tar_y = 0; 
        tar_z = 0; 

        up_x = 0; 
        up_y = 0; 
        up_z = 1; 
    }
    // plane view
    else if(view[1]) {
        eye_x = ball.position.x + 2.0f * ball.rmat[1][0];
        eye_y = ball.position.y + 2.0f * ball.rmat[1][1];
        eye_z = ball.position.z + 2.0f * ball.rmat[1][2]; 

        tar_x = ball.position.x + 25.0f * ball.rmat[2][0]; 
        tar_y = ball.position.y + 25.0f * ball.rmat[2][1]; 
        tar_z = ball.position.z + 25.0f * ball.rmat[2][2]; 

        up_x = ball.rmat[1][0]; 
        up_y = ball.rmat[1][1]; 
        up_z = ball.rmat[1][2]; 
    }
    // top view
    else if(view[2]) {

        eye_x = ball.position.x;
        eye_y = ball.position.y + 20.0f;
        eye_z = ball.position.z; 

        tar_x = ball.position.x; 
        tar_y = ball.position.y; 
        tar_z = ball.position.z; 

        up_x = ball.rmat[2][0]; 
        up_y = ball.rmat[2][1]; 
        up_z = ball.rmat[2][2];

    }
    // tower view
    else if(view[3]) {

        eye_x = ball.position.x + 50.0f;
        eye_y = ball.position.y + 10.0f;
        eye_z = ball.position.z - 50.0f; 

        tar_x = ball.position.x; 
        tar_y = ball.position.y; 
        tar_z = ball.position.z; 

        up_x = 0; 
        up_y = 1; 
        up_z = 0;
    }
    // follow cam
    else if(view[4]) {

        eye_x = ball.position.x + 10.0*ball.rmat[1][0] - 10.0f*ball.rmat[2][0];
        eye_y = ball.position.y + 10.0*ball.rmat[1][1] - 10.0f*ball.rmat[2][1];
        eye_z = ball.position.z + 10.0*ball.rmat[1][2] - 10.0f*ball.rmat[2][2]; 

        tar_x = ball.position.x; 
        tar_y = ball.position.y; 
        tar_z = ball.position.z;  

        up_x = ball.rmat[1][0]; 
        up_y = ball.rmat[1][1]; 
        up_z = ball.rmat[1][2]; 
    }

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);

    glm::vec3 eye = glm::vec3(eye_x, eye_y, eye_z);
    glm::vec3 target = glm::vec3(tar_x, tar_y, tar_z);
    glm::vec3 up = glm::vec3(up_x, up_y, up_z);

    glm::mat4 VP;
    Matrices.view = glm::lookAt( eye, target, up );
    if (camera_view != HELICOPTER) {
        VP = Matrices.view * glm::scale(glm::vec3(exp(camera_zoom)));
    }
    else {
        VP = Matrices.view;
    }
    if (camera_ortho){
        VP = Matrices.projectionO * VP;
    }
    else {
        VP = Matrices.projectionP * VP;
    }

    // Scene render
    ball.draw(VP);
    sea.draw(VP);
}

void tick_input(GLFWwindow *window) {
	int up    = glfwGetKey(window, GLFW_KEY_UP);
	int down    = glfwGetKey(window, GLFW_KEY_DOWN);

	// Move Boat 
	int a   = glfwGetKey(window, GLFW_KEY_A);
	int s   = glfwGetKey(window, GLFW_KEY_S);
	int d   = glfwGetKey(window, GLFW_KEY_D);
	int w   = glfwGetKey(window, GLFW_KEY_W);
    int q   = glfwGetKey(window, GLFW_KEY_Q);
	int e   = glfwGetKey(window, GLFW_KEY_E);
    int enter = glfwGetKey(window, GLFW_KEY_ENTER);
	int space = glfwGetKey(window, GLFW_KEY_SPACE);

	// Change Camera
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);

    

    if (q){
        ball.yaw -= 0.5;
    }

    if (e){
        ball.yaw += 0.5;
    }

    if (a){
        ball.roll -= 0.5;
    }

    if (d){
        ball.roll += 0.5;
    }

    if (up){
        ball.pitch += 0.5;
    }

    if (down){
        ball.pitch -= 0.5;
    }

    if (w) {
        ball.position.x += 1.5f * ball.rmat[2][0];
        ball.position.y += 1.5f * ball.rmat[2][1];
        ball.position.z += 1.5f * ball.rmat[2][2];
    }

    if (s) {
        ball.position.x -= 1.5f * ball.rmat[2][0];
        ball.position.y -= 1.5f * ball.rmat[2][1];
        ball.position.z -= 1.5f * ball.rmat[2][2];
    }

    if (one) {
        for( int i = 0; i < 5; i++) view[i] = false;
        view[0] = true; 
    }

    if (two) {
        for( int i = 0; i < 5; i++) view[i] = false;
        view[1] = true; 
    }

    if (three){
        for( int i = 0; i < 5; i++) view[i] = false;
        view[2] = true;
    }

    if (four){
        for( int i = 0; i < 5; i++) view[i] = false;
        view[3] = true; 
    }

    if (five){
        for( int i = 0; i < 5; i++) view[i] = false;
        view[4] = true; 
    }

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
}

void tick_elements() {
    ball.tick();
    sea.tick(ball.position.x, ball.position.y, ball.position.z);
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // GLuint seaTextureID = createTexture("../images/sea1.jpg");
	sea        = Sea( 0, -200, 0);
    ball       = Ball(0, 0, 0, COLOR_BLACK);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);
    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    Matrices.projectionO = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 500.0f);
    Matrices.projectionP = glm::perspective(1.0f, 1.0f, 1.0f, 500.0f);
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
struct VAO* create3DTexturedObject(GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* texture_buffer_data, GLuint textureID, GLenum fill_mode=GL_FILL);
void       draw3DObject(struct VAO *vao);
void draw3DTexturedObject (struct VAO* vao);
GLuint createTexture (const char* filename);
GLuint loadDDS(const char * imagepath);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint TextureBuffer;
    GLuint TextureID;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projectionP;
    glm::mat4 projectionO;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
    GLuint    TexMatrixID;
};
typedef struct GLMatrices GLMatrices;
extern GLMatrices Matrices;
extern GLuint ProgramID,textureProgramID;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };
enum camera_view_t {PLANE, TOP, TOWER, FOLLOW, HELICOPTER};
extern enum camera_view_t camera_view;

struct bounding_box_t {
    float x;
    float y;
    float z;
    float width;
    float height;
    float depth;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
void change_view();
extern float screen_zoom, screen_center_x, screen_center_y;
extern double camera_rotation_angle, camera_y, camera_zoom,camera_look_x, camera_look_y;
void reset_screen();

// ---- Colors ----

extern const color_t COLOR_RED;
extern const color_t COLOR_RED_B;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_SEA;
extern const color_t COLOR_WOOD;
extern const color_t COLOR_WOOD_L;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_GOLD;
extern const color_t COLOR_SKY;

extern const color_t BOAT_1;
extern const color_t BOAT_2;
extern const color_t BOAT_3;

extern const color_t MONSTER_1;
extern const color_t MONSTER_2;

const double PI = M_PI;
extern bool camera_ortho;


#endif

#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->rmat = glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=50;
    float r = 1,r2 = 1.5;
    GLfloat g_vertex_buffer_data0[9*n+9] ;
    for (int i = 0; i < n; ++i)
    {
        float a = 2*M_PI*i/n;
        float a2 = 2*M_PI*(i+1)/n;

        g_vertex_buffer_data0[9*i  ] = r*cos(a);
        g_vertex_buffer_data0[9*i+1] = r*sin(a);
        g_vertex_buffer_data0[9*i+2] = -2.0f;

        g_vertex_buffer_data0[9*i+3] = r2*cos(a);
        g_vertex_buffer_data0[9*i+4] = r2*sin(a);
        g_vertex_buffer_data0[9*i+5] = -3.0f;

        g_vertex_buffer_data0[9*i+6] = r2*cos(a2);
        g_vertex_buffer_data0[9*i+7] = r2*sin(a2);
        g_vertex_buffer_data0[9*i+8] = -3.0f;
    } 
    this->object0 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data0, color, GL_FILL);


    GLfloat g_vertex_buffer_data01[9*n+9] ;    
    for (int i = 0; i < n; ++i)
    {
        float a = 2*M_PI*i/n;
        float a2 = 2*M_PI*(i+1)/n;

        g_vertex_buffer_data01[9*i]   = r2*cos(a2);
        g_vertex_buffer_data01[9*i+1] = r2*sin(a2);
        g_vertex_buffer_data01[9*i+2] = -3.0f;

        g_vertex_buffer_data01[9*i+3] = r*cos(a);
        g_vertex_buffer_data01[9*i+4] = r*sin(a);
        g_vertex_buffer_data01[9*i+5] = -2.0f;

        g_vertex_buffer_data01[9*i+6] = r*cos(a2);
        g_vertex_buffer_data01[9*i+7] = r*sin(a2);
        g_vertex_buffer_data01[9*i+8] = -2.0f;
    } 
    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data01, color, GL_FILL);



    GLfloat g_vertex_buffer_data[9*n+9] ;
    
   
    for (int i = 0; i < n; ++i)
    {
        float a = 2*M_PI*i/n;
        float a2 = 2*M_PI*(i+1)/n;

        g_vertex_buffer_data[9*i]   = r*cos(a);
        g_vertex_buffer_data[9*i+1] = r*sin(a);
        g_vertex_buffer_data[9*i+2] = 2.0f;

        g_vertex_buffer_data[9*i+3] = r*cos(a);
        g_vertex_buffer_data[9*i+4] = r*sin(a);
        g_vertex_buffer_data[9*i+5] = -2.0f;

        g_vertex_buffer_data[9*i+6] = r*cos(a2);
        g_vertex_buffer_data[9*i+7] = r*sin(a2);
        g_vertex_buffer_data[9*i+8] = -2.0f;
    } 
    this->object2 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);


    GLfloat g_vertex_buffer_data1[9*n+9] ;
    for (int i = 0; i < n; ++i)
    {
        float a = 2*M_PI*i/n;
        float a2 = 2*M_PI*(i+1)/n;

        g_vertex_buffer_data1[9*i]   = r*cos(a2);
        g_vertex_buffer_data1[9*i+1] = r*sin(a2);
        g_vertex_buffer_data1[9*i+2] = -2.0f;

        g_vertex_buffer_data1[9*i+3] = r*cos(a);
        g_vertex_buffer_data1[9*i+4] = r*sin(a);
        g_vertex_buffer_data1[9*i+5] = 2.0f;

        g_vertex_buffer_data1[9*i+6] = r*cos(a2);
        g_vertex_buffer_data1[9*i+7] = r*sin(a2);
        g_vertex_buffer_data1[9*i+8] = 2.0f;
    } 

    this->object3 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data1, color, GL_FILL);

    GLfloat g_vertex_buffer_data2[9*n+9] ;
    for (int i = 0; i < n; ++i)
    {
        float a = 2*M_PI*i/n;
        float a2 = 2*M_PI*(i+1)/n;

        g_vertex_buffer_data2[9*i]   = 0;
        g_vertex_buffer_data2[9*i+1] = 0;
        g_vertex_buffer_data2[9*i+2] = 3.0f;

        g_vertex_buffer_data2[9*i+3] = r*cos(a);
        g_vertex_buffer_data2[9*i+4] = r*sin(a);
        g_vertex_buffer_data2[9*i+5] = 2.0f;

        g_vertex_buffer_data2[9*i+6] = r*cos(a2);
        g_vertex_buffer_data2[9*i+7] = r*sin(a2);
        g_vertex_buffer_data2[9*i+8] = 2.0f;
    } 

    this->object4 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data2, color, GL_FILL);

    float w1 = 1;
    float w2 = 3;
    float nr = r/4.0f;
    static const GLfloat vertex_buffer_data[] = {
            nr*3.0f      ,   0, -1.0f,
            nr*3.0f      ,   0,  1.0f,
            nr*3.0f +  w2,   0, -1.0f,

            -1*(nr*3.0f)     ,  0,  1.0f,
            -1*(nr*3.0f)     ,  0, -1.0f,
            -1*(nr*3.0f + w2),  0, -1.0f,

            0 , r        ,  1.0f, 
            nr, r        , -1.0f,
            nr, r + w1   , -1.0f,

            0  , r        ,  1.0f, 
            -nr, r        , -1.0f,
            -nr, r + w1   , -1.0f,     

     };
    this->object5 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y    = glm::rotate((float) (this->yaw   * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->rmat     = rotate_z * rotate_x * rotate_y;
    Matrices.model *= (translate * this->rmat);
    // Matrices.model *= (this->rmat * translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object0);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    // this->rotation += 0;
    // // this->position.x -= speed;
    // // this->position.y -= speed;
}


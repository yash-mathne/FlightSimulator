#include "main.h"
#include "bullet.h"

Bullet::Bullet(float x, float y, float z, float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->speed = 0.0;
    this->yspeed = 0.0;
    this->rotation = 0.0;
    this->is_alive = true;
    this->radius = radius;
    
    GLfloat vertex_buffer_data[90000];
    int sides = 100;
    float angle = (2 * M_PI) / float(sides);

    for(int j=0;j<sides;j++)
        for(int i=0;i<sides;i++)
        {
            int k = sides*i + j;
            vertex_buffer_data[9*k] = 0.0f;
            vertex_buffer_data[9*k + 1] = 0.0f;  
            vertex_buffer_data[9*k + 2] = radius*sin(j*angle);
            vertex_buffer_data[9*k + 3] = radius*cos(i*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 4] = radius*sin(i*angle)*cos(j*angle);
            vertex_buffer_data[9*k + 5] = radius*sin(j*angle); 
            vertex_buffer_data[9*k + 6] = radius*cos((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 7] = radius*sin((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 8] = radius*sin(j*angle); 
        }

    this->object = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, color, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bullet::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Bullet::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float D = 2 * this->radius;
    bounding_box_t bbox = { x, y, z, D, D, D };
    return bbox;
}

void Bullet::tick() {
    if (this->position.y < -5) {
        this->is_alive = false;
    }

    this->position.y += yspeed;
    this->yspeed -= 0.0005;

    this->position.x += speed * sin(rotation * M_PI / 180.0f);
    this->position.z += speed * cos(rotation * M_PI / 180.0f);   
}
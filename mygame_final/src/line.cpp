#include "line.h"
#include "main.h"

Line::Line(float fx, float fy, float tx, float ty, float len, float width, color_t color)
{
    if (tx == fx) this->rotation = ty > fy ? M_PI/2 : -M_PI/2;
    else if (ty == fy) this->rotation = tx > fx ? 0 : M_PI;
    else this->rotation = atan((ty-fy)/(tx-fx));
    this->position = glm::vec3(fx, fy, 0);
    GLfloat vertex_buffer_data [] = {
           0, -width/2, 0.0f,
         len, -width/2, 0.0f,
           0,  width/2, 0.0f,
         len,  width/2, 0.0f,
         len, -width/2, 0.0f,
           0,  width/2, 0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Line::draw(glm::mat4 VP) {
    if (!this->object) return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(0,0,1));
    glm::mat4 translate = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
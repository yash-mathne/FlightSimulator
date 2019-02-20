#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::mat4 rmat;
    float yaw,pitch,roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object0, *object1, *object2, *object3, *object4, *object5;
};

#endif // BALL_H

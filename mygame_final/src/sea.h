#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, float z);
    glm::vec3 position;
    float rotation, yspeed;
    void draw(glm::mat4 VP);
    void set_position();
    void tick(float xb, float yb, float zb);
private:
    VAO *object;
};

#endif // SEA_H

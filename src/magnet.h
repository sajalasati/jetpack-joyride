#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float timelength;
    float maxtime;
    float xspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
private:
    VAO *object1;
    VAO *object2;
};

#endif // MAGNET_H
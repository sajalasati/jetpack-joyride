#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float size;
    float radius;
    float width;
    float length;
    bool ball_contact = false;
    // float xspeed = 0.02;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
private:
    VAO *object;
};

#endif // RING_H

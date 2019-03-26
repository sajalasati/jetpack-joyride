#include "main.h"

#ifndef BOOM_H
#define BOOM_H

class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float yspeed;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
private:
    VAO *object;
};

#endif // BOOM_H

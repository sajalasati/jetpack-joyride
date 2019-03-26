#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H

#define GLM_ENABLE_EXPERIMENTAL
class Platform {
public:
    Platform() {}
    Platform(float x, float y,float lower_boundary, color_t color, int flag);
    glm::vec3 position;
    float rotation;
    float width;
    float length;
    int number;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color, float angle);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float ballradius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
    float angle;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float yspeed;
    float gap;
    float length;
    float width;
    float maxh;
    float minh;
    float ballradius;
    float lenincrate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void update_figure();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLATFORM_H
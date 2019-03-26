#include "main.h"

#ifndef SPECIAL_OBJECT_H
#define SPECIAL_OBJECT_H

#define GLM_ENABLE_EXPERIMENTAL
class Heart {
public:
    //fixed object, provides additional lives
    Heart() {}
    Heart(float x, float y, color_t color, float rad, float rot);
    glm::vec3 position;
    float rotation;
    float angle;
    float radius;
    float speed;
    float gap;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float height;
    float width;
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
private:
    VAO *object;
};

class Jet {
public:
    //fixed object, speeds up
    Jet() {}
    Jet(float x, float y,color_t color, float rot);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float height;
    float width;
    float speed;
    float gap;
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
    bool frame_collision_check();
private:
    VAO *object;
};

// class Coinbank {
// public:
//     //fixed object, provides additional coins
//     Coinbank() {}
//     Coinbank(float x, float y,float radius,color_t color);
//     glm::vec3 position;
//     float rotation;
//     void draw(glm::mat4 VP);
//     void set_position(float x, float y);
//     float radius;
//     void tick();
//     bounding_box_t bounding_box();
// private:
//     VAO *object;
// };

#endif // SPECIAL_OBJECT_H
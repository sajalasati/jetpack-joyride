#include "main.h"

#ifndef BALL_H
#define BALL_H

#define GLM_ENABLE_EXPERIMENTAL
class Ball {
public:
    Ball() {}
    Ball(float x, float y,float radius,float speed, color_t color, float yspeed);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float radius;
    double xspeed;
    double yspeed;
    bool onRing;
    bool gflag;
    int score;
    int lives;
    int direc; //0 means left, 1 means right
    void tick(bool ball_on_ring);
    void flyup(bool magnetic_field, bool ball_on_ring);
    void flydown();
    void apply_gravity();
    void frame_collision_check();
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
};

class Coin {
public:
    Coin() {}
    Coin(float x, float y,float radius, color_t color, int points);
    glm::vec3 position;
    float rotation;
    float radius;
    int points;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t a, bounding_box_t b);
    bool frame_collision_check();
private:
    VAO *object;
};

class WaterBalloon {
public:
    WaterBalloon() {}
    WaterBalloon(float x, float y,float speed,float radius, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    double xspeed;
    double yspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void apply_gravity();
    bounding_box_t bounding_box();
    bool frame_collision_check();
private:
    VAO *object;
};
#endif // BALL_H
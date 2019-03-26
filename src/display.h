#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    Display() {}
    Display(float x, float y);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    int value;
    float one[18];
    float two[18];
    float three[18];
    float four[18];
    float five[18];
    float six[18];
    float seven[18];
    void fill_one();
    void fill_two();
    void fill_three();
    void fill_four();
    void fill_five();
    void fill_six();
    void fill_seven();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int val);
    void set_objects(int val);
    bounding_box_t bounding_box();
    bool check_collision(bounding_box_t ball);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // DISPLAY_H
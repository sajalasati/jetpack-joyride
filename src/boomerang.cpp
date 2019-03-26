#include "boomerang.h"
#include "unistd.h"
#include "main.h"
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->size = 0.4;
    this->yspeed = 0.03;
    float xpos=this->size/2, bigy=this->size*2*sin(M_PI/3)/3, smally=this->size*sin(M_PI/3)/3; 
    GLfloat vertex_buffer_data[] = {
        0.0f,bigy,0.0f,
        -xpos,-smally,0.0f,
        xpos,-smally,0.0f,
        -xpos,smally,0.0f,
        xpos,smally,0.0f,
        0.0f,-bigy,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->position[1] -= this->yspeed;
    this->position[0] = (this->position[1])*(this->position[1])/2 - 5 + screen_center_x;
    this->rotation += 10;
}

bool Boomerang::check_collision(bounding_box_t ball){
    float myradius = this->size*2*sin(M_PI/3)/3;
    return abs(ball.x-this->position[0])*abs(ball.x-this->position[0]) + abs(ball.y-this->position[1])*abs(ball.y-this->position[1]) <= (myradius+ball.width)*(myradius+ball.width);
}

bool Boomerang::frame_collision_check(){
    if(this->position[1] <= -4) return true;
    return false;
}
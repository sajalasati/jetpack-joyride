#include "magnet.h"
#include "unistd.h"
#include "main.h"
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.8;
    this->width = 0.2;
    this->xspeed = 0.25;
    this->timelength = 0.0;
    this->maxtime = 4;
    GLfloat vertex_buffer_data1[] = {
        
        0.0f, 1.5f*(this->width),0.0f,
        0.0f,this->width,0.0f,
        this->width, this->width, 0.0f,
        0.0f, 1.5f*(this->width),0.0f,
        this->width, 1.5f*this->width, 0.0f,
        this->width, this->width, 0.0f,

        0.0f,this->width,0.0f,
        0.0f,0.0f,0.0f,
        this->length, 0.0f, 0.0f,
        0.0f,this->width,0.0f,
        this->length,this->width,0.0f,
        this->length, 0.0f, 0.0f,

        this->length - this->width, 1.5f*(this->width),0.0f,
        this->length - this->width,this->width,0.0f,
        this->length, this->width, 0.0f,
        this->length - this->width, 1.5f*(this->width),0.0f,
        this->length, 1.5f*this->width, 0.0f,
        this->length, this->width, 0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data1, COLOR_FIREBEAM, GL_FILL);
    GLfloat vertex_buffer_data2[] = {
        0.0f,2.0f*this->width,0.0f,
        0.0f, 1.5f*(this->width),0.0f,
        this->width, 1.5f*(this->width),0.0f,
        0.0f,2.0f*this->width,0.0f,
        this->width, 2.0f*(this->width),0.0f,
        this->width, 1.5f*(this->width),0.0f,

        this->length-this->width,2.0f*this->width,0.0f,
        this->length-this->width, 1.5f*(this->width),0.0f,
        this->length, 1.5f*(this->width),0.0f,
        this->length-this->width,2.0f*this->width,0.0f,
        this->length, 2.0f*(this->width),0.0f,
        this->length, 1.5f*(this->width),0.0f,

    };
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, COLOR_WHITE, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    this->position[0] += 0.02;
    this->timelength += (1.0)/60;
}

bool Magnet::check_collision(bounding_box_t ball){
    
}
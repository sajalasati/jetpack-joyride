#include "special_objects.h"
#include "unistd.h"
#include "main.h"
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL

Heart::Heart(float x, float y, color_t color, float rad, float rot) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = rot;
    this->angle = (M_PI/6);
    this->radius = rad;

    float a = 4.0f - wall_width - (this->position[1]+this->radius);
    float b = (this->position[1] - 1.5*(this->radius)/tan(angle)) - (wall_width - 4.0f) ;
    if(a>=b) this->gap = b;
    else this->gap = a;
    this->gap = (this->gap <= 2)? this->gap:2;
    int n = 100; //sides of n-sided polygon
    GLfloat vertex_buffer_data[909];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = 0.0f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 4*(this->radius);
    vertex_buffer_data[4] = 0.0f;
    vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6] = 2*(this->radius);
    vertex_buffer_data[7] = -1.5*(this->radius)/tan(angle); //will affect collision function
    vertex_buffer_data[8] = 0.0f;
    
    double x_cord, y_cord, t1, t2;
    double theta = 0, ang = (2 * M_PI) / n, xcentre, radius = this->radius;
    for(int j=0;j<2;++j){
        xcentre = (j==0)? (this->radius) : 3*(this->radius);
        theta = 0;
        for (int i = 0; i < n/2; ++i)
        {
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i + 450*j+9] = 0.0f+xcentre;
            vertex_buffer_data[9 * i + 1+ 450*j+9] = 0.0f;
            vertex_buffer_data[9 * i + 2+ 450*j+9] = 0.0f;
            vertex_buffer_data[9 * i + 3+ 450*j+9] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 4+ 450*j+9] = y_cord;
            vertex_buffer_data[9 * i + 5+ 450*j+9] = 0.0f;
            theta += ang;
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * (i) + 6+ 450*j+9] = x_cord+xcentre;
            vertex_buffer_data[9 * (i) + 7+ 450*j+9] = y_cord;
            vertex_buffer_data[9 * (i) + 8+ 450*j+9] = 0.0f;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 303, vertex_buffer_data, color, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Heart::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Heart::tick() {
    if(this->speed==0)this->position.x += screen_speed;
    this->rotation += this->speed;
    if(this->speed!=0){
        if(this->position.x - this->width <= screen_center_x + 3.0f){
            this->position.x += 0.01;
            this->position.y = this->gap*(sin(this->position.x));
        }
        this->position.y -= speed/100;
    }
    
}

bool Heart::check_collision(bounding_box_t ball){
    bool r1=false,r2=false,r3=false,r4=false,r5=false,r6=false;
    float a = this->position[0]+this->radius, b = this->position[1];
    r1 = (abs(ball.x - a)*abs(ball.x - a) + abs(ball.y - b)*abs(ball.y - b) <= abs(ball.width + this->radius)*abs(ball.width + this->radius));     
    a += 2*(this->radius);
    r2 = (abs(ball.x - a)*abs(ball.x - a) + abs(ball.y - b)*abs(ball.y - b) <= abs(ball.width + this->radius)*abs(ball.width + this->radius));     
    float m = 1.0f/(tan(this->angle));
    float numer1 = abs(ball.y +m*ball.x - b -m*this->position[0]);
    a = this->position[0] + 2*this->radius; // should be acc to collison function
    float numer2 = abs(ball.y - m*ball.x - b + m*a);
    float denom = sqrt(1 + m*m);
    float dist = numer1/denom;
    float y_up = this->position[1]-ball.width*cos(angle);
    float y_down = this->position[1]-1.5*(this->radius)/tan(angle)-ball.width*cos(angle);
    float x_min = this->position[0];
    float x_max = this->position[0] + 2*this->radius;
    r3 = (dist <= (ball.width)) && (ball.y <= y_up) && (ball.y >= y_down) && (ball.x <= x_max) && (ball.x >= x_min);
    x_min = this->position[0] + 2*this->radius;
    x_max = this->position[0] + 4*this->radius;
    dist = numer2/denom;
    r4 = (dist <= (ball.width)) && (ball.y <= y_up) && (ball.y >= y_down) && (ball.x <= x_max) && (ball.x >= x_min);
    return (r1||r2||r3||r4);
}

bool Heart::frame_collision_check(){
    return (this->position.x - 2*this->radius <= screen_center_x - 4.0f);
}

Jet::Jet(float x, float y,color_t color,float rot) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = rot;
    this->width = 0.4f;
    float a = 4.0f - wall_width - (this->position[1]+this->width);
    float b = (this->position[1] - this->width) - (wall_width - 4.0f) ;
    if(a>=b){
        this->gap = b;
    }
    else this->gap = a;
    this->gap = (this->gap <= 2)? this->gap:2;
    GLfloat vertex_buffer_data[] = {
        0.0f,this->width,0.0f,
        this->width,0.0f,0.0f,
        0.0f,-this->width,0.0f,
        0.0f,this->width,0.0f,
        0.0f,-this->width,0.0f,
        -this->width,0.0f,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Jet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Jet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Jet::tick() {
    this->rotation += this->speed;
    if(this->position.x - this->width <= screen_center_x + 3.0f){
        this->position.x += 0.01;
        this->position.y = this->gap*(sin(this->position.x));
        // this->position.y -= speed/100;
        if(this->position.y <= this->width - 4.0f + platform_width){
            this->position.y = this->width - 4.0f + platform_width;
        }
    }
}

bool Jet::check_collision(bounding_box_t ball){
    return ((ball.x - this->position.x)*(ball.x - this->position.x) + (ball.y - this->position.y)*(ball.y - this->position.y) <= (ball.width + this->width)*(ball.width + this->width));
}

bool Jet::frame_collision_check(){
    return (this->position.x + this->width <= screen_center_x - 4.0f);
}
#include "platform.h"
#include "main.h"
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL

Platform::Platform(float x, float y,float lower_boundary, color_t color, int flag) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    if(flag) this->width = platform_width;
    else this->width = wall_width;
    this->length = 2;
    this->number = 250; //pairs of sqaures = total 500
    float starting = -5.0f;
    GLfloat vertex_buffer_data[this->number*36];
    for(int i=0; i<this->number; i++){
        for(int j=0; j<2;++j){
            color_t col = (j==0)? COLOR_BROWN:COLOR_BROWN2;
            vertex_buffer_data[36*i + 18*j] = (2*i + j)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+1] = lower_boundary+this->width;
            vertex_buffer_data[36*i + 18*j+2] = 0.0f;
            vertex_buffer_data[36*i + 18*j+3] = (2*i + j)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+4] = lower_boundary;
            vertex_buffer_data[36*i + 18*j+5] = 0;
            vertex_buffer_data[36*i + 18*j+6] = (2*i + j+1)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+7] = lower_boundary;
            vertex_buffer_data[36*i + 18*j+8] = 0.0f;
            vertex_buffer_data[36*i + 18*j+9] = (2*i + j)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+10] = lower_boundary+this->width;
            vertex_buffer_data[36*i + 18*j+11] = 0.0f;
            vertex_buffer_data[36*i + 18*j+12] = (2*i + j+1)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+13] = lower_boundary+this->width;
            vertex_buffer_data[36*i + 18*j+14] = 0;
            vertex_buffer_data[36*i + 18*j+15] = (2*i + j+1)*(this->length)+starting;
            vertex_buffer_data[36*i + 18*j+16] = lower_boundary;
            vertex_buffer_data[36*i + 18*j+17] = 0.0f;
        }    
    }
    this->object = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Platform::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Platform::tick() {
    // this->position.y -= speed;
}

Fireline::Fireline(float x, float y, color_t color, float angle) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    this->length = 3.0f;
    this->width = 0.05f;
    this->ballradius = 0.16;
    this->angle = (this->rotation)*(M_PI/180.0f);
    GLfloat vertex_buffer_data[1818];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = this->width;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.0f;
    vertex_buffer_data[4] = -this->width;
    vertex_buffer_data[5] = 0;
    vertex_buffer_data[6] = this->length;
    vertex_buffer_data[7] = -this->width;
    vertex_buffer_data[8] = 0;
    vertex_buffer_data[9] = 0.0f;
    vertex_buffer_data[10] = this->width;
    vertex_buffer_data[11] = 0;
    vertex_buffer_data[12] = this->length;
    vertex_buffer_data[13] = this->width;
    vertex_buffer_data[14] = 0;
    vertex_buffer_data[15] = this->length;
    vertex_buffer_data[16] = -this->width;
    vertex_buffer_data[17] = 0;

    //code for circle won't change

    int n = 100; //sides of n-sided polygon
    double x_cord, y_cord, t1, t2, radius = this->ballradius, xcentre, ycentre=y;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    for(int j=0;j<2;++j){
        xcentre = (j==0) ? 0 : this->length;
        for (int i = 0; i < 100; ++i)
        {
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i+900*j+18] = 0.0f+xcentre;
            vertex_buffer_data[9 * i + 1+900*j+18] = 0.0f;
            vertex_buffer_data[9 * i + 2+900*j+18] = 0.0f;
            vertex_buffer_data[9 * i + 3+900*j+18] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 4+900*j+18] = y_cord;
            vertex_buffer_data[9 * i + 5+900*j+18] = 0.0f;
            theta += ang;
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i + 6+900*j+18] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 7+900*j+18] = y_cord;
            vertex_buffer_data[9 * i + 8+900*j+18] = 0.0f;
        }   
    }

    this->object = create3DObject(GL_TRIANGLES, 606, vertex_buffer_data, color, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
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

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    // this->position.y -= speed;
    // this->rotation += 1;
}

bool Fireline::check_collision(bounding_box_t ball) {
    bool r1=false,r2=false,r3=false;
    float a = this->position[0], b = this->position[1];
    float numer = abs(-ball.y + tan(angle)*ball.x + b - a*tan(angle));
    r1 = (abs(ball.x - a)*abs(ball.x - a) + abs(ball.y - b)*abs(ball.y - b) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    a += 3*cos(this->angle), b += 3*sin(this->angle);
    r2 = (abs(ball.x - a)*abs(ball.x - a) + abs(ball.y - b)*abs(ball.y - b) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    float denom = sqrt(1+tan(this->angle)*tan(this->angle));
    float dist = numer/denom;
    r3 = (dist <= (ball.width)) && (ball.x+ball.width >= this->position[0]) && (ball.x-ball.width <= this->position[0]+3*cos(this->angle)); 
    return (r1||r2||r3);
}

bool Fireline::frame_collision_check(){
    if(this->position[0] + this->length*cos(angle) <=screen_center_x - 4) return true;
    return false;
}

Firebeam::Firebeam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0f;
    this->yspeed = 0.01; //adjust for faster movement
    // this->length = 3;
    this->length = 0;
    this->gap = 3.0f;
    this->width = 0.05f;
    this->ballradius = 0.16;
    this->lenincrate = 0.01f;
    this->maxh = 4-wall_width-this->ballradius; //1 up and below is the movement gap taken
    this->minh = -4+platform_width+this->ballradius;
    GLfloat vertex_buffer_data[3636];
    for(int i=0;i<2;++i){
        float ad=0.0f;
        if(i==1) ad = this->gap;
        vertex_buffer_data[0+18*i] = 0.0f;
        vertex_buffer_data[1+18*i] = this->width-ad;
        vertex_buffer_data[2+18*i] = 0.0f;
        vertex_buffer_data[3+18*i] = 0.0f;
        vertex_buffer_data[4+18*i] = -this->width-ad;
        vertex_buffer_data[5+18*i] = 0;
        vertex_buffer_data[6+18*i] = this->length;
        vertex_buffer_data[7+18*i] = -this->width-ad;
        vertex_buffer_data[8+18*i] = 0;
        vertex_buffer_data[9+18*i] = 0.0f;
        vertex_buffer_data[10+18*i] = this->width-ad;
        vertex_buffer_data[11+18*i] = 0;
        vertex_buffer_data[12+18*i] = this->length;
        vertex_buffer_data[13+18*i] = this->width-ad;
        vertex_buffer_data[14+18*i] = 0;
        vertex_buffer_data[15+18*i] = this->length;
        vertex_buffer_data[16+18*i] = -this->width-ad;
        vertex_buffer_data[17+18*i] = 0;
    }

    //code for circle won't change

    int n = 100; //sides of n-sided polygon
    double x_cord, y_cord, t1, t2, radius = this->ballradius, xcentre, ycentre;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    
    for(int j=0;j<4;++j){
        xcentre = (j%2==0) ? 0 : this->length;
        ycentre = (j>=2) ? 0 : -this->gap;
        for (int i = 0; i < 100; ++i)
        {
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i+900*j+36] = 0.0f+xcentre;
            vertex_buffer_data[9 * i + 1+900*j+36] = 0.0f+ycentre;
            vertex_buffer_data[9 * i + 2+900*j+36] = 0.0f;
            vertex_buffer_data[9 * i + 3+900*j+36] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 4+900*j+36] = y_cord+ycentre;
            vertex_buffer_data[9 * i + 5+900*j+36] = 0.0f;
            theta += ang;
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i + 6+900*j+36] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 7+900*j+36] = y_cord+ycentre;
            vertex_buffer_data[9 * i + 8+900*j+36] = 0.0f;
        }   
    }

    this->object = create3DObject(GL_TRIANGLES, 1212, vertex_buffer_data, color, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    this->position.y += this->yspeed;
    if((this->position.y >= this->maxh) || (this->position.y-this->gap <= this->minh)) this->yspeed *= -1;
    if(this->position[0]<=screen_center_x + 3.8){
        if(this->length+this->lenincrate <= 4.0f) this->length += this->lenincrate;
    }
    this->update_figure();
}

bool Firebeam::frame_collision_check(){
    if(this->position[0] + this->length <=screen_center_x - 4) return true;
    return false;
}

void Firebeam::update_figure(){
    GLfloat vertex_buffer_data[3636];
    for(int i=0;i<2;++i){
        float ad=0.0f;
        if(i==1) ad = this->gap;
        vertex_buffer_data[0+18*i] = 0.0f;
        vertex_buffer_data[1+18*i] = this->width-ad;
        vertex_buffer_data[2+18*i] = 0.0f;
        vertex_buffer_data[3+18*i] = 0.0f;
        vertex_buffer_data[4+18*i] = -this->width-ad;
        vertex_buffer_data[5+18*i] = 0;
        vertex_buffer_data[6+18*i] = this->length;
        vertex_buffer_data[7+18*i] = -this->width-ad;
        vertex_buffer_data[8+18*i] = 0;
        vertex_buffer_data[9+18*i] = 0.0f;
        vertex_buffer_data[10+18*i] = this->width-ad;
        vertex_buffer_data[11+18*i] = 0;
        vertex_buffer_data[12+18*i] = this->length;
        vertex_buffer_data[13+18*i] = this->width-ad;
        vertex_buffer_data[14+18*i] = 0;
        vertex_buffer_data[15+18*i] = this->length;
        vertex_buffer_data[16+18*i] = -this->width-ad;
        vertex_buffer_data[17+18*i] = 0;
    }
    //code for circle won't change
    int n = 100; //sides of n-sided polygon
    double x_cord, y_cord, t1, t2, radius = this->ballradius, xcentre, ycentre;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    
    for(int j=0;j<4;++j){
        xcentre = (j%2==0) ? 0 : this->length;
        ycentre = (j>=2) ? 0 : -this->gap;
        for (int i = 0; i < 100; ++i)
        {
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i+900*j+36] = 0.0f+xcentre;
            vertex_buffer_data[9 * i + 1+900*j+36] = 0.0f+ycentre;
            vertex_buffer_data[9 * i + 2+900*j+36] = 0.0f;
            vertex_buffer_data[9 * i + 3+900*j+36] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 4+900*j+36] = y_cord+ycentre;
            vertex_buffer_data[9 * i + 5+900*j+36] = 0.0f;
            theta += ang;
            x_cord = cos(theta) * radius;
            y_cord = sin(theta) * radius;
            vertex_buffer_data[9 * i + 6+900*j+36] = x_cord+xcentre;
            vertex_buffer_data[9 * i + 7+900*j+36] = y_cord+ycentre;
            vertex_buffer_data[9 * i + 8+900*j+36] = 0.0f;
        }   
    }

    this->object = create3DObject(GL_TRIANGLES, 1212, vertex_buffer_data, COLOR_FIREBEAM, GL_FILL);
}

bool Firebeam::check_collision(bounding_box_t ball) {
    bool r1=false,r2=false,r3=false,r4=false,r5=false,r6=false;
    float a1 = this->position[0], a2 = this->position[0]+this->length;
    float b1 = this->position[1], b2 = this->position[1]-this->gap;
    r1 = (abs(ball.x - a1)*abs(ball.x - a1) + abs(ball.y - b1)*abs(ball.y - b1) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    r2 = (abs(ball.x - a1)*abs(ball.x - a1) + abs(ball.y - b2)*abs(ball.y - b2) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    r3 = (abs(ball.x - a2)*abs(ball.x - a2) + abs(ball.y - b1)*abs(ball.y - b1) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    r4 = (abs(ball.x - a2)*abs(ball.x - a2) + abs(ball.y - b2)*abs(ball.y - b2) <= abs(ball.width + this->ballradius)*abs(ball.width + this->ballradius));     
    r5 = (ball.width + this->width >= abs(ball.y - b1)) && (ball.x+ball.width >= this->position[0]) && (ball.x-ball.width <= this->position[0]+this->length);
    r6 = (ball.width + this->width >= abs(ball.y - b2)) && (ball.x+ball.width >= this->position[0]) && (ball.x-ball.width <= this->position[0]+this->length);
    return (r1||r2||r3||r4||r5|r6);
}
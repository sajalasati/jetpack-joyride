#include "ball.h"
#include "main.h"
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL

Ball::Ball(float x, float y,float radius,float speed, color_t color, float yspeed) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->xspeed = speed;
    this->yspeed = yspeed;
    this->score = 0;
    this->direc = 1;
    this->lives = 5;
    this->gflag = true; // initially don't apply gravity
    int n = 100; //sides of n-sided polygon
    GLfloat g_vertex_buffer_data[9*n];
    double x_cord, y_cord, t1, t2;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    for (int i = 0; i < n; ++i)
    {
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * i] = 0.0f;
        g_vertex_buffer_data[9 * i + 1] = 0.0f;
        g_vertex_buffer_data[9 * i + 2] = 0.0f;
        g_vertex_buffer_data[9 * i + 3] = x_cord;
        g_vertex_buffer_data[9 * i + 4] = y_cord;
        g_vertex_buffer_data[9 * i + 5] = 0.0f;
        theta += ang;
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * (i) + 6] = x_cord;
        g_vertex_buffer_data[9 * (i) + 7] = y_cord;
        g_vertex_buffer_data[9 * (i) + 8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);
    GLfloat g_vertex_buffer_data2[]{
        -0.05-0.3,-this->radius-0.02f,0.0f,
        -0.05-0.3,-this->radius-0.1f-0.02f,0.0f,
        +0.05-0.3,-this->radius-0.1f-0.02f,0.0f,
        -0.05-0.3,-this->radius-0.1f,0.0f,
        +0.05-0.3,-this->radius-0.02f,0.0f,
        +0.05-0.3,-this->radius-0.1f-0.02f,0.0f,

        -0.05-0.15,-this->radius-0.02f,0.0f,
        -0.05-0.15,-this->radius-0.1f-0.02f,0.0f,
        +0.05-0.15,-this->radius-0.1f-0.02f,0.0f,
        -0.05-0.15,-this->radius-0.1f,0.0f,
        +0.05-0.15,-this->radius-0.02f,0.0f,
        +0.05-0.15,-this->radius-0.1f-0.02f,0.0f,
        
        -0.05,-this->radius-0.02f,0.0f,
        -0.05,-this->radius-0.1f-0.02f,0.0f,
        +0.05,-this->radius-0.1f-0.02f,0.0f,
        -0.05,-this->radius-0.1f,0.0f,
        +0.05,-this->radius-0.02f,0.0f,
        +0.05,-this->radius-0.1f-0.02f,0.0f,
        
        -0.05+0.15,-this->radius-0.02f,0.0f,
        -0.05+0.15,-this->radius-0.1f-0.02f,0.0f,
        +0.05+0.15,-this->radius-0.1f-0.02f,0.0f,
        -0.05+0.15,-this->radius-0.1f,0.0f,
        +0.05+0.15,-this->radius-0.02f,0.0f,
        +0.05+0.15,-this->radius-0.1f-0.02f,0.0f,

        -0.05+0.3,-this->radius-0.02f,0.0f,
        -0.05+0.3,-this->radius-0.1f-0.02f,0.0f,
        +0.05+0.3,-this->radius-0.1f-0.02f,0.0f,
        -0.05+0.3,-this->radius-0.1f,0.0f,
        +0.05+0.3,-this->radius-0.02f,0.0f,
        +0.05+0.3,-this->radius-0.1f-0.02f,0.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES,30, g_vertex_buffer_data2, COLOR_WHITE, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(jet_propulsion) draw3DObject(this->object2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(bool ball_on_ring) {
    //moves the ball in x and y
    this->position.x += (xspeed)/25;
    // this->position.x += screen_speed;

    if(!ball_on_ring){
        this->position.y += yspeed;
    }
}

void Ball::flyup(bool magnetic_field, bool ball_on_ring) {
    /* in 1 cycle -> net upwards vel += 0.0055, hence
        i) v<0 only when moving downwards
        ii) if continuously SPACE is pressed -> gain of +0.0055 in velocity each time 
    */
    if(ball_on_ring) return;
    if(this->yspeed < 0) this->yspeed = 0.01; 
    this->yspeed += 0.00900;
    if(magnetic_field){
        if(this->yspeed >= 0.02) this->yspeed=0.02;
    }
}

void Ball::flydown() {
    this->position.y -= 0.0800;
}

void Ball::apply_gravity() {
    if(this->gflag) this->yspeed -=0.00350; // effect of gravity
}

bounding_box_t Ball::bounding_box() {
    return {this->position.x, this->position.y, this->radius, this->radius};
}

void Ball::frame_collision_check(){
    if(this->position[1]>=4-wall_width-this->radius) {
        this->position[1] = 4-wall_width-this->radius;
        this->yspeed = 0;
    }
    if(this->position[1]<=-4+platform_width+this->radius){
        this->position[1] = -4+platform_width+this->radius;
        this->gflag = false;
        this->yspeed = 0;
    }
    if(this->position[0]<=screen_center_x - (4.0 - (this->radius+0.1))) this->position[0] = screen_center_x - (4.0 - (this->radius+0.1));
    if(this->position[0]>=screen_center_x + (4.0 - (this->radius+0.1))) this->position[0] = screen_center_x + (4.0 - (this->radius+0.1));
}

Coin::Coin(float x, float y,float radius,color_t color, int points) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->points = points;
    int n = 100; //sides of n-sided polygon
    GLfloat g_vertex_buffer_data[9*n];
    double x_cord, y_cord, t1, t2;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    for (int i = 0; i < n; ++i)
    {
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * i] = 0.0f;
        g_vertex_buffer_data[9 * i + 1] = 0.0f;
        g_vertex_buffer_data[9 * i + 2] = 0.0f;
        g_vertex_buffer_data[9 * i + 3] = x_cord;
        g_vertex_buffer_data[9 * i + 4] = y_cord;
        g_vertex_buffer_data[9 * i + 5] = 0.0f;
        theta += ang;
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * (i) + 6] = x_cord;
        g_vertex_buffer_data[9 * (i) + 7] = y_cord;
        g_vertex_buffer_data[9 * (i) + 8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
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

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    //moves the ball in x and y
    // this->position.x += 1;
    // this->position.y += 1;
}

bounding_box_t Coin::bounding_box() {
    return {this->position.x, this->position.y, this->radius, this->radius};
}

bool Coin::check_collision(bounding_box_t a, bounding_box_t b) {
    double X = abs(a.x - b.x), Y = abs(a.y - b.y), R = (a.width + b.width);
    return (X*X + Y*Y <= R*R);
}

bool Coin::frame_collision_check(){
    return (this->position[0] - this->radius) <= screen_center_x - 4.0f;
}

WaterBalloon::WaterBalloon(float x, float y,float radius,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->xspeed = speed;
    this->yspeed = 0.1; //fixed for now
    int n = 100; //sides of n-sided polygon
    GLfloat g_vertex_buffer_data[9*n];
    double x_cord, y_cord, t1, t2;
    double theta = M_PI / n, ang = (2 * M_PI) / n;
    for (int i = 0; i < n; ++i)
    {
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * i] = 0.0f;
        g_vertex_buffer_data[9 * i + 1] = 0.0f;
        g_vertex_buffer_data[9 * i + 2] = 0.0f;
        g_vertex_buffer_data[9 * i + 3] = x_cord;
        g_vertex_buffer_data[9 * i + 4] = y_cord;
        g_vertex_buffer_data[9 * i + 5] = 0.0f;
        theta += ang;
        x_cord = cos(theta) * radius;
        y_cord = sin(theta) * radius;
        g_vertex_buffer_data[9 * (i) + 6] = x_cord;
        g_vertex_buffer_data[9 * (i) + 7] = y_cord;
        g_vertex_buffer_data[9 * (i) + 8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);
}

void WaterBalloon::draw(glm::mat4 VP) {
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

void WaterBalloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void WaterBalloon::tick() {
    //moves the WaterBalloon in x and y
    this->position.x += (xspeed)/25;
    this->position.y += yspeed;
}

void WaterBalloon::apply_gravity() {
    this->yspeed -=0.00350; // effect of gravity
}

bounding_box_t WaterBalloon::bounding_box() {
    return {this->position.x, this->position.y, this->radius, this->radius};
}

bool WaterBalloon::frame_collision_check(){
    if(this->position[1]>=4-wall_width || this->position[1]<=-4+platform_width) return true;
    if(this->position[0]<=screen_center_x - 4 - this->radius || this->position[0]>=screen_center_x + 4 + this->radius) return true;
    return false;
}
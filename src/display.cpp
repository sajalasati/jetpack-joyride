#include "display.h"
#include "unistd.h"
#include "main.h"
#include <math.h>
#include <iostream>
using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

Display::Display(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.3;
    this->width = 0.05;
    this->value = 2;
    this->set_objects(this->value);

}

void Display::set_objects(int val){
    int find_d[10][8]={
        0,1,1,1,0,1,1,1,
        0,0,0,1,0,0,1,0,
        0,1,0,1,1,1,0,1,
        0,1,0,1,1,0,1,1,
        0,0,1,1,1,0,1,0,
        0,1,1,0,1,0,1,1,
        0,1,1,0,1,1,1,1,
        0,1,0,1,0,0,1,0,
        0,1,1,1,1,1,1,1,
        0,1,1,1,1,0,1,1
    };

    int d1 = val%10; val/=10; 
    int d2 = val%10; val/=10; 
    int d3 = val%10; 

    this->fill_one();
    this->fill_two();
    this->fill_three();
    this->fill_four();
    this->fill_five();
    this->fill_six();
    this->fill_seven();

    //digit d3
    int len = 0, cur=0;
    float moveby = 0.0f;
    for(int i=0;i<=7;++i){
        if(find_d[d3][i]==1)++len;
    }
    GLfloat vertex_buffer_data1[len*18];
    if(find_d[d3][1]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->one[i]+moveby:this->one[i];
    }
    if(find_d[d3][2]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->two[i]+moveby:this->two[i];
    }
    if(find_d[d3][3]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->three[i]+moveby:this->three[i];
    }
    if(find_d[d3][4]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->four[i]+moveby:this->four[i];
    }
    if(find_d[d3][5]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->five[i]+moveby:this->five[i];
    }
    if(find_d[d3][6]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->six[i]+moveby:this->six[i];
    }
    if(find_d[d3][7]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data1[cur++] = (i%3==0)? this->seven[i]+moveby:this->seven[i];
    }
    this->object1 = create3DObject(GL_TRIANGLES, len*6, vertex_buffer_data1, COLOR_WHITE, GL_FILL);

    //digit d2
    len=0; cur=0; moveby += this->length + 0.2;
    for(int i=0;i<=7;++i){
        if(find_d[d2][i]==1)++len;
    }
    GLfloat vertex_buffer_data2[len*18];
    if(find_d[d2][1]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->one[i]+moveby:this->one[i];
    }
    if(find_d[d2][2]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->two[i]+moveby:this->two[i];
    }
    if(find_d[d2][3]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->three[i]+moveby:this->three[i];
    }
    if(find_d[d2][4]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->four[i]+moveby:this->four[i];
    }
    if(find_d[d2][5]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->five[i]+moveby:this->five[i];
    }
    if(find_d[d2][6]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->six[i]+moveby:this->six[i];
    }
    if(find_d[d2][7]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data2[cur++] = (i%3==0)? this->seven[i]+moveby:this->seven[i];
    }
    this->object2 = create3DObject(GL_TRIANGLES, len*6, vertex_buffer_data2, COLOR_WHITE, GL_FILL);


    // digit d1
    len=0; cur=0; moveby += this->length + 0.2;
    for(int i=0;i<=7;++i){
        if(find_d[d1][i]==1)++len;
    }
    GLfloat vertex_buffer_data3[len*18];
    if(find_d[d1][1]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->one[i]+moveby:this->one[i];
    }
    if(find_d[d1][2]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->two[i]+moveby:this->two[i];
    }
    if(find_d[d1][3]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->three[i]+moveby:this->three[i];
    }
    if(find_d[d1][4]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->four[i]+moveby:this->four[i];
    }
    if(find_d[d1][5]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->five[i]+moveby:this->five[i];
    }
    if(find_d[d1][6]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->six[i]+moveby:this->six[i];
    }
    if(find_d[d1][7]==1){
        for(int i=0; i<18; ++i)vertex_buffer_data3[cur++] = (i%3==0)? this->seven[i]+moveby:this->seven[i];
    }
    this->object3 = create3DObject(GL_TRIANGLES, len*6, vertex_buffer_data3, COLOR_WHITE, GL_FILL);

}

void Display::draw(glm::mat4 VP) {
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
    draw3DObject(this->object3);
}

void Display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Display::tick(int val) {
    this->position[0] += screen_speed;
    this->set_objects(val);
    // this->timelength += (1.0)/60;
}

bool Display::check_collision(bounding_box_t ball){
    // 
}

void Display::fill_one(){
    float a = this->length, b = this->width;
    this->one[0] = 0.0f;
    this->one[1] = a;
    this->one[2] = 0.0f;
    this->one[3] = 0.0f;
    this->one[4] = a-b;
    this->one[5] = 0.0f;
    this->one[6] = a;
    this->one[7] = a-b;
    this->one[8] = 0.0f;
    this->one[9] = 0.0f;
    this->one[10] = a;
    this->one[11] = 0.0f;
    this->one[12] = a;
    this->one[13] = a;
    this->one[14] = 0.0f;
    this->one[15] = a;
    this->one[16] = a-b;
    this->one[17] = 0.0f;
}

void Display::fill_two(){
    float a = this->length, b = this->width;
    this->two[0] = 0.0f;
    this->two[1] = 0.0f;
    this->two[2] = 0.0f;
    this->two[3] = 0.0f;
    this->two[4] = a;
    this->two[5] = 0.0f;
    this->two[6] = b;
    this->two[7] = 0.0f;
    this->two[8] = 0.0f;
    this->two[9] = b;
    this->two[10] = 0.0f;
    this->two[11] = 0.0f;
    this->two[12] = 0.0f;
    this->two[13] = a;
    this->two[14] = 0.0f;
    this->two[15] = b;
    this->two[16] = a;
    this->two[17] = 0.0f;
}

void Display::fill_three(){
    float a = this->length, b = this->width;
    this->three[0] = a-b;
    this->three[1] = a;
    this->three[2] = 0.0f;
    this->three[3] = a-b;
    this->three[4] = 0.0f;
    this->three[5] = 0.0f;
    this->three[6] = a;
    this->three[7] = 0.0f;
    this->three[8] = 0.0f;
    this->three[9] = a-b;
    this->three[10] = a;
    this->three[11] = 0.0f;
    this->three[12] = a;
    this->three[13] = a;
    this->three[14] = 0.0f;
    this->three[15] = a;
    this->three[16] = 0.0f;
    this->three[17] = 0.0f;
}

void Display::fill_four(){
    float a = this->length, b = this->width;
    this->four[0] = 0.0f;
    this->four[1] = 0.0f;
    this->four[2] = 0.0f;
    this->four[3] = 0.0f;
    this->four[4] = -b;
    this->four[5] = 0.0f;
    this->four[6] = a;
    this->four[7] = -b;
    this->four[8] = 0.0f;
    this->four[9] = 0.0f;
    this->four[10] = 0.0f;
    this->four[11] = 0.0f;
    this->four[12] = a;
    this->four[13] = 0.0f;
    this->four[14] = 0.0f;
    this->four[15] = a;
    this->four[16] = -b;
    this->four[17] = 0.0f;
}

void Display::fill_five(){
    float a = this->length, b = this->width;
    this->five[0] = 0.0f;
    this->five[1] = -b;
    this->five[2] = 0.0f;
    this->five[3] = 0.0f;
    this->five[4] = -b-a;
    this->five[5] = 0.0f;
    this->five[6] = b;
    this->five[7] = -b-a;
    this->five[8] = 0.0f;
    this->five[9] = 0.0f;
    this->five[10] = -b;
    this->five[11] = 0.0f;
    this->five[12] = b;
    this->five[13] = -b;
    this->five[14] = 0.0f;
    this->five[15] = b;
    this->five[16] = -b-a;
    this->five[17] = 0.0f;
}

void Display::fill_six(){
    float a = this->length, b = this->width;
    this->six[0] = a-b;
    this->six[1] = -b;
    this->six[2] = 0.0f;
    this->six[3] = a-b;
    this->six[4] = -b-a;
    this->six[5] = 0.0f;
    this->six[6] = a;
    this->six[7] = -b-a;
    this->six[8] = 0.0f;
    this->six[9] = a-b;
    this->six[10] = -b;
    this->six[11] = 0.0f;
    this->six[12] = a;
    this->six[13] = -b;
    this->six[14] = 0.0f;
    this->six[15] = a;
    this->six[16] = -b-a;
    this->six[17] = 0.0f;
}

void Display::fill_seven(){
    float a = this->length, b = this->width;
    this->seven[0] = 0.0f;
    this->seven[1] = -a;
    this->seven[2] = 0.0f;
    this->seven[3] = 0.0f;
    this->seven[4] = -a-b;
    this->seven[5] = 0.0f;
    this->seven[6] = a-b;
    this->seven[7] = -a-b;
    this->seven[8] = 0.0f;
    this->seven[9] = 0.0f;
    this->seven[10] = -a;
    this->seven[11] = 0.0f;
    this->seven[12] = a;
    this->seven[13] = -a;
    this->seven[14] = 0.0f;
    this->seven[15] = a;
    this->seven[16] = -a-b;
    this->seven[17] = 0.0f;
}
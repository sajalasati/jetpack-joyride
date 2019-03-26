#include "main.h"

const color_t COLOR_PLAYER = { 0, 153, 153 };
const color_t COLOR_WALL = { 204, 102, 0 };
const color_t COLOR_COIN1 = { 160, 160, 160 };
const color_t COLOR_COIN2 = { 0, 204, 0 };
const color_t COLOR_COIN3 = { 204, 0, 102 };
const color_t COLOR_COIN4 = { 255, 255, 0 };
const color_t COLOR_RED = { 204, 0, 0 };

const color_t COLOR_FIREBEAM = { 255, 0, 0 };
const color_t COLOR_WATER_BALLOON = { 0, 102, 204 };
// const color_t COLOR_PLAYER = { 5, 50, 37 };
const color_t COLOR_GREEN = { 135, 211, 124 };
const color_t COLOR_BLACK = { 0, 0, 0 };
const color_t COLOR_BACKGROUND = { 20, 20, 20 };
// const color_t COLOR_BACKGROUND = { 242, 241, 239 };
const color_t COLOR_PLATFORM = { 0, 153, 153 };
const color_t COLOR_NEON = {37, 201, 53};
const color_t COLOR_GREY = {96, 96, 96};
const color_t COLOR_PURPLE = {204, 0, 204};
const color_t COLOR_ORANGE = {255, 128, 0};
const color_t COLOR_BROWN = {102, 51, 0};
const color_t COLOR_BROWN2 = {228, 105, 11};
const color_t COLOR_YELLOW = {255, 255, 0};
const color_t COLOR_HEART = {255, 153, 255};
const color_t COLOR_WHITE = {255, 255, 255};

// const color_t colors[]={COLOR_GREEN, COLOR_BLACK, COLOR_BROWN, COLOR_GREY, COLOR_PURPLE};

float screen_speed = 0.02;
const float platform_width = 0.8;
const float wall_width = 0.8;
bool jet_propulsion;
bool speeding_up = false;
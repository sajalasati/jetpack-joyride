#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "boomerang.h"
#include "magnet.h"
#include "display.h"
#include "ring.h"
#include "special_objects.h"
#include "unistd.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Display display;
Ball ball;
Platform platform, upper_wall;
list <Jet> jets;
list <Magnet> magnets;
list <Ring> rings;
list <Coin> coins;
list <WaterBalloon> water_balloons;
list <Fireline> firelines;
list <Firebeam> firebeams;
list <Heart> hearts;
list <Heart> life_hearts;
list <Boomerang> boomerangs;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
bool magnetic_field = false;
bool ball_on_ring = false;
float target_distance = 0.0f;

Timer t60(1.0 / 60);
Timer t1(0.1);
Timer t2(3.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    screen_center_x += screen_speed;
    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( screen_center_x,0,5);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (screen_center_x, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    ball.draw(VP);
    for(list<Heart>::iterator it = hearts.begin(); it!=hearts.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Jet>::iterator it = jets.begin(); it!=jets.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Fireline>::iterator it = firelines.begin(); it!=firelines.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Firebeam>::iterator it = firebeams.begin(); it!=firebeams.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Ring>::iterator it = rings.begin(); it!=rings.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Boomerang>::iterator it = boomerangs.begin(); it!=boomerangs.end(); ++it){
        (*it).draw(VP);
    }
    for(list<Coin>::iterator it = coins.begin(); it!=coins.end(); ++it){
        (*it).draw(VP);
    }
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end(); ++it){
        (*it).draw(VP);
    }
    platform.draw(VP);
    for(list<Magnet>::iterator it = magnets.begin(); it!=magnets.end(); ++it){
        (*it).draw(VP);
    }
    upper_wall.draw(VP);
    
    int life = ball.lives, i=0;
    for(list<Heart>::iterator it = life_hearts.begin(); it!=life_hearts.end() && i<life; ++it){
        (*it).draw(VP); ++i;
    }
    display.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int reset_zoom = glfwGetKey(window, GLFW_KEY_R);
    if(reset_zoom) screen_zoom = 1.0f;
    if(left){
        if(!speeding_up){
            if(ball.xspeed > 0) ball.xspeed = -0.5;
            ball.xspeed -= 0.040;
        }
        ball.direc = 0;
    }
    else if(right){
        ball.direc = 1;
        if(!speeding_up){
            if(ball.xspeed < 0) ball.xspeed = 0.5;
            ball.xspeed += 0.040;
        }
    }
    else{
        if(abs(ball.xspeed)< 25*screen_speed) ball.xspeed = 25*screen_speed;
        else{
            if (ball.xspeed < 0) {
                ball.xspeed += 0.024;
            }
            else if (ball.xspeed > 0) {
                ball.xspeed -= 0.024;
            }
        }
	}
    if(up){
        if(!ball_on_ring){
            ball.gflag = true;
            ball.flyup(magnetic_field,ball_on_ring);   
            jet_propulsion = true;
        }
    }
    else if(down) {
        if(!ball_on_ring)
        ball.flydown();
    } 
}

void tick_input2(GLFWwindow *window) {
    int water = glfwGetKey(window, GLFW_KEY_W);
    int throwbom = glfwGetKey(window, GLFW_KEY_Z);
    if(water){
        if(ball.direc == 1){
            float x1 = ball.position.x + (ball.radius + 0.16)/1.414213;
            float y1 = ball.position.y + (ball.radius + 0.16)/1.414213;
            water_balloons.push_back(WaterBalloon(x1, y1,0.16,1.5,COLOR_WATER_BALLOON));
        }
        else{
            float x1 = ball.position.x - (ball.radius + 0.16)/1.414213;
            float y1 = ball.position.y + (ball.radius + 0.16)/1.414213;
            water_balloons.push_back(WaterBalloon(x1, y1,0.16,-1,COLOR_WATER_BALLOON));
        }
    }
    if(throwbom){
        boomerangs.push_back(Boomerang(screen_center_x+4.2, screen_center_y+4.0,COLOR_RED));
    }
}

void apply_gravity(){
    if(magnets.size()>=1 && !ball_on_ring){
        ball.apply_gravity();
        ball.apply_gravity();
    }
    else{
        if(!ball_on_ring) ball.apply_gravity();
    }
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end();++it){
        (*it).apply_gravity();        
    }
}

void tick_elements() {
    // to move all the moving objects
    display.tick(ball.score);
    for(list<Ring>::iterator it = rings.begin(); it!=rings.end(); ++it){
        (*it).tick();
    }
    ball.tick(ball_on_ring);
    for(list<Heart>::iterator it = life_hearts.begin(); it!=life_hearts.end();++it){
        (*it).tick();        
    }
    for(list<Heart>::iterator it = hearts.begin(); it!=hearts.end();++it){
        (*it).tick();        
    }
    for(list<Jet>::iterator it = jets.begin(); it!=jets.end();++it){
        (*it).tick();        
    }
    for(list<Magnet>::iterator it = magnets.begin(); it!=magnets.end();){
        (*it).tick();
        if((*it).timelength >= 4){
            it = magnets.erase(it);
        }
        else ++it;  
    }
    for(list<Boomerang>::iterator it = boomerangs.begin(); it!=boomerangs.end();++it){
        (*it).tick();        
    }
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end();++it){
        (*it).tick();        
    }
    for(list<Firebeam>::iterator it = firebeams.begin(); it!=firebeams.end(); ++it){
        (*it).tick();
    }
}

void check_frame_collisions(){
    // to control the moving objects going out of the game frame
    ball.frame_collision_check();
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end();){
        if((*it).frame_collision_check()) it = water_balloons.erase(it);
        else ++it;
    }
    for(list<Fireline>::iterator it = firelines.begin(); it!=firelines.end();){
        if((*it).frame_collision_check()) it = firelines.erase(it);
        else ++it;
    }
    for(list<Firebeam>::iterator it = firebeams.begin(); it!=firebeams.end();){
        if((*it).frame_collision_check()) it = firebeams.erase(it);
        else ++it;
    }
    for(list<Boomerang>::iterator it = boomerangs.begin(); it!=boomerangs.end();){
        if((*it).frame_collision_check()) it = boomerangs.erase(it);
        else ++it;
    }
    for(list<Ring>::iterator it = rings.begin(); it!=rings.end();){
        if((*it).frame_collision_check()) it = rings.erase(it);
        else ++it;
    }
    for(list<Coin>::iterator it = coins.begin(); it!=coins.end();){
        if((*it).frame_collision_check()) it = coins.erase(it);
        else ++it;
    }
    for(list<Heart>::iterator it = hearts.begin(); it!=hearts.end();){
        if((*it).frame_collision_check()) it = hearts.erase(it);
        else ++it;
    }
    for(list<Jet>::iterator it = jets.begin(); it!=jets.end();){
        if((*it).frame_collision_check()) it = jets.erase(it);
        else ++it;
    }

}

void check_other_collisions(){
    // coin collection
    for(list<Coin>::iterator it = coins.begin(); it!=coins.end(); ){
        if((*it).check_collision((*it).bounding_box(),ball.bounding_box())==true){
            ball.score += (*it).points;
            it = coins.erase(it);
        }
        else ++it;
    }
    for(list<Jet>::iterator it = jets.begin(); it!=jets.end(); ){
        if((*it).check_collision(ball.bounding_box())==true){
            speeding_up = true;
            screen_speed = 0.5;
            target_distance = screen_center_x + 50.0f;
            it = jets.erase(it);
        }
        else ++it;
    }
    for(list<Heart>::iterator it = hearts.begin(); it!=hearts.end(); ){
        if((*it).check_collision(ball.bounding_box())==true){
            ball.lives += 1;
            it = hearts.erase(it);
        }
        else ++it;
    }
    //water_balloon colliding fireline
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end(); ){
        bool flag = false;
        for(list<Fireline>::iterator it2 = firelines.begin(); it2!=firelines.end(); ++it2){
            if((*it2).check_collision((*it).bounding_box())){
                firelines.erase(it2);
                flag=true;
                break;       
            }
        }
        if(flag){
            it = water_balloons.erase(it);
            //maybe some score increment here
        }
        else ++it;
    }
    //water_balloon colliding firebeam
    for(list<WaterBalloon>::iterator it = water_balloons.begin(); it!=water_balloons.end(); ){
        bool flag = false;
        for(list<Firebeam>::iterator it2 = firebeams.begin(); it2!=firebeams.end(); ++it2){
            if((*it2).check_collision((*it).bounding_box())){
                firebeams.erase(it2);
                flag=true;
                break;       
            }
        }
        if(flag){
            //maybe some score increment here
            it = water_balloons.erase(it);
        }
        else ++it;
    }
    for(list<Ring>::iterator it = rings.begin(); it!=rings.end();){
        if((*it).check_collision(ball.bounding_box())){
            if((*it).ball_contact){
                if((ball.position[0]>=(*it).position[0] + (*it).radius) || (ball.position[0]<=(*it).position[0]- (*it).radius)){
                    if(ball.position[0]>=(*it).position[0] + (*it).radius) 
                    {
                        it = rings.erase(it);
                        ball_on_ring = false;
                    }
                    else {
                        ball_on_ring = false;
                        ++it;
                    }
                }
                else{
                    float ra = (*it).radius, xa = ball.position[0]-(*it).position[0];
                    ball.position[1] = sqrt(abs(ra*ra - xa*xa));//sethere
                    ++it;
                }
            }
            else{
                (*it).ball_contact = true;
                ball_on_ring = true;
                ball.xspeed = 0;
                // ball.position[0] = (*it).position[0] - (*it).radius + 0.1;
                float ra = (*it).radius, xa = ball.position[0]-(*it).position[0];
                ball.position[1] = sqrt(abs(ra*ra - xa*xa));//sethere
                ++it;
            }
        }
        else ++it;
    }
    //then check collision of ball with firelines and firebeams  
    if(!speeding_up){
        for(list<Fireline>::iterator it = firelines.begin(); it!=firelines.end(); ){
            if((*it).check_collision(ball.bounding_box())){
                it = firelines.erase(it);
                ball.lives -= 1;
                // quit(window);//change this in future
            }
            else ++it;
        }
        for(list<Firebeam>::iterator it = firebeams.begin(); it!=firebeams.end(); ){
            if((*it).check_collision(ball.bounding_box())){
                it = firebeams.erase(it);
                ball.lives -= 1;
                // quit(window);//change this in future
            }
            else ++it;
        }
        for(list<Boomerang>::iterator it = boomerangs.begin(); it!=boomerangs.end(); ){
            if((*it).check_collision(ball.bounding_box())){
                it = boomerangs.erase(it);
                ball.lives -= 1;
                // quit(window);//change this in future
            }
            else ++it;
        }
    }
    if(ball.lives==0){
        quit(window);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball = Ball(0, 0,0.5,0.25,COLOR_PLAYER,0);
    platform = Platform(0,0,-4.0f,COLOR_BROWN,1);
    upper_wall = Platform(0,0,4.0f-wall_width,COLOR_BROWN2,0);
    display = Display(2,3.6);
    for(int i=0; i<10; ++i){
        life_hearts.push_back(Heart(-3.5 + i*0.4,3.6,COLOR_WHITE,0.08,0));
    }
    rings.push_back(Ring(5,0,COLOR_YELLOW));
    for(int i=0; i<5; ++i){
        int zz = rand()%2;
        if(zz==1) hearts.push_back(Heart(rand()%10+rand()%100,-rand()%3,COLOR_HEART,0.1,1));
        else hearts.push_back(Heart(rand()%10+rand()%100,rand()%3,COLOR_HEART,0.1,1));
    }
    jets.push_back(Jet(20,0,COLOR_HEART,1));
    jets.push_back(Jet(27,0,COLOR_HEART,1));
    jets.push_back(Jet(37,0,COLOR_HEART,1));
    for(int i=0;i<10;++i){
        int zz = rand()%7;
        int ang = rand()%60;
        firelines.push_back(Fireline(14+zz*i,rand()%2,COLOR_YELLOW,ang));
    }
    for(int i=0;i<10;++i){
        int zz = rand()%7;
        int ang = rand()%60;
        firelines.push_back(Fireline(114+zz*i,0,COLOR_YELLOW,ang));
    }
    // firelines.push_back(Fireline(14,1,COLOR_YELLOW));
    for(int i=0; i<10; ++i){
        firebeams.push_back(Firebeam(108+12*i,1,COLOR_FIREBEAM));
    }
    for(int i=0; i<10; ++i){
        firebeams.push_back(Firebeam(108+12*i,1,COLOR_FIREBEAM));
    }
    magnets.push_back(Magnet(0,-4.0));
    magnets.push_back(Magnet(40,-4.0));
    magnets.push_back(Magnet(320,-4.0));
    
    //coins
    for(int i=0; i<300; ++i){
        float y = rand()%4, z = rand()%100;
        if(z>=50) y*=-1;
        float x = rand()%500;
        if(abs(y)==0) coins.push_back(Coin(x, y,0.16,COLOR_COIN1,1));
        else if(abs(y)==1) coins.push_back(Coin(x, y,0.16,COLOR_COIN2,2));
        else if(abs(y)==2) coins.push_back(Coin(x, y,0.16,COLOR_COIN3,3));
        else coins.push_back(Coin(x, y,0.16,COLOR_COIN4,4));
    }
    float yspeed;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);
    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    //boundaries at -4
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);
    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if(screen_center_x >= target_distance){
                screen_speed = 0.02;
                speeding_up = false;
            }
            tick_input(window);
            if(t1.processTick()){
               tick_input2(window);
            }
            if(t2.processTick()){
                boomerangs.push_back(Boomerang(screen_center_x+3.5, screen_center_y+4.0,COLOR_RED));       
            }
            // usleep(1e9);
            magnetic_field = (magnets.size()>=1) ? true:false;
            apply_gravity();// objects who accelerate due to gravity and don't have const velocity
            tick_elements();//move the objects accordingly (both moving and apparently static)
            check_frame_collisions(); //check collision frame collisions for moving objects
            check_other_collisions(); // like coin collection, reducing lives, killing fireline/beam
            // cout<<jet_propulsion<<endl;
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

void reset_screen() {
    float top    = 0.0f + 4 / screen_zoom;
    float bottom = 0.0f - 4 / screen_zoom;
    float left   = 0.0f - 4 / screen_zoom;
    float right  = 0.0f + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
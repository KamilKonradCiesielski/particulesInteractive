#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
   
    ofSetBackgroundColor(rand(), rand(), rand());
    hue = 0;
    // sets the maximum number of particles to 2000
    maxParticles = 2000;
    //enables lighting in the scene
    ofEnableLighting();
    //enables depth testing, which ensures that objects are rendered in the correct order based on their depth
    ofEnableDepthTest();
    //sets the position of the light used in the scene
    light.setPosition(0, -600, 300);

    // sets the resolution of all spheres rendered in the application to 32 segments in both the vertical and horizontal directions
    ofSetSphereResolution(32);

    //Hide Mouse Courser during the particles drawing 
    ofHideCursor();


    
    
}

//--------------------------------------------------------------
//this function is called on every update frame of the application
void ofApp::update() {
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    // if the number of particles exceeds the maxParticles limit, the oldest particles are removed from the vector particles
    if (particles.size() > maxParticles) {
        particles.erase(particles.begin());
    
    // for each particle in the particles vector, the update() function of the particle is called to update its position and behavior
    }
    for (int i = 0; i < particles.size(); i++) {
        particles[i].update();
      
    }
}

//--------------------------------------------------------------
//this function is called on every draw frame of the application
void ofApp::draw() {
    //enables the light in the scene
    light.enable();
    //draws a visual axis with a length of 400 units
    ofDrawAxis(400);
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    // for each particle in the particles vector, the draw() function of the particle is called to render the particle
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();

    }
}


//--------------------------------------------------------------

//void ofApp::keyReleased(int key): This function is called when a keyboard key is released. 
//In this case, it sets a random value for hue every time a key is released
void ofApp::keyPressed(int key) {
    switch (key) {
//pressing 'f' or 'F' toggles the fullscreen mode of the application using 
    case 'f':
    case 'F':
        ofToggleFullscreen();
        break;
//pressing the spacebar (' ') creates a certain number of particles and adds them to the particles vector
    case ' ':
        int numParticles = 200;
        for (int i = 0; i < numParticles; i++) {
            particle newParticle(0, 0, 0, hue);
            // push the new particle we just made onto the back of the vector 'particles'
            particles.push_back(newParticle);
        }
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    //this function is called when a keyboard key is released, in this case, it sets a random value for hue every time a key is released
    hue = ofRandom(255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    //this function is called when the mouse is dragged, it creates a new particle object and sets 
    //its initial position to the current mouse position, the particle is then added to the particles vector.
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters

     particle newParticle( mouseX, mouseY, 0, hue );
    //    // push the new particle we just made onto the back of the vector 'particles'
    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    //This function is called when a mouse button is pressed, it changes the background color to a random RGB value
    ofSetBackgroundColor(rand(), rand(), rand());
    // sets a random value for hue when pressed
    hue = ofRandom( 255); 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int startZ, int hue) {
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    //This is the constructor of the particle class. It initializes the particle object with the given position and hue.
   //
   // It sets the initial position and force vectors based on the provided arguments
   // It generates a random size for the particle using rand() within a specified range
   // It sets the color of the particle based on the provided hue

    float speed = 4.0;
    position = glm::vec3(startX, startY, startZ);
    force = glm::vec3(0, 0.002, 0);
    direction = glm::vec3(ofRandom(-speed, speed), ofRandom(-speed, speed), ofRandom(-speed, speed));
   //set the randomNumber as a variable for the size of a particule, to draw diffrenct sizes of particules
    int minValue = 5;
    int maxValue = 25;
    int randomNumber = minValue + (rand() % (maxValue - minValue + 1));

    size = randomNumber;
    color.setHsb(hue, 255, 255);

    
}
//--------------------------------------------------------------

particle::~particle() {
    // destructor
}
//--------------------------------------------------------------

void particle::update() {
    // update the particle x,y position by incrementing each by the velocity vx and vy
    // this function is called on every update frame of the particle, it updates the position and direction of the particle based on its force.
    position += direction;
    direction += force;
  

}

//--------------------------------------------------------------

void particle::draw() {
    //this function is called on every draw frame of the particle, it sets the color of the particle and draws a sphere at the particle's position
    //set diffrenct color for each time when the mouse is being pressed 
    ofSetColor(color);
  
    //rotates the coordinate system 50 degrees along the x-axis and 25 degrees on the y-axis
    ofRotate(50, 1, 0.5, 0);

    //draws a sphere at the particle's position with the specified size 
    ofDrawSphere(position, size);
    

}
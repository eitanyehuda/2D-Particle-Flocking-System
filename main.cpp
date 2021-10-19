#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "particle.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

const int INITIAL_NUMBER_OF_PARTICLES = 500;

int windowSizeX = 700;
int windowSizeY = 700;

int mouseX;
int mouseY;

std::vector<Particle> particles;

bool leftClick = false;
bool rightClick = false;
bool stop = false;
bool frictionMode = false;
bool evacuate = false;

void display(void)
{   

    glClear(GL_COLOR_BUFFER_BIT);
    for(Particle particle : particles)
    {
        glColor3f(particle.colour.r, particle.colour.g, particle.colour.b);
        glPointSize(particle.size);
		glBegin(GL_POINTS);
		glVertex2f(particle.position.mX, particle.position.mY);
		glEnd();
    }
    glFlush();
	glutSwapBuffers();

}

bool withinWindowWidth(std::vector<Particle>::iterator particle){
	if(particle->position.mX - particle->size/2 < 0 || particle->position.mX + particle->size/2 > windowSizeX)
	{
		return false;
	}
	return true;
}

bool withinWindowHeight(std::vector<Particle>::iterator particle){
	if(particle->position.mY - particle->size/2 < 0 || particle->position.mY + particle->size/2 > windowSizeY)
	{
		return false;
	}
	return true;
}

void addParticle(int x, int y)
{
	Particle particle = Particle(x, y);
    particles.push_back(particle);
}

void generateParticles()
{   
    particles.clear();
    for(int i = 0; i < INITIAL_NUMBER_OF_PARTICLES; i++)
    {
        float x = rand() % windowSizeX;
        float y = rand() % windowSizeY;

        addParticle(x, y);
    }
    std::cout << INITIAL_NUMBER_OF_PARTICLES << " particles generated" << std::endl;
}

void removeParticle(int x, int y)
{
	std::vector<Particle>::iterator closestParticle;
	float closestDistance = INT_MAX;
	Point2D mousePosition = Point2D(x,y);
	float distanceFromMouse;
	
	if(particles.size() <= 0)
	{
		std::cout << "There are no particles left to remove" << std::endl;
		return;
	}

	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle) // parse through actual addresses of particles in the array
	{
		distanceFromMouse = particle->position.fastDistanceTo(mousePosition);
		if(distanceFromMouse <= closestDistance)
		{
			
			closestDistance = distanceFromMouse;
			closestParticle = particle;
		}
	}
	particles.erase(closestParticle);
	std::cout << "Particle Removed!" << std::endl;
}

void increaseParticleRanges()
{
	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle)
	{
			particle->incrementRange();
	}
}

void decreaseParticleRanges()
{
	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle)
	{
			particle->decrementRange();
	}
}

void increaseParticleSpeeds()
{
	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle)
	{
			particle->incrementSpeed();
	}
}

void decreaseParticleSpeeds()
{
	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle)
	{
			particle->decrementSpeed();
	}
}

bool inRange(Point2D mouseLocation, Particle particle)
{
	if(particle.position.distanceTo(mouseLocation) <= particle.range)
	{
		return true;
	}
	return false;
}

bool cursorWithinWindow(int x, int y)
{
	if(x > 0 && x < windowSizeX && y > 0 && y < windowSizeY)
	{
		return true;
	}
	return false;
}

void attractParticle(std::vector<Particle>::iterator particle)
{
	Point2D cursorPosition = Point2D(mouseX, mouseY);
	if(inRange(cursorPosition, *particle) && cursorWithinWindow(mouseX, mouseY))
	{
		particle->moveTo(cursorPosition); //(*p). = p-> These are the same
	}
}

void repelParticle(std::vector<Particle>::iterator particle)
{
	Point2D cursorPosition = Point2D(mouseX, mouseY);
	if(withinWindowWidth(particle) && withinWindowHeight(particle) && inRange(cursorPosition, *particle))
	{
		particle->moveAway(cursorPosition);
	}
}

void drawHeart(int centreX, int centreY)
{
	std::vector<std::vector<Particle>::iterator> heartParticles;
	float domain = 200.0;
	
	Point2D centre = Point2D(centreX,centreY);
	for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle)
	{
		if(inRange(centre, *particle) && cursorWithinWindow(centreX, centreY) && !particle->hasTarget && heartParticles.size() <= domain*2 + 1) 
		{
			heartParticles.push_back(particle);
		}
	}
	
	float xCoord = centreX - domain/2;
	float yCoord;
	float scale = domain/2;
	int detail;
	bool top = true;
	int numberOfHeartParticles = heartParticles.size();
	Colour colour = Colour((rand() % 100)*0.01 + 0.2, (rand() % 60)*0.01 + 0.1, (rand() % 80)*0.01 + 0.2);

	if(numberOfHeartParticles > domain*2 + 1) { detail = 1;} // 402+ particles  400/number
	else if(numberOfHeartParticles > domain + 1) { detail = 2;} // 202+ particles
	else if(numberOfHeartParticles > domain/2 + 1) { detail = 4;} // 102+ particles
	else if(numberOfHeartParticles > domain/2.5 + 1) { detail = 5;} // 82+ particles
	else if(numberOfHeartParticles > domain/4 + 1) { detail = 8;} // 52+ particles
	else if(numberOfHeartParticles > domain/5 + 1) { detail = 10;} // 42+ particles
	else if(numberOfHeartParticles > domain/10 + 1) { detail = 20;} // 22+ particles
	else if(numberOfHeartParticles > domain/12.5 + 1) { detail = 25;} // 18+ particles
	else { std::cout << "Not enough free particles in range :(" << std::endl; return; } // if less than 18 particles doesnt draw a heart

	std::cout << "Number of Particles in Range: " << numberOfHeartParticles << std::endl;

	for(std::vector<Particle>::iterator particle : heartParticles)
	{
		if (xCoord <= centreX + domain/2)
		{
			if(top) // drawing top of heart
			{
				yCoord = scale * (sqrt(1.0 - pow((xCoord - centreX)/scale ,2)) + sqrt(abs((xCoord - centreX)/scale)) - 0.5) + centreY; // function for top of heart
				top = false;
			}
			else // drawing bottom of heart
			{
				yCoord = scale * (0.6 * (sqrt(abs((xCoord - centreX)/scale )) - sqrt(1.0 - pow((xCoord - centreX)/scale,2)) + sqrt(pow((0.25 * (xCoord - centreX))/scale,2))) - 0.25) + centreY; // function for bottom of heart
				xCoord += detail;
				top = true;
			}

			particle->setTarget(Point2D(xCoord,yCoord));
			particle->colour = colour;
		}
	}
	
	std::cout << "Heart :)" << std::endl; 
}

void keyboard(unsigned char key, int xMouse, int yMouse)
{
	yMouse = windowSizeY - yMouse; // flip y
	switch (key){
		case 'A':
		case 'a':
            addParticle(xMouse, yMouse);
			std::cout << "Particle Added!" << std::endl; 
			break;
		case 'D':
		case 'd':
            removeParticle(xMouse, yMouse);
			break;
		case '+':
            increaseParticleRanges();
			break;
		case '-':
            decreaseParticleRanges();
			break;
		case ' ':
            if(stop) 
			{ 
				stop = false; 
			}
			else 
			{ 
				stop = true; 
				leftClick = false;    // handles the case where pause button is clicked while left mouse button is clicked
				rightClick = false;
			}
			break;
		case 'R':
		case 'r':
            generateParticles();
			evacuate = false;
			std::cout << "SCREEN CLEARED!" << std::endl; 
			break;
		case 'Q':
		case 'q':
        case 27:
			std::cout << "BYE!" << std::endl; 
			exit(0);
			break;
		case 'F':
		case 'f':
            if(!frictionMode) {
				frictionMode = true;
				std::cout << "Friction Mode ON" << std::endl; 
			}
			else { 
				frictionMode = false; 
				std::cout << "Friction Mode OFF" << std::endl; 
			}
			break;
		case 'E':
		case 'e':
            if(!evacuate) {
				evacuate = true;
				std::cout << "Evacuate!" << std::endl; 
			}
			else { 
				evacuate = false; 
				std::cout << "Stop Evacuation" << std::endl; 
			}
			break;
		case 'H':
		case 'h':
			drawHeart(xMouse, yMouse);
			break;
    }
}

void special(int key, int xMouse, int yMouse)
{
	switch (key){
		case GLUT_KEY_UP:
            increaseParticleSpeeds();
			break;
		case GLUT_KEY_DOWN:
            decreaseParticleSpeeds();
			break;
    }
}

void mouse(int button, int state, int x , int y)
{
	if(!stop)
	{
		y = windowSizeY - y; // flip y

		std::cout << "Mouse Coordinates: ";
		std::cout << x << ", " << y << std::endl; // endline is neccassary for terminal to print line by line

		mouseX = x; // update global mouse coords
		mouseY = y;

		if (button == GLUT_LEFT_BUTTON) // LMB pressed
		{
			std::cout << "LEFT BUTTON" << std::endl;
			if (state == GLUT_UP)
			{
				std::cout << "RELEASED!" << std::endl;
				leftClick = false;
			}
			if (state == GLUT_DOWN)
			{
				std::cout << "PRESSED!" << std::endl;
				leftClick = true;
			}
		}

		if (button == GLUT_RIGHT_BUTTON) // RMB pressed
		{
			std::cout << "RIGHT BUTTON" << std::endl;
			if (state == GLUT_UP)
			{
				std::cout << "RELEASED!" << std::endl;
				rightClick = false;
			}
			if (state == GLUT_DOWN)
			{
				std::cout << "PRESSED!" << std::endl;
				rightClick = true;
			}
		}
	}
}

void motion(int x, int y)
{
	y = windowSizeY - y; // flip y

	mouseX = x; // update global mouse coords
	mouseY = y;
}

void reshape(int w, int h)
{
	windowSizeX = w; //set global width
	windowSizeY = h; //set global height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

// update animation
void timer(int)
{
	if(!stop)
	{
		for(std::vector<Particle>::iterator particle = (&particles)->begin(); particle != (&particles)->end(); ++particle) // parse through actual addresses of particles in the array
		{
			particle->momentum(); // keeps particles moving 

			if(!withinWindowWidth(particle))
			{
				particle->bounceX(); // collision with side walls
			}
			if(!withinWindowHeight(particle))
			{
				particle->bounceY(); // collision with up and down wall walls
			}
			if(frictionMode)
			{
				particle->slowDown();
			}
			if(evacuate)
			{
				particle->evacuate();
			}
			if(particle->hasTarget)
			{
				particle->moveTo(particle->target); // move particles to set target
			}
			if(leftClick)
			{
				attractParticle(particle);
			}
			else if(rightClick)
			{
				repelParticle(particle);
			}
		}

		glutPostRedisplay();
	}

	glutTimerFunc(1000.0/60.0, timer, 0);
}

void listOfCommands()
{
	std::cout << "Press or hold LMB to attract particles within range of mouse cursor" << std::endl;
	std::cout << "Press or hold RMB to repel particles within range of mouse cursor" << std::endl;
	std::cout << "Press 'a' to add new particle at current cursor position" << std::endl;
	std::cout << "Press 'd' to remove a particle closest to cursor position" << std::endl;
	std::cout << "Press '+' to globally increase the range of all particles" << std::endl;
	std::cout << "Press '-' to globally decrease the range of all particles" << std::endl;
	std::cout << "Press 'up' arrow key to globally increase movment speed of particles" << std::endl;
	std::cout << "Press 'down' arrow key to globally decrease movment speed of particles" << std::endl;
	std::cout << "Press 'space bar' to stop/run annimation if it it running/stopped" << std::endl;
	std::cout << "Press 'r' to wipe screen and re-generate a new set of particles" << std::endl;
	std::cout << "Press 'q' or 'Esc' to exit the program" << std::endl;
	std::cout << "Press 'f' to toggle friction on/off" << std::endl;
	std::cout << "Press 'e' to toggle evacuation on/off" << std::endl;
	std::cout << "Press 'h' to gather particles and create a heart" << std::endl;
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Sets dispaly mode to double,rgb,depth


	glutInitWindowSize(windowSizeX, windowSizeY);
    glutInitWindowPosition(100, 100);

	glutCreateWindow("2D-Particle Flocking System");	// creates the window

    generateParticles();

	glutDisplayFunc(display);	// registers "display" as the display callback function
	glutReshapeFunc(reshape);
	
	listOfCommands(); // print out command options

	glutTimerFunc(1000.0/60.0, timer, 0);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
#ifndef PLAYGROUND_H
#define PLAYGROUND_H

// Include GLEW
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>

//some global variables for handling the vertex buffer
GLuint vertexbuffer;
GLuint VertexArrayID;
GLuint vertexbuffer_size;
GLuint MatrixID;
glm::mat4 MVP;

GLuint mandelbrotID;

GLfloat mandelbrot_iteration;
//program ID of the shaders, required for handling the shaders with OpenGL
GLuint programID;

float FoV , scaler, position_x, position_y, mouse_transform_x, mouse_transform_y;

double mouse_pos_x, mouse_pos_y;

int screen_width, screen_height;




int main( void ); //<<< main function, called at startup
void updateAnimationLoop(); //<<< updates the animation loop
void checkpressedkey();
bool initializeWindow(); //<<< initializes the window using GLFW and GLEW
bool initializeVertexbuffer(); //<<< initializes the vertex buffer array and binds it OpenGL
bool cleanupVertexbuffer(); //<<< frees all recources from the vertex buffer
bool closeWindow(); //<<< Closes the OpenGL window and terminates GLFW
void initalizeAttributes();
void updateModelViewProjection();
#endif

#include "playground.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
  //Initialize window
  bool windowInitialized = initializeWindow();
  if (!windowInitialized) return -1;
  programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
  //Initialize vertex buffer
  bool vertexbufferInitialized = initializeVertexbuffer();
  if (!vertexbufferInitialized) return -1; 

  // Create and compile our GLSL program from the shaders
  initalizeModelViewProjection();
	//start animation loop until escape key is pressed
	do{

    checkpressedkey();
    updateAnimationLoop();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	
  //Cleanup and close window
  cleanupVertexbuffer();
  glDeleteProgram(programID);
	closeWindow();
  
	return 0;
}

void updateAnimationLoop()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Use our shader
  glUseProgram(programID);
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniform1f(mandelbrotID, mandelbrot_iteration);
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, vertexbuffer_size); // 3 indices starting at 0 -> 1 triangle

  glDisableVertexAttribArray(0);

  // Swap buffers
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool initializeWindow()
{
  // Initialise GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return false;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Mandelbrot Set", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return false;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetCursorPos(window, 1024/2, 768/2);

  // Dark blue background
  //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  return true;
}

void initalizeModelViewProjection(){
  MatrixID = glGetUniformLocation(programID, "MVP");
  mandelbrotID = glGetUniformLocation(programID, "mandelbrot_iteration");

  FoV = 20.0f;
  scaler = 1.0f;
  position_x = 0.0f;
  position_y = 0.0f;
  mandelbrot_iteration = 128.0f;

}

bool initializeVertexbuffer()
{
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  vertexbuffer_size = 2*3;
  static const GLfloat g_vertex_buffer_data[] = {
    -10.0f, -10.0f, 0.0f,
    10.0f, -10.0f, 0.0f,
    10.0f,  10.0f, 0.0f,
    -10.0f, -10.0f, 0.0f,
    10.0f, 10.0f, 0.0f,
    -10.0f,  10.0f, 0.0f
  };

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  return true;
}

bool cleanupVertexbuffer()
{
  // Cleanup VBO
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  return true;
}

bool closeWindow()
{
  glfwTerminate();
  return true;
}

void checkpressedkey(){
  glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
  // if(position_x < 1.0f || position_x > -1.0f){
  //   std::cout << (mouse_pos_x - 512.0f) / 5120.0f;
  // }
  // if(position_y < 1.0f || position_y > -1.0f){
  //   std::cout << (mouse_pos_y - 384.0f) / 3840.0f;
  // }
  
   
  //std::cout << "x: " << mouse_pos_x << ", y: " << mouse_pos_y << "\n";
  
    if (glfwGetKey( window, GLFW_KEY_I ) == GLFW_PRESS){
		  if(FoV > 0.0000001f){
      FoV -= 0.01;
    }
    std::cout << FoV << "\n";
  }
	if (glfwGetKey( window, GLFW_KEY_O ) == GLFW_PRESS){
    if(FoV <= 70.0f){
		  FoV += 0.01;
    }
    //std::cout << FoV << "\n";
	}
  if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
    position_x -= 0.0001;
	}
  if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
    position_x += 0.0001;
	}

  if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
    position_y -= 0.0001;
	}
  if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
    position_y += 0.0001;
	}

  if (glfwGetKey( window, GLFW_KEY_M ) == GLFW_PRESS){
    if(mandelbrot_iteration < 500){
      mandelbrot_iteration += 0.1;
      std::cout << mandelbrot_iteration << "\n";  
    }
	}
  if (glfwGetKey( window, GLFW_KEY_N ) == GLFW_PRESS){
    if(mandelbrot_iteration > 10){
      mandelbrot_iteration -= 0.1;
      std::cout << mandelbrot_iteration << "\n";  
    }
  }

  glm::mat4 Projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,0,3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );

  glm::mat4 scaleMatrix =	glm::scale(glm::vec3(scaler, scaler, scaler)); 
	glm::mat4 rotationMatrix = glm::rotate(glm::radians(0.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::vec3(position_x, position_y, 0.0f)); // - (mouse_pos_x - 512.0f) / 1024.0f + (mouse_pos_y - 384.0f) / 768.0f

  glm::mat4 Model = translationMatrix * rotationMatrix * scaleMatrix;

  MVP =  Projection* View * Model;
} 
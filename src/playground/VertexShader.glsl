#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 position_for_color;
uniform mat4 MVP;

void main(){

    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    position_for_color = vertexPosition_modelspace;
}
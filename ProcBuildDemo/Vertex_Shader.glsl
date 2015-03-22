#version 430 core

layout(location = 0) in vec3 in_position; // the location 0 holds the position sent by the program
void main(void)
{
    // notice conversion to vec4
    gl_Position = vec4(in_position, 1.0); // w = 1.0, point position in space
}
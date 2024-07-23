#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform float pointSize;

void main() {
    gl_PointSize = pointSize;

    vec4 offsetPos = vec4(position.x, position.y, position.z - 2.0, 1.0);

    gl_Position = projection * offsetPos;
}

// #version 450 core

// layout (location = 0) in vec3 position;

// uniform mat4 projection;
// uniform mat4 modelView;
// uniform float scale; 
// uniform float pointSize;

// void main() {
//     gl_PointSize = pointSize;

//     vec4 offsetPos = vec4(position.x, position.y, position.z - 2.0, 1.0);

//     vec4 scaledPos = vec4(offsetPos.xyz * scale, 1.0);

//     vec4 modelViewPos = modelView * scaledPos;

//     gl_Position = projection * modelViewPos;


//     //gl_Position = projection * (modelView * offsetPos);
// }

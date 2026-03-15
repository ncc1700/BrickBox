#version 330 core

uniform mat4 projection;
uniform mat4 transform;

in vec3 position;
in vec2 uv;
out vec2 frag_uv;

void main() {
   gl_Position = projection  * (transform * vec4(position, 1.0));
   frag_uv = uv;
}

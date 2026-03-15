#version 330 core

uniform mat4 transform;

in vec3 position;
in vec2 uv;
out vec2 frag_uv;

void main() {
   gl_Position = transform * vec4((position / vec3(32)) - vec3(0.5), 1.0);
   frag_uv = uv;
}

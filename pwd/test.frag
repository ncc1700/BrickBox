#version 330 core

uniform sampler2D tex_sampler;

out vec4 color;
in vec2 frag_uv;

void main() {
   color = vec4(texture(tex_sampler, frag_uv / textureSize(tex_sampler, 0)).xyz, 1.0);
}


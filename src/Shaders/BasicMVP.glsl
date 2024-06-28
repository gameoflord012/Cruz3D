@vs vs
uniform vs_params 
{
    mat4 u_mvp;
};
in vec4 position;
in vec4 color0;
in vec2 texcoord0;

out vec4 color;
out vec2 uv;

void main() {
    gl_Position =  u_mvp * position;
    color = color0;
    uv = texcoord0;
}
@end

@fs fs
uniform fs_params
{
    vec4 u_diffuseCol;
};

uniform sampler u_sampler;
uniform texture2D u_texture;

in vec4 color;
in vec2 uv;

out vec4 frag_color;

void main() {
    frag_color = texture(sampler2D(u_texture, u_sampler), uv);
}
@end

@program mvp vs fs
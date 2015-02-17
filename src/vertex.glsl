uniform float mul;

attribute vec3 position;
attribute vec3 color;

varying vec3 out_color;

void main()
{
    out_color = mul * color;
    gl_Position = vec4(position.x, position.y, -0.1, 1);
}

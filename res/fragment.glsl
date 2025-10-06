#version 410 core

in vec2 fragCoord;
out vec4 FragColor;

uniform vec2 center;
uniform float scale;
uniform float aspect;
uniform int max_iteration;

vec3 hsv2rgb(float hue, float saturation, float value) {
    vec4 HSV_CONST = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 tri = abs(fract(vec3(hue) + HSV_CONST.xyz) * 6.0 - vec3(HSV_CONST.w));
    return value * mix(vec3(HSV_CONST.x), clamp(tri - vec3(HSV_CONST.x), 0.0, 1.0), saturation);
}

void main() {
    float x0 = center.x + fragCoord.x * scale * aspect;
    float y0 = center.y + fragCoord.y * scale;
    float x = 0.0;
    float y = 0.0;
    float x2 = 0.0;
    float y2 = 0.0;
    int iteration = 0;

    while (x2 + y2 <= 4.0 && iteration < max_iteration) {
        y = 2.0 * x * y + y0;
        x = x2 - y2 + x0;
        x2 = x * x;
        y2 = y * y;
        iteration++;
    }

    if (iteration == max_iteration) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        vec3 color = hsv2rgb(float(iteration) / float(max_iteration), 1.0, 1.0);
        FragColor = vec4(color, 1.0);
    }
}

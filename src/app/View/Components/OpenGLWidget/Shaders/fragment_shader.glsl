#version 450 core

out vec4 fragColor;

uniform int lineType;
uniform vec3 fragmentColor;

void main() {

    if (lineType == 0) {
        fragColor = vec4(fragmentColor, 1.0);
    } else {

        float dashSize = 15.0;
        float gapSize = 5.0;

        float pattern = mod(gl_FragCoord.x + gl_FragCoord.y, dashSize + gapSize);

        if (pattern > dashSize) {
            discard;
        }

        fragColor = vec4(fragmentColor, 1.0);
    }
}
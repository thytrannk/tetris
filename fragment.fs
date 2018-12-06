#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 pos;

uniform float startX;
uniform float startY;
uniform bool nextPc;
uniform float cubeSizeX;
uniform float cubeSizeY;
uniform int boardWidth;
uniform int boardHeight;

/**
 * Return the normalized direction to march in from the eye point for a single pixel.
 *
 * fieldOfView: vertical field of view in degrees
 * size: resolution of the output image
 * fragCoord: the x,y coordinate of the pixel in the output image
 */
vec3 rayDirection(float fieldOfView, vec2 fragCoord) {
    vec2 xy = fragCoord;
    float z = 1.0 / tan(radians(fieldOfView) / 2.0);// y goes from 1 to -1
    return normalize(vec3(xy, -z));
}

/**
 * Normal on the surface at point p.
 */
vec3 estimateNormal(vec3 p) {
    return normalize(vec3(0.0, 0.0, 1.0));
}

/**
 * Lighting contribution of a single point light source via Phong illumination.
 *
 * The vec3 returned is the RGB color of the light's contribution.
 *
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 * lightPos: the position of the light
 * lightIntensity: color/intensity of the light
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye,
        vec3 lightPos, vec3 lightIntensity) {
    vec3 N = estimateNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));

    float dotLN = dot(L, N);
    float dotRV = dot(R, V);

    if (dotLN < 0.0) {
        // Light not visible from this point on the surface
        return vec3(0.0, 0.0, 0.0);
    }
    if (dotRV < 0.0) {
        // Light reflection in opposite direction as viewer, apply only diffuse
        // component
        return lightIntensity * (k_d * dotLN);
    }
    return lightIntensity * (k_d * dotLN + k_s * pow(dotRV, alpha));
}

/**
 * Lighting via Phong illumination.
 *
 * The vec3 returned is the RGB color of that point after lighting is applied.
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongIllumination(vec3 origin, vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    const vec3 ambientLight = 0.5 * vec3(1.0, 1.0, 1.0);
    vec3 color = ambientLight * k_a;

    vec3 light1Pos = vec3(origin.x + cubeSizeX / 2, origin.y + cubeSizeY / 2, origin.z + 0.07);
    vec3 light1Intensity = vec3(0.4, 0.4, 0.4);

    color += phongContribForLight(k_d, k_s, alpha, p, eye,
        light1Pos,
        light1Intensity);

    return color;
}

void main() {
    vec3 col;

    float lineWidthX = cubeSizeX / 50;
    float lineWidthY = cubeSizeY / 50;
    float x = floor((pos.x - startX) / cubeSizeX);
    float y = floor((pos.y - startY) / cubeSizeY);
    vec3
    origin = vec3(startX + cubeSizeX * x, startY + cubeSizeY * y, 0.0);
    float xLocal = pos.x - origin.x;
    float yLocal = pos.y - origin.y;

    if (xLocal < lineWidthX || yLocal < lineWidthY
        || xLocal > cubeSizeX - 2 * lineWidthX || yLocal > cubeSizeY - 2 * lineWidthY
        || ourColor == vec3(0.0, 0.0, 0.0)) {
        // borders, empty locations, and outside board
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else if (ourColor == vec3(0.3, 0.3, 0.3)) {
        // ghost
        FragColor = vec4(ourColor, 1.0);
    } else if (ourColor != vec3(1.0, 1.0, 1.0)) {
        // locations with cubes
        col = ourColor;
        vec3
        dir = rayDirection(45, vec2(xLocal, yLocal));
        vec3
        eye = vec3(origin.x, origin.y + cubeSizeY, 0.01);

        // distance from eye to point on the board
        float dist = sqrt(eye.z * eye.z + (pos.x - eye.x) * (pos.x - eye.x) + (pos.y - eye.y) * (pos.y - eye.y));

        // shading details
        vec3
        k_a = col;
        vec3
        k_d = col;
        vec3
        k_s = vec3(1.0, 1.0, 1.0);
        float alpha = 1.5;

        vec3
        color = phongIllumination(origin, k_a, k_d, k_s, alpha, pos, eye);

        FragColor = vec4(color, 1.0);
    }
    if (ourColor == vec3(1.0, 1.0, 1.0)
        || x > boardWidth - 1 || x < 0
        || y > boardHeight - 1 || y < 0
        ) {
        // transparent locations on pieces
        if (nextPc) {
            FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        } else {
            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        }
    }

//    FragColor = vec4(ourColor, 1.0);
}
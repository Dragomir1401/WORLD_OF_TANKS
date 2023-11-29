#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float damageIntensity;

// Output
out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;
out float damageFactor;

// Custom function to calculate displacement
vec3 calculateDisplacement(float intensity, vec3 position) {
    float displacementScale = sin(position.x * intensity) * sin(position.y * intensity) * sin(position.z * intensity);
    return v_normal * displacementScale * intensity;
}

void main() {
    // Send output to fragment shader
    frag_normal = v_normal;
    frag_color = v_color;
    tex_coord = v_texture_coord;
    
    // Compute world position
    vec4 worldPos = Model * vec4(v_position, 1.0f);

    // Apply damage effect
    vec3 displacement = calculateDisplacement(damageIntensity, v_position);
    vec3 damagedPosition = worldPos.xyz + displacement;
    damageFactor = length(displacement); // The length of the displacement can represent the damage factor

    // Compute gl_Position
    gl_Position = Projection * View * vec4(damagedPosition, 1.0f);
}

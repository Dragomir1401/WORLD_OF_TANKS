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
uniform float translateX;
uniform float translateZ;
uniform float damageIntensity;

// Output
out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;

float hash(vec3 p) // replace with a proper 3D noise function if available
{
    p = fract(p * 0.3183099 + vec3(1.0, 1.711, 2.303));
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

void main()
{
   // Send output to fragment shader
    frag_normal = v_normal;
    frag_color = v_color;
    tex_coord = v_texture_coord;
    
    // Compute world position
    vec4 worldPos = Model * vec4(v_position, 1.0f);

    // Apply damage effect
    float noise = hash(v_position * damageIntensity); // Noise based on vertex position
    vec3 damagedPosition = worldPos.xyz + v_normal * noise * damageIntensity;

    // Compute gl_Position
    gl_Position = Projection * View * vec4(damagedPosition, 1.0f);
}
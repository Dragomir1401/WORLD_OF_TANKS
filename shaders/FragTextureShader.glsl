#version 330

// Input
in vec3 frag_normal;
in vec2 tex_coord;
in float damageFactor;

// Uniform properties
uniform sampler2D texture_1;

// Output
layout(location = 0) out vec4 out_color;

// Function to calculate new color based on damage
vec4 calculateDamagedColor(vec4 originalColor, float damage) {
    vec4 damageColor = vec4(0.0, 0.0, 0.0, 1.0); // Dark color for damaged areas
    float damageEffect = clamp(damage, 0.0, 1.0); // Ensure damage factor is within [0, 1]

    // Increase the impact of the damage factor
    float enhancedDamageEffect = pow(damageEffect, 0.5); // Use a power function to enhance the effect

    // Linear blend between original color and damage color
    return mix(originalColor, damageColor, enhancedDamageEffect);
}

void main() {
    vec4 texColor = texture(texture_1, tex_coord);

    // Calculate new color based on damage factor
    vec4 newColor = calculateDamagedColor(texColor, damageFactor);

    if(newColor.a < 0.9) {
        discard;
    }

    out_color = newColor;
}

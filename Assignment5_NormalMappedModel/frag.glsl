#version 330

// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[1];  // Our lights

// Import our normal data
in vec3 norm;
// Import our texture coordinates from vertex shader
in vec2 texCoords;
// Import the fragment position
in vec3 fragPos;

void main() {
// Compute the normal direction
  vec3 norm = normalize(norm);

  // Store our final texture color
  vec3 diffuseColor;
  diffuseColor = texture(tex, texCoords).rgb;

  // (1) Compute ambient light
  vec3 ambient = pointLights[0].ambientIntensity * pointLights[0].color;

  // (2) Compute diffuse light
  // From our lights position and the fragment, we can get
  // a vector indicating direction
  // Note it is always good to 'normalize' values.
  vec3 lightDir = normalize(pointLights[0].position - fragPos);
  // Now we can compute the diffuse light impact
  float diffImpact = max(dot(norm, lightDir), 0.0);
  vec3 diffuseLight = diffImpact * pointLights[0].color;

  // (3) Compute Specular lighting
  vec3 viewPos = vec3(0.0,0.0,0.0);
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = pointLights[0].specularIntensity * spec * pointLights[0].color;

  // Calculate Attenuation here
  // distance and lighting...

  // Our final color is now based on the texture.
  // That is set by the diffuseColor
  vec3 Lighting = diffuseLight + ambient + specular;

  // Final color + "how dark or light to make fragment"
  if(gl_FrontFacing){
      fragColor = vec4(diffuseColor * Lighting,1.0);
  }else{
      // Additionally color the back side the same color
       fragColor = vec4(diffuseColor * Lighting,1.0);
  }}

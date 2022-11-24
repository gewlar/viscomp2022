#version 120
//=======================================================================
// World Information
//=======================================================================
uniform vec4 w_LightPosition;		// light position (first light)
uniform vec4 w_LightPositions[4];	// position of all lights


//=======================================================================
// Default Uniforms
//=======================================================================
uniform vec4 color;

//=======================================================================
// Varying: interpolated values from rasterizer
//=======================================================================
varying vec4 world_pos;
varying vec4 world_normal;

//=======================================================================
// Computes the intensity of the reflected diffuse light for a point
// at position 'position' with normal vector 'normal', if the light
// source is located at 'lightPos'.
//=======================================================================
float computeDiffuseIntens(vec3 position, vec3 normal, vec3 lightPos)
{
	normal = normalize(normal);
	vec3 vecToLight = normalize(lightPos.xyz - position.xyz);
	
	float diffuseIntensity = dot(normal, vecToLight);
	
	diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);
	
	return diffuseIntensity;
}


//=======================================================================
// Fragment program entry point
//=======================================================================
void main(void)
{
	// Do some simple diffuse shading
	float diffuseIntensity = computeDiffuseIntens(world_pos.xyz, world_normal.xyz, w_LightPosition.xyz);
	float ambientIntensity = 0.3;
	
	gl_FragColor = (diffuseIntensity + ambientIntensity)*color;
}

#version 130
//=======================================================================
// World Information
//=======================================================================
uniform mat4 w_ViewMatrix;			// The camera vie matrix
uniform mat4 w_ProjectionMatrix;		// The projection matrix
uniform mat4 w_ProjectionViewMatrix;		// multiplied matrix
		
uniform vec4 w_CameraPosition;			// camera position in world coord
uniform vec4 w_LightPosition;			// light position (first light)

uniform vec4 w_LightPositions[4];		// position of all lights


//=======================================================================
// Model Information
//=======================================================================
uniform mat4 m_ModelMatrix;
uniform mat4 m_ModelNormalMatrix;
uniform mat4 m_ViewModelMatrix;
uniform mat4 m_ProjectionViewModelMatrix;


//=======================================================================
// In: Per vertex data
//=======================================================================
//uniform vec4 in_color;

in vec4 position;			// Vertex coordinates in model space
in vec4 normal;				// Vertex normal
in vec2 texcoord;			// Vertex normal


//=======================================================================
// Out: Vertex shader output, input to rasterizer
//=======================================================================
out vec4 world_pos;
out vec4 world_normal;

out vec4 out_color;


//=======================================================================
// Vertex program entry point
//=======================================================================
void main(void)
{	
	// do everything in world coordinates
	world_pos = m_ModelMatrix * position;
	world_normal = m_ModelNormalMatrix * normal;
	
   	gl_Position = w_ProjectionViewMatrix * world_pos;
}

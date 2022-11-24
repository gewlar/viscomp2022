#include <stdio.h>
#include <iostream>

#include "exercises.h"

#include "Helpers/Matrix.h"
#include "Helpers/Vector.h"
#include "Helpers/glutApplication.h"
#include "Helpers/GLShader.h"
#include "Helpers/Model.h"
#include "Helpers/World.h"
#include "Helpers/Quaternion.h"

#include "BuiltInPath.h"

using namespace std;

class TransformWindow: public GlutWindow, public World
{
private:
	Model	heli_body;
	Model	heli_rotor1;
	Model	heli_rotor2;
	Model	tower_eth;

	//moving camera
	bool m_doCameraMotion;
	float m_CameraStartTime;
	vector < Matrix> m_CameraViews;
	vector < Vector > m_CameraPositions, m_CameraTangents;
	vector < Quaternion > m_CameraRot_q, m_CameraRot_a;
	vector < float > m_CameraTimes;
	
	// Flag for each of 256 characters. true = pressed, false = not pressed.
	vector<bool> m_keyPressed;

	// Time in previous call to Update()
	float m_timePrev;

public:
	TransformWindow()
	: 
		GlutWindow("Transform",  GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE),
		m_doCameraMotion(false)
	{
		m_keyPressed.resize(256, false);
		m_timePrev = 0; 
#if STEP >= 5
		m_doCameraMotion = true;
#else
		m_doCameraMotion = false;
#endif
	}

	virtual void LoadEvent() {
		glutReshapeWindow(1024, 768);
        std::cout << "glutReshapeWindow\n";
        //glewInit(); // <-- uncomment if glew is used
		GLuint vao=0;
		glGenVertexArrays(1, &vao);
        glCheckandPrintError();
        std::cout << "glGenVertexArrays\n";

		glBindVertexArray(vao);
        std::cout << "glBindVertexArray\n";
        
		//wglSwapIntervalEXT(0);
		
		// Load Default(0) Material
		this->addMaterial(new ColoredDiffuseMaterial());
        std::cout << "addMaterial\n";

		// Load Models
		heli_body.loadFromFile(MAIN_DIR "models/helicopter_body.ptn");
		heli_body.setDefaultColor(Vector(0.5f,0.5f,0.8f));
		heli_body.setGroupColor(heli_body.findGroup("window"), Vector(0.8f,0.8f,0.9f));

		heli_rotor1.loadFromFile(MAIN_DIR "models/helicopter_rotor1.ptn");
		heli_rotor1.setDefaultColor(Vector(0.9f,0.4f,0.4f));

		heli_rotor2.loadFromFile(MAIN_DIR "models/helicopter_rotor2.ptn");
		heli_rotor2.setDefaultColor(Vector(0.4f,0.9f,0.4f));

		tower_eth.loadFromFile(MAIN_DIR "models/eth_tower.ptn");
		tower_eth.setDefaultColor(Vector(187.f, 167.f, 156.f) * (1.0f / 255.0f));
		tower_eth.setGroupColor(tower_eth.findGroup("glass_windows"), Vector(0.8f,0.8f,0.9f));
		tower_eth.setGroupColor(tower_eth.findGroup("untextured"), Vector(1.0f, 0.8f, 0.05f));
		tower_eth.setGroupColor(tower_eth.findGroup("textnorm_brushedmetal"), Vector(.5f, 0.55f, 0.6f));

	
		// background color
		glClearColor(114.f/255.f, 163.f/255.f, 219.f/255.f, 1.0f);

		//initialize camera
		//position and orientation
		m_cameraPosition= Vector(-5.636f,       2.426f,       6.570f,       1.000f);
		m_cameraDirection=Vector(0.613f,      -0.014f,      -0.796f,       1.000f);
		m_cameraUpVector = Vector( 0.f, 1.f, 0.f );

		
		//Moving Camera
		//get build in view matrices
		getBuiltInViews(m_CameraViews);

		//construct interpolation path from view matrices
		buildCameraPathFromViews( m_CameraViews );

		glCheckandPrintError();
	}

	virtual void Draw( float time ) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updatePredefinedMaterialParamters();

		heli_body.draw(*this, DRAWPASS_FINAL);
		heli_rotor1.draw(*this, DRAWPASS_FINAL);
		heli_rotor2.draw(*this, DRAWPASS_FINAL);
		tower_eth.draw(*this, DRAWPASS_FINAL);		

		glCheckandPrintError();
	}

	virtual void Update( float time ) 
	{
		// Speed of camera in units per second
		const float camSpeed = 40.0f;

		float deltaTime = time - m_timePrev;
		m_timePrev = time;

#if STEP >= 2
		//Step 2
		//Use the keys to move the camera
#else
		if(m_keyPressed['w'] || m_keyPressed['W'])
		{
			// TODO
		}

		if(m_keyPressed['s'] || m_keyPressed['S'])
		{
			// TODO
		}

		if(m_keyPressed['d'] || m_keyPressed['D'])
		{
			// TODO
		}

		if(m_keyPressed['a'] || m_keyPressed['A'])
		{
			// TODO
		}
#endif

		//////////////////////////////////////////////////////////////////////////
		// Calculate Transformation
		//////////////////////////////////////////////////////////////////////////
		Matrix helicopter, rotor1, rotor2;
		helicopter = rotor1 = rotor2 = Matrix::createIdentityMatrix();
#if STEP >= 3

		//Step 3
		//--------------------------------------------------------------------//

		//Rotate rotors

		//Translate rotors

		//Position Helicopter

		//Set new matrices to the models

		//--------------------------------------------------------------------//

#else
		TODO(3);
#endif

		//do camera motion
		updateCamera( time );
		glutPostRedisplay();
	}

	virtual void KeyEvent(unsigned char key, int state, int modifiers , int x, int y) 
	{
		if(state == GLUT_DOWN)
			m_keyPressed[key] = true;
		else
			m_keyPressed[key] = false;

		if(state == GLUT_DOWN) {
			switch(key) {
				case 'p': //print camera position
						cout << "m_cameraPosition=" << (string) m_cameraPosition << endl;
						cout << "m_cameraDirection=" << (string) m_cameraDirection << endl;
						break;
				case 'P':
						cout << (string) m_viewMatrix << endl;
						break;				
				case '1':
						m_cameraPosition = Vector(-5.636f,      2.426f,       6.570f,       1.000f);
						m_cameraDirection = Vector(0.613f,      -0.014f,      -0.796f,       1.000f);
                        cout << "1 pressed\n";
						break;
				case '2':
						m_cameraPosition = Vector(84.180f,     200.767f,      56.161f,       1.000f);
						m_cameraDirection = Vector(-0.413f,      -0.573f,      -0.715f,       1.000f);
                        cout << "2 pressed\n";
						break;
				case '3':
						m_cameraPosition = Vector(59.861f,     175.408f,      32.249f,       1.000f);
						m_cameraDirection = Vector(-0.391f,      -0.316f,      -0.900f,       1.000f);
                        cout << "3 pressed\n";
						break;
				case ' ':
						m_doCameraMotion = !m_doCameraMotion;
						m_CameraStartTime = -1.0f;
                        cout << "space pressed\n";
						break;
				case 27:  // ESCAPE
						this->Close();
						break;
			}
		}
	}
	
	virtual void MouseEvent(unsigned int buttons, int first_time, int x, int y)
	{
		if(buttons & (1<<GLUT_LEFT_BUTTON)) {
			static Vector start_direction;
			static Vector start_bidirection;
			static Vector start_upvector;

			if(first_time & (1<<GLUT_LEFT_BUTTON)) {
				//when drag start remember original directions
				start_direction = m_cameraDirection;
				start_upvector = m_cameraUpVector;
				start_bidirection = m_cameraDirection.cross3(m_cameraUpVector);
			}

			//during drag
			int ox, oy;
			getMouseDragStartPositions(GLUT_LEFT_BUTTON, ox,oy);
			
			//calculate rotation
			Matrix rot;
			float pixeltorad = PI / 500.0f;  //500 pixel is half sphere

#if STEP >= 2
			
			//Step 2

			//-------------------------------------------------------------------------------------//

			//This code should rotate the camera direction when dragging the mouse.

			//Calculate a rotation matrix rot from the current position (x,y) and initial position
			//(x0, y0) of the mouse.

			//Rotate direction of camera by using rot.

			//-------------------------------------------------------------------------------------//

			// enforce that horizon stays horizontal (no roll)
			Vector bidirection = rot * start_bidirection;
			bidirection[1] = 0;
			m_cameraUpVector = bidirection.cross3(m_cameraDirection);
			m_cameraUpVector = m_cameraUpVector.normalized3();

#else

			//calculate rotation matrix
			TODO(2);
			rot = Matrix::createIdentityMatrix();

			//apply rotation to camera direction vector

			// enforce that horizon stays horizontal (no roll)
			Vector bidirection = rot * start_bidirection;
			bidirection[1] = 0;
			m_cameraUpVector = bidirection.cross3(m_cameraDirection);
			m_cameraUpVector = m_cameraUpVector.normalized3();
#endif
		}

		glutPostRedisplay();
	}

	virtual void ReshapeEvent(int width, int height) {
		glViewport(0, 0, width, height);
		//projection
		m_projectionMatrix = Matrix::createPerspectiveMatrix(Matrix::radians(60),
			(float)width/(float)height,
			0.5,
			1000
			);
	}

	//////////////////////////////////////////////////////////////////////////
	// Helper functions
	//////////////////////////////////////////////////////////////////////////
	void updateCamera( float time )
	{
		if(m_doCameraMotion) {
			if(m_CameraStartTime == -1.0f)
				m_CameraStartTime = time;

			float t = time - m_CameraStartTime; 

			if(t > m_CameraTimes.back()) {
				t = 0;
				m_CameraStartTime = time;
			}

			doCameraMotion( t );
		} else {
			// set m_viewMatrix by calling createLookAtMatrix
			// with m_cameraPosition, m_cameraDirection, m_cameraUpVector
			// as parameter

			m_viewMatrix = Matrix::createLookAtMatrix(
				m_cameraPosition,
				m_cameraPosition + m_cameraDirection,
				m_cameraUpVector
				);
		}

		//light moves with camera
		m_lightPositions[0] = m_cameraPosition;

	}

	void buildCameraPathFromViews( const vector< Matrix >& m_CameraViews )
	{
		// Delete Old Path
		m_CameraPositions.clear();
		m_CameraTangents.clear();
		m_CameraRot_q.clear();
		m_CameraRot_a.clear();
		m_CameraTimes.clear();

		float time = 0.0f;
		for(unsigned int i = 0; i < m_CameraViews.size(); i++) {
#if STEP >= 5 
			//Step 5
			//Read the current camera view matrix and set the corresponding m_CameraPositions and m_CameraRot_q
#else
			TODO(5);
			m_CameraPositions.push_back(Vector());
			m_CameraRot_q.push_back(Quaternion());

#endif
			m_CameraTimes.push_back(time);
			time += 1.0f;
		}

		calcKochanekBartelsTagents(m_CameraPositions, m_CameraTangents, m_CameraTimes);
		calcInbetweenQuaternions(m_CameraRot_q, m_CameraRot_a, m_CameraTimes );

	}

	void doCameraMotion( float time ) 
	{
#if STEP >= 5
		
		m_cameraPosition = cubicInterpolate(m_CameraPositions, m_CameraTangents, m_CameraTimes, time);
		Quaternion rot = cubicQuaternion(m_CameraRot_q, m_CameraRot_a, m_CameraTimes, time);

		//Step 5
		//Set the view matrix according to m_cameraPosition and rot.
#else
		TODO(5);
		// USE 
		// cubicInterpolate( m_CameraPositions, m_CameraTangents, m_CameraTimes, time  );
		// cubicQuaternion( m_CameraRot_q, m_CameraRot_a, m_CameraTimes, time);
		// to recosntruct view matrix
#endif
	}


	//////////////////////////////////////////////////////////////////////////
	// Does interpolation with Cubic Hermite splines
	//////////////////////////////////////////////////////////////////////////
	Vector cubicInterpolate( const vector< Vector > & positions,
							 const vector< Vector >	& tangents,
							 const vector< float  > & times,
							 float t,
							 unsigned int i = 0) 
	{
		assert( positions.size() == tangents.size() &&
				positions.size() == times.size() );
		assert( positions.size() > 1);
		assert( i >= 0 && i < times.size() );

		//find segment i
		if( t <= times.front() )
			return positions.front();

		if( t >= times.back() )
			return positions.back();

		//if i is wrong start from beginning;
		if(times[i] > t)
			i = 0;

		//find the current interval
		for(; i < times.size(); i++) {
			if( times[i] > t)
				break;
		}
		i = i - 1;

		//t in [0,1]
		t = (t - times[i]) / (times[i+1] - times[i]);

		float t3 = t*t*t;
		float t2 = t*t;
		
		return	positions[i]	* (2*t3 - 3*t2 +1 ) +
				tangents[i]		* (t3 - 2*t2 +t) +
				tangents[i+1]	* (t3-t2) +
				positions[i+1]	* ((-2)*t3 + 3*t2);
	}

	//////////////////////////////////////////////////////////////////////////
	// Does interpolation for quaternions
	//////////////////////////////////////////////////////////////////////////
	Quaternion cubicQuaternion( const vector< Quaternion > & qs,
							const vector< Quaternion > & as,
							const vector< float  > & times,
							float t,
							unsigned int i = 0) 
	{
		assert( qs.size() == as.size() &&
				qs.size() == times.size() );
		assert( qs.size() > 1);
		assert( i >= 0 && i < times.size() );

		//find segment i
		if( t <= times.front() )
			return qs.front();

		if( t >= times.back() )
			return qs.back();
		
		//if i is wrong start from beginning;
		if(times[i] > t)
			i = 0;

		//find the current interval
		for(; i < times.size(); i++) {
			if( times[i] > t)
				break;
		}
		i = i - 1;

		//t in [0,1]
		t = (t - times[i]) / (times[i+1] - times[i]);

		Quaternion res =	Quaternion::slerp(
							Quaternion::slerp( qs[i], qs[i+1], t),
							Quaternion::slerp( as[i], as[i+1], t),
							2*t*(1-t)
							);
		return	res;
	}

	//////////////////////////////////////////////////////////////////////////
	// Calculates the in between tangents which are used by cubicQuaternion
	// this gives smooth transitions from one segment to the next 
	//////////////////////////////////////////////////////////////////////////
	void  calcInbetweenQuaternions(	vector< Quaternion > & qs,
									vector< Quaternion >	& as,
									const vector< float  > & times) 
	{
		assert( qs.size() > 1 );

		as.resize(qs.size());

		as.front() = qs.front();
		as.back()  = qs.back();
		for(unsigned int i = 1; i < as.size(); i++ ) {
			if( qs[i-1].dot(qs[i]) < 0.0 ) {
				qs[i] = -qs[i];
			}
		}

		for(unsigned int i = 1; i < as.size() - 1; i++ ) {
			Quaternion qi = qs[i].inversed();
	
			as[i] = qs[i] * Quaternion::qexp(
								(
									Quaternion::qlog(qi*qs[i-1]) + 
									Quaternion::qlog(qi*qs[i+1])
								)* (-0.25)
							);	
		}

	} 

	//////////////////////////////////////////////////////////////////////////
	// Calculates the in between tangents which are used by cubicInterpolate
	// Tangents are chosen according Kochanek-Bartels with the default 
	// parameters(a = b = c = 0) which gives a Catmull�Rom spline
	//////////////////////////////////////////////////////////////////////////
	void  calcKochanekBartelsTagents(	const vector< Vector > & positions,
		vector< Vector >	& tangents,
		const vector< float  > & times) 
	{
		assert( positions.size() > 1 );

		tangents.resize(positions.size());

		tangents.front() = positions[1] - positions[0];
		tangents.back()  = positions[positions.size()-1] - positions[positions.size()-2];

		//okay make it simple all parameters a = b = c = 0
		for(unsigned int i = 1; i < tangents.size() - 1; i++ ) {
			tangents[i] = (positions[i] - positions[i-1]) * 0.5 +
				(positions[i+1] - positions[i]) * 0.5;
			//weight with time
			tangents[i] = tangents[i] * ( 2*(times[i+1] - times[i])/ ( times[i] - times[i-1] + times[i+1] - times[i] ));
		}

	} 


	
};


int main(int argc, char **argv)
{
	GlutApplication app(&argc, argv);
	
	app.setOpenGLVersion(2, 1);

	GlutWindow *window = new TransformWindow();
	
	app.addWindow(window);

	app.Run();

	return 0;
}

#include <cmath>
#include <fstream>
#include <iostream>
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "soil/SOIL.h"

#include "camera.h"
#include "GameObject.h"
#include "Particle.h"
#include "Gnome.h"
#include "LoadTexture.h"
#include "Fungus.h"
#include "shader.h"
#include "vertex.h"
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <unordered_map>

#include <chrono>
#include <ctime>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "Cuda.cuh"

#pragma comment(lib, "glew32.lib") 
#endif

using namespace std;
using namespace glm;

class GameEngine
{
private:
	static vector<GameObject*> grass;                                                       // Vector of Game Object pointers for the grass tiles
	static vector<GameObject*> gnomes;                                                      // Vector of Game Object pointers for the gnome tiles
	static std::vector<std::vector<GameObject*>> grid;                                      // The grid of tiles
	static vector<Particle>* objectParticle;                                                // A pointer to a vector of particles
	static int oldTimeSinceStart;
	static int newTimeSinceStart;

	void CleanUpEngine();                                                                   // Delete the objects afterwards.
	static void ResizeWindow(int w, int h);                                                 // The function to alter the window contents if the screen changes shape.
	static void DrawGame(void);				                                                // Renders the game
	static void UpdateGame(void);			                                                // Updates the game
	static int  GrassRules(vector<GameObject*> grassObjs);
	static void GnomeInteractor(vector<GameObject*> grassObjs, vector<GameObject*> gnomes);
	static void GnomeMovement(vector<GameObject*> grassObjs, vector<GameObject*> gnomes);

public:
	static Camera camera;                                                                   // Access to camera object..
	static Cuda   cudaClass;				                                                // To runn CUDA Kernels
	static LoadTexture texture;				                                                // To manage the textures
	static int xGridCells;                                                                  // Cells across
	static int yGridCells;                                                                  // Cells up
	static int gnomeCount;                                                                  // Gnomes
	static int percentAlive;                                                                // Percentage of cells alive

	static cudaError_t cudaStatus;


	void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height); //The function to set up/initialize Opengl and GLUT and the function to get things ready (but not run).
	void Initialise();						                                                // Human input for variables
	void StartEngine();						                                                // Start the game world.
	static void Setup();					                                                // Instatiated and populates world.
};
//Proyecto - 2 Final
//Autor: 311243563
//Fecha de entrega: 25 de noviembre de 2025


#include <iostream>
#include <cmath> 

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation(GLfloat deltaTime);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);

//Variables Animación Momia/Sarcófago
bool animMummy = false;
float mummyLegRot = 0.0f;
bool mummyStep = false;
glm::vec3 mummyPos = glm::vec3(37.0f, 2.8f, 0.0f);
float mummyRot = 270.0f;

const float MUMMY_SCALE_MIN = 1.0f;
const float MUMMY_SCALE_MAX = 1.4f;
float mummyScale = MUMMY_SCALE_MIN;

bool animSarcofago = false;
glm::vec3 sarcofagoPos = glm::vec3(37.0f, 2.8f, 0.0f);
float tapaPosCerrado = 0.0f;
float tapaPosAbierto = 0.5f;
float tapaPosX = tapaPosCerrado;
float tapaAnimSpeed = 0.0002f;
float tapaPosBaseZ = 0.2f;
float tapaLevitateAmount = 0.3f;
float tapaPosZ = tapaPosBaseZ;
float tapaShakeAmount = 0.008f;


int animState = 0;
float mummyMoveSpeed = 0.001f;
float mummyWalkTargetDist = 1.0f;
float mummyWalkDistance = 0.0f;
float stateTimer = 0.0f;
float mummyArmRot = 0.0f;
float mummyArmSpeed = 1.0f;
float mummyArmMaxAngle = 90.0f;
bool mummyArmWavingUp = true;


//Variables Animación Perro
bool animDog = false; // Activado con tecla P

//Posición inicial del perro
glm::vec3 dogPos = glm::vec3(18.0f, 3.0f, -18.0f);

float dogRotBody = 0.0f;

float dogTailRot = 0.0f;
float dogHeadRot = 0.0f;
float dogFLegLRot = 0.0f;
float dogFLegRRot = 0.0f;
float dogBLegLRot = 0.0f;
float dogBLegRRot = 0.0f;

//Variables de control de trayectoria
int dogPathState = 0;       // 0=Subir, 1=Izquierda, 2=Bajar, 3=Derecha
float dogWalkSpeed = 0.05f; // Velocidad con la que camina el perro


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto 2 - Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	Shader skyboxshader("Shader/SkyBox.vs", "Shader/SkyBox.frag");


	//Carga de Modelos

	// Momia
	Model MummyBody((char*)"Models/cuerpo.obj");
	Model MummyArmL((char*)"Models/brazo_izq.obj");
	Model MummyArmR((char*)"Models/brazo_der.obj");
	Model MummyLegR((char*)"Models/pierna_der.obj");
	Model MummyLegL((char*)"Models/pierna_izq.obj");

	// Sarcófago
	Model Sarcofago((char*)"Models/sarcofago.obj");
	Model TapaSarcofago((char*)"Models/tapa_sarcofago.obj");

	// Perro
	Model DogBody((char*)"Models/DogBody.obj");
	Model HeadDog((char*)"Models/HeadDog.obj");
	Model DogTail((char*)"Models/TailDog.obj");
	Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");

	// Museo
	Model SalaEgipcia((char*)"Models/museo.obj");



	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	//Skybox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Load textures
	vector < const GLchar*> faces;
	faces.push_back("SkyBox/right.jpg");
	faces.push_back("SkyBox/left.jpg");
	faces.push_back("SkyBox/top.jpg");
	faces.push_back("SkyBox/bottom.jpg");
	faces.push_back("SkyBox/back.jpg");
	faces.push_back("SkyBox/front.jpg");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation(deltaTime);

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 sarcofagoModelTemp = glm::mat4(1.0f);
		glm::mat4 dogModelTemp = glm::mat4(1.0f); //Temp para el perro

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);


		//museo
		model = glm::mat4(1); // Matriz identidad para la sala
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		SalaEgipcia.Draw(lightingShader);


		// Dibujo de la momia

		sarcofagoModelTemp = glm::mat4(1);
		sarcofagoModelTemp = glm::translate(sarcofagoModelTemp, sarcofagoPos);
		sarcofagoModelTemp = glm::rotate(sarcofagoModelTemp, glm::radians(mummyRot), glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::mat4(1); // Reiniciar matriz

		// Aplicar transformaciones base (Posición y Rotación)
		model = glm::translate(model, mummyPos);
		model = glm::rotate(model, glm::radians(mummyRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(mummyScale, mummyScale, mummyScale));

		modelTemp = model; // Guardar matriz base cuerpo

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MummyBody.Draw(lightingShader);

		// Pierna Izquierda
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.08f, -0.9f, 0.09f));
		model = glm::rotate(model, glm::radians(mummyLegRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MummyLegL.Draw(lightingShader);

		// Pierna Derecha
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.1f, -0.9f, 0.0f));
		model = glm::rotate(model, glm::radians(-mummyLegRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MummyLegR.Draw(lightingShader);


		// Brazo Izquierdo
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.24f, 0.15f, 0.0f));

		float leftArmXRot = 0.0f;
		float leftArmYRot = 0.0f;

		if (animState == 2 || animState == 3)
		{
			leftArmXRot = -90.0f;
			leftArmYRot = 0.0f;
		}
		else
		{
			leftArmXRot = -75.0f;
			leftArmYRot = 35.0f;
		}

		model = glm::rotate(model, glm::radians(leftArmXRot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(leftArmYRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MummyArmL.Draw(lightingShader);

		// Brazo Derecho
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.24f, 0.15f, 0.0f));

		float rightArmXRot = 0.0f;
		float rightArmYRot = 0.0f;

		if (animState == 2 || animState == 3)
		{
			rightArmXRot = -90.0f;
			rightArmYRot = 0.0f;
		}
		else
		{
			rightArmXRot = -75.0f;
			rightArmYRot = -35.0f;
		}

		model = glm::rotate(model, glm::radians(rightArmXRot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rightArmYRot), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MummyArmR.Draw(lightingShader);

		// Sarcofago Cuerpo
		model = sarcofagoModelTemp;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sarcofago.Draw(lightingShader);

		// Sarcofago Tapa
		float shakeOffsetY = 0.0f;
		if (animState == 1 || animState == 5)
		{
			shakeOffsetY = sinf(currentFrame * 10.0f) * tapaShakeAmount;
		}

		model = sarcofagoModelTemp;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(tapaPosX, -0.1f + shakeOffsetY, tapaPosZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TapaSarcofago.Draw(lightingShader);


		// Dibujo del perro

		model = glm::mat4(1);
		//Body Dog
		model = glm::translate(model, dogPos); // Posición dinámica
		model = glm::rotate(model, glm::radians(dogRotBody), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		

		// Matriz del cuerpo del perro
		dogModelTemp = model;

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);

		//Head Dog
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(dogHeadRot), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);

		//Tail Dog
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(dogTailRot), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar en Y para mover cola izq/der
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogTail.Draw(lightingShader);

		//Front Left Leg
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(dogFLegLRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);

		//Front Right Leg
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(dogFLegRRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);

		//Back Left Leg
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218));
		model = glm::rotate(model, glm::radians(dogBLegLRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_LeftLeg.Draw(lightingShader);

		//Back Right Leg
		model = dogModelTemp;
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(dogBLegRRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader);



		//Draw SkyBox
		glDepthFunc(GL_LEQUAL);
		skyboxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVAO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}

}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);

		}
		else
		{
			Light1 = glm::vec3(0);
		}
	}

	// TECLA M PARA LA MOMIA 
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		animMummy = !animMummy;
	}


	// TECLA N PARA EL SARCÓFAGO 
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		if (animState == 0)
		{
			animSarcofago = true;
			animState = 1;
		}
	}

	// TECLA P PARA EL PERRO 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		animDog = !animDog;
	}

}


void Animation(GLfloat deltaTime) {


	// ANIMACION MOMIA
	if (animMummy)
	{

		float animSpeed = 0.02f;
		float maxAngle = 40.0f;

		if (!mummyStep) {
			mummyLegRot += animSpeed;
			if (mummyLegRot > maxAngle) {
				mummyLegRot = maxAngle;
				mummyStep = true;
			}
		}
		else {
			mummyLegRot -= animSpeed;
			if (mummyLegRot < -maxAngle) {
				mummyLegRot = -maxAngle;
				mummyStep = false;
			}
		}
	}
	else
	{
		mummyLegRot = 0.0f;
	}

	// ANIMACION PERRO 
	if (animDog)
	{
		// Animación de patas y cola
		float time = glfwGetTime();
		float speed = 10.0f;

		dogTailRot = sin(time * 15.0f) * 20.0f;
		dogFLegLRot = sin(time * speed) * 30.0f;
		dogFLegRRot = sin(time * speed + 3.14f) * 30.0f;
		dogBLegLRot = sin(time * speed + 1.0f) * 30.0f;
		dogBLegRRot = sin(time * speed + 4.14f) * 30.0f;


		// Máquina de Estados

		switch (dogPathState)
		{
		case 0: // Mover hacia +Z (Hacia abajo en pantalla)
			dogPos.z += dogWalkSpeed;
			dogRotBody = 0.0f; 
			if (dogPos.z >= 5.0f) dogPathState = 1;
			break;

		case 1: // Mover hacia -X (Izquierda)
			dogPos.x -= dogWalkSpeed;
			dogRotBody = 270.0f; 
			if (dogPos.x <= -5.0f) dogPathState = 2;
			break;

		case 2: // Mover hacia -Z (Hacia arriba en pantalla)
			dogPos.z -= dogWalkSpeed;
			dogRotBody = 180.0f; 
			if (dogPos.z <= -18.0f) dogPathState = 3;
			break;

		case 3: // Mover hacia +X (Derecha)
			dogPos.x += dogWalkSpeed;
			dogRotBody = 90.0f; 
			if (dogPos.x >= 18.0f) dogPathState = 0;
			break;
		}

	}
	else
	{
		// Resetear perro a pose estatica
		dogTailRot = 0.0f;
		dogFLegLRot = 0.0f;
		dogFLegRRot = 0.0f;
		dogBLegLRot = 0.0f;
		dogBLegRRot = 0.0f;
	}


	// ANIMACION SARCOFAGO

	if (animSarcofago)
	{
		float ratio = 0.0f;

		switch (animState)
		{
		case 1: // Abrir Tapa
			tapaPosX += tapaAnimSpeed;
			ratio = tapaPosX / tapaPosAbierto;
			tapaPosZ = tapaPosBaseZ + (sinf(ratio * 3.14159f) * tapaLevitateAmount);

			if (tapaPosX > tapaPosAbierto)
			{
				tapaPosX = tapaPosAbierto;
				tapaPosZ = tapaPosBaseZ;
				animState = 2;
				animMummy = true;
			}
			break;

		case 2: // Momia caminando adelante
		{
			mummyPos.x += sinf(glm::radians(mummyRot)) * mummyMoveSpeed;
			mummyPos.z += cosf(glm::radians(mummyRot)) * mummyMoveSpeed;
			mummyWalkDistance += mummyMoveSpeed;

			float walkRatio = mummyWalkDistance / mummyWalkTargetDist;
			mummyScale = MUMMY_SCALE_MIN + (walkRatio * (MUMMY_SCALE_MAX - MUMMY_SCALE_MIN));
			if (mummyScale > MUMMY_SCALE_MAX) mummyScale = MUMMY_SCALE_MAX;

			if (mummyWalkDistance > mummyWalkTargetDist)
			{
				mummyScale = MUMMY_SCALE_MAX;
				animState = 3;
				animMummy = false;
				stateTimer = 0.0f;
			}
		}
		break;

		case 3: // Pausa
			stateTimer += deltaTime;
			if (stateTimer > 3.0f)
			{
				animState = 4;
				animMummy = true;
				mummyArmRot = 0.0f;
			}
			break;

		case 4: // Momia caminando atrás
		{
			mummyPos.x -= sinf(glm::radians(mummyRot)) * mummyMoveSpeed;
			mummyPos.z -= cosf(glm::radians(mummyRot)) * mummyMoveSpeed;

			mummyWalkDistance -= mummyMoveSpeed;

			float walkRatioBack = mummyWalkDistance / mummyWalkTargetDist;
			mummyScale = MUMMY_SCALE_MIN + (walkRatioBack * (MUMMY_SCALE_MAX - MUMMY_SCALE_MIN));
			if (mummyScale < MUMMY_SCALE_MIN) mummyScale = MUMMY_SCALE_MIN;

			if (mummyWalkDistance < 0.0f)
			{
				mummyWalkDistance = 0.0f;
				mummyPos = sarcofagoPos;
				mummyScale = MUMMY_SCALE_MIN;
				animState = 5;
				animMummy = false;
			}
		}
		break;

		case 5: // Cerrando Tapa
			tapaPosX -= tapaAnimSpeed;

			ratio = tapaPosX / tapaPosAbierto;
			tapaPosZ = tapaPosBaseZ + (sinf(ratio * 3.14159f) * tapaLevitateAmount);

			if (tapaPosX < tapaPosCerrado)
			{
				tapaPosX = tapaPosCerrado;
				tapaPosZ = tapaPosBaseZ;
				animState = 0;
				animSarcofago = false;
			}
			break;
		}
	}

}



void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = (GLfloat)xPos;
		lastY = (GLfloat)yPos;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat)xPos - lastX;
	GLfloat yOffset = lastY - (GLfloat)yPos;

	lastX = (GLfloat)xPos;
	lastY = (GLfloat)yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
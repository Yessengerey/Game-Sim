#pragma once
#include "Renderer.h"
#include "Entity.h"
#pragma comment(lib, "nclgl.lib")

class GameInit{
public:
	
	GameInit(Renderer& r);

	//Function to create all entities and populate
	//the entity vectore 
	void populateEntities();

	//Function to create all appropriate meshes,
	//physical representations, render objects,
	//as well as assign all necessary model 
	//matricies.
	//Store all render objects in the render
	//object array
	void createMeshes(Shader* s, Shader* os);

	//Function to add all objects from the
	//render object array on to the screen
	void addToScreen(Renderer& r);

	//Initial positions of the balls (non-red)
	Vector3 whiteBallPosition = Vector3(0.7f, 0.0f, -3.0f);
	Vector3 greenBallPosition = Vector3(0.6f, -0.17f, -3.0f);
	Vector3 brownBallPosition = Vector3(0.6f, 0.0f, -3.0f);
	Vector3 yellowBallPosition = Vector3(0.6f, 0.17f, -3.0f);
	Vector3 blueBallPosition = Vector3(0.0f, 0.0f, -3.0f);
	Vector3 pinkBallPosition = Vector3(-0.5f, 0.0f, -3.0f);
	Vector3 blackBallPosition = Vector3(-0.85f, 0.0f, -3.0f);

	//Ball Colours
	Vector4 WHITE = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 GREEN = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	Vector4 BROWN = Vector4(0.4f, 0.2f, 0.0f, 1.0f);
	Vector4 YELLOW = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	Vector4 BLUE = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	Vector4 PINK = Vector4(1.0f, 0.6f, 0.6f, 1.0f);
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4 RED = Vector4(0.8f, 0.0f, 0.0f, 1.0f);
	Vector4 GREY = Vector4(0.753f, 0.753f, 0.753f, 1.0f);

	//Table Colours
	Vector4 TABLE_BROWN = Vector4(0.298f, 0.125f, 0.027f, 1.0f);
	Vector4 TABLE_GREEN = Vector4(0.0f, 0.6f, 0.298f, 1.0f);

	//Radius of balls and pockets
	float ballRadius = 0.025f;
	float pocketRadius = 0.035f;

	//Size of arrayOfMeshes and arrayOfRenders
	static const int size_of_arrays = 39;

	//Vector storing all the indecies of the table
	vector<Vector3> tableIndecies;

	//Vector to store all of the indecies (coordinates)
	//of the pockets
	vector<Vector3> pocketIndecies;

	//Vector sotring all coordinates of all coloured balls
	//including the white one
	vector<Vector3> colouredBallPos;

	//Vector storing all entity objects
	//Balls, tables, pockets, lines, markings, etc.
	vector<Entity*> entities;

	//Array storing all meshes for each of the entities
	Mesh* arrayOfMeshes[size_of_arrays];

	//Array storing all render objects for each entity
	RenderObject arrayOfRenders[size_of_arrays];

	//Counter that is used in createMeshes function
	//when creating meshes and other things for entities
	//type Pocket
	int k = 0;

	//Initial positions of all entity objects
	Vector3 init_pos = Vector3(0.0f, 0.0f, 0.0f);
};
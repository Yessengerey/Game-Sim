#pragma once
#include "Renderer.h"
#include "Physics.h"

enum ENT_TYPE{
	BALL,
	WHITE_BALL,
	RED_BALL,
	POCKET,
	HALF_CIRCLE,
	LINE,
	SPOT,
	TABLE,
	POW_BAR,
	ARROW
};

class Entity{
public:
	//Entity constructor for a half circle object
	Entity(Vector3 v, float y, ENT_TYPE);

	//Entity for a Ball object
	Entity(Vector3, Vector4, float, ENT_TYPE);

	//Entity constructor for a line object
	Entity(Vector3 p1, Vector3 p2, Vector4 colour, ENT_TYPE);

	//Entity constructor for a point (spot) object
	Entity(Vector3, ENT_TYPE);

	//Entity constructor for a table object
	Entity(vector<Vector3>, Vector4, ENT_TYPE);

	//Entity default constructor
	Entity();

	//Destructor
	~Entity();

	//Get and set colour of an entity
	Vector4 getColour();
	void setColour(Vector4);

	//Get/Set the type of the entity object
	ENT_TYPE getObjectType();
	void setObjectType(ENT_TYPE t);

	//Get/Set the radius of the circle entities
	float getRadius();
	void updateRadius(float x);

	//Get/Set/Update the position of an entity
	Vector3& getPosition();
	void setPosition(Vector3 new_position); //This function sets the old position of the object to a new given position
	//This function takes a new given position, 
	//and adds it to the current position of 
	//the entity, the physical object and the render object
	void updatePosition(Vector3 x);			

	//Get position of the second point of a line entity
	Vector3& getPosition2();
	//Update the position of the second point of a line entity (i.e. add the new vector to the current one)
	void updatePosition2(Vector3 x);

	//Method to retrieve and set the original/assigned 
	//position of an entity
	Vector3& getOrigialPosition();
	void setOriginalPosition(Vector3 new_original);

	//Get/Set number of entities which are within the radius
	//of this entity
	int getEntitiesInRange();
	void updateEntitiesInRange(int x);

	//Get/Set render object of an entity
	RenderObject& getRenderObject();
	void setRenderObject(RenderObject rendNew);

	//Get/Set the physical representation of
	//an entity
	Physics& getPhysObject();
	void setPhysObject(Physics new_phys);

	//Checks the collision detection between balls (ball-ball collision detection)
	int inRange(Entity* e);

	//Checks the collision detection between balls and pockets (ball-pocket collision detection)
	int inPocket(Entity* e);

	//Checks the collision of a ball entity
	//with the D section of the table
	int inDSection(Entity* e);
	
	//Vector array to store all given positions of 
	//a table entity
	std::vector<Vector3> indecies;

	bool in_game = true;
private:
	RenderObject rend;
	ENT_TYPE objectType;
	Vector3 position;			//Current position of an entity
	Vector3 position2;			//The second Point of a line entity
	Vector3 originalPosition;	//The original position of an entity (once set, doesn't change through out the game)
	Vector4 colour;
	Physics phys_obj;
	float radius;
	int entitiesInRange = 0;
};
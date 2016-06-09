#include "Entity.h"
#include <cmath>

using namespace std;

//Entity contructor for HALF_CIRCLE objects
Entity::Entity(Vector3 v, float r, ENT_TYPE t){
	position.x = v.x;
	position.y = v.y;
	position.z = v.z;

	radius = r;

	entitiesInRange = 0;

	objectType = t;
}

//Entity contructor for SPOT objects
Entity::Entity(Vector3 v, ENT_TYPE t){
	position.x = v.x;
	position.y = v.y;
	position.z = v.z;

	objectType = t;
}

//Entity contructor for LINE/ARROW objects
Entity::Entity(Vector3 p1, Vector3 p2, Vector4 c, ENT_TYPE t){
	position.x = p1.x;
	position.y = p1.y;
	position.z = p1.z;

	position2.x = p2.x;
	position2.y = p2.y;
	position2.z = p2.z;

	colour = c;

	objectType = t;
}

//Entity contructor for BALL objects
Entity::Entity(Vector3 v, Vector4 c, float r, ENT_TYPE t){
	position.x = v.x;
	position.y = v.y;
	position.z = v.z;

	radius = r;

	entitiesInRange = 0;

	colour = c;

	objectType = t;
}

//Entity contructor for TABLE objects
Entity::Entity(std::vector<Vector3> v, Vector4 c, ENT_TYPE t){
	indecies = v;

	colour = c;

	objectType = t;
}

//Entity defualt contructor 
Entity::Entity(){
	position.x = 0;
	position.y = 0;
	position.z = 0;

	radius = 0;

	entitiesInRange = 0;
}

//Entity destructor
Entity::~Entity(){

}

RenderObject& Entity::getRenderObject(){
	return rend;
}

void Entity::setRenderObject(RenderObject rendNew){
	rend = rendNew;
}

Vector4 Entity::getColour(){
	return colour;
}

void Entity::setColour(Vector4 c){
	colour = c;
}

ENT_TYPE Entity::getObjectType(){
	return objectType;
}

void Entity::setObjectType(ENT_TYPE t){
	objectType = t;
}

float Entity::getRadius(){
	return radius;
}

void Entity::updateRadius(float x){
	radius = x;
}

int Entity::getEntitiesInRange(){
	return entitiesInRange;
}

void Entity::updateEntitiesInRange(int x){
	entitiesInRange = x;
}

Vector3& Entity::getPosition(){
	return position;
}

void Entity::setPosition(Vector3 v) {
	position = v;
}

void Entity::updatePosition(Vector3 v){
	position += v;
	this->getPhysObject().updatePhysPosition(v);
	this->getRenderObject().SetModelMatrix(this->getRenderObject().GetModelMatrix() * Matrix4::Translation(v));
}

Vector3& Entity::getPosition2(){
	return position2;
}

void Entity::updatePosition2(Vector3 v){
	position2.x = v.x;
	position2.y = v.y;
	position2.z = v.z;
}

Vector3& Entity::getOrigialPosition() {
	return originalPosition;
}

void Entity::setOriginalPosition(Vector3 v) {
	originalPosition = v;
}

Physics& Entity::getPhysObject() {
	return phys_obj;
}

void Entity::setPhysObject(Physics new_phys) {
	phys_obj = new_phys;
}

int Entity::inRange(Entity* e){
	float a = (position.x - e->position.x) * (position.x - e->position.x);
	float b = (position.y - e->position.y) * (position.y - e->position.y);
	float c = (position.z - e->position.z) * (position.z - e->position.z);

	float dist = a + b + c; //Calculat the distance between two points

	float sumAggro = (radius + e->radius) * (radius + e->radius); //Find the distance between radii

	if (sumAggro >= dist){ //If the distance between two radii is bigger OR euqals to the distance between the two points, then collision is occurring
		return 1;
	}
	else
		return 0;
}

//Same as inRange method 
int Entity::inPocket(Entity* e) {
	float a = (position.x - e->position.x) * (position.x - e->position.x);
	float b = (position.y - e->position.y) * (position.y - e->position.y);
	float c = (position.z - e->position.z) * (position.z - e->position.z);

	float distP = a + b + c;

	//The only difference is that here we have to divide the distance 
	//between the radii by 2 to ensure that the centre point of the 
	//ball falls into the radius of the pocket
	float distR = ((radius + e->radius) * (radius + e->radius)) * 0.5f;

	//If the distance between the two centre points of ball and a
	//pocket is less than or equal to
	if (distP <= distR) {
		return 1;
	}
	else return 0;
}

//Same as the inRange method
int Entity::inDSection(Entity* e) {
	float a = (position.x - e->position.x) * (position.x - e->position.x);
	float b = (position.y - e->position.y) * (position.y - e->position.y);
	float c = (position.z - e->position.z) * (position.z - e->position.z);

	float distP = a + b + c;

	//Except here we only take into account the size of the radius of 
	// the D section of the table. 
	float distR = (e->radius * e->radius);

	//If the center point of the ball 
	//is within the D zone then the 
	//return 1 (true)
	if (distP <= distR) {
		return 1;
	}
	else return 0;
}
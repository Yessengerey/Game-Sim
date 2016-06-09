#include "Physics.h"
#include <iostream>
#include <cmath>

using namespace std;

Physics::Physics() {

}

Physics::Physics(PX_TYPE px){
	mass = 1000.0f;
	f_force = null_dummy;
	v_velocity = null_dummy;
	phys_type = px;
}

Physics::Physics(Vector3 p, float m, PX_TYPE px){
	p_position = p;
	mass = m;
	phys_type = px;
	f_force = null_dummy;
	a_acceleration = null_dummy;
	u_initialVelocity = null_dummy;
	v_velocity = null_dummy;
}

Physics::Physics(Vector3 p, PX_TYPE px) {
	p_position = p;
	mass = 1000.0f;
	phys_type = px;
	f_force = null_dummy;
}

Vector3 Physics::getFinalVelocity(float t){
	return v_finalVelocity = this->u_initialVelocity + (this->a_acceleration*t);
}

void Physics::setFinalVelocity(Vector3 v){
	v_finalVelocity = v;
}

Vector3 Physics::getVelocity(){
	return v_velocity;
}

void Physics::setVelocity(Vector3 v){
	v_velocity.x = v.x;
	v_velocity.y = v.y;
	v_velocity.z = v.z;
}

float Physics::getMass() {
	return mass;
}

void Physics::setMass(float m) {
	mass = m;
}

Vector3& Physics::getPhysPosition() {
	return p_position;
}

void Physics::setPhysPosition(Vector3 p) {
	p_position = p;
}

void Physics::updatePhysPosition(Vector3 v) {
	p_position.x += v.x;
	p_position.y += v.y;
	p_position.z += v.z;
}

PX_TYPE Physics::getPhysType() {
	return phys_type;
}

void Physics::setPhysType(PX_TYPE px) {
	phys_type = px;
}

Vector3 Physics::calcDisplacement(float t){
	this->s_displacement = (this->u_initialVelocity*t) + ((this->a_acceleration*(t*t))*0.5);
	return s_displacement;
}

Vector3 Physics::getDisplacement() {
	return s_displacement;
}

void Physics::setDisplacement(Vector3 new_d) {
	this->s_displacement = new_d;
}

Vector3 Physics::getForce() {
	return f_force;
}

void Physics::applyForce(Vector3 new_f) {
	f_force = new_f;
	this->updatePhysPosition(new_f);
}

void Physics::calcForce() {
	this->f_force = this->a_acceleration * this->mass;
}

Vector3 Physics::getInitialVelocity() {
	return u_initialVelocity;
}

void Physics::setInitialVelocity(Vector3 u) {
	u_initialVelocity = u;
}

Vector3 Physics::calcAcceleration(float t) {
	Vector3 x = this->v_finalVelocity - this->u_initialVelocity;
	this->a_acceleration = x / t;
	return a_acceleration;
}

Vector3 Physics::getAcceleration() {
	return a_acceleration;
}

void Physics::setAcceleration(Vector3 a) {
	a_acceleration = a;
}

void Physics::toRest(Vector3 pos) {
	applyForce(pos);
}



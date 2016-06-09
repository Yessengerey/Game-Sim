#pragma once
#include "Renderer.h"
#include <iostream>
#include <cmath>

enum PX_TYPE{
	PX_BALL,
	PX_TABLE,
	PX_POCKET,
};

class Physics{
public:
	
	Physics();
	Physics(PX_TYPE);
	Physics(Vector3 p_position, float mass, PX_TYPE);
	Physics(Vector3 p_position, PX_TYPE);

	Vector3 calcDisplacement(float time);
	Vector3 getDisplacement();
	void setDisplacement(Vector3 new_d);
	
	Vector3 getFinalVelocity(float time);
	void setFinalVelocity(Vector3 new_final_velocity);

	Vector3 getVelocity();
	void setVelocity(Vector3 new_velocity);

	float getMass();
	void setMass(float new_mass);

	Vector3& getPhysPosition();
	void setPhysPosition(Vector3 new_position);
	void updatePhysPosition(Vector3 move_by);

	PX_TYPE getPhysType();
	void setPhysType(PX_TYPE);

	Vector3 getForce();
	void applyForce(Vector3 new_force);
	void calcForce();

	Vector3 getInitialVelocity();
	void setInitialVelocity(Vector3 new_u);

	Vector3 calcAcceleration(float time);
	Vector3 getAcceleration();
	void setAcceleration(Vector3 new_acceleration);

	void toRest(Vector3 pos);



	Vector3 null_dummy = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 acceleration = Vector3(0.001f, 0.0f, 0.0f);
	float friction = 0.9995f;
	float radius = 0.025f;
	float t_time;
private:
	Vector3 v_velocity;
	Vector3 v_finalVelocity;
	Vector3 s_displacement;
	Vector3 p_position;
	Vector3 f_force;
	Vector3 a_acceleration;
	Vector3 u_initialVelocity;
	PX_TYPE phys_type;
	float mass;
};
#pragma once
#include "Renderer.h"
#include "RenderObject.h"
#include "Entity.h"
#include "Physics.h"
#include "GameInit.h"
class GameLogic{
public:
	GameLogic();

	//The stages of the game
	void waitUserInput(GameInit* gI);
	
	void updatePositions(GameInit* gI, float msec);
	//end of stages

	//Subfunctions of the stages that control all the movement
	void adjustPower(GameInit* gI);

	void confirmPower(GameInit* gI);
	
	void updateObjects(GameInit* gI, float msec);

	void updateCollision(GameInit* gI);

	void applyIntegration(GameInit* gI, int idx, float msec);

	void toRest(GameInit* gI, int i);

	void collisionResponse(Entity* gI1, Entity* gI2);

	void circleSideCollision(Entity* e);
	
	void ballInPocket(GameInit* gI, int i);

	void chooseWBAtStart(GameInit* gI);

	//void chooseWBContinue(GameInit* gI);

	void confirmWBPosition(GameInit* gI);

	void chooseWBDirection(GameInit* gI);
	//end of subfunctions

	bool allAtRest(GameInit* gI);

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

	Vector3 confirmed_pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 direction_vec;
	Vector3 null_vector = Vector3(0.0f, 0.0f, 0.0f);
	float power_percentage = 0.0f;
	int k = 0;
	bool firstHit = true;
	bool confirmed_power = false;
	bool confirmed_position = false;
	bool ball_stopped = false;
	bool choose_direction = false;
	bool choose_ball_pos = false;
	bool game_start = true;
	float pow_conf = 0.0f;
	bool continue_game = false;

	float direction_x = 0.0f;
	float direction_y = 1.0f;
	float direction_z = 0.0f;


	float speed = 0.0f;
	Vector3 acceleration = Vector3(0.001f, 0.001f, 0.0f);
	float max_speed = 5.0f;
	Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f);
	float friction = 0.9996f;
	Vector4 matrix_column;
	Matrix4 mode_mat;

	vector<Entity*> balls_in_game;
};
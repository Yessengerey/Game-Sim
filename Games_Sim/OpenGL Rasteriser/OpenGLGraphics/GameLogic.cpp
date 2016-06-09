#include "GameLogic.h"

GameLogic::GameLogic() {
}

void GameLogic::waitUserInput(GameInit* gI) {

	//start of the game
	if (firstHit == true && choose_ball_pos == false) {
		chooseWBAtStart(gI);
		confirmWBPosition(gI);
		chooseWBDirection(gI);
	}
	if (choose_ball_pos == true && choose_direction == false) {
		chooseWBDirection(gI);
	}

	//game continues...
	if (continue_game == true && choose_direction == false) {
		chooseWBDirection(gI);
	}

	if (choose_ball_pos == true && choose_direction == true) {
		adjustPower(gI);
		confirmPower(gI);
	}
}

void GameLogic::chooseWBAtStart(GameInit* gI) {
	gI->entities[22]->getRenderObject().SetModelMatrix(gI->entities[22]->getRenderObject().GetModelMatrix() * Matrix4::Scale(null_vector));
	if (Keyboard::KeyDown(KEY_UP)) {
		if (gI->entities[0]->inDSection(gI->entities[30]) == 1 && gI->entities[0]->getPosition().y < 0.169f) {

			gI->entities[0]->updatePosition(Vector3(0.0f, 0.0001f, 0.0f));
			gI->entities[22]->updatePosition(Vector3(0.0f, 0.0001f, 0.0f));
		}
	}
	if (Keyboard::KeyDown(KEY_DOWN)) {
		if (gI->entities[0]->inDSection(gI->entities[30]) == 1 && gI->entities[0]->getPosition().y > -0.169f) {
			gI->entities[0]->updatePosition(Vector3(0.0f, -0.0001f, 0.0f));
			gI->entities[22]->updatePosition(Vector3(0.0f, -0.0001f, 0.0f));
		}
	}
	if (Keyboard::KeyDown(KEY_RIGHT)) {
		if (gI->entities[0]->inDSection(gI->entities[30]) == 1) {
			gI->entities[0]->updatePosition(Vector3(0.0001f, 0.0f, 0.0f));
			gI->entities[22]->updatePosition(Vector3(0.0001f, 0.0f, 0.0f));
		}
		else {
			gI->entities[0]->setPosition(Vector3(gI->entities[0]->getPosition().x - 0.0006f, gI->entities[0]->getPosition().y, gI->entities[0]->getPosition().z));
			gI->entities[0]->getPhysObject().setPhysPosition(Vector3(gI->entities[0]->getPosition().x - 0.0006f, gI->entities[0]->getPosition().y, gI->entities[0]->getPosition().z));
			gI->entities[0]->getRenderObject().SetModelMatrix(Matrix4::Translation(Vector3(gI->entities[0]->getPosition().x - 0.0006f, gI->entities[0]->getPosition().y, gI->entities[0]->getPosition().z)));

			gI->entities[22]->setPosition(Vector3(gI->entities[22]->getPosition().x - 0.0006f, gI->entities[22]->getPosition().y, gI->entities[22]->getPosition().z));
			gI->entities[22]->getRenderObject().SetModelMatrix(Matrix4::Translation(Vector3(gI->entities[22]->getPosition().x - 0.0006f, gI->entities[22]->getPosition().y, gI->entities[22]->getPosition().z)));
		}

	}
	if (Keyboard::KeyDown(KEY_LEFT)) {
		if (gI->entities[0]->getPosition().x >= 0.6f) {
			gI->entities[0]->updatePosition(Vector3(-0.0001f, 0.0f, 0.0f));
			gI->entities[22]->updatePosition(Vector3(-0.0001f, 0.0f, 0.0f));
		}

	}
}

void GameLogic::confirmWBPosition(GameInit* gI) {
	if (Keyboard::KeyDown(KEY_E)) {
		int n = 0;
		bool no_collisions = false;
		for (int i = 1; i < 22; i++) {
			if (gI->entities[0]->inRange(gI->entities[i]) != 1) {
				n++;
				if (n == 21) {
					no_collisions = true;
				}
				else no_collisions = false;
			}
			if (gI->entities[0]->inRange(gI->entities[i]) == 1) {
				n = 0;
				no_collisions = false;
			}
		}
		if (no_collisions == true) {
			gI->entities[22]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[0]->getPosition()));
			firstHit = false;
			choose_ball_pos = true;
		}
	}
}

void GameLogic::chooseWBDirection(GameInit* gI) {
	if (Keyboard::KeyDown(KEY_RIGHT)) {
		gI->entities[22]->getRenderObject().SetModelMatrix(gI->entities[22]->getRenderObject().GetModelMatrix() * Matrix4::Rotation(-0.02f, Vector3(0, 0, 1)));
		mode_mat = gI->entities[22]->getRenderObject().GetModelMatrix();
		direction_x = gI->entities[22]->getRenderObject().GetModelMatrix().GetColumn(1).x;
		direction_y = gI->entities[22]->getRenderObject().GetModelMatrix().GetColumn(1).y;
	}
	if (Keyboard::KeyDown(KEY_LEFT)) {
		gI->entities[22]->getRenderObject().SetModelMatrix(gI->entities[22]->getRenderObject().GetModelMatrix() * Matrix4::Rotation(0.02f, Vector3(0, 0, 1)));
		mode_mat = gI->entities[22]->getRenderObject().GetModelMatrix();
		direction_x = gI->entities[22]->getRenderObject().GetModelMatrix().GetColumn(1).x;
		direction_y = gI->entities[22]->getRenderObject().GetModelMatrix().GetColumn(1).y;

	}
	if (Keyboard::KeyDown(KEY_D)) {
		choose_direction = true;
		choose_ball_pos = true;
	}
}

//Once the position of the white ball was confirmed, user has to adjust the power of the acceleration that he would
//like to apply onto the white ball; press SPACE to do that
void GameLogic::adjustPower(GameInit* gI) {

	//Find and save the power bar slider 
	//to perform further actions

	Entity* temp;
	for (int i = 0; i < gI->entities.size(); ++i) {
		if (gI->entities[i]->getColour() == Vector4(0.753f, 0.753f, 0.753f, 1.0f)) {
			temp = gI->entities[i];
		}
	}
	if (confirmed_power == false) {
		if (Keyboard::KeyDown(KEY_SPACE)) {
			if (power_percentage < 100.0f) {
				temp->updatePosition(Vector3(0.05f, 0.0f, 0.0f));
				gI->entities[22]->getRenderObject().SetModelMatrix(gI->entities[22]->getRenderObject().GetModelMatrix() * Matrix4::Scale(Vector3(1.0003f, 1.0003f, 0)));

				power_percentage += 0.0336f;
			}
		}
		//If the user decides to change the power,
		//press Z to bring back the slider to the/
		//beginning of the power bar
		if (Keyboard::KeyDown(KEY_Z)) {
			temp->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
			temp->getPhysObject().setPhysPosition(Vector3(-1.5f, -1.7f, -3.0f));
			temp->getRenderObject().SetModelMatrix(Matrix4::Translation(temp->getPosition()) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));

			gI->entities[22]->getRenderObject().SetModelMatrix(mode_mat);
			power_percentage = 0;
		}
	}
}

//To confirm the position of the power slider and 
//the strength of the shot, press P
void GameLogic::confirmPower(GameInit* gI) {
	if (Keyboard::KeyDown(KEY_P) && confirmed_power == false) {

		speed = (power_percentage / 100) * max_speed;

		velocity = Vector3(direction_x, direction_y, 0.0f) * speed;

		gI->entities[0]->getPhysObject().setVelocity(velocity);

		gI->entities[22]->getRenderObject().SetModelMatrix(gI->entities[22]->getRenderObject().GetModelMatrix() * Matrix4::Scale(null_vector));

		confirmed_power = true;
	}
}

// *** SECOND STAGE ***
//Second stage of the game
void GameLogic::updateObjects(GameInit* gI, float fixed) {
	if (confirmed_power == true) {
		updatePositions(gI, fixed);
		updateCollision(gI);
	}
}

void GameLogic::updatePositions(GameInit* gI, float fixed) {
	for (int i = 0; i < 22; i++) {
		//if (gI->entities[i]->getObjectType() == WHITE_BALL || gI->entities[i]->getObjectType() == BALL || gI->entities[i]->getObjectType() == RED_BALL) {
		if (gI->entities[i]->getPhysObject().getVelocity() != null_vector && gI->entities[i]->in_game == true) {
			applyIntegration(gI, i, fixed);
			circleSideCollision(gI->entities[i]);
			ballInPocket(gI, i);
		}
		//}
	}
}

//Semi-implicit integration 
void GameLogic::applyIntegration(GameInit* gI, int i, float fixed) {
	//Update the velocity
	gI->entities[i]->getPhysObject().setVelocity(gI->entities[i]->getPhysObject().getVelocity() - (acceleration * fixed));

	//Apply the damping factor of friction to the velocity
	gI->entities[i]->getPhysObject().setVelocity(gI->entities[i]->getPhysObject().getVelocity() * friction);

	//Update the displacement for both physics object and entity
	gI->entities[i]->setPosition(gI->entities[i]->getPosition() + (gI->entities[i]->getPhysObject().getVelocity() * fixed));
	gI->entities[i]->getPhysObject().setPhysPosition(gI->entities[i]->getPhysObject().getPhysPosition() + (gI->entities[i]->getPhysObject().getVelocity() * fixed));

	//Translate the render object on the screen given the new displacement using model matrix
	gI->entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[i]->getPosition()));

	//If the velocity of an object is very small, make it zero
	if ((gI->entities[i]->getPhysObject().getVelocity().x * gI->entities[i]->getPhysObject().getVelocity().x) + (gI->entities[i]->getPhysObject().getVelocity().y * gI->entities[i]->getPhysObject().getVelocity().y) < 0.0125f) {
		toRest(gI, i);
	}
}

//Function that contantly updates the velocities of objects based on their collision between each other
void GameLogic::updateCollision(GameInit* gI) {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			if (i != j && (gI->entities[i]->inRange(gI->entities[j]) == 1) && gI->entities[i]->in_game == true && gI->entities[j]->in_game == true) {
				collisionResponse(gI->entities[i], gI->entities[j]);
			}
		}
	}
}

void GameLogic::collisionResponse(Entity* e1, Entity* e2) {
	//"Stickiness" resolution part 
	//This part deals with the issues of having objects getting stuck inside each other
	Vector3 obj1 = e1->getPosition();
	Vector3 obj2 = e2->getPosition();

	float rad1 = e1->getRadius();
	float rad2 = e2->getRadius();

	Vector3 p = obj2 - obj1;

	float l = p.Length();

	p.Normalise();

	float d = ((rad1 + rad2) - l) + 0.01f;

	const float per = 0.2;

	p = p * d * per;

	e1->getPhysObject().setPhysPosition(e1->getPhysObject().getPhysPosition() - p / 2.0f);
	e1->setPosition(e1->getPosition() - p / 2.0f);

	e2->getPhysObject().setPhysPosition(e2->getPhysObject().getPhysPosition() + p / 2.0f);
	e2->setPosition(e2->getPosition() + p / 2.0f);

	e1->getRenderObject().SetModelMatrix(Matrix4::Translation(e1->getPosition()));
	e2->getRenderObject().SetModelMatrix(Matrix4::Translation(e2->getPosition()));

	//Stickiness resolution part ends

	//Part that updates velocities of the objects
	float over_mass;
	float deriv_of_x;
	float a;
	float x_difference;
	float y_difference;
	float velocity_x_difference;
	float velocity_y_difference;

	over_mass = e2->getPhysObject().getMass() / e1->getPhysObject().getMass();

	x_difference = e2->getPhysObject().getPhysPosition().x - e1->getPhysObject().getPhysPosition().x;

	y_difference = e2->getPhysObject().getPhysPosition().y - e1->getPhysObject().getPhysPosition().y;

	velocity_x_difference = e2->getPhysObject().getVelocity().x - e1->getPhysObject().getVelocity().x;

	velocity_y_difference = e2->getPhysObject().getVelocity().y - e1->getPhysObject().getVelocity().y;

	a = y_difference / x_difference;

	deriv_of_x = -2 * (velocity_x_difference + (a * velocity_y_difference)) / ((1 + a*a) * (1 + over_mass));

	e2->getPhysObject().setVelocity(Vector3(e2->getPhysObject().getVelocity().x + deriv_of_x, e2->getPhysObject().getVelocity().y + a * deriv_of_x, e2->getPhysObject().getVelocity().z));
	e1->getPhysObject().setVelocity(Vector3(e1->getPhysObject().getVelocity().x - over_mass * deriv_of_x, e1->getPhysObject().getVelocity().y - a * over_mass * deriv_of_x, e1->getPhysObject().getVelocity().z));

}

void GameLogic::circleSideCollision(Entity* e) {
	float damping = 0.8f;
	if (e->getPosition().x >= 1.0f - (e->getRadius()) && e->getPhysObject().getVelocity().x > 0.0f) {
		e->getPhysObject().setVelocity(Vector3((e->getPhysObject().getVelocity().x * -1.0f * damping), e->getPhysObject().getVelocity().y, e->getPhysObject().getVelocity().z));
	}
	if (e->getPosition().x <= -1.0 + e->getRadius() && e->getPhysObject().getVelocity().x < 0.0f) {
		e->getPhysObject().setVelocity(Vector3((e->getPhysObject().getVelocity().x * -1.0f * damping), e->getPhysObject().getVelocity().y, e->getPhysObject().getVelocity().z));
	}
	if (e->getPosition().y >= 0.5f - (e->getRadius()) && e->getPhysObject().getVelocity().y > 0.0f) {
		e->getPhysObject().setVelocity(Vector3((e->getPhysObject().getVelocity().x), e->getPhysObject().getVelocity().y * -1.0f * damping, e->getPhysObject().getVelocity().z));
	}
	if (e->getPosition().y <= -0.5f + e->getRadius() && e->getPhysObject().getVelocity().y < 0.0f) {
		e->getPhysObject().setVelocity(Vector3((e->getPhysObject().getVelocity().x), e->getPhysObject().getVelocity().y * -1.0f * damping, e->getPhysObject().getVelocity().z));
	}

}

void GameLogic::ballInPocket(GameInit* gI, int i) {
	for (int j = 0; j < gI->entities.size(); j++) {
		if (gI->entities[j]->getObjectType() == POCKET) {
			if (gI->entities[i]->inPocket(gI->entities[j]) == 1 && gI->entities[i]->getObjectType() == WHITE_BALL) {
				gI->entities[i]->setPosition(whiteBallPosition);
				gI->entities[i]->getPhysObject().setPhysPosition(whiteBallPosition);
				gI->entities[i]->getPhysObject().setVelocity(null_vector);
				gI->entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(whiteBallPosition));
				bool aar = allAtRest(gI);
				if (aar == true) {
					Entity* temp;
					for (int i = 0; i < gI->entities.size(); ++i) {
						if (gI->entities[i]->getColour() == Vector4(0.753f, 0.753f, 0.753f, 1.0f)) {
							temp = gI->entities[i];
						}
					}

					temp->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getPhysObject().setPhysPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getRenderObject().SetModelMatrix(Matrix4::Translation(temp->getPosition()) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));
					power_percentage = 0;

					choose_direction = false;
					continue_game = true;
					confirmed_power = false;
					choose_ball_pos = false;
					firstHit = true;
				}
			}
			if (gI->entities[i]->inPocket(gI->entities[j]) == 1 && gI->entities[i]->getObjectType() == RED_BALL) {
				gI->entities[i]->getPhysObject().setVelocity(null_vector);
				gI->entities[i]->getPhysObject().setPhysPosition(null_vector);
				gI->entities[i]->setPosition(null_vector);


				gI->entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(Vector3(gI->entities[j]->getPosition().x, gI->entities[j]->getPosition().y, -5.0f)) * Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
				gI->entities[i]->in_game = false;
				bool aar = allAtRest(gI);
				if (aar == true) {
					Entity* temp;
					for (int i = 0; i < gI->entities.size(); ++i) {
						if (gI->entities[i]->getColour() == Vector4(0.753f, 0.753f, 0.753f, 1.0f)) {
							temp = gI->entities[i];
						}
					}

					temp->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getPhysObject().setPhysPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getRenderObject().SetModelMatrix(Matrix4::Translation(temp->getPosition()) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));
					power_percentage = 0;

					choose_direction = false;
					confirmed_power = false;
					choose_ball_pos = true;
					continue_game = true;
					gI->entities[22]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[0]->getPosition()));
				}
			}
			if (gI->entities[i]->inPocket(gI->entities[j]) == 1 && gI->entities[i]->getObjectType() == BALL)  {
				gI->entities[i]->getPhysObject().setVelocity(null_vector);
				gI->entities[i]->getPhysObject().setPhysPosition(gI->entities[i]->getOrigialPosition());
				gI->entities[i]->setPosition(gI->entities[i]->getOrigialPosition());


				gI->entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[i]->getOrigialPosition()));
				gI->entities[i]->in_game = true;
				bool aar = allAtRest(gI);
				if (aar == true) {
					Entity* temp;
					for (int i = 0; i < gI->entities.size(); ++i) {
						if (gI->entities[i]->getColour() == Vector4(0.753f, 0.753f, 0.753f, 1.0f)) {
							temp = gI->entities[i];
						}
					}

					temp->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getPhysObject().setPhysPosition(Vector3(-1.5f, -1.7f, -3.0f));
					temp->getRenderObject().SetModelMatrix(Matrix4::Translation(temp->getPosition()) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));
					power_percentage = 0;

					choose_direction = false;
					confirmed_power = false;
					choose_ball_pos = true;
					continue_game = true;
					gI->entities[22]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[0]->getPosition()));
				}
			}
			/*
			else {
				gI->entities[i]->getPhysObject().setVelocity(null_vector);
				gI->entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[j]->getPosition()) * Matrix4::Scale(Vector3(0.0f, 0.0f, 0.0f)));
			}*/
		}
	}
}

//Puts all
void GameLogic::toRest(GameInit* gI, int i) {
	gI->entities[i]->getPhysObject().setVelocity(Vector3(0.0f, 0.0f, 0.0f));
	int n = 0;
	bool no_collisions = false;
	for (int i = 1; i < 22; i++) {
		if (gI->entities[i]->getPhysObject().getVelocity() == null_vector) {
			n++;
			if (n == 21) {
				no_collisions = true;
			}
			else no_collisions = false;
		}
		else {
			n = 0;
			no_collisions = false;
		}
	}
	if (no_collisions == true) {
		gI->entities[22]->getRenderObject().SetModelMatrix(Matrix4::Translation(gI->entities[0]->getPosition()));
		Entity* temp;
		for (int i = 0; i < gI->entities.size(); ++i) {
			if (gI->entities[i]->getColour() == Vector4(0.753f, 0.753f, 0.753f, 1.0f)) {
				temp = gI->entities[i];
			}
		}
		temp->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
		temp->getPhysObject().setPhysPosition(Vector3(-1.5f, -1.7f, -3.0f));
		temp->getRenderObject().SetModelMatrix(Matrix4::Translation(temp->getPosition()) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));
		power_percentage = 0;


		choose_direction = false;
		continue_game = true;
		confirmed_power = false;
		ball_stopped = true;
	}
}

bool GameLogic::allAtRest(GameInit* gI) {
	int n = 0;
	bool no_collisions = false;
	for (int i = 1; i < 22; i++) {
		if (gI->entities[i]->getPhysObject().getVelocity() == null_vector) {
			n++;
			if (n == 21) {
				no_collisions = true;
			}
			else no_collisions = false;
		}
		else {
			n = 0;
			no_collisions = false;
		}
	}
	return no_collisions;
}


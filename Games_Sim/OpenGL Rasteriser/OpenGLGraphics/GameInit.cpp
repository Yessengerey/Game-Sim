#include "GameInit.h"


GameInit::GameInit(Renderer& r) {
	Shader* s = new Shader("basicvert.glsl", "basicFrag.glsl");
	Shader* os = new Shader("OutlineVert.glsl", "OutlineFrag.glsl");
	populateEntities();
	createMeshes(s, os);
	addToScreen(r);
}

void GameInit::populateEntities() {
	//vector of Indecies (x, y, z) for the 
	//triangle strip that is used to generate
	//the snooker table's base (the brown and 
	//green parts).
	//Indecies are created in a way to have the centre
	//of the object in the middle when it is rendered
	tableIndecies.push_back(Vector3(-1.0f, -0.5f, -3.0f));
	tableIndecies.push_back(Vector3(-1.0f, 0.5f, -3.0f));
	tableIndecies.push_back(Vector3(0.0f, -0.5f, -3.0f));
	tableIndecies.push_back(Vector3(0.0f, 0.5f, -3.0f));
	tableIndecies.push_back(Vector3(1.0f, -0.5f, -3.0f));
	tableIndecies.push_back(Vector3(1.0f, 0.5f, -3.0f));

	//Populate the vector of indecies for pockets
	//Vector of Indicies for the pockets
	pocketIndecies.push_back(Vector3(-1.0f, -0.5f, -3.0f));	//bottom left pocket
	pocketIndecies.push_back(Vector3(-1.0f, 0.5f, -3.0f));	//top-left pocket
	pocketIndecies.push_back(Vector3(0.0f, -0.5f, -3.0f));	//side pocket bottom
	pocketIndecies.push_back(Vector3(0.0f, 0.5f, -3.0f));	//side pocket top
	pocketIndecies.push_back(Vector3(1.0f, -0.5f, -3.0f));	//bottom-right pocket
	pocketIndecies.push_back(Vector3(1.0f, 0.5f, -3.0f));	//top-right pocket

	//Populate coloured ball positions vector
	//Vector of all coloured balls' positions, including the white ball
	colouredBallPos.push_back(whiteBallPosition);
	colouredBallPos.push_back(greenBallPosition);
	colouredBallPos.push_back(brownBallPosition);
	colouredBallPos.push_back(yellowBallPosition);
	colouredBallPos.push_back(blueBallPosition);
	colouredBallPos.push_back(pinkBallPosition);
	colouredBallPos.push_back(blackBallPosition);

	//Calculate the exact positions of each of the red
	//ball. Positions are calculated based on the previous
	//red ball.
	//Then add all the calcualted positions into the appropriate
	//vector
	int l = 0;
	float yPosN = -0.025f;
	for (int i = 0; i < 5; ++i) {
		float distX = -0.025f * 2;
		float distY = 0.026f * 2;
		yPosN += 0.025f;
		for (int j = 0; j <= i; ++j) {
			colouredBallPos.push_back(Vector3((-0.5f + (2 * -0.025f)) + distX *i, (distY * j) - (yPosN), -3.0f));
			l++;
		}
	}

	//Start creating entities and adding them to the entities vector.
	//First the ball objects are created, then the arrow, then pockets, 
	//then table markings, power bars and then the table parts.
	//I created it this way to know exactly where certain things are located.
	//For example I always know that the white ball is an object with an index
	//of 0 everywhere, or that the arrows comes right after the balls, making it
	//an object 12. This is done to make accessing these objects easier and
	//saving up some computational time
	entities.push_back(new Entity(init_pos, WHITE, ballRadius, WHITE_BALL));
	entities.push_back(new Entity(init_pos, GREEN, ballRadius, BALL));
	entities.push_back(new Entity(init_pos, BROWN, ballRadius, BALL));
	entities.push_back(new Entity(init_pos, YELLOW, ballRadius, BALL));
	entities.push_back(new Entity(init_pos, BLUE, ballRadius, BALL));
	entities.push_back(new Entity(init_pos, PINK, ballRadius, BALL));
	entities.push_back(new Entity(init_pos, BLACK, ballRadius, BALL));

	for (int i = 0; i < 15; ++i) {
		entities.push_back(new Entity(init_pos, RED, ballRadius, RED_BALL));
	}

	entities.push_back(new Entity(init_pos, (init_pos + Vector3(0.0f, 0.5f, 0.0f)), WHITE, ARROW));

	for (int i = 0; i < 6; ++i) {
		entities.push_back(new Entity(init_pos, BLACK, pocketRadius, POCKET));
	}

	entities.push_back(new Entity(Vector3(0.6f, 0.5f, -3.0f), Vector3(0.6f, -0.5f, -3.0f), WHITE, LINE));
	entities.push_back(new Entity(Vector3(0.6f, 0.0f, -3.0f), 0.17f, HALF_CIRCLE));
	entities.push_back(new Entity(Vector3(0.6f, 0.0f, -3.0f), SPOT));
	entities.push_back(new Entity(Vector3(0.0f, 0.0f, -3.0f), SPOT));
	entities.push_back(new Entity(Vector3(-0.5f, 0.0f, -3.0f), SPOT));
	entities.push_back(new Entity(Vector3(-0.85f, 0.0f, -3.0f), SPOT));
	entities.push_back(new Entity(tableIndecies, GREY, POW_BAR));
	entities.push_back(new Entity(tableIndecies, TABLE_GREEN, POW_BAR));
	entities.push_back(new Entity(tableIndecies, TABLE_GREEN, TABLE));
	entities.push_back(new Entity(tableIndecies, TABLE_BROWN, TABLE));


}

//All objects have types, when a certain type is located in the entities vector,
//appropriate actions are taken
//The process for each entity object is very similar, except that sometimes some tings 
//are not assigned for certain entities since they don't need them
void GameInit::createMeshes(Shader* s, Shader* os) {

	for (int i = 0; i < entities.size(); ++i) {
		if (entities[i]->getObjectType() == WHITE_BALL || entities[i]->getObjectType() == BALL || entities[i]->getObjectType() == RED_BALL) {
			//Create the physical representation for this object
			entities[i]->setPhysObject(Physics(entities[i]->getPosition(), 1.0f, PX_BALL));
			//create a mesh for this object
			arrayOfMeshes[i] = Mesh::GenerateCircle(entities[i]->getPosition(), entities[i]->getColour(), entities[i]->getRadius());
			//Create a render object for this object
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], os));
			
			//The thing is that all objects are initially created at (0,0,0) and then reallocated into their own intended positions.
			//This is done to ensure that the positions of the entities and their physics is the same as the positions of their
			//respective rendered objects on the screen
			
			//So first translate the render object to the intended position on the screen
			entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(colouredBallPos[i]) * Matrix4::Scale(Vector3(1, 1, 1)));
			//Then set the position of the entity object
			entities[i]->setPosition(colouredBallPos[i]);
			//Every entity however has an original (intended) position variable within them
			//this is so that when balls are potted into the pockets, I could easily access the 
			//intended positions of each object individually and set the current positions of the 
			//objects to the intended ones.
			entities[i]->setOriginalPosition(colouredBallPos[i]);
			//Set the physics of each entity to the intended position on the screen
			entities[i]->getPhysObject().setPhysPosition(colouredBallPos[i]);
		}
		if (entities[i]->getObjectType() == ARROW) {
			arrayOfMeshes[i] = Mesh::GenerateArrow(entities[i]->getPosition(), entities[i]->getPosition2());
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
			entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(whiteBallPosition) * Matrix4::Scale(Vector3(1, 1, 1)));
			entities[i]->setPosition(whiteBallPosition);
		}
		if (entities[i]->getObjectType() == POCKET) {
			for (int j = k; j < pocketIndecies.size(); j++) {
				entities[i]->setPhysObject(Physics(entities[i]->getPosition(), 1.0f, PX_POCKET));
				arrayOfMeshes[i] = Mesh::GenerateCircle(entities[i]->getPosition(), entities[i]->getColour(), entities[i]->getRadius());
				entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
				entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(pocketIndecies[k]) * Matrix4::Scale(Vector3(1, 1, 1)));
				entities[i]->setPosition(pocketIndecies[k]);
				entities[i]->getPhysObject().setPhysPosition(pocketIndecies[k]);
				break;
			}
			k++;
		}
		if (entities[i]->getObjectType() == LINE) {
			arrayOfMeshes[i] = Mesh::GenerateLine(entities[i]->getPosition(), entities[i]->getPosition2());
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
		}
		if (entities[i]->getObjectType() == HALF_CIRCLE) {
			arrayOfMeshes[i] = Mesh::GenerateHalfCircle(entities[i]->getPosition(), entities[i]->getColour(), entities[i]->getRadius());
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
		}
		if (entities[i]->getObjectType() == SPOT) {
			arrayOfMeshes[i] = Mesh::GeneratePoints(entities[i]->getPosition());
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
		}
		if (entities[i]->getObjectType() == TABLE) {
			entities[i]->setPhysObject(Physics(entities[i]->getPosition(), PX_TABLE));
			arrayOfMeshes[i] = Mesh::GenerateTriangleStrip(entities[i]->getColour(), entities[i]->getColour(), entities[i]->getColour(), tableIndecies);
			entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
			if (entities[i]->getColour() == TABLE_BROWN)
				entities[i]->getRenderObject().SetModelMatrix(Matrix4::Scale(Vector3(1.05f, 1.1f, 1.0f)));
		}
		if (entities[i]->getObjectType() == POW_BAR) {
			if (entities[i]->getColour() == TABLE_GREEN) {
				entities[i]->setPosition(Vector3(0.0f, -1.7f, -3.0f));
				entities[i]->setPhysObject(Physics(entities[i]->getPosition(), PX_TABLE));
				entities[i]->getPhysObject().setPhysPosition(entities[i]->getPosition());
				arrayOfMeshes[i] = Mesh::GenerateTriangleStrip(GREEN, YELLOW, RED, tableIndecies);
				entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
				entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(Vector3(0.0f, -1.7f, -3.0f)) * Matrix4::Scale(Vector3(1.5f, 0.2f, 1.0f)));
			}
			if (entities[i]->getColour() == GREY) {
				entities[i]->setPhysObject(Physics(entities[i]->getPosition(), PX_TABLE));
				arrayOfMeshes[i] = Mesh::GenerateTriangleStrip(entities[i]->getColour(), entities[i]->getColour(), entities[i]->getColour(), tableIndecies);
				entities[i]->setRenderObject(RenderObject(arrayOfMeshes[i], s));
				entities[i]->getRenderObject().SetModelMatrix(Matrix4::Translation(Vector3(-1.5f, -1.7f, -3.0f)) * Matrix4::Scale(Vector3(0.02f, 0.3f, 1.0f)));
				entities[i]->setPosition(Vector3(-1.5f, -1.7f, -3.0f));
				entities[i]->getPhysObject().setPhysPosition(entities[i]->getPosition());
			}
		}
	}
	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
}

//Add all entities' render objects to the screen space
void GameInit::addToScreen(Renderer& r) {
	for (int i = 0; i < entities.size(); ++i) {
		r.AddRenderObject(entities[i]->getRenderObject());
	}
}


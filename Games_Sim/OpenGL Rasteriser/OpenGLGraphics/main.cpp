#include "GameInit.h"
#include "GameLogic.h"
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>  
#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#pragma comment(lib, "nclgl.lib")


Window w = Window(800, 600);
Renderer r(w);

//float fixed_step = 0.0008333f;
//float delta_time = 0.0f;

void setMatrices(Renderer& r) {
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, -1), Vector3(0, 0, -10)));
}

void main(void) {

	//Initializes the snooker world
	//Creates all entities, assigns position and colour, creates meshes and renders them on the screen
	GameInit gameInitialization(r);

	//Create Game Logic 
	GameLogic gLogic;

	//Set the projection and view matrices for the game world
	setMatrices(r);

	while (w.UpdateWindow()) {
		float msec = w.GetTimer()->GetTimedMS() / 1000;

		gLogic.waitUserInput(&gameInitialization);

		gLogic.updateObjects(&gameInitialization, msec);

		//Press ESCAPE key to exit the game
		if (Keyboard::KeyDown(KEY_ESCAPE)) {
			break;
		}

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
	}
	//Iterate through and delete all entity objects
	for (std::vector<Entity*>::iterator it = gameInitialization.entities.begin(); it != gameInitialization.entities.end(); ++it) {
		delete *it;
	}
}

/* The code below shows my attempt at trying to fix the time-step
in order for the my program to run consistently. However none of
the methods I've implemented, including the one below have worked.*/

/*delta_time += msec;
if (delta_time >= fixed_step) {

gLogic.waitUserInput(&gameInitialization);

gLogic.updateObjects(&gameInitialization, fixed_step);

delta_time = 0;
}*/
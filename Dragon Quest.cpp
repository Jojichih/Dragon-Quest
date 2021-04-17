#include <bangtal.h>
#include <stdio.h>

SceneID TAKEGISM, Santa, end;
ObjectID door1, map, flowerpot, man, moveButton;
bool closed1 = true;
int santaX = 0, santaY = 500;

//Scenario
int Scenario() {
	int a, b;
	printf("One day, a dragon came to a peaceful small country. \nThe dragon did no evil, robbed the princess. \nThe king offered a large reward for the warrior to kill the dragon and rescue the princess. \nAfter many people have failed, you have been chosen for the task. \n\nAfter a long journey, you meet the dragon. \nThe dragon said: To save the princess, you must accept two challenges! \n'Will you accept the challenge?' asked the dragon contemptuously. \n\n1: Accept \n2: Rufuse \n\n\nYour choice is:");

	//Accept task
	scanf_s("%d", &a);
	printf("\n\n");
	if (a == 1) {
		printf("You had accepted the task! \nAdventure Begins!\n\n");
	}
	//Refuse task
	if (a == 2) {
		printf("You are a coward and burned to death by the dragon. \nGame Over! \n\n");
		endGame();
		return 0;
  }
}

int endMessage() {
	printf("\n\nYou completed all the challenges... \nNow I wll leave... The princess belongs to you...\n\n");
	return 0;
}

void endGame(bool success)
{
	if (success) {
		endMessage();
		enterScene(end);
		showMessage("The End.");
	}
}

//Redefine the 'createObject' function
ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	//Level 1 
	if (object == door1) {
		//Determine whether the door can be opened
		if (closed1 == true) {
			if (getHandObject() == map) {
				setObjectImage(door1, "Images/Level1/open.png"); //Change the state of the door
				closed1 = false;
			}
			else {
				showMessage("You need to have a item to open this door!");
			}
		}
		//Determine if can proceed to the Level2
		else {
			enterScene(Santa); //Enter Level 2
			setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
		}
	}
	else if (object == flowerpot) {
		if (action == MouseAction::MOUSE_DRAG_LEFT) {
			locateObject(flowerpot, TAKEGISM, 975, 10); //Move item to the left
		}
		else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			locateObject(flowerpot, TAKEGISM, 775, 10); //Move item to the right
		}
	}
	else if (object == map) {
		pickObject(map); //Pick up item
	}

	//Level 2
	else if (object == moveButton) {
		santaX += 30;			// move 30;
		locateObject(man, Santa, santaX, santaY); //Santa's intial position

		//If the santa pass the right side of the picture, end the game
		if (santaX > 1280) {
			endGame(true);
			}
		}
	}

int main() {

	Scenario();
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setMouseCallback(mouseCallback);

	//Level 1
	TAKEGISM = createScene("Level1", "Images/Level1/TAKEGISM.png"); //Create Scene
	door1 = createObject("Images/Level1/close.png", TAKEGISM, 1170, 100, true); //Create Door
	map = createObject("Images/Level1/map.png", TAKEGISM, 924, 12, true); //Create the iteam to open the door
	scaleObject(map, 0.06f); //Scales 6%
	flowerpot = createObject("Images/Level1/flowerpot.png", TAKEGISM, 875, 10, true); //Create the iteam to hide the map
	scaleObject(flowerpot, 1.1f); //Scales 110%

	//Level 2
	Santa = createScene("Level2", "Images/Level2/background.png");

	/*
	//Show Button or nor  ???
	if (Santa) {
		if (true) {
			setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false); //Hide Button
		}
		else {
			setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, true); //Show Button
		}
	}
	*/
	man = createObject("Images/Level2/santa.png", Santa, santaX, santaY, true); //Create the iteam that can be moved
	moveButton = createObject("Images/Level2/play.png", Santa, 640, 40, true); //Create the botton to move the santa

	//End Scene
	end = createScene("END SCENE", "Images/Level2/end.jpg");

	startGame(TAKEGISM);
 
}
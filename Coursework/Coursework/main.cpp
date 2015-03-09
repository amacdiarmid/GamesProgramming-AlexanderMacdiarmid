#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	//main variables
	int difficulty = 1;
	LPCSTR wallToUse[] = { "wall texture easy.png", "wall texture medium.png", "wall texture hard.png" };

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
	const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;	

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails
        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//create textures
	//background
	cTexture textureBkgd;
	textureBkgd.createTexture("background.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	//wall
	cTexture textureWall;
	textureWall.createTexture("wall texture easy.png");
	cSprite spriteWall;
	spriteWall.setSpritePos(glm::vec2((windowWidth / 2) - (textureWall.getTWidth() / 2), windowHeight - textureWall.getTHeight()));
	spriteWall.setTexture(textureWall.getTexture());
	spriteWall.setTextureDimensions(textureWall.getTWidth(), textureWall.getTHeight());

	//player 1
	
	cTexture textureP1;
	textureP1.createTexture("man texture.png");
	cSprite spriteP1;
	spriteP1.setSpritePos(glm::vec2((windowWidth / 4) - (textureP1.getTWidth() / 2), windowHeight - textureP1.getTHeight()));
	spriteP1.setTexture(textureP1.getTexture());
	spriteP1.setTextureDimensions(textureP1.getTWidth(), textureP1.getTHeight());
	player player1 = player::player("alex");
	player1.attachInputMgr(theInputMgr);
	player1.attachPlayerSprite(spriteP1);

	/*
	//players 2
	static player player2 = player::player("not alex");
	cTexture textureP2;
	textureP2.createTexture("man texture.png");
	cSprite spriteP2;
	spriteP2.setSpritePos(glm::vec2(((windowWidth / 4) * 3) - (textureP2.getTWidth() / 2), windowHeight - textureP2.getTHeight()));
	spriteP2.setTexture(textureP2.getTexture());
	spriteP2.setTextureDimensions(textureP2.getTWidth(), textureP2.getTHeight());
	spriteP2.attachInputMgr(theInputMgr);
	spriteP2.attatchPlayerObject(player2);
	*/

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		spriteBkgd.render();
		spriteWall.render();
		
		//player 1
		player1.update();
		player1.render();

		//player 2 renderers
		//spriteP2.update();
		//spriteP2.render();


		//game->render();

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

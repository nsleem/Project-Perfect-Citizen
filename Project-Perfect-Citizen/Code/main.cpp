//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath() string("Resources/")
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Library/json/json.h"
#include "Game/testRenderSprite.h"
#include "Engine/InputHandler.h"
#include "Engine/subject.h"
#include "Engine/debug.h"
#include "Engine/entity.h"
#include "Engine/Window.h"
#include "Engine/desktop.h"
#include "Game/mousePressButton.h"
#include "Game/buttonRenderComponent.h"
#include "Game/consoleIconRenderComponent.h"
#include "Game/TreeCommands.h"
#include "Engine/NodeState.h"
#include "Game/animatorComponent.hpp"
#include "Game/textInputKeys.hpp"
#include "Game/createWindow.h"
#include "Game/createIcon.h"
#include "Game/createButton.h"
#include "Engine/BorderDecorator.h"
#include "Game/createDesktop.h"
#include "Game/desktopExtractionComponent.hpp"
#include "Game/expressionistParser.hpp"
#include "Engine/Audio/Audio.h"
#include "Engine/Audio/Sounds.h"
#include "Engine/Audio/DesktopAudio.h"
#include "Engine/Audio/AudioLocator.h"
#include "Engine/Audio/AudioLogger.h"
#include "Engine/Audio/AudioLocator.h"
#include "Engine/Audio/NullAudio.h"
#include "Game/PipelineCharacter.h"
#include "Game/Database.h"
#include "Engine/Audio/AudioQueue.h"
#include "Engine/Network.h"
#include "Game/BootLoader.hpp"
#include "Game/characterRender.hpp"
#include "Engine/debug.h"
#include "Engine/TestFunctionClass.h"
#include "Engine/FreeFunctionObserver.h"
#include "Game/interpolateUpdateComponent.hpp"

#include "Game/bootLoadingUpdateComponent.hpp"
#include "Game/bootLoadingAnimationRender.hpp"


using namespace ppc;

bool printFunc(TestFunctionClass* tfc, sf::Event& ev) {
	std::cout << "inside printFunc" << std::endl;
	tfc->callFunc(ev);
	return true;
}



bool runBootDesktop(sf::RenderWindow& screen, sf::Image& iconSheet, sf::Image& spriteSheet, sf::Sprite& wallpaper) {
    ppc::NodeState testState;
    testState.setUp();
    Window* desktopWindow = new Window(1800, 1000, sf::Color(0, 0, 0));
    
    Desktop myDesktop(*desktopWindow, testState);
    myDesktop.addBackgroundCmpnt(desktopWindow, wallpaper);
    //createPlayerDesktop(myDesktop, *desktopWindow, myDesktop.getInputHandler(), iconSheet, spriteSheet);
    
    Window* bootWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity loading;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    
    textLabelComponent* textLabel = new textLabelComponent(font,sf::Color::Green, 0,0, 20, " PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n   Beginning File System Initialization \n");
    
    bootLoadingAnimationRender* bootRender = new bootLoadingAnimationRender(spriteSheet,*textLabel,7,5);
    buttonRenderComponent* dcps =  new buttonRenderComponent(spriteSheet, 6, 6, 1, 0);
    //dcps->setImageScale(2.0f, 2.0f);
    //dcps->renderPosition(sf::Vector2f(355,200));

    
    bootLoadingUpdateComponent* bootUpdate = new bootLoadingUpdateComponent(*bootRender,*dcps,0.1f);
    loading.addComponent(bootRender);
    loading.addComponent(bootUpdate);
    loading.addComponent(textLabel);
    //loading.addComponent(dcps);
    bootWindow->addEntity(loading);
    
    myDesktop.addWindow(bootWindow);
    
    // Go into main game loop
    sf::Clock deltaTime;
    sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
    while (screen.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (screen.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::KeyPressed) {
              if (event.key.code == sf::Keyboard::Return){
                // Boots player to teacher desktop
                return false;
              }
            }
            if (event.type == sf::Event::Closed) {
                screen.close();
            }
            
            //Input phase
            myDesktop.registerInput(event);
        }
        
        sf::Time elapsed = deltaTime.getElapsedTime();
        while (elapsed > framePeriod) {
            screen.clear(sf::Color::Black);
            sf::Time dt = deltaTime.restart();
            myDesktop.update(dt);
            elapsed -= framePeriod;
        }
        myDesktop.refresh();
        screen.draw(myDesktop);
        screen.display();
    }
    return false;
    
}


bool runPlayerDesktop(sf::RenderWindow& screen, sf::Image& iconSheet, sf::Image& spriteSheet, sf::Sprite& wallpaper) {
	ppc::NodeState* testState = new NodeState();
	testState->setUp();
	Window* desktopWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Desktop myDesktop(*desktopWindow, *testState);
	myDesktop.addBackgroundCmpnt(desktopWindow, wallpaper);
	createPlayerDesktop(myDesktop, *desktopWindow, myDesktop.getInputHandler(), iconSheet, spriteSheet);

	// Go into main game loop
	sf::Clock deltaTime; 
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	while (screen.isOpen()) {
		//Process sf::events
		sf::Event event;
		while (screen.pollEvent(event)) {
			// Close window: exit
			//if (event.type == sf::Event::MouseButtonReleased) {
				// Boots player to teacher desktop
				//return false;
			//}
			if (event.type == sf::Event::Closed) {
				screen.close();
			}	

			//Input phase
			myDesktop.registerInput(event);
		}

		sf::Time elapsed = deltaTime.getElapsedTime();
		while (elapsed > framePeriod) {
			screen.clear(sf::Color::Black);
			sf::Time dt = deltaTime.restart();
			myDesktop.update(dt);
			elapsed -= framePeriod;
		}
		myDesktop.refresh();
		screen.draw(myDesktop);
		screen.display();
	}
	return false;

}


bool runTargetDesktop(sf::RenderWindow& screen, sf::Image& iconSheet, sf::Image& spriteSheet, sf::Sprite& wallpaper) {
		ppc::NodeState testState;
		testState.setUp();
		Window* desktopWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

		Desktop myDesktop(*desktopWindow, testState);
		myDesktop.addBackgroundCmpnt(desktopWindow, wallpaper);
		createTeacherDesktop(myDesktop, *desktopWindow, myDesktop.getInputHandler(), iconSheet, spriteSheet);

		// Go into main game loop
		sf::Clock deltaTime; 
		sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
		while (screen.isOpen()) {
			//Process sf::events
			sf::Event event;
			while (screen.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					screen.close();
				myDesktop.registerInput(event);
			}

			sf::Time elapsed = deltaTime.getElapsedTime();
			while (elapsed > framePeriod) {
				screen.clear(sf::Color::Black);
				sf::Time dt = deltaTime.restart();
				myDesktop.update(dt);
				elapsed -= framePeriod;
			}
			myDesktop.refresh();
			screen.draw(myDesktop);
			screen.display();
		}
		return false;
}

int main(int argc, char** argv) {

    DBG_INIT();
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	DEBUGF("ac", argc);


	bool BootToTitleCard = false; 
    // Create the main sf::window
	sf::Event testEvent;
    sf::RenderWindow screen(sf::VideoMode(1000, 800), "SFML window");
	////////////////////////////////////////////FUNCTION OBSERVER TESTING/////////////////////////////////
	TestFunctionClass cool;
	//FunctionObserver<TestFunctionClass> c(&TestFunctionClass::callFunc); //= new FunctionObserver<TestFunctionClass>(&TestFunctionClass::callFunc);
	//FunctionObserver<TestFunctionClass>* c = new FunctionObserver<TestFunctionClass>(&TestFunctionClass::callFunc, cool);
	//bool coolReturnValue = (*cool.*(c->functionPointer))(testEvent);
	//c->eventHandler(testEvent);


	FreeFunctionObserver<TestFunctionClass> d(printFunc, &cool);
	d.eventHandler(testEvent);
	////////////////////////////////////////////FUNCTION OBSERVER TESTING/////////////////////////////////

	//bool coolReturnValue = (*cool.*(c->functionPointer))(sf::Event());

	///////////// Load Spritesheets/Textures/Background Images ////////
	sf::Sprite playerWallpaper;
	sf::Sprite teacherWallpaper;
	sf::Texture playerWallpaperTexture;
	sf::Texture teacherWallpaperTexture;
	playerWallpaperTexture.loadFromFile(resourcePath() + "Wallpaper.png");
	teacherWallpaperTexture.loadFromFile(resourcePath() + "Teacher_Wallpaper.png");

	playerWallpaper.setTexture(playerWallpaperTexture);
	teacherWallpaper.setTexture(teacherWallpaperTexture);

	playerWallpaper.setScale(0.7f, 0.7f);
	playerWallpaper.setPosition(0, 0);

    sf::Image spriteSheet;
	spriteSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
	sf::Image teacherIconSheet;
	teacherIconSheet.loadFromFile(resourcePath() + "Teacher_Icon_Sheet.png");
	///////////////////////////////////////////////////////////////////

    
    //while (runBootDesktop(*&screen, iconSheet, spriteSheet, playerWallpaper)) {}
	//while (runPlayerDesktop(*&screen, iconSheet, spriteSheet, playerWallpaper)) {}
	while (runTargetDesktop(*&screen, teacherIconSheet, spriteSheet, teacherWallpaper)) {}
    
    return EXIT_SUCCESS;
}




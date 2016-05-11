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
#include "Engine/Engine.h"
#include "Game/mousePressButton.h"
#include "Game/buttonRenderComponent.h"
#include "Game/consoleIconRenderComponent.h"
#include "Game/TreeCommands.h"
#include "Game/animatorComponent.hpp"
#include "Game/textInputKeys.hpp"
#include "Game/createWindow.h"
#include "Game/createIcon.h"
#include "Game/createButton.h"
#include "Game/createDesktop.h"
#include "Game/desktopExtractionComponent.hpp"
#include "Game/expressionistParser.hpp"
#include "Game/PipelineCharacter.h"
#include "Game/Database.h"
#include "Game/BootLoader.hpp"
#include "Game/characterRender.hpp"
#include "Game/interpolateUpdateComponent.hpp"

#include "Game/bootLoadingUpdateComponent.hpp"
#include "Game/bootLoadingAnimationRender.hpp"
#include "Game/endAnimationUpdateComponent.hpp"
#include "Game/endingAnimationRender.hpp"

#include "Game/TextBubble.h"

#include "Game/createTutorial.h"
#include "Game/CreateReportScreen.h"

using namespace ppc;



void setUpBootDesktop(ppc::Desktop& myDesktop) {
    
    Window* bootWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity loading;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    
    
    textLabelComponent* textLabel = new textLabelComponent(font,sf::Color::Green, 0,0, 20, " PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n   Beginning File System Initialization \n");
    
    bootLoadingAnimationRender* bootRender = new bootLoadingAnimationRender(myDesktop.getButtonSheet(),*textLabel,7,5);
    
    bootLoadingUpdateComponent* bootUpdate = new bootLoadingUpdateComponent(*bootRender,0.1f);
    
    loading.addComponent(bootRender);
    loading.addComponent(bootUpdate);
    loading.addComponent(textLabel);
    bootWindow->addEntity(loading);
    
    myDesktop.addWindow(bootWindow);
}



void setUpEndDesktop(ppc::Desktop& myDesktop) {
    
    Window* endWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity ending;
    
    endingAnimationRender* endRender = new endingAnimationRender(myDesktop.getButtonSheet());
    endAnimationUpdateComponent* endUpdate = new endAnimationUpdateComponent(*endRender, 0.1f);
    
    ending.addComponent(endRender);
    ending.addComponent(endUpdate);
    endWindow->addEntity(ending);
    
    myDesktop.addWindow(endWindow);
}


void setUpPlayerDesktop(ppc::Desktop& myDesktop) {
    createPlayerDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpDummyDesktop(ppc::Desktop& myDesktop) {
    createDummyDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                       myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpTeacherDesktop(ppc::Desktop& myDesktop) {
    createTeacherDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                         myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpArtistDesktop(ppc::Desktop& myDesktop) {
    createArtistDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpPoliticianDesktop(ppc::Desktop& myDesktop) {
    createPoliticianDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

int main(int argc, char** argv) {
    
    DBG_INIT();
    //Scans Debug Flags
    Debug::scanOpts(argc, argv);
    DEBUGF("ac", argc);
    
    World::initFontMap();
	World::initLoadScreen();

    bool BootToTitleCard = false;
    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(1000, 800), "SFML window");
       
    AudioQueue audiotest(5);
    audiotest.addBgm("SoundTrack_Extraction.ogg");
    audiotest.loopBgm();
    audiotest.playBgm();

    ///////////////////////////////////////////////////////////////////
    
    //// ----------------   PYTHON LOCATION STUFF ---------------- ////
    
    // Run the locator python app
    //system("osascript -e 'tell app \"ppc_location_print\" to open'");
    // -----------------------------------------------------------//

    World::setGameScreen(screen);
	ifstream desktopFileInput;

    //Main Loops for each Desktops
    
	//Boot Desktop

	Desktop mainDesktop;
	desktopFileInput.open(resourcePath() + "Saves/bootDesktop.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();
	Logger::startTimer("bootDesktop");
    
	World::setCurrDesktop(mainDesktop);
	setUpBootDesktop(mainDesktop);
	World::runCurrDesktop();
    
    Logger::endTimer("bootDesktop");
	//End Boot Desktop

	


	//PE Tutorial Desktop
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/pipelineTutorial.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

    Logger::startTimer("PipeTutorialDesktop");

	World::setCurrDesktop(mainDesktop);
    createTutorial(mainDesktop);
    World::runCurrDesktop();
    
    Logger::endTimer("PipeTutorialDesktop");
	//End PE Tutorial Desktop


	//DE Tutorial Desktop 
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/desktopTutorial.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

	Logger::startTimer("DeskTutorialDesktop");

	World::setCurrDesktop(mainDesktop);
	createDesktopTutorial(mainDesktop);
	World::runCurrDesktop();

	Logger::endTimer("DeskTutorialDesktop");

	//Player Desktop
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/playerDesktop.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

    Logger::startTimer("playerDesktop");
    
    World::setCurrDesktop(mainDesktop);
	setUpPlayerDesktop(mainDesktop);
	World::runCurrDesktop();
    
    Logger::endTimer("playerDesktop");
	// End Player Desktop

	//Testing Report Screen
	//Desktop reportScreen;
	//createReportScreen(reportScreen, World::DE1A);
	//World::setCurrDesktop(reportScreen);
	//World::runCurrDesktop();

	//ENd of report screen

	//Desktop 1 / Teacher Desktop
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/teacherDesktop.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();
    Logger::startTimer("TeacherDesktop");
    
    World::setCurrDesktop(mainDesktop);
	setUpTeacherDesktop(mainDesktop);
	World::runCurrDesktop();
    
    Logger::endTimer("TeacherDesktop");
	//End of Target/Teacher Desktop
    
	//Player Desktop (2)
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/playerDesktop2.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

	Logger::startTimer("playerDesktop2");

	World::setCurrDesktop(mainDesktop);
	setUpPlayerDesktop(mainDesktop);
	World::runCurrDesktop();

	Logger::endTimer("playerDesktop2");
    

	//Desktop Extraction 2 / (Artist Desktop or politician)
	World::startLoading();
	if (ppc::SuspiciousFileHolder::isGuilty()) {
		desktopFileInput.open(resourcePath() + "Saves/politicianDesktop.ini", std::ifstream::in);
	} else {
		desktopFileInput.open(resourcePath() + "Saves/artistDesktop.ini", std::ifstream::in);
	}
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

    Logger::startTimer("DE2Desktop");
    
    World::setCurrDesktop(mainDesktop);
	if (!ppc::SuspiciousFileHolder::isGuilty()) {
		setUpPoliticianDesktop(mainDesktop);
	} else {
		setUpArtistDesktop(mainDesktop);
	}
	World::runCurrDesktop();
    
    Logger::endTimer("DE2Desktop");
    //End of Target/Teacher Desktop

	//Player Desktop (3)
	World::startLoading();
	desktopFileInput.open(resourcePath() + "Saves/playerDesktop3.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();

	Logger::startTimer("playerDesktop3");

	World::setCurrDesktop(mainDesktop);
	setUpPlayerDesktop(mainDesktop);
	World::runCurrDesktop();

	Logger::endTimer("playerDesktop3");


	//Desktop Extraction 3 goes here

	//Ending Desktop
	desktopFileInput.open(resourcePath() + "Saves/endDesktop.ini", std::ifstream::in);
	desktopFileInput >> mainDesktop;
	desktopFileInput.close();
    Logger::startTimer("endDesktop");
    
    World::setCurrDesktop(mainDesktop);
	setUpEndDesktop(mainDesktop);
	World::runCurrDesktop();
    
    Logger::endTimer("endDesktop");
    
    Logger::exportParcels();
    
    
    
    return EXIT_SUCCESS;
}



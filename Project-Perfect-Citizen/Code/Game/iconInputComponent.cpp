#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>
#include <string>
#include "../Game/emailExtraction.hpp"

using namespace ppc;
const string MOUSE_DOWN_CODE = "MDC";
const string MOUSE_RELEASED_CODE = "MRC";
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const string OPEN_THE_CONSOLE = "OTC";
const string OPEN_THE_FILE = "OTF";
const string OPEN_THE_SETTINGS = "OTS";
const string OPEN_THE_CHAT = "OTCH";
const string OPEN_THE_SEARCH = "OTSER";
const string OPEN_THE_PIPELINE = "OTP";
const string OPEN_THE_HELP = "OTH";
const string OPEN_THE_BROWSER = "OTB";
const string OPEN_THE_EXPLORER = "OTE";
const string OPEN_THE_EMAIL = "OTEM";

iconInputComponent::iconInputComponent(Desktop& dT, Database* dB, Inbox& ib, sf::Image& bS)
	: theDesktop_(dT), theDatabase_(dB), theInbox_(ib), buttonSheet_(bS) {

}



void iconInputComponent::recieveMessage(msgType msg) {
	// Case: Double Clicked Console Icon
	if (msg.compare(OPEN_THE_CONSOLE) == 0) {
		WindowInterface* consoleWindow = 
			new Window(600, 500, sf::Color(51, 50, 161));
		spawnConsole(consoleWindow, consoleWindow->getInputHandler(), 
			theDesktop_.getNodeState(), buttonSheet_, 200, 200);
		theDesktop_.addWindow(consoleWindow);
	}
	else if (msg.compare(OPEN_THE_FILE) == 0) {
        ppc::WindowInterface* FileWindow =
            new ppc::Window(400, 400, sf::Color(255, 255, 255));
        spawnFile(FileWindow, FileWindow->getInputHandler(),
            theDesktop_.getNodeState(), buttonSheet_, 100, 200, "DesktopContent/Desktop1/3-29-12-184.jpg");
        theDesktop_.addWindow(FileWindow);
	}
	else if (msg.compare(OPEN_THE_SETTINGS) == 0) {
		ppc::WindowInterface* ErrorMsgWindow =
			new ppc::Window(500, 150, sf::Color(255, 255, 255));
		spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
		theDesktop_.addWindow(ErrorMsgWindow);
	}
	else if (msg.compare(OPEN_THE_CHAT) == 0) {
		ppc::WindowInterface* ErrorMsgWindow =
			new ppc::Window(500, 150, sf::Color(255, 255, 255));
		spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
		theDesktop_.addWindow(ErrorMsgWindow);
	}
	else if (msg.compare(OPEN_THE_SEARCH) == 0) {
		WindowInterface* databaseWindow =
			new Window(800, 600, sf::Color(200, 200, 200));
		spawnDatabase(databaseWindow, databaseWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
		theDesktop_.addWindow(databaseWindow);
	}
	else if (msg.compare(OPEN_THE_PIPELINE) == 0) {
		ppc::WindowInterface* piplineWindow =
			new ppc::Window(800, 600, sf::Color(200, 200, 200));
		ppc::spawnPipeline(piplineWindow, piplineWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
		theDesktop_.addWindow(piplineWindow);
	}
	else if (msg.compare(OPEN_THE_HELP) == 0) {
		ppc::WindowInterface* ErrorMsgWindow =
			new ppc::Window(500, 150, sf::Color(255, 255, 255));
		spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
		theDesktop_.addWindow(ErrorMsgWindow);
	}
	else if (msg.compare(OPEN_THE_BROWSER) == 0) {
		ppc::WindowInterface* ErrorMsgWindow =
			new ppc::Window(500, 150, sf::Color(255, 255, 255));
		spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
		theDesktop_.addWindow(ErrorMsgWindow);
	}
	else if (msg.compare(OPEN_THE_EXPLORER) == 0) {
		ppc::WindowInterface* explorerWindow =
			new ppc::Window(500, 250, sf::Color(255, 255, 255));
		spawnExplorer(explorerWindow, explorerWindow->getInputHandler(), theDesktop_.getNodeState(), buttonSheet_, 100, 200);
		theDesktop_.addWindow(explorerWindow);
	}
	else if (msg.compare(OPEN_THE_EMAIL) == 0) {
		ppc::WindowInterface* inboxWindow =
			new ppc::Window(600, 400, sf::Color(200, 200, 200));
		ppc::spawnInbox(theDesktop_, inboxWindow, inboxWindow->getInputHandler(), buttonSheet_, 100, 200, theInbox_);
		theDesktop_.addWindow(inboxWindow);
	}
}

iconInputComponent::~iconInputComponent() {

}

bool iconInputComponent::registerInput(sf::Event& ev) {
	return true;
}


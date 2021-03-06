
#include "textOutputRenderComponent.h"


#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"
#include "../Engine/desktop.h"
#include "../Engine/World.h"
#include "../Engine/WindowInterface.h"
#include "../Engine/BorderDecorator.h"
#include "../Engine/ScrollBarDeco.h"
#include "../Engine/Window.h"
#include "../Engine/SuspiciousFileHolder.h"

#include "../Engine/SubjectObsvr.h"

#include "TreeCommands.h"
#include "createWindow.h"
#include "textInputRenderComponent.hpp"

const std::string TEXT_KEY_INPUT = "TKI";

using namespace ppc;

textOutputRenderComponent::textOutputRenderComponent(Desktop& dt, WindowInterface* wip, sf::Image bs, sf::Font f,
	NodeState fT, textInputRenderComponent* tirc, int x, int y, int size ) : promptLine(tirc), theDesktop_(&dt), theWindow_(wip),
	buttonSheet_(bs), font_(f), fileTree_(fT) {

	numDisplayedLines = 0;

	this->text_ = new sf::Text();

	promptLine = tirc;

	text_->setFont(font_);
	text_->setColor(sf::Color::Green);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	text_->setString("DCPS CONSOLE PROMPT [Version 10.0.10586] \n(c) Department of Cyber Police and Security.\nEnter 'help' for command references. \n");

}


textOutputRenderComponent::~textOutputRenderComponent() {

}

void textOutputRenderComponent::updateString(std::vector<std::string> cmd) {
    for (size_t i = 0; i < cmd[0].size(); i++) {
        cmd[0][i] = tolower(cmd[0][i]);
    }
	
	/* Print out what was just typed */
	str_ = str_ + "> ";
	for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) 
		str_ = str_ + " " + (*iter);
	str_ = str_ + "\n";
	++numDisplayedLines;

	/* CASE: LS*/
	if (cmd.at(0) == "ls") {
		std::vector<std::string> firstLsCommand;
		std::string ls = "ls";
		firstLsCommand.push_back(ls);
		commandFn firstLs = findFunction(ls);
		firstLs(fileTree_, firstLsCommand);

		str_ = str_ + fileTree_.getDirString();
		int numLines = std::count(str_.begin(), str_.end(), '@');
		std::replace(str_.begin(), str_.end(), '@', '\n' );
		numDisplayedLines += numLines;
	}

	/* CASE: PWD*/
	else if (cmd.at(0) == "pwd") {
		std::vector<std::string> wd = fileTree_.getPwdVector();
		for (auto iter = wd.begin(); iter != wd.end(); ++iter)
			str_ = str_ + (*iter) + "/";
		str_ = "Current Working Directory: "+ str_ + "\n";
		++numDisplayedLines;
	}

	/* CASE: OPEN*/
	else if (cmd.at(0) == "open") {
		if (cmd.size() > 2) {
			str_ = str_ + "Error: 'open' requires one parameter.\n";
			numDisplayedLines++;
		}
        if(cmd.size() == 2){
            if (fileTree_.getCwd()->findElement(cmd.at(1)) != nullptr) {
                std::string fileResourcePath = fileTree_.getCwd()->findElement(cmd.at(1))->getFileData();
                fileTree_.readFile(cmd.at(1));
                str_ += "\nOpening " + cmd.at(1) + " ... \n";
                numDisplayedLines += 3;
            }
            else{
                str_ = str_ + "Error: file not found.\n";
                numDisplayedLines++;
            }
        }
        if(cmd.size() == 1){
            str_ = str_ + "Error: 'open' requires one parameter.\n";
            numDisplayedLines++;
        }
    }

	/* CASE: CLEAR*/
	else if (cmd.at(0) == "clear") {
		str_.clear();
		numDisplayedLines = 0;
	}

	/* CASE: CD */
	else if (cmd.at(0) == "cd") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'cd' requires one parameter.\n";
			numDisplayedLines++;
		}
        if(cmd.size() > 1){
            if (cmd.at(1).compare("CP") == 0) { World::quitDesktop(); }
            if (fileTree_.getCwd()->findElement(cmd.at(1)) == nullptr) {
                str_ = str_ + "Error: Directory '" + cmd.at(1) + "' not found. \n";
                numDisplayedLines++;
            }
            else {
                if (fileTree_.getCwd()->findElement(cmd.at(1))->isPasswordProtected()) {
                    str_ = str_ + "Error: Directory '" + cmd.at(1)+"' is password protected. \nHint: " + fileTree_.getCwd()->findElement(cmd.at(1))->getHint() + "\n";
                    numDisplayedLines+=3;
                }
                std::vector<std::string> cdCommand;
                std::string cd = "cd";
                cdCommand.push_back(cd);
                cdCommand.push_back(cmd.at(1));
                commandFn newCD = findFunction(cd);
                newCD(fileTree_, cdCommand);
                numDisplayedLines++;
            }
        }
	}

	//CASE: FLAG
	else if (cmd.at(0) == "flag" || cmd.at(0) == "Flag") {
		ppc::BaseFileType* tempBFT = this->fileTree_.getCwd()->findElement(cmd.at(1));
		if (tempBFT != nullptr) {
			std::vector<std::string> firstFlagCommand;
			firstFlagCommand.push_back("flag");
			firstFlagCommand.push_back(cmd.at(1));
			commandFn firstLs = findFunction("flag");
			firstLs(fileTree_, firstFlagCommand);
			str_ = str_ + " " + cmd.at(1) + " submitted for processing.\n";
		}
		else {
			str_ = str_ + " Unable to find " + cmd.at(1) + ".";
		}
		numDisplayedLines+=2;
		
		WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
		spawnFileTracker(*theDesktop_, fileTracker, fileTracker->getInputHandler(), 250, 50);
		//spawnFileTracker(*theDesktop_, fileTracker, fileTracker->getInputHandler(), SuspiciousFileHolder::getSusVecElement(0), 250, 50);
		theDesktop_->addWindow(fileTracker);
		SuspiciousFileHolder::setWindow(fileTracker);
	}

	/* CASE: MKDIR */
	else if (cmd.at(0) == "mkdir") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'mkdir' requires one parameter.\n";
			numDisplayedLines++;
		}
		else {
			std::vector<std::string> mkdirCommand;
			std::string mkdir = "mkdir";
			mkdirCommand.push_back(mkdir);
			mkdirCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(mkdir);
			newCD(fileTree_, mkdirCommand);
			numDisplayedLines++;
		}
		
	}

	/* CASE: MAKE */
	else if (cmd.at(0) == "make") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'make' requires one parameter.\n";
			numDisplayedLines++;
		}
		else {
			std::vector<std::string> makeCommand;
			std::string make = "make";
			makeCommand.push_back(make);
			makeCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(make);
			newCD(fileTree_, makeCommand);
			numDisplayedLines++;
		}
		
	}

	/* CASE: DECRYPT/ENCRYPT */
	else if ( cmd.at(0) == "decrypt" || 
		cmd.at(0) == "encrypt") {
		// Do nothing currently.
	}

	/* CASE: UNLOCK */
	else if (cmd.at(0) == "unlock") {
		std::vector<std::string> unlockCommand;
		std::string unlock = "unlock";
		if (cmd.size() == 3) {
            unlockCommand.push_back(unlock);
            unlockCommand.push_back(cmd.at(1));
			unlockCommand.push_back(cmd.at(2));
		}
        else {
            str_ = str_ + "Please enter: unlock [directory] [password].\n";
            numDisplayedLines++;
        }
        if(cmd.size() == 3){
            commandFn newCommand = findFunction(unlock);
            newCommand(fileTree_, unlockCommand);
            if (fileTree_.getCwd()->findElement(cmd.at(1)) == nullptr) {
                str_ = str_ + "Error: Directory '" + cmd.at(1) + "' not found. \n";
            }
            else if (fileTree_.getCwd()->findElement(cmd.at(1))->isPasswordProtected()) {
                str_ = str_ + "Access denied.\n";
            }
            else {
                str_ = str_ + "\nAccess granted. Moving into directory '" + cmd.at(1)+"' ...\n\n";
                std::vector<std::string> cd_cmd;
                cd_cmd.push_back("cd");
                cd_cmd.push_back(cmd.at(1));
                updateString(cd_cmd);
                numDisplayedLines += 2;
            }
            numDisplayedLines+= 2;
        }
	}
    
    /* CASE: HELP*/
    else if (cmd.at(0) == "help") {
        str_ = str_ + "help                       basic help for commands\n";
        str_ = str_ + "pwd                        prints the working directory\n";
        str_ = str_ + "cd [path]                  changes the current directory\n";
        str_ = str_ + "open [file]                opens a file\n";
        str_ = str_ + "unlock [folder] [password] attempts to open a locked directory\n";
        str_ = str_ + "ls                         lists the contents of the current\n";
        str_ = str_ + "                           working directory\n";
        numDisplayedLines+= 9;
    }
    
    /* CASE: GIT SHREKT*/
    else if (cmd.at(0) == "git") {
        if(cmd.size() == 2){
            if(cmd.at(1) == "shrekt"){
                str_ = str_ + "\n..####...##..##..#####...######..##..##. \n";
                str_ = str_ + ".##......##..##..##..##..##......##.##.. \n";
                str_ = str_ + "..####...######..#####...####....####... \n";
                str_ = str_ + ".....##..##..##..##..##..##......##.##.. \n";
                str_ = str_ + "..####...##..##..##..##..######..##..##. \n";
                str_ = str_ + "........................................ \n";
                numDisplayedLines+= 7;
            }
            if(cmd.at(1) == "gud"){
                str_ = str_ + "You stupid bottom fragger, you need to git gud \n";
                numDisplayedLines+= 1;
            }
        }
        else{
            str_ = str_ + "Error: 'git' requires one parameter.\n";
            numDisplayedLines++;
        }
    }


	/* CASE: DEFAULT*/
	else { 
		str_ = str_ + "Error: command '" + cmd.at(0) + 
			"' not found." + "\n"; 
		numDisplayedLines++;
	}

	/* Set the new console display */
	if (numDisplayedLines > maxDisplayedLines) {
		
		sf::FloatRect viewRect = {
			0.0f,
			float((promptLine->getText()->getPosition().y) - (theWindow_->getView().getSize().y - 300)),
			float(theWindow_->getBounds().width),
			float(theWindow_->getBounds().height)
		};
		
		//dynamic_cast<ScrollBarDecorator*>(theWindow_)->move(0, numDisplayedLines - maxDisplayedLines);
		theWindow_->setView(sf::View(viewRect));
	}
	text_->setString(str_);
}

void textOutputRenderComponent::updatePrompt() {
	std::vector<std::string> pwd_vector = fileTree_.getPwdVector();
	std::string pwd = "C:/";

	for (auto iter = pwd_vector.begin() + 1; iter != pwd_vector.end(); ++iter) {
		pwd += *iter;
		pwd.push_back('/');
	}
	promptLine->updatePrompt(pwd);
}

int textOutputRenderComponent::getNumLines() {
	return numDisplayedLines;
}

void textOutputRenderComponent::clearString() {
	str_.clear();
}

sf::Vector2f textOutputRenderComponent::getPosition() const {
    return text_->getPosition();
}

sf::Text* textOutputRenderComponent::getText() {
	return text_;
}



void textOutputRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void textOutputRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}
#include "CreateReportScreen.h"

#include <fstream>

#include "../Engine/Window.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"

#include "TextDisplayRenderComponent.h"
#include "TextDisplayBuilder.h"
#include "TextCharacterUpdate.h"
#include "ReportScreenInput.h"
#include "ReportEndObsvr.h"

using namespace ppc;

void ppc::createReportScreen(Desktop &d) {
	
	
	//will be a front top
	ppc::Window* reportScreen = new Window(1800, 1000);
	
	Entity reportEntity;
	std::string filename = World::getReportFile();
	std::ifstream reportFile(filename);

	std::string content((std::istreambuf_iterator<char>(reportFile)),
						(std::istreambuf_iterator<char>()));

	TextDisplayBuilder reportText;
	reportText.setColor(sf::Color::Green);
	reportText.setFont(World::getFont(World::FontList::Consola));
	reportText.setPosition({ 100,100 });
	reportText.setSize(25);
	reportText.setString("");

	reportText.create(reportEntity);
	

	//next, make/add components to end report screen
	TextCharacterUpdate* tcu = new TextCharacterUpdate();
	ReportEndObsvr* reO = new ReportEndObsvr(*reportScreen);
	reO->setPos(400.f, 700.f);
	tcu->onAnimEnd().addObserver(reO);

	TextDisplayRenderComponent* tdrc = dynamic_cast<TextDisplayRenderComponent*>(reportEntity.getComponent(0));
	tcu->setTextDisplay(*tdrc);
	tcu->setContent(content);
	tcu->setDisplayRate(sf::milliseconds(sf::Int32(30.0f)));

	ReportScreenInput* rsi = new ReportScreenInput(reportScreen->getInputHandler());
	rsi->setTextCharacterUpdate(*tcu);
	

	reportEntity.addComponent(tcu);
	reportEntity.addComponent(rsi);

	reportScreen->addEntity(reportEntity);

	d.setFrontTop(reportScreen, false);
	

}


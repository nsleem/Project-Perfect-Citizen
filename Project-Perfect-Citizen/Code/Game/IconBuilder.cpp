#include "IconBuilder.h"
#include "../Engine/debug.h"

//#include "../Engine/Engine.h"
#include "../Engine/desktop.h"


#include "animatorComponent.hpp"
#include "textLabelComponent.hpp"
#include "notifcationRenderComponent.h"

#include "buttonRenderComponent.h"


ppc::IconBuilder::IconBuilder() {

	dt = nullptr;
	ih = nullptr;
	db = nullptr;
	ib = nullptr;
	renderNotifications = false;
	buttonSheet = nullptr;

	font = nullptr;
	fontColor = sf::Color::White;

	label = "";
	isBeingPressed = "";

	iconType = ppc::iconInputComponent::IconType::Count;

	sheetX = 0;
	sheetY = 0;
	width = 0;
	frames = 0;

	size = 0.f;
	animationSpeed = 0.f;

	posX = 0.f;
	posY = 0.f;

}

ppc::IconBuilder::~IconBuilder() {
}

void ppc::IconBuilder::setSpritebyIndicies(int x, int y, int r, int f) {

	sheetX = x;
	sheetY = y;
	width = r;
	frames = f;
}

void ppc::IconBuilder::setSprites(sf::Sprite &, sf::Sprite &) {
}

void ppc::IconBuilder::setSize(float s) {
	size = s;
}

void ppc::IconBuilder::setIconType(ppc::iconInputComponent::IconType type) {
	iconType = type;
}

void ppc::IconBuilder::setDesktop(ppc::Desktop &d) {
	dt = &d;
}

void ppc::IconBuilder::setInputHandle(ppc::InputHandler &handle) {
	ih = &handle;
}

void ppc::IconBuilder::setButtonSheet(sf::Image &bsheet) {
	this->buttonSheet = &bsheet;
}

void ppc::IconBuilder::setDatabase(ppc::Database &dbase) {
	db = &dbase;
}

void ppc::IconBuilder::setInbox(ppc::Inbox &ibox) {
	ib = &ibox;
}

void ppc::IconBuilder::setText(std::string name, sf::Font &f , 
	sf::Color col = sf::Color::White ) {

	label = name;
	font = &f;
	fontColor = col;
}

void ppc::IconBuilder::setAnimSpeed(float spd) {
	animationSpeed = spd;
}

void ppc::IconBuilder::setPosition(float x, float y) {
	posX = x;
	posY = y;
}

void ppc::IconBuilder::setPosition(sf::Vector2f pos) {

	posX = pos.x;
	posY = pos.y;
}

void ppc::IconBuilder::setRenderNotifications(bool toset) {
	renderNotifications = toset;
}

void ppc::IconBuilder::create(Entity &e) {
	textLabelComponent* textLabel = new textLabelComponent(*font, fontColor, posX, posY + size * 128, 20, label);

	buttonRenderComponent* IconRender = new buttonRenderComponent(dt->getIconSheet(), sheetX, sheetY, width, frames);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition({ posX, posY });
	if(iconType != iconInputComponent::IconType::File) IconRender->setButtonType("ICON");
	animatorComponent* animator = new animatorComponent(*IconRender, animationSpeed);

	sf::FloatRect iconBounds(IconRender->getSprite()->getGlobalBounds().left, IconRender->getSprite()->getGlobalBounds().top,
		IconRender->getSprite()->getGlobalBounds().width, IconRender->getSprite()->getGlobalBounds().height + 25);
	mousePressButton* mpbFolder = new mousePressButton(*ih, iconBounds);
	iconInputComponent* iconInputComp = new iconInputComponent(*dt, db, *ib, *buttonSheet, dt->getIconSheet(), iconType);
	iconInputComp->setIconLabelName(label);

	notificationRenderComponent* notirc = new notificationRenderComponent();

	if (renderNotifications) {
		NotificationObserver* notiobs = &notirc->getNotiObserver();
		dt->getInbox().getInboxSubject().addObserver(notiobs);
		notirc->setPosition({ posX, posY });
		notirc->updateText(-(dt->getInbox().getUnreadEmailCount()));
	}

	e.addComponent(IconRender);
	e.addComponent(textLabel);
	e.addComponent(iconInputComp);
	e.addComponent(animator);
	e.addComponent(mpbFolder);
	if (renderNotifications) {
		e.addComponent(notirc);
	}
	else {
		delete notirc;
	}

}

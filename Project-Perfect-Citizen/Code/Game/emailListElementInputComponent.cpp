#include "../Engine/debug.h"
#include "emailListElementInputComponent.h"

#include <iostream>
#include <string>

#include <SFML/Graphics/Image.hpp>

#include "../Engine/Window.h"
#include "../Engine/desktop.h"

#include "createWindow.h"
#include "Email.h"


using namespace ppc;
const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const std::string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const std::string OPEN_EMAIL = "OE";
const std::string SELECT_EMAIL = "SE";
const std::string DESELECT_EMAIL = "DSE";
const float DOUBLE_CLICK_TIME = 500.0f;


emailListElementInputComponent::emailListElementInputComponent(ppc::Desktop& dT, ppc::InputHandler& ih,
	ppc::Email* eM, sf::Image& bS, sf::FloatRect rect) : InputComponent(2), boxRect(rect), buttonSheet(bS), emailToOpen(eM), theDesktop(dT) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed); 
	watch(ih, sf::Event::MouseButtonReleased);

}

emailListElementInputComponent::~emailListElementInputComponent() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void emailListElementInputComponent::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void emailListElementInputComponent::setFloatRect(sf::FloatRect rect) {
	boxRect = rect;
}

bool emailListElementInputComponent::isCollision(sf::Vector2i mousePos) {
	//Gets the position as a Float Vector
	sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));
	return boxRect.contains(mouseFloatPos);
}


bool emailListElementInputComponent::registerInput(ppc::Event ppcEv) {
    sf::Event ev(ppcEv);
	if (getEntity() != nullptr) {

		/* Case: Mouse Pressed Event*/
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

				/* Send the mouse down message regardless */
				getEntity()->broadcastMessage(MOUSE_DOWN_CODE);

				/* Handle Double Click Register */
				mouseTime = mouseClock.getElapsedTime().asMilliseconds();
				if (mouseTime > DOUBLE_CLICK_TIME) {
					mouseClock.restart();
					getEntity()->broadcastMessage(SELECT_EMAIL);
				}
				else if (mouseTime < DOUBLE_CLICK_TIME) {
					ppc::WindowInterface* emailWindow =
					new ppc::Window(600, 500, sf::Color(200, 200, 200));
					spawnEmailMessage(emailWindow, emailWindow->getInputHandler(), emailToOpen, buttonSheet, 200, 50);
					theDesktop.addWindow(emailWindow);
					getEntity()->broadcastMessage(MOUSE_DOUBLE_CLICK_CODE);

					ppc::Event ppcEv(ev);
					ppcEv.type = ppc::Event::EventTypes::OpenType;
					ppcEv.open.winType = ppc::Event::OpenEv::Email;
					getEntity()->broadcastMessage(ppcEv);
					sf::Event ev;
					//complains that its unintialized without this line.
					ev.type = sf::Event::EventType::Closed;
					if (emailToOpen->setRead()) {
						ppc::Event readEvent(ev);
						readEvent.type = ppc::Event::EventTypes::NotificationType;
						readEvent.notification.count = 1;
                        theDesktop.getInbox().getInboxSubject().sendEvent(readEvent);
						//this->onRead_.sendEvent(readEvent);
					}
				}
			}
			else {
				getEntity()->broadcastMessage(DESELECT_EMAIL);
			}
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
			}
		}
		/* Case: Mouse Moved Event*/
		else if (ev.type == sf::Event::MouseMoved) {
			if (!boxRect.contains(float(ev.mouseMove.x), float(ev.mouseMove.y)) &&
				ev.mouseButton.button == sf::Mouse::Left) {
				std::cout << "left the button" << std::endl;
			}
		}
	}

	return true;
}

ppc::Subject & emailListElementInputComponent::onRead()
{
	return onRead_;
}

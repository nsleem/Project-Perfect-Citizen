#include "buttonRenderComponent.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <typeinfo>

#include "../Engine/debug.h"
#include "../Engine/event.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include "../Engine/Entity.h"

#include "iconInputComponent.h"

using namespace ppc;
const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const std::string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const std::string ICON_TYPE = "ICON";
const std::string BUTTON_TYPE = "BUTTON";
const std::string OPEN_EMAIL = "OE";
const std::string SELECT_EMAIL = "SE";
const std::string DESELECT_EMAIL = "DSE";

buttonRenderComponent::buttonRenderComponent( sf::Image& image, 
                                             int x, int y, int r, int f) : buttonImage(image) {
	
	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();
    
    width = r;
    frameCount = f;
    xIndex = x;
    yIndex = y;

    //Set up circle shape
    //badge_.setFillColor(sf::Color::Red);
    //badge_.setOutlineColor(sf::Color::White);
    //badge_.setOutlineThickness(2.f);
    //badge_.setRadius(5.f);

    //set up text
    //notificationText_ = sf::Text(std::to_string(5),
      //                           World::getFont(World::Consola),
        //                         10);
    //notificationText_.move(2.5f, -2.0f);
    //notificationText_.setStyle(sf::Text::Bold);
    

    _buttonType = BUTTON_TYPE;
    _willAnimate = false;

    
    rectSourceSprite = new sf::IntRect(xIndex*size,
                                       yIndex*size,
                                       width*size,
                                       size);
    
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(0,0,buttonImage.getSize().x,buttonImage.getSize().y)))
        std::exit(-1);

	sprite->setTexture(*texture);
    sprite->setTextureRect(*rectSourceSprite);
	sprite->setPosition(0, 0);
	sprite->setScale(.5f, .5f);
}

buttonRenderComponent::~buttonRenderComponent() {
	delete texture;
	delete sprite;
    delete rectSourceSprite;
}

void buttonRenderComponent::setButtonType(std::string t) {
    if (t == ICON_TYPE) {
        _buttonType = t;
        sprite->setScale(0.5, 0.5);
    } else if (t == BUTTON_TYPE) _buttonType = t;
}


void buttonRenderComponent::renderPosition(sf::Vector2f pos) {
	//TODO
	//getEntity()->setPosition(pos);
    sprite->setPosition(pos.x, pos.y);
}

void buttonRenderComponent::setImageScale(float ScaleX, float ScaleY) {
	sprite->setScale(ScaleX, ScaleY);
}

sf::Sprite*  buttonRenderComponent::getSprite() {
	return sprite;
}

void buttonRenderComponent::setSprite(int x, int y, int r) {
    //if(!texture->loadFromImage(buttonImage,
		//sf::IntRect(x*size, y*size, r*size, size))) { exit(-1); }
    
    rectSourceSprite->left = x*size;
    rectSourceSprite->top = y*size;
    rectSourceSprite->width = r*size;
    rectSourceSprite->height = size;
    //texture->loadFromImage(buttonImage, *rectSourceSprite);
    sprite->setTextureRect(*rectSourceSprite);
    //sprite->setTexture(*texture);
    
}

void buttonRenderComponent::setButtonScale(int r) {
	sprite->setScale(r + 0.0f, r + 0.0f);
}

void buttonRenderComponent::animate() {
    if (_willAnimate) {
        if (rectSourceSprite->left == (frameCount * size)) {
            rectSourceSprite->left = 0;
            _willAnimate = false;
        } else
            rectSourceSprite->left += size;
        
        //texture->loadFromImage(buttonImage, *rectSourceSprite);
        sprite->setTextureRect(*rectSourceSprite);
       // sprite->setTexture(*texture);
    }
}



bool buttonRenderComponent::willAnimate() {
    return _willAnimate;
}

void ppc::buttonRenderComponent::setRenderable(bool r){
	_willRender = r;
}


void buttonRenderComponent::draw( sf::RenderTarget& target,
	sf::RenderStates states) const {

		if (_willRender) target.draw(*sprite, states);

        //if (getButtonType() == "ICON") {

        //    states.transform.translate(sprite->getPosition());
        //    states.transform.scale(1.3, 1.3, 0, 0);

        //    target.draw(badge_, states);
        //    target.draw(notificationText_, states);
        //}
}


void buttonRenderComponent::recieveMessage(ppc::Event ev) {
	switch (ev.type) {
	case Event::EventTypes::ButtonType:
		if (((ev.buttons.state == ev.buttons.Clicked
			&& _buttonType.compare("ICON") != 0
			) || ev.buttons.state == ev.buttons.DblClicked) &&
				ev.buttons.activation != ev.buttons.RightMouse) {
					setSprite(xIndex + width, yIndex, width);
		}
		if ((ev.buttons.state == ev.buttons.Release) &&
				ev.buttons.activation != ev.buttons.RightMouse) {
					setSprite(xIndex, yIndex, width);
		}
		break;
	case Event::EventTypes::AbleType:
		setRenderable(ev.able.enable);
		break;
	case Event::EventTypes::OpenType:
		if (ev.open.winType = Event::OpenEv::Email) {
		setSprite(xIndex + width, yIndex, width);
	}
		break;
	default:
		break;
	}
}


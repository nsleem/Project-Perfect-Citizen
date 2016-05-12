//
//  BadCopRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/11/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "BadCopRenderComponent.hpp"

#include "../Engine/debug.h"
#include "../Engine/event.h"
#include "../Engine/world.h"
#include <ostream>

using namespace ppc;


BadCopRenderComponent::BadCopRenderComponent(sf::Image& image) : BadCopImage(image) {
    
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
    
    blackScreen = 0;
    
    alpha = 255;
    
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(0,0,size,size)))
        std::exit(-1);


    rectSourceSprite = new sf::IntRect(0, 0, size, size);
    
    sprite->setTexture(*texture);
    sprite->setTextureRect(*rectSourceSprite);
    sprite->setPosition(120, 0);
    sprite->setScale(1.5f, 1.5f);
    
    _willAnimate = true;
}

BadCopRenderComponent::~BadCopRenderComponent() {
    delete texture;
    delete sprite;
    delete rectSourceSprite;
}

void BadCopRenderComponent::renderPosition(sf::Vector2f pos) {
    sprite->setPosition(pos.x, pos.y);
}

void BadCopRenderComponent::setImageScale(float ScaleX, float ScaleY) {
    sprite->setScale(ScaleX, ScaleY);
}


void BadCopRenderComponent::animate() {
    
     if (_willAnimate) {
         if (rectSourceSprite->top == 6144) {
             blackScreen++;
             if (blackScreen > 20) alpha -= 12;
             sprite->setColor(sf::Color(255, 255, 255, alpha));

             //Wait time at end of animation
             if (blackScreen == 40)  {
                 _willAnimate = false;
                 World::quitDesktop();
                 
             }
             
         } else
             rectSourceSprite->top += size;
     
         texture->loadFromImage(BadCopImage, *rectSourceSprite);
         sprite->setTexture(*texture);
     }
}



void BadCopRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    if (!_willAnimate) return;
    target.draw(*sprite, states);
}

void BadCopRenderComponent::recieveMessage(msgType code) {
}

void BadCopRenderComponent::recieveMessage(ppc::Event ev) {

}
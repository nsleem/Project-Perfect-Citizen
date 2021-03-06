#include "Transition.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

Transition::Transition() {
    start_ = end_ = nullptr;
    transitionShape_.setFillColor(sf::Color::Black);
    transitionShape2_.setFillColor(sf::Color::Black);

}




Transition::~Transition() {

}




///////////////////////////////////////////////////////////////////////
// Set Up
///////////////////////////////////////////////////////////////////////

void Transition::setTextures(sf::Texture& start, sf::Texture& end) {
    start_ = &start;
    end_ = &end;
}




void Transition::setBounds(sf::FloatRect bounds) {
    transitionShape_.setPosition(bounds.left, 0);
    transitionShape_.setSize({bounds.width, 0});
    
    transitionShape2_.setPosition(bounds.left, bounds.height);
    transitionShape2_.setSize({bounds.width,0});

}




///////////////////////////////////////////////////////////////////////
// Transition Functionality
///////////////////////////////////////////////////////////////////////

float Transition::getTransitionPoint() const {
    return transitionPoint_;
}




void Transition::setTransitionPoint(float position) {
    //Set the position of the Transition
    transitionPoint_ = position;

    //Do onAdvance schtuff
    onAdvance();

    //Bounds check
    clipTransitionPoint();
}




void Transition::incrementTransition(float delta) {
    //Add delta to increment.
    transitionPoint_ += delta;

    //Do onAdvance schtuff
    onAdvance();
    
    //Bounds check
    clipTransitionPoint();
}




void Transition::decrementTransition(float delta) {
    //Simply negate delta and call increment
    incrementTransition(-1.0f * delta);
}




void Transition::draw(sf::RenderTarget& target,
                      sf::RenderStates states) const {
    target.draw(transitionShape_, states);
    target.draw(transitionShape2_, states);
}




///////////////////////////////////////////////////////////////////////
// Helper Functions
///////////////////////////////////////////////////////////////////////

void Transition::clipTransitionPoint() {
    if (transitionPoint_ > 1.0f) {
        transitionPoint_ = 1.0f;
    } else if (transitionPoint_ < 0.0f) {
        transitionPoint_ = 0.0f;
    }
}


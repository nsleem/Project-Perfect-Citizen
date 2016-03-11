//desktop.cpp
// Nader Sleem
#include "Window.h"
#include "NodeState.h"
#include "BaseFileType.h"

#include "desktop.h"
#include "debug.h"

ppc::Desktop::Desktop(WindowInterface& bkgndWin, NodeState& n) {
	style_ = nullptr;
	nodeState_ = new NodeState(n);

	windows_.push_back(&bkgndWin);
	desktopWindow_ = &bkgndWin;
	focused_ = desktopWindow_;
	
}

ppc::Desktop::Desktop(const Desktop& other) {
	this->style_ = other.style_;
	this->nodeState_ = other.nodeState_;
	this->windows_ = other.windows_;
	this->desktopWindow_ = other.desktopWindow_;
	this->focused_ = other.focused_;

}

ppc::Desktop::~Desktop() {
	if (style_ != nullptr) delete style_;
	if (nodeState_ != nullptr) delete nodeState_;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		delete *it;
	}
	focused_ = nullptr;
	desktopWindow_ = nullptr;
	windows_.clear();
}


bool ppc::Desktop::focusWindow(WindowInterface* wi) {
	DEBUGF("df", wi);
	//Keep desktopWindow_ in the back of the vector
	if (wi == this->desktopWindow_ || wi == nullptr) {
		this->focused_ = this->desktopWindow_;
		return false;
	}
	//while the itor is not desktopWindow_
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		//if we find the window to be focused
			//if it is not at the beginning, we have to put it there.
		if (*it == wi && it != windows_.begin()) {
			//keep swapping it w/ thing before until at front
			auto it2 = it;
			auto temp = it - 1;
			while (it2 != windows_.begin()) {
				auto tempWindow = *it2;
				*it2 = *temp;
				*temp = tempWindow;
				it2 = temp;
				if(temp != windows_.begin()) --temp;
			}
			this->focused_ = windows_.front();
			return true;
			//if it is already at the beginning, then focus it and 
			//stop looping.
		} else if(*it == wi && it == windows_.begin()) {
			this->focused_ = windows_.front();
			return true;
		}
	}
	return false;
}

void ppc::Desktop::draw(sf::RenderTarget& target, 
						sf::RenderStates states) const {

	//Draw the background image here first.
	//then:
	//Using reverse itors
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		target.draw(*(*it), states);
	}
}


void ppc::Desktop::addWindow(WindowInterface* wi){
	if (wi == nullptr || wi == this->desktopWindow_) return;

	//If the Window is already in the Desktop, we merely need
	//to focus it.
	if (focusWindow(wi)) return;

	//Otherwise, if wi is not a window in the desktop,
	//automatically put it at the front,
	//and focused is set to what was added
	focused_ = *(windows_.insert(windows_.begin(), wi));
}

void ppc::Desktop::destroyWindow(WindowInterface* wi) {
	if (wi == nullptr || wi == desktopWindow_) return;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == wi) {
			delete *it;
			cout << "found and deleted" << endl;
			windows_.erase(it);
			focusWindow(desktopWindow_);
			return;
		}
	}
}

void ppc::Desktop::setStyle(OSStyle* oss) {
	style_ = oss;
}

ppc::NodeState& ppc::Desktop::getNodeState() {
	return *nodeState_;
}

ppc::InputHandler& ppc::Desktop::getInputHandler() {
	return desktopWindow_->getInputHandler();
}

void ppc::Desktop::addBackgroundCmpnt(WindowInterface* wi, sf::Sprite& s) {
	WindowBkgndRenderCmpnt* wBRC = new WindowBkgndRenderCmpnt(s);
	wi->addRenderComponent(wBRC);
}

void ppc::Desktop::registerInput(sf::Event& ev) {
	//first check if the mouse clicked in the focused window.
	//if the window clicked in a window that wasnt focused,
	//then focus that window.
	//for any mouse event
	if (ev.type == sf::Event::MouseButtonPressed) {
		for (auto it = windows_.begin(); it != windows_.end(); ++it) {
			sf::FloatRect winBounds = (*it)->getBounds();
			if (winBounds.contains(float(ev.mouseButton.x), float(ev.mouseButton.y))) {
				focusWindow(*it);
                break;
			}
		}
	}

    if (ev.type == sf::Event::MouseMoved) {
        ev.mouseMove.x -= int(focused_->getPosition().x);
        ev.mouseMove.y -= int(focused_->getPosition().y);
    } else if ((ev.type == sf::Event::MouseButtonPressed) || (ev.type == sf::Event::MouseButtonReleased)){
        ev.mouseButton.x -= int(focused_->getPosition().x);
        ev.mouseButton.y -= int(focused_->getPosition().y);
    }
	
	focused_->registerInput(ev);

}

void ppc::Desktop::update(sf::Time& deltaTime){
	//No reverse itors needed
	for (size_t i = 0; i < windows_.size(); ) {
		windows_.at(i)->update(deltaTime);
		if (!windows_.at(i)->isOpen()) {
			delete windows_.at(i);
			windows_.erase(windows_.begin() + i);
			focusWindow(desktopWindow_);
		} else {
			++i;
		}

		//dont increment if you delete it
	}
}

void ppc::Desktop::refresh(sf::RenderStates states) {
	//Reverse itors needed
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		(*it)->refresh(states);
	}
}

bool ppc::Desktop::isMouseCollision(WindowInterface* wi,
	sf::Vector2i pos) {
	
	bool result = false;
	sf::Vector2f windowPos = wi->getPosition();
	sf::Vector2u windowDim = wi->getSize();
	
	if (pos.x >= windowPos.x && pos.x <= windowPos.x + windowDim.x) {
		if (pos.y >= windowPos.y && pos.y <= windowPos.y + windowDim.y) {
			result = true;
		}
	}

	return result;
}
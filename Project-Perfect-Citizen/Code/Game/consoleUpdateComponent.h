#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/updateComponent.h"
#include "buttonRenderComponent.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/NodeState.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Update Component for Console window
/// @author Alex Vincent
/// @details Parses and executes commands of the filetree
///////////////////////////////////////////////////////////////////////

class consoleUpdateComponent : public ppc::UpdateComponent {

private:
	ppc::NodeState& fileTree;
    bool canParse;
	string lastCommand;
    std::vector<string> commandVec;

public:
	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor linking it to a live fileTree
	///////////////////////////////////////////////////////////////////////
	consoleUpdateComponent(ppc::NodeState& ns);

	///////////////////////////////////////////////////////////////////////
	/// @brief No default constructor. A console needs a fileTree to live
	///////////////////////////////////////////////////////////////////////
	consoleUpdateComponent() = delete;

	///////////////////////////////////////////////////////////////////////
	/// @brief A flag switcher that lets this component parse console input
	///////////////////////////////////////////////////////////////////////
	void toggleParsing();

	///////////////////////////////////////////////////////////////////////
	/// @brief Converts the passed string into a useable vector that the
	/// function map will read
	///////////////////////////////////////////////////////////////////////
	void executeCommand(std::vector<string> cmd);

	///////////////////////////////////////////////////////////////////////
	/// @brief Default destructor
	///////////////////////////////////////////////////////////////////////
	~consoleUpdateComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief Overridden update function of all update components.
	/// Sends the vector command to the fileTree to be run.
	///////////////////////////////////////////////////////////////////////
	void update(sf::Time& deltaTime) override;

};
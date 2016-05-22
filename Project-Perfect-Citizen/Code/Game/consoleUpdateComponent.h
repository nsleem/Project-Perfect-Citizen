#pragma once

#include <SFML/System/Time.hpp>

#include "../Engine/updateComponent.h"

namespace ppc {
	class NodeState;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Update Component for Console window
/// @author Alex Vincent
/// @details Parses and executes commands of the filetree
///////////////////////////////////////////////////////////////////////

class consoleUpdateComponent : public UpdateComponent {

private:
	ppc::NodeState& fileTree;
    bool canParse;
	std::string lastCommand;
    std::vector<std::string> commandVec;

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
	void executeCommand(std::vector<std::string> cmd);

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


};
#pragma once

#include "../Engine/Network.h"
#include "../Engine/debug.h"

///////////////////////////////////////////////////////////////////////
/// @author Mark Biundo
/// @brief Builds procedurally generated PE levels based on a ruleset
/// @details This space is used for level design, containing several
///   handy functions for quickly building and modifying pipeline
///   extraction scenarios.
///////////////////////////////////////////////////////////////////////


namespace ppc {

class PipelineLevelBuilder {
public:
	///////////////////////////////////////////////////////////////////
	/// @brief A function that builds the first (example) level of the
	///   pipeline extraction
	/// @param [out]  Network  a network solution used for the pipeline
	///                        level.  The player's work is compared
	///                        against this.
	///////////////////////////////////////////////////////////////////
	static Network buildLevelOneNetworkSolution();

	/*
	static Network BuildLevelTwoNetwork();
	*/

private:

	static void populateLevelEdges(int start, int end, int numEdges, 
		Network& net, int suspLevel);



};

};
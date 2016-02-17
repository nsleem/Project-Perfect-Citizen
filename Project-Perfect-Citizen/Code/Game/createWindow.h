#pragma once

#include "../Engine/WindowInterface.h"
#include "../Engine/InputHandler.h"
#include "../Engine/NodeState.h"


namespace ppc {

WindowInterface* spawnConsole(InputHandler& ih, NodeState& ns, float x, float y, int w, int h);

};


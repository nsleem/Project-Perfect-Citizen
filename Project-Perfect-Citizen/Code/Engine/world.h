#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "desktop.h"

namespace ppc {


	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {

	private:

		sf::RenderWindow* screen_;
		ppc::Desktop currDesktop_;

    public:

		///////////////////////////////////////////////////////////////
		// Ctors
		///////////////////////////////////////////////////////////////
		World();
		World(sf::RenderWindow&);
		World(sf::RenderWindow&, ppc::Desktop&);

		///////////////////////////////////////////////////////////////
		// Dtor
		///////////////////////////////////////////////////////////////
		~World();

      /////////////////////////////////////////////////////////////////
      // Setters
      /////////////////////////////////////////////////////////////////


		void setGameScreen(sf::RenderWindow&);

		///////////////////////////////////////////////////////////////
		///@brief Set the Desktop currently used by World
		///////////////////////////////////////////////////////////////
		void setCurrDesktop(ppc::Desktop&);

		///////////////////////////////////////////////////////////////
		///@brief Returns a pointer to the Game Screen
		///////////////////////////////////////////////////////////////
		sf::RenderWindow* getGameScreen();

		///////////////////////////////////////////////////////////////
		///@brief Returns a pointer to the Current Desktop
		///////////////////////////////////////////////////////////////
		Desktop* getCurrDesktop();

		///////////////////////////////////////////////////////////////
		// Desktop Manipulation
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		///@brief Runs the main game loop with the given Desktop
		///////////////////////////////////////////////////////////////
		bool runDesktop(ppc::Desktop&);

		///////////////////////////////////////////////////////////////
		///@brief Runs the main game loop with the current Desktop
		///////////////////////////////////////////////////////////////
		bool runCurrDesktop();


		friend std::istream& operator>>(std::istream& in, World& world);
	};

	///////////////////////////////////////////////////////////////
	///@brief Loads in a Desktop from a file to the World
	///@details The imported Desktop becomes the new current 
	/// Desktop, while the old one (if there was one) is destroyed.
	///////////////////////////////////////////////////////////////
	std::istream& operator>>(std::istream& in, World& world);
};
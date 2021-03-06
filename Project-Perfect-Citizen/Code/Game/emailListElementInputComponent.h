#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <array>

#include "../Engine/inputComponent.h"
#include "../Engine/subject.h"

namespace sf {
	class Image;
};

namespace ppc {
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Input Component for an email element in the inbox
	/// @author Alex Vincent 
	/// @details Listens for clicks on an email list element and opens
	/// the corresponding window for the email clicked on
	///////////////////////////////////////////////////////////////////////
	class Email;
	class Desktop;
	class InputHandler;

	class emailListElementInputComponent : public ppc::InputComponent {
	private:

		///////////////////////////////////////////////////////////////////////
		/// @brief FloatRect bounds of the surrounding list element box
		///////////////////////////////////////////////////////////////////////
		sf::FloatRect boxRect;

		///////////////////////////////////////////////////////////////////////
		/// @brief Sprite sheet of the button
		///////////////////////////////////////////////////////////////////////
		sf::Image& buttonSheet;
		sf::Clock mouseClock;
		sf::Int32 mouseTime;

		///////////////////////////////////////////////////////////////////////
		/// @brief Returns true if the mouse clicked in the boxRect
		///////////////////////////////////////////////////////////////////////
		bool isCollision(sf::Vector2i);

		///////////////////////////////////////////////////////////////////////
		/// @brief The object containing the content of the email
		///////////////////////////////////////////////////////////////////////
		ppc::Email* emailToOpen;

		///////////////////////////////////////////////////////////////////////
		/// @brief reference to the desktop to open a new window
		///////////////////////////////////////////////////////////////////////
		ppc::Desktop& theDesktop;
		ppc::Subject onRead_;

	public:

		///////////////////////////////////////////////////////////////////////
		/// @brief No default ctor - needs elements to be passed in.
		///////////////////////////////////////////////////////////////////////
		emailListElementInputComponent() = delete;

		///////////////////////////////////////////////////////////////////////
		///@brief Useable ctor which constructs a email list element
		///@param The desktop to make a window
		///@param The input handler of the window it is in
		///@param The email to read from when opening a new window
		///@param The button sprite sheet to make the new window's close button
		///@param The bounding box of this list element to detect click input
		///////////////////////////////////////////////////////////////////////
		emailListElementInputComponent(ppc::Desktop& dT, ppc::InputHandler& ih, ppc::Email* eM, sf::Image& buttonSheet, sf::FloatRect rect);

		///////////////////////////////////////////////////////////////////////
		///@brief Adds the input handler to the component. Also sets up the
		/// neccessary subject and observers for this component.
		///////////////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler& ih);

		///////////////////////////////////////////////////////////////////////
		///@breif Sets the FloatRect of the sprite associated with this cmpnt.
		///@details Must pass in the globad bounds of the sprite.
		///////////////////////////////////////////////////////////////////////
		void setFloatRect(sf::FloatRect rect);

		virtual ~emailListElementInputComponent();

		virtual bool registerInput(ppc::Event ev) override;
		////
		///@brief gets the subject
		////
		ppc::Subject& onRead();

	};

};
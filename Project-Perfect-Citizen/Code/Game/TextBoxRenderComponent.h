#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"


namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Label Render Component for a text label
	/// @author Michael Lowe
	/// @details The buttonRenderComponent is a basic packaged subclass
	///     extension of RenderComponent, make specifically to handle
	///     all generic "X" button related drawing/animating parts that
	///     also broadcast and recieve messages from an input handler.
	///		Stick this onto an entity to give it this functionality.
	///////////////////////////////////////////////////////////////////////
	class TextBoxRenderComponent : public ppc::RenderComponent {
	private:
		sf::Text* text;
		sf::Text* outline;
		sf::Font font;
		sf::Sprite* cursorSprite;
		sf::Texture* cursorTexture;
		std::string labelString;
		bool isMasked = false;
		bool renderCursor = true;


	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @param f is the font to be used.
		/// @param x is the x position of the font relative to the entity
		/// @param y is the y position of the font relative to the entity
		///////////////////////////////////////////////////////////////////////
		TextBoxRenderComponent(sf::Font& f, sf::Color c, float x, float y, int s, std::string str);

		~TextBoxRenderComponent();

		sf::Vector2f getTextPosition() const { return outline->getPosition(); }

		std::string getString();

		void updateLabelString(std::string str, unsigned int);

		void updateLabelPosition(float x, float y);

		void updateLabelSize(int s);

		void setIsMasked(bool);

		void toggleCursorRender();

		void setCursorRender(bool);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	};

	bool blink_cursor(TextBoxRenderComponent* tbr, ppc::Event ev);

};
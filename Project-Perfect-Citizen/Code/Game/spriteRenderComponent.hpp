#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Render Component for a text field
	/// @author Micahel Lowe
	/// @details Draws generic sprites
	///////////////////////////////////////////////////////////////////////
	class spriteRenderComponent : public ppc::RenderComponent {
	private:
		sf::Sprite* sprite;
		sf::Texture* texture;
		sf::Image& image;
		const int size = 128;

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @param w is width
		/// @param h is height
		///////////////////////////////////////////////////////////////////////
		spriteRenderComponent(sf::Image& i, float x, float y, float w, float h);

		void setRenderScale(sf::Vector2f vec);
		void setRenderPosition(sf::Vector2f vec);

		~spriteRenderComponent();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	};
};
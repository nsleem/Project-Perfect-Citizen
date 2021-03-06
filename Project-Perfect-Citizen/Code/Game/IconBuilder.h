#pragma once

#include <string>
#include "../Engine/Entity.h"

#include "mousePressButton.h" //needed
#include "iconInputComponent.h" //needed

namespace sf {
	class Image;
	class Font;
};

namespace ppc {

	class Desktop;
	class InputHandler;
	class Database;
	class Inbox;
	class notificationRenderComponent;

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for Icons
	/// @author Nader Sleem
	/// @details A package with API function calls allowing for individual
	/// creations and augmentations of a Icons.
	///////////////////////////////////////////////////////////////////////
	class IconBuilder {
	private:

		ppc::Desktop* dt;
		ppc::InputHandler* ih;
		ppc::Database* db;
		ppc::Inbox* ib;
		bool renderNotifications;
		sf::Image* buttonSheet;

		sf::Font* font;
		sf::Color fontColor;

		std::string label;
		std::string isBeingPressed;

		iconInputComponent::IconType iconType;

		int sheetX;
		int sheetY;
		int width;
		int frames;

		float size;
		float animationSpeed;

		float posX;
		float posY;

	public:
		///////////////////////////////////////////////////////////////
		///@brief CTor
		///////////////////////////////////////////////////////////////
		IconBuilder();

		///////////////////////////////////////////////////////////////
		///@brief Dtor
		///////////////////////////////////////////////////////////////
		~IconBuilder();

		///////////////////////////////////////////////////////////////
		///@brief Sets the sprite given the indices in the spritesheet
		///////////////////////////////////////////////////////////////
		void setSpritebyIndicies(int x, int y, int r, int f);

		///////////////////////////////////////////////////////////////
		///@brief Sets the sprite given two sprites
		///////////////////////////////////////////////////////////////
		void setSprites(sf::Sprite&, sf::Sprite&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the size of the icon's text
		///////////////////////////////////////////////////////////////
		void setSize(float s);


		void setIconType(ppc::iconInputComponent::IconType type);

		///////////////////////////////////////////////////////////////
		///@breif Sets the desktop for the Icon
		///////////////////////////////////////////////////////////////
		void setDesktop(ppc::Desktop&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the input handle for the Icon
		///////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the button sheet used for the Icon
		///////////////////////////////////////////////////////////////
		void setButtonSheet(sf::Image&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the database for the Icon
		///////////////////////////////////////////////////////////////
		void setDatabase(ppc::Database&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the inbox for the Icon
		///////////////////////////////////////////////////////////////
		void setInbox(ppc::Inbox&);

		///////////////////////////////////////////////////////////////
		///@breif Sets the text, font, and color of an icon's label.
		/// Default color is white.
		///////////////////////////////////////////////////////////////
		void setText(std::string, sf::Font&, sf::Color);

		///////////////////////////////////////////////////////////////
		///@breif Sets the animation speed for the Icon
		///////////////////////////////////////////////////////////////
		void setAnimSpeed(float spd);

		///////////////////////////////////////////////////////////////
		///@breif Sets the position for the Icon
		///////////////////////////////////////////////////////////////
		void setPosition(float x, float y);

		///////////////////////////////////////////////////////////////
		///@breif Sets the position for the Icon
		///////////////////////////////////////////////////////////////
		void setPosition(sf::Vector2f pos);

		void setRenderNotifications(bool);

///////////////////////////////////////////////////////////////////////
/// @brief Returns the constructed icon
///////////////////////////////////////////////////////////////////////
		void create(ppc::Entity&);
	};

	template<class T>
	void createWithEventFunc(IconBuilder& builder, Entity& e, T* target, bool(*func)(T *, ppc::Event)) {

		builder.create(e);
		size_t s = e.cmpntCount();
		ppc::mousePressButton* mpb = dynamic_cast<mousePressButton*>(e.getComponent(s - 1));

		if (mpb != nullptr) {
			setOnPress(mpb, target, func);
		} else {
			return;
		}
	}


};
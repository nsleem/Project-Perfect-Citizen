#pragma once

#include <string>
#include <iostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

//#include "iconInputComponent.h"
#include "../Engine/inputComponent.h"
#include "../Engine/NodeState.h"
#include "../Engine/subject.h"
#include "../Engine/FreeFunctionObserver.h"

namespace sf {
	class Image;
};

namespace ppc {
	class Desktop;
	class WindowInterface;
	class InputHandler;

    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated input component for explorer files
    /// @author Alex Vincent 
    /// @details Functionality: when clicked opens the corresponding file 
    ///////////////////////////////////////////////////////////////////////
	class explorerFileInputComponent : public ppc::InputComponent {

	private:

		Desktop& theDesktop_;
		WindowInterface* containingWindow_;
		NodeState* theFileTree_;
		sf::FloatRect buttonRect;
		sf::Image& buttonSheet_;
		std::string fileName;
		sf::Clock mouseClock;
		sf::Int32 mouseTime;
		bool isCollision(sf::Vector2i);

		Subject onPress_;
		Subject onDoublePress_;
		Subject onRelease_;

	public:

		explorerFileInputComponent() = delete;
		///////////////////////////////////////////////////////////////////////
		///@brief Ctor
		///////////////////////////////////////////////////////////////////////
		explorerFileInputComponent(Desktop& dt, WindowInterface* cW,
			ppc::InputHandler& ih, NodeState* ns, sf::Image& bS, sf::FloatRect rect, std::string directoryName);

		template <class T>
		friend void setOnPress(explorerFileInputComponent* mpb,
			T* objPtr,
			bool(*onPress)(T*, Event));

		///////////////////////////////////////////////////////////////////////
		//SETTERS
		///////////////////////////////////////////////////////////////////////

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

		virtual ~explorerFileInputComponent();
		virtual bool registerInput(Event ev) override;


		Subject& onClick() { return onPress_; };
		Subject& onDblClick() { return onDoublePress_; };
		Subject& onRelease() { return onRelease_; };
		bool andy_flag_file(Desktop*, ppc::Event);

		void openFile();

		NodeState* getFileNodeState();
		std::string getFileName();
		Desktop* getFileDesktop();
		

	};

	template<class T>
	inline void setOnPress(explorerFileInputComponent* eFIC, T * objPtr, bool(*onPress)(T *, sf::Event &)) {

		FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onPress, objPtr);

		eFIC->onRelease().addObserver(fnObsvr);

	}

	bool open_file(explorerFileInputComponent*, ppc::Event);
	bool flag_file(explorerFileInputComponent*, ppc::Event);
	bool submitFiles(ppc::Desktop* ptr, ppc::Event ev);
	//bool spawnPromptMessage(ppc::explorerFileInputComponent* ptr, ppc::Event);
	//bool (ppc::Desktop* ptr, ppc::Event ev);
	bool spawnPromptMessage(ppc::explorerFileInputComponent * ptr, ppc::Event);
};



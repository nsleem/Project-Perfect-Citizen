//desktop.h
// Nader Sleem

#pragma once

#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "Window.h"

//temporary typedefs for classes/types not defined yet
typedef int OSStyle;
typedef char FileTree;
typedef float FileState;

namespace ppc {
	///////////////////////////////////////////////////////////////////////
///@brief Manages a series of Windows, an associated file tree and
/// OS style.
///@details Desktops drawn on the screen will also have their
/// containing Windows drawn and managed on the screen. In 
/// addition, each Desktop has its own unique FileTree and
/// OS style.
///@author Nader Sleem
///@todo Hook up this class with FileTree and OSStyle when they are
/// done
///////////////////////////////////////////////////////////////////////
	class Desktop : public sf::Drawable {

///////////////////////////////////////////////////////////////////////
// PRIVATE FIELDS
///////////////////////////////////////////////////////////////////////
	private:
///////////////////////////////////////////////////////////////////////
///@brief The OS style of this Desktop
///////////////////////////////////////////////////////////////////////
		OSStyle* style_;

///////////////////////////////////////////////////////////////////////
///@brief The FileTree structure of this Desktop
///////////////////////////////////////////////////////////////////////
		FileTree* fileTree_;

///////////////////////////////////////////////////////////////////////
///@brief The container of all WindowInterfaces/Windows
///////////////////////////////////////////////////////////////////////
		std::vector<WindowInterface*> windows_;

		//ask what this is and about its def in the uml
		//map<string, (WindowInterface*)(Node*)> extensionMap_;


///////////////////////////////////////////////////////////////////////
///@brief Brings the desired Window into focus.
///@details To be called when a specificed Window should be 
/// drawn above all others. The Window is then moved to the
/// front of the Window container, ahead of all other Windows,
/// but the ordering of the remaining Windows is kept.
/// @param wi A WindowInterface* which points to the Window that
/// is to be focused on.
///////////////////////////////////////////////////////////////////////
		void focusWindow(WindowInterface*);

///////////////////////////////////////////////////////////////////////
///@brief Draws the Desktop & all its Windows.
///
///@param in target The object that is to be drawn on.
///@param in states Used to manipulate draw calls.
///////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

///////////////////////////////////////////////////////////////////////
//PUBLIC FIELD
///////////////////////////////////////////////////////////////////////
	public:

///////////////////////////////////////////////////////////////////////
// CTORs & DTOR
///////////////////////////////////////////////////////////////////////
		
		//No default CTor
		Desktop() = delete;
///////////////////////////////////////////////////////////////////////
///@brief Desktop Constructor.
///@details Creates a Desktop with a given FileTree.
///@param ft The FileTree object to be associated with the Desktop.
///
///@todo Add param for OSStyle?.
///////////////////////////////////////////////////////////////////////
		Desktop(FileTree& ft);

		
///////////////////////////////////////////////////////////////////////
///@brief Copy Ctor
///////////////////////////////////////////////////////////////////////
		Desktop(const Desktop& other);

///////////////////////////////////////////////////////////////////////
///@brief The virtual Dtor
///////////////////////////////////////////////////////////////////////
		virtual ~Desktop();

///////////////////////////////////////////////////////////////////////
///@brief Adds a new Window to the Desktop.
///@details When a new Window is added to the Desktop, it is 
/// automatically focused on.
///@param wi A WindowInterface* which points to the Window to be added.
/// If the pointer is nullptr, nothing happens.
///@post Desktop contains 1 more Window.
///////////////////////////////////////////////////////////////////////
		void addWindow(WindowInterface*);

///////////////////////////////////////////////////////////////////////
///@brief Removes a Window from the Desktop.
///@param wi  A WindowInterface* which points to the Window to be 
/// deleted. If the pointer is nullptr, nothing happens.
///@post Desktop contains 1 less Window.
///////////////////////////////////////////////////////////////////////
		void destroyWindow(WindowInterface*);

///////////////////////////////////////////////////////////////////////
///@brief Sets the Desktop to the given OS style.
///@param oss The style the Desktop is to be associated with.
///////////////////////////////////////////////////////////////////////
		void setStyle(OSStyle*);

///////////////////////////////////////////////////////////////////////
///@brief Returns the root of the FileTree in the Desktop.
///////////////////////////////////////////////////////////////////////
		FileState& getRoot();

///////////////////////////////////////////////////////////////////////
///@brief Reacts to Input for all Windows, and all objects
/// in the Windows.
///////////////////////////////////////////////////////////////////////
		void registerInput(sf::Event& ev);

///////////////////////////////////////////////////////////////////////
///@brief Updates all Windows and all objects in the Windows.
///@param deltaTime The time the object needs to catch up with.
///////////////////////////////////////////////////////////////////////
		void update(sf::Time&);

///////////////////////////////////////////////////////////////////////
///@brief Refreshes all Windows of the Desktop, so they are ready
/// to be drawn again.
///@param states Used to manipulate draw.
///////////////////////////////////////////////////////////////////////
		void refresh(sf::RenderStates states = sf::RenderStates());
			
	};
};
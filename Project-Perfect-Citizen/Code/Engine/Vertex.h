#ifndef VERTEX_H
#define VERTEX_H

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../Game/characterRender.hpp"
#include "../Game/PipelineCharacter.h"

namespace ppc {
	class DraggableInput;
	class InputHandler;


///////////////////////////////////////////////////////////////////////
/// @brief Defines a Vertes for the Network
/// @details Vertices contail data of a Pipeline Extraction Character.
///		They also have a color and show the 2 initials of characters
///		they represent. At the moment, a vertex is represented by
///     a sf::CircleShape.
///////////////////////////////////////////////////////////////////////
class Vertex: public sf::Drawable, public sf::Transformable {

private:
    
    ////////  SCALING FOR  MARK    ///////////
    float scale = 0.9f;
    //////////////////////////////////////////

	sf::Color color_;

	sf::Text text_;
	sf::Font font_;
	static const int fontSize_;
	
	PipelineCharacter char_;
    characterRender rend_;

	sf::CircleShape circ_;
    sf::RectangleShape rect_;
    sf::RectangleShape bgrect_;
	static const float radius_;
	sf::FloatRect bounds_;
    
	bool isSelected_;

public:
	///////////////////////////////////////////////////////////////////////
	///@brief Default Ctor
	///////////////////////////////////////////////////////////////////////
	Vertex();
	
	///////////////////////////////////////////////////////////////////////
	///@brief Copy Ctor
	///////////////////////////////////////////////////////////////////////
	Vertex(const Vertex& other);

	///////////////////////////////////////////////////////////////////////
	///@brief Copy operator=
	///////////////////////////////////////////////////////////////////////
	Vertex& operator=(const Vertex& other);

	///////////////////////////////////////////////////////////////////////
	///@brief Dtor
	///////////////////////////////////////////////////////////////////////
	virtual ~Vertex();

	///////////////////////////////////////////////////////////////////////
	///@brief Gets the color of the vertex.
	///////////////////////////////////////////////////////////////////////
	sf::Color getColor() const;

	///////////////////////////////////////////////////////////////////////
	///@brief Sets the color of a vertex
	///@param The desired sf::Color.
	///////////////////////////////////////////////////////////////////////
	void setColor(sf::Color);

	///////////////////////////////////////////////////////////////////////
	///@brief Returns the position of the center of the Vertex
	///////////////////////////////////////////////////////////////////////
	sf::Vector2f getPosCenter() const;

	///////////////////////////////////////////////////////////////////////
	///@brief Gets the local bounds of the Vertex
	///////////////////////////////////////////////////////////////////////
	sf::FloatRect getLocalBounds() const;

	///////////////////////////////////////////////////////////////////////
	///@brief Gets the global bounds of the Vertex
	///////////////////////////////////////////////////////////////////////
	sf::FloatRect getGlobalBounds() const;

	///////////////////////////////////////////////////////////////////////
	///@brief Returns the PipelineCharacter associated with the Vertex.
	///////////////////////////////////////////////////////////////////////
	PipelineCharacter getCharacter() const;

	///////////////////////////////////////////////////////////////////////
	///@brief Sets the PipelineCharacter associated with the Vertex.
	///////////////////////////////////////////////////////////////////////
	void setCharacter(PipelineCharacter);

	///////////////////////////////////////////////////////////////////////
	///@brief Sets the sf::Font of the text on the Vertex.
	///////////////////////////////////////////////////////////////////////
	void setTextFont(sf::Font);

	///////////////////////////////////////////////////////////////////////
	///@brief Loads/Sets the sf::Font of the text on the Vertex.
	///////////////////////////////////////////////////////////////////////
	void setTextFontLoad(std::string font);

	///////////////////////////////////////////////////////////////////////
	///@brief Sets up the DraggableInput's observers for the given
	/// InputHandler.
	///@param di DraggableInput for the Vertex.
	///@param ih InputHandler to be associated with the DraggableInput.
	///////////////////////////////////////////////////////////////////////
	void applyDraggable(ppc::DraggableInput&,ppc::InputHandler&);


	void selectVert();

	void deselectVert();

	bool isSelected();

	///////////////////////////////////////////////////////////////////////
	///@brief Definition of how to draw a Vertex.
	///////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;

};


};      //End namespace mdg


#endif  //End VERTEX_H

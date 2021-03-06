#pragma once

#include <array>
#include <vector>
#include <map>

#include "../Engine/inputComponent.h"
#include "../Engine/subject.h"
#include "../Engine/event.h"

#include "FloppySequence.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a Floppy
/// @author Alex Vincent
/// @details This component recieves a FloppyEvent and tells
/// floppy render component and the text box what to display.
///////////////////////////////////////////////////////////////////////

namespace ppc {
	class mousePressButton;
	class TextDisplayRenderComponent;
	class buttonRenderComponent;

	class FloppyInputComponent : public ppc::InputComponent {
	private:
		unsigned int sequence;
		unsigned int frame;
		Subject onSequenceEnd_;

		buttonRenderComponent* floppyBtnRndr = nullptr;
		mousePressButton* floppyBtnInpt = nullptr;
		TextDisplayRenderComponent* floppyTxtRndr = nullptr;


		///////////////////////////////////////////////////////////////////////
		/// @brief Initializes the table of what Floppy says and how he emotes
		///////////////////////////////////////////////////////////////////////
		void initializeFloppyDict();

		//void initTimerDisableEvents();
		//void initTimerResetEvents();

	public:

		FloppyInputComponent();
		virtual ~FloppyInputComponent();

		

		static std::vector<FloppySequence> floppyDictionary;

		///////////////////////////////////////////////////////////////////////
		/// Emum of Floppy Sequence names to integers
		///////////////////////////////////////////////////////////////////////
		enum FloppySequenceName {
            Welcome = 0,
            Pipeline,
			Connections,
			SelectEdge,
			DeleteEdge,
			TempFix,
			Goal,
			ColorChange,
			Suspicion,
			Center,
			Submission,
			Feedback,
			DesktopStart,
			Email,
			Explorer,
			Passwords,
            Unlocked,
			SuspFolder,
			Scanning,
			DeskSubmission,
			Wrapup,
			AltStart,
            AltWelcome = AltStart,
            AltPipeline,
            AltConnections,
            AltSelectEdge,
            AltDeleteEdge,
            AltTempFix,
            AltGoal,
            AltColorChange,
            AltSuspicion,
            AltCenter,
            AltSubmission,
            AltFeedback,
            AltDesktopStart,
            AltEmail,
            AltExplorer,
            AltPasswords,
            AltUnlocked,
            AltSuspFolder,
            AltScanning,
            AltDeskSubmission,
            AltWrapup
		};


		static std::map<FloppySequenceName, std::vector<ppc::Event>> TimerDisableEvents;
		static std::map<FloppySequenceName, std::vector<ppc::Event>> TimerResetEvents;

        static bool initialized;
		
		///////////////////////////////////////////////////////////////////////
		/// Basic Getters
		///////////////////////////////////////////////////////////////////////
		unsigned int getFrame();
		unsigned int getSequence();
		FloppySequenceName getSeqName();

		///////////////////////////////////////////////////////////////////////
		/// Basic Setters
		///////////////////////////////////////////////////////////////////////
		void setFrame(unsigned int);
		void setSequence(unsigned int s, unsigned int f = 0);
	

		///////////////////////////////////////////////////////////////////////
		/// Basic incrementers and decrementers (by one)
		///////////////////////////////////////////////////////////////////////
		void advanceFrame();
		void regressFrame();
		void advanceSequence();
		void regressSequence();
        
        virtual bool registerInput(Event ev) override;

		Subject& onSequenceEnd() { return onSequenceEnd_; };

		void setFloppyButtonRenderCmpt(buttonRenderComponent*);
		void setFloppyButtonInputCmpt(mousePressButton*);
		void setFloppyTextRenderCmpt(TextDisplayRenderComponent*);

		void setFloppyButton(bool);

	};

	////////////////////////////////////////////////////////////////
	/// @brief Accepts a generic floppy type, saves the frame and
	/// sequence for future use, and then passes that event to
	/// the entity
	/// @param Pointer to Floppy's input component
	/// @param A FloppyType'd event with a set frame and sequence
	////////////////////////////////////////////////////////////////
	bool summonFloppyDialog(FloppyInputComponent*, ppc::Event);
 
	////////////////////////////////////////////////////////////////
	/// @brief Accepts a generic button type, increments the saved frame
	/// and sends a new event to the entity
	////////////////////////////////////////////////////////////////
	bool incrementFloppyDialog(FloppyInputComponent*, ppc::Event);

    bool enableFloppyDialog(FloppyInputComponent*, ppc::Event);

};

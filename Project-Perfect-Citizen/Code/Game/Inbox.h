#pragma once

#include <vector>
#include <string>
#include "../Engine/subject.h"

///////////////////////////////////////////////////////////////////////
/// @author Alex Vincent
/// @brief A singleton structure to a desktop that contains emails
/// @details Contains a vector of emails to which can be added to
/// the email application on the desktop. Each desktop should only
/// have one Inbox in theory.
///////////////////////////////////////////////////////////////////////

namespace ppc {
	class Email;


	class Inbox {

	public:

		///////////////////////////////////////////////////////////////////////
		///@brief Default constructor
		///////////////////////////////////////////////////////////////////////
		Inbox();
        
        ///////////////////////////////////////////////////////////////////////
        ///@brief Destructor
        ///////////////////////////////////////////////////////////////////////
        ~Inbox();

		///////////////////////////////////////////////////////////////////
		// ACCESSORS - Simple Getters
		///////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		///@brief Returns true/false depending on if the email vector is empty.
		///////////////////////////////////////////////////////////////////////
		bool isEmpty();

		///////////////////////////////////////////////////////////////////////
		///@brief Returns the email at the designated index in the vector
		///@note It is the caller's responsibility to ensure the position to which
		/// they're accessing is non-null. 
		///////////////////////////////////////////////////////////////////////
		ppc::Email* getEmailAt(int position);

		///////////////////////////////////////////////////////////////////////
		///@brief Simple getter of the email vector size
		///////////////////////////////////////////////////////////////////////
		int getInboxSize();

		///////////////////////////////////////////////////////////////////
		// MUTATORS
		///////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		///@brief Adds the designated email to the end of the vector list
		///////////////////////////////////////////////////////////////////////
		void addEmailToList(ppc::Email* email);

		///////////////////////////////////////////////////////////////////////
		///@brief Removes the email from the vector as the designated index
		///////////////////////////////////////////////////////////////////////
		void removeEmailFromList(int position);
        
        int getMaxSize();
		ppc::Subject& getInboxSubject();
		int getUnreadEmailCount();

	protected:
		std::vector<ppc::Email*> messageList;
        int maxSize = 18;
	private:
		ppc::Subject inboxSubject_;
	};

}
#include "Inbox.h"
#include "Email.h"

using namespace ppc;

Inbox::Inbox() {}

Inbox::~Inbox() {
	for (auto it = messageList.begin(); it != messageList.end(); ++it) {
		delete *it;
    }
    messageList.clear();
}

bool Inbox::isEmpty() { return messageList.empty(); }

Email* Inbox::getEmailAt(int pos) { return messageList.at(pos); }

int Inbox::getInboxSize() { return messageList.size(); }

void Inbox::addEmailToList(Email* newEmail) { messageList.push_back(newEmail); }

void Inbox::removeEmailFromList(int position) { 
	messageList.erase(messageList.begin()+position); 
}

int Inbox::getMaxSize(){
    return maxSize;
}

ppc::Subject& ppc::Inbox::getInboxSubject()
{
	return inboxSubject_;
}

int ppc::Inbox::getUnreadEmailCount()
{
	int count = 0;
	for (auto iter = messageList.begin(); iter != messageList.end(); iter++) {
		if ( (*iter)->getVisible() == true) {
			if ((*iter)->getReadFlag() == false) {
				count++;
			}
		}
	}
	return count;
}



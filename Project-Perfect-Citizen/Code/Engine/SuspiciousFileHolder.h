#pragma once
#include "BaseFileType.h"
#include <iostream>
#include <string>
#include <vector>
#include"WindowInterface.h"


namespace ppc {
	class SuspiciousFileHolder {
	private:
		SuspiciousFileHolder() = delete;
		~SuspiciousFileHolder() = delete;
		const unsigned int MAX_SIZE_ = 3;
		static std::vector<ppc::BaseFileType*> bftVector_;
		static ppc::WindowInterface* susWindow_;
		//static std::vector<ppc::SuspiciousFileHolder*> susVec_;
		static int staticCount_;
		//is he innocent?
		static int goodThreshold_;
		//is he guilty?
		static int badThreshold_;
		static bool guilty_; 
		//suspicion score of the last file marked with TreeCommand::scan
		static int susScore_;

		static int finalScore_;

	public:
        static Subject onChange;
		static std::vector<ppc::BaseFileType*>& getBftVector();
		static void flagFile(ppc::BaseFileType* file);
		static unsigned int getFileSuspicion(int element);
		static unsigned int getTotalSucpicion();
		static void printSuspiciousVector();
		static void setWindow(ppc::WindowInterface* sWindow);
		static ppc::WindowInterface* getWindow();
		//static ppc::SuspiciousFileHolder* getSusVecElement(int element);
		static int getStaticCount();
		static bool isInFileHolder(ppc::BaseFileType* file);
		//static int pushWindow(ppc::SuspiciousFileHolder* fileHolder);
		static ppc::BaseFileType* getBFTVectorElement(unsigned int element);
		static void submitFiles();
		static void clearFiles();
		static void clearFile(std::string doomedFile);
		static void setSusScore(int score);
		static bool isGuilty();
		static int getFinalScore();
	};
};

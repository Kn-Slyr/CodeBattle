#ifndef __MACRO_FOR_PLAY_h__
#define __MACRO_FOR_PLAY_h__

#include <string>

#define PLAYER0 0
#define PLAYER1 1
#define DRAW -1

#define CODE '#'

namespace {
	class CodeReader
	{
	public :
		static const std::string TIMEOVER;
		static const std::string MISSPLAY;
		static const std::string GAMEOVER;
	};

	const std::string CodeReader::TIMEOVER = "#TIMEOVER";
	const std::string CodeReader::MISSPLAY = "#MISSPLAY";
	const std::string CodeReader::GAMEOVER = "#GAMEOVER";
}
#endif

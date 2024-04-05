//
// Word.h
//

#ifndef WORD_H
	#define WORD_H

	#include <map> // std::map
	#include <string> // std::string, std::getline

	class Dictionary {
		public:
			Dictionary(void);
			void print(void) const;
			std::map<int, std::string> dict;
	};
#endif
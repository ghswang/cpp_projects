//
// Word.h
//

#ifndef WORD_H
	#define WORD_H

	#include <map>
	#include <string>

	class Dictionary {
		public:
			Dictionary(void);
			void print(void) const;
			std::map<int, std::string> dict;
	};
#endif
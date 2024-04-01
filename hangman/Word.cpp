//
// Word.cpp
//

#include "Word.h"
#include <iostream>
using namespace std;

Dictionary::Dictionary(void) {
	dict[0] = "o f t e n";
	dict[1] = "r a k e d";
	dict[2] = "a p p l e";
	dict[3] = "u r b a n";
	dict[4] = "h e a r t";
	dict[5] = "s t a t e";
	dict[6] = "t r u s t";
	dict[7] = "t h e i f";
	dict[8] = "a l o n g";
	dict[9] = "m o n e y";
	dict[10] = "w a v e d";
	dict[11] = "g r o w s";
	dict[12] = "b l o a t";
	dict[13] = "q u i e t";
	dict[14] = "i n c e l";
	dict[15] = "p r i c k";
	dict[16] = "f o u n d";
	dict[17] = "m o u n t";
	dict[18] = "l o a t h";
	dict[19] = "k i c k s";
	dict[20] = "f r i a r";
	dict[21] = "t h e r e";
	dict[22] = "n a k e d";
	dict[23] = "a o r t a";
	dict[24] = "b l a s t";
	dict[25] = "b r a v e";
	dict[26] = "m o l a r";
	dict[27] = "s o l a r";
	dict[28] = "d e v i l";
	dict[29] = "i m a g e";
	dict[30] = "c o u r t";
	dict[31] = "f o r t y";
	dict[32] = "g r i n d";
	dict[33] = "h e a v y";
	dict[34] = "s h o u t";
	dict[35] = "s k a t e";
	dict[36] = "l e v e r";
	dict[37] = "n e v e r";
	dict[38] = "b u i l d";
	dict[39] = "a r o s e";
	dict[40] = "a r i s e";
	dict[41] = "a g a p e";
	dict[42] = "a v i a n";
	dict[43] = "w h e a t";
	dict[44] = "c l a s p";
	dict[45] = "b o a s t";
	dict[46] = "t o a s t";
	dict[47] = "r o a s t";
	dict[48] = "m o i s t";
	dict[49] = "s t a s h";
}

void Dictionary::print(void) const {
	for (auto& i : dict) {
		cout << i.first << ": " << i.second << endl;
	}
	cout << endl;
}

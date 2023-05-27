#include "Tools.h"
#include <iostream>
#include <string>
using namespace std;
int SearchString(string str, char c) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == c)return i;
	}
	return -1;
}
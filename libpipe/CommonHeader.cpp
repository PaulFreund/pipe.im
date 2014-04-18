//======================================================================================================================

#include "CommonHeader.h"
using namespace std;

//======================================================================================================================

tstring timplode(const vector<tstring>& fragments, const TCHAR delimiter) {
	tstring result;

	for(size_t i = 0, c = fragments.size(); i < c; i++) {
		result.append(fragments[i]);
		if(i < (c - 1)) {
			result += delimiter;
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------------


vector<tstring> texplode(const tstring& data, const TCHAR delimiter) {
	vector<tstring> result;

	tstring fragment;
	for(auto it = begin(data); it != end(data); it++) {
		if((*it) == delimiter) {
			if(!fragment.empty()) {
				result.push_back(fragment);
				fragment.clear();
			}
		}
		else {
			fragment += (*it);
		}
	}

	if(!fragment.empty()) {
		result.push_back(fragment);
	}

	return result;
}

//======================================================================================================================

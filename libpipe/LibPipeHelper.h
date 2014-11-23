//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

//======================================================================================================================

inline std::shared_ptr<PipeArray> newArray(PipeArray&& data = PipeArray {}) {
	return std::make_shared<PipeArray>(std::move(data));
}

inline PipeArrayPtr parseArray(const tstring& data) {
	tstring err;
	PipeArrayPtr result = std::make_shared<PipeArray>(PipeJson::parse(data, err).array_items());
	if(!err.empty()) { throw err; }
	return result;
}

inline tstring dumpArray(const PipeArray& array) { return std::move(PipeJson(array).dump()); }
inline tstring dumpArray(PipeArrayPtr array) { return std::move(dumpArray(*array)); }

//----------------------------------------------------------------------------------------------------------------------

inline std::shared_ptr<PipeObject> newObject(PipeObject&& data = PipeObject {}) {
	return std::make_shared<PipeObject>(std::move(data));
}

inline PipeObjectPtr parseObject(const tstring& data) {
	tstring err;
	PipeObjectPtr result = std::make_shared<PipeObject>(PipeJson::parse(data).object_items());
	if(!err.empty()) { throw err; }
	return result;
}

inline tstring dumpObject(const PipeObject& object) { return std::move(PipeJson(object).dump()); }
inline tstring dumpObject(PipeObjectPtr object) { return std::move(dumpObject(*object)); }

//----------------------------------------------------------------------------------------------------------------------

inline tstring timplode(const std::vector<tstring>& fragments, const TCHAR delimiter) {
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

inline std::vector<tstring> texplode(const tstring& data, const TCHAR delimiter) {
	std::vector<tstring> result;

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

//----------------------------------------------------------------------------------------------------------------------

inline bool startsWith(const tstring& heystack, const tstring& needle) {
	return (heystack.substr(0, needle.length()) == needle);
}

//======================================================================================================================

inline bool endsWith(const tstring& heystack, const tstring& needle) {
	if(heystack.length() < needle.length()) { return false; }
	return (heystack.substr(heystack.length() - needle.length(), needle.length()) == needle);
}

//======================================================================================================================

inline tstring currentTimestamp() {
	time_t timestamp;
	time(&timestamp);
	return to_tstring(timestamp);
}

//======================================================================================================================

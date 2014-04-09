#include "CommonHeader.h"
using namespace std;

class PipeInstance {
private:
	tstring _path;
	vector<tstring> _providers; 
	//vector<tstring> _providers = {}; // This line crashes the optimizing compiler

	vector<tstring> debugEchos;

public:
	PipeInstance(tstring path, vector<tstring> providers) : _path(path), _providers(providers) {

	}

	~PipeInstance() {

	}

	void send(vector<tstring> messages) {
		for(auto& message : messages) {
			debugEchos.push_back(_T("Echo: ") + message);
		}
	}

	vector<tstring> receive() {
		vector<tstring> messages = {};
		messages.insert(messages.end(), debugEchos.begin(), debugEchos.end());
		debugEchos.clear();
		return messages;
	}
};
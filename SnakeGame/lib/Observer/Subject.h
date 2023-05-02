#pragma once
#include <list>
#include "Observer.h"

class Subject
{
public:
	Subject() {};
	~Subject() {
		observers.clear();
	};

	void Attach(Observer* o) {
		observers.push_back(o);
	};
	void Detach(Observer* o) {
		observers.remove(o);
	};
	virtual void Notify(EventFlag flag) {
		for (auto o : observers) {
			o->OnNotify(flag);
		}
	}
private:
	std::list<Observer*> observers;
};


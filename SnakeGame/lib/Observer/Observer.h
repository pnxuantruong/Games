#pragma once

enum class EventFlag {
	Food,
	Death
};

class Observer
{
public:
	Observer() {};
	~Observer() {};
	virtual void OnNotify(EventFlag flag) {};
};


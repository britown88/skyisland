#pragma once
/*
#include "singleton.h"
class foo : public Singleton<foo> {......};
foo::instance().bar();
*/

template <typename T>
class Singleton
{
public:
	static T& instance()
	{
		static T instance;
		return instance;
	}
};


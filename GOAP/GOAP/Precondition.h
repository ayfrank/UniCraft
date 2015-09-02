#pragma once

#include <string>

using namespace std;

class Precondition
{
	public:
		Precondition(string);
		~Precondition();

		string getName();
		virtual bool check() = 0;

	private:
		string name;
};


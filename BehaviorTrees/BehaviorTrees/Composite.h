#pragma once

#include <list>
#include "Component.h"

using namespace std;

class Composite : public Component
{
	public:
		Composite();
		~Composite();

		bool add(Component*);
		bool remove(Component*) final;

		list< Component* > getChildren();

	private:
		list< Component* > children;
};


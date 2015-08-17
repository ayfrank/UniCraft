#pragma once

#include <list>

using namespace std;

class Component
{
	public:
		Component();
		~Component();

		virtual bool operation() = 0;
		virtual bool add(Component*);
		virtual bool remove(Component*);

		Component* getParent();
		void setParent(Component*);

		virtual list<Component*> getChildren();

	private:
		Component* parent;
};


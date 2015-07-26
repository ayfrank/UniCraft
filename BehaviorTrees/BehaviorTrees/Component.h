#pragma once
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

	private:
		Component* parent;
};


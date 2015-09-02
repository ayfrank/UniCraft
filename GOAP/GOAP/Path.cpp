#include "Path.h"


Path::Path()
{
}

Path::~Path()
{
}

void Path::setReachable(bool reachable)
{
	this->reachable = reachable;
}

void Path::setPath(vector<GoapAction*> path)
{
	this->path = path;
}

void Path::setCost(float cost)
{
	this->cost = cost;
}

bool Path::isReachable()
{
	return reachable;
}

vector<GoapAction*> Path::getPath()
{
	return path;
}

float Path::getCost()
{
	return cost;
}
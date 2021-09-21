#include "header.h"

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#pragma once

class ObjectManager
{
private:
public:
	ObjectManager();
	~ObjectManager();

	void addActor(Actor *actor);
	void removeActor(Actor *actor);
};
#endif
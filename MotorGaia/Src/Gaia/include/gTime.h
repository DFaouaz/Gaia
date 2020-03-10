#pragma once
#ifndef G_TIME_H
#define G_TIME_H

#include "Ogre.h"
#include "Singleton.h"

class gTime : public Ogre::FrameListener, public Singleton<gTime>
{
protected:
	float deltaTime;
	float timeSinceStart;

	// Updates the deltaTime
	bool frameStarted(const Ogre::FrameEvent& evt);

public:
	gTime();
	~gTime();

	void setup();

	float getDeltaTime() const;
	void resetTime();
};

#endif
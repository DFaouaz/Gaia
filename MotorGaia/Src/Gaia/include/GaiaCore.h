#pragma once
#ifndef GAIA_CORE_H
#define GAIA_CORE_H

#include "ResourcesManager.h"
#include "GaiaExports.h"

namespace Ogre
{
	class Root;
}

class Window;

class Timer;

class EventSystem;
class RenderSystem;
class InputSystem;
class PhysicsSystem;
class InterfaceSystem;
class SoundSystem;
class WindowManager;
class ComponentManager;
class SceneManager;

class GAIA_API GaiaCore
{
public:
	GaiaCore();
	~GaiaCore();

	void init(const std::string& windowTitle, unsigned int width = 0, unsigned int height = 0);
	void run();
	void close();

private:
	void render(float deltaTime);
	void preUpdate(float deltaTime);
	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void initLib();

	Ogre::Root* root;
	Window* window;

	//Timer
	Timer* timer;

	//Systems
	EventSystem* eventSystem;
	RenderSystem* renderSystem;
	InputSystem* inputSystem;
	InterfaceSystem* interfaceSystem;
	PhysicsSystem* physicsSystem;
	SoundSystem* soundSystem;

	//Managers
	ResourcesManager resourcesManager;
	ComponentManager* componentManager;
	SceneManager* sceneManager;
	WindowManager* windowManager;
};

#endif
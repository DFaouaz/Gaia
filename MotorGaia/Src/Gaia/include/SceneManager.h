#pragma once

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Singleton.h"

#include <string>
#include <map>

#include "Scene.h"
#include "SceneData.h"

#include <OgreRoot.h>
#include "Camera.h"

class DebugDrawer;

class GAIA_API SceneManager : public Singleton<SceneManager>
{
	friend class GaiaCore;
	friend class InterfaceSystem;
	friend class Scene;
	friend class GameObject;
public:
	SceneManager();
	~SceneManager();

	bool changeScene(const std::string& name, bool async = false);
	bool exist(const std::string& name) const;

	Scene* getCurrentScene() const;
	std::string getSceneToLoad() const;

private:
	void init(Ogre::Root* root);
	void close();

	// Before process currentScene
	void preUpdate(float deltaTime);
	// Process currentScene
	void update(float deltaTime);
	// After process currentScene
	void postUpdate(float deltaTime);

	Scene* createScene(const SceneData* data);
	GameObject* createGameObject(const GameObjectData* data, Scene* scene, GameObject* parent = nullptr);

	void loadScene(const SceneData* data);

	void processSceneChange();
	void processCameraChange();
	void processDontDestroyObjects();

	std::string getNextNodeID();

private:
	Scene* currentScene;
	Scene* stackScene;

	// For loading screens
	std::string sceneToLoad;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;

	int countNodeIDs;

	DebugDrawer* debugDrawer;

	float timeScaleAccumulator;
};

#endif
#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <OgreRoot.h>
#include "GameObject.h"
#include "Camera.h"

#include "GaiaComponent.h"
#include "UserComponent.h"

class Scene {
	friend class SceneManager;
	friend class UserComponent;
public:
	Scene(const std::string& sceneName, Ogre::Root* root);
	~Scene();

	//Component Calls
	void awake();
	void start();
	void preUpdate(float deltaTime);
	void update(float deltaTime);
	void postUpdate(float deltaTime);
	
	const std::string& getName();
	Ogre::SceneManager* getSceneManager() const;

	Ogre::Entity* createEntity(const std::string& name);

	GameObject* getGameObjectWithName(const std::string& name);
	std::vector<GameObject*> getGameObjectsWithTag(const std::string& tag);

	void setMainCamera(Camera* camera);
	Camera* getMainCamera() const;

	std::map<std::string, Ogre::AnimationState*> getAnimations();

private:
	void addUserComponent(UserComponent* component);

	bool addGameObject(GameObject* gameObject);

	void destroyPendingGameObjects();
	void destroyGameObject(GameObject* gameObject);

	void instantiatePendingGameObjects();
	void instantiate(GameObject* gameObject);

	void updateAllAnimations(float deltaTime);

private:
	const std::string name;
	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;

	std::vector<UserComponent*> userComponents;

	/* Name - Number of instances */
	std::map<std::string, int> repeatedNames;

	/* Objects, no parent-child */
	std::vector<GameObject*> sceneObjects;
	std::vector<GameObject*> destroyQueue;
	std::vector<GameObject*> instantiateQueue;

	Camera* mainCamera;

	std::map<std::string, Ogre::AnimationState*> animations;
};

#endif
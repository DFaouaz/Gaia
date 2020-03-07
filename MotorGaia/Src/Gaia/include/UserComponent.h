#pragma once
#ifndef USER_COMPONENT_H
#define USER_COMPONENT_H

#include "Component.h"

class UserComponent : public Component
{
public:
	UserComponent(GameObject* gameObject);
	~UserComponent();

	virtual void awake();
	virtual void start();
	virtual void preUpdate(float deltaTime);
	virtual void update(float deltaTime);
	virtual void postUpdate(float deltaTime);

	virtual void onCollisionEnter(GameObject* other);
	virtual void onCollisionStay(GameObject* other);
	virtual void onCollisionExit(GameObject* other);

	virtual void onTriggerEnter(GameObject* other);
	virtual void onTriggerStay(GameObject* other);
	virtual void onTriggerExit(GameObject* other);
};

#endif

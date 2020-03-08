#include "GaiaCore.h"

#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreViewport.h>
#include <iostream>

#include "ResourcesManager.h"
#include "RenderSystem.h"
#include "Window.h"
#include "Camera.h"
#include "Light.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Reverb.h"

GaiaCore::GaiaCore()
{

}

GaiaCore::~GaiaCore()
{
	delete root;
	delete obj;
    delete win;
}

void GaiaCore::init()
{
#ifdef _DEBUG
	root = new Ogre::Root("plugins_d.cfg", "window_d.cfg");
#else
	root = new Ogre::Root("plugins.cfg", "window.cfg");
#endif

	if (!(root->restoreConfig() || root->showConfigDialog(nullptr)))
        return;

	// Setup window
	Window* win = new Window(root, "Test window - 2020 (c) Gaia ");

	ResourcesManager rManager("resources.asset");
	rManager.init();

	RenderSystem::GetInstance()->setup(root);

	aux = new GameObject("Camera", "Cam", nullptr);
	Transform* transform1 = new Transform(aux);
	Camera* cam = new Camera(aux);
	lis = new SoundListener(aux);
	
	//aux->transform->rotate(Vector3(0, -90, 0));

	Ogre::Viewport* vp = win->addViewport(cam->getCamera());

	Light* lz = new Light(aux);
	lz->setType(Light::Point);
	lz->setColour(0.7, 0.1, 0.7);

	obj = new GameObject("Churro", "Ch", nullptr);
	Transform* transform2 = new Transform(obj);
	MeshRenderer* ms = new MeshRenderer(obj);
	ms->createEntity("knot", "knot.mesh");
	obj->transform->setPosition(Vector3(0, 0, -400));
	obj->transform->setScale(Vector3(0.5, 0.5, 0.5));
	obj->transform->rotate(Vector3(0, 90, 0));

	emi = new SoundEmitter(obj);
	

	Reverb* rev = new Reverb(aux);
	rev->setReverbMaxDistance(200.0f);
	rev->setReverbPreset(rev->CAVE);
	sound->initSystem();
	emi->playSound("prueba2");
}

void GaiaCore::run()
{
	while (true)
	{
		RenderSystem::GetInstance()->render();
		update();
		sound->updateSounds();
	}
}

void GaiaCore::close()
{
	sound->destroy();
}

void GaiaCore::update()
{
	obj->transform->translate(Vector3(0, 0, 0));
	//obj->getComponent<SoundEmitter>()->update(2);
	emi->update(0);
	lis->update(0);

	aux->transform->rotate(Vector3(0, 0, 0));
/*	SoundListener* lis = aux->getComponent<SoundListener>();
	emi->update(0);*/


}
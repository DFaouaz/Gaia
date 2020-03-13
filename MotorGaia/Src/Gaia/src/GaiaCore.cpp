#include "GaiaCore.h"


GaiaCore::GaiaCore() :	root(nullptr), win(nullptr),
						renderSystem(nullptr), inputSystem(nullptr), interfaceSystem(nullptr), physicsSystem(nullptr), soundSystem(nullptr),
						resourcesManager("resources.asset"), sceneManager(nullptr), componentManager(nullptr)
{

}

GaiaCore::~GaiaCore()
{
	// Call close before GaiaCore destructor
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
	win = new Window(root, "Test window - 2020 (c) Gaia ");

	// Systems initialization
	// RenderSystem
	renderSystem = RenderSystem::GetInstance();
	renderSystem->init(root);

	// InputSystem
	inputSystem = InputSystem::GetInstance();
	inputSystem->init();

	// InterfaceSystem
	interfaceSystem = InterfaceSystem::GetInstance();
	interfaceSystem->init(win);

	// PhysicsSystem
	physicsSystem = PhysicsSystem::GetInstance();
	physicsSystem->init();

	// SoundSystem
	soundSystem = SoundSystem::GetInstance();
	soundSystem->init();

	// Managers initialization
	// ResourcesManager initialization
	resourcesManager.init();

	// ComponentManager initialization
	componentManager = ComponentManager::GetInstance();
	componentManager->init();

	// SceneManager initialization (required ResourcesManager and ComponentManager previous initialization)
	sceneManager = SceneManager::GetInstance();
	sceneManager->init(root, win);
}

void GaiaCore::run()
{
	bool exit = false;
	float deltaTime = 1.f / 60.f;
	while (!inputSystem->getKeyPress("Escape")) {
		// Render
		render(deltaTime);

		// Pre-process
		preUpdate(deltaTime);
		
		// Process
		update(deltaTime);

		// Post-process
		postUpdate(deltaTime);
	}
}

void GaiaCore::close()
{
	// ResourcesManager termination
	resourcesManager.close();
	// ComponentManager termination
	componentManager->close();
	// SceneManager termination
	sceneManager->close();

	//Systems termination
	renderSystem->close();
	inputSystem->close();
	interfaceSystem->close();
	physicsSystem->close();
	soundSystem->close();

	if (win != nullptr)
		delete win;
	win = nullptr;

	if (root != nullptr)
		delete root;
	root = nullptr;
}

void GaiaCore::render(float deltaTime)
{
	// RenderSystem
	renderSystem->render(deltaTime);

	// PhysicsSystem
#ifdef _DEBUG
	physicsSystem->render();
#endif

	// InterfaceSystem
	interfaceSystem->render();
}

void GaiaCore::preUpdate(float deltaTime)
{
	// Systems TODO:
	// RenderSystem (animations)
	// renderSystem->update(deltaTime);

	// InputSystem
	inputSystem->update();

	// InterfaceSystem
	interfaceSystem->update(deltaTime);

	// PhysicsSystem
	physicsSystem->update();

	// SoundSystem
	soundSystem->update(deltaTime);

	// Managers (escena)
	sceneManager->preUpdate(deltaTime);
}

void GaiaCore::update(float deltaTime)
{
	// Managers
	sceneManager->update(deltaTime);
	sceneManager->getCurrentScene()->getMainCamera()->gameObject->transform->rotate(Vector3(0, 0.3, 0));
}

void GaiaCore::postUpdate(float deltaTime)
{
	// Managers
	sceneManager->postUpdate(deltaTime);

	// Systems 
	// Si es que hay
}
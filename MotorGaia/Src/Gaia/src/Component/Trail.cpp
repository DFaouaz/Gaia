#include "Trail.h"

#include <OgreRibbonTrail.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreTagPoint.h>
#include <OgreBillboardSet.h>
#include <OgreEntity.h>

#include "GameObject.h"
#include "Scene.h"
#include "ComponentRegister.h"
#include "MeshRenderer.h"
#include "GaiaData.h"

REGISTER_FACTORY(Trail);

Trail::Trail(GameObject* gameObject) : GaiaComponent(gameObject), bbs(nullptr), trail(nullptr), offset(0, 0, 0)
{

}

Trail::~Trail()
{
	if (trail != nullptr) {
		gameObject->getScene()->getSceneManager()->getRootSceneNode()->detachObject(trail);
		gameObject->getScene()->getSceneManager()->destroyRibbonTrail(trail);
		trail = nullptr;
	}
	if (bbs != nullptr) {
		gameObject->getScene()->getSceneManager()->destroyBillboardSet(bbs);
		bbs = nullptr;
	}
}

void Trail::configureTrail(const std::string& trailFilename)
{
	GaiaData trailData;
	trailData.load(trailFilename);

	GaiaData trailParamsData = trailData.find("TrailParameters");
	for (int i = 0; i < trailParamsData.size(); i++)
	{
		std::stringstream ss(trailParamsData[i][0].getValue());
		std::string paramName;
		double x, y, z, a;
		float value;
		std::string s;
		if (!(ss >> paramName))
		{
			LOG_ERROR("TRAIL MANAGER", "invalid trail parameter name \"%s\"", trailParamsData[i][0].getValue().c_str());
			continue;
		}

		if (paramName == "offset")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> x >> y >> z))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid offset value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setOffset(Vector3(x, y, z));
		}
		else if (paramName == "trail")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> s))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid trail value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}

			if (s == "node")
				newTrail();
			else if (s == "bone")
			{
				if (!(ss >> s))
				{
					LOG_ERROR("TRAIL MANAGER", "invalid bone value \"%s\"", trailParamsData[i][1].getValue().c_str());
					continue;
				}
				newTrail(s);
			}
		}
		else if (paramName == "length")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> value))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid length value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setLength(value);
		}
		else if (paramName == "max")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> value))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid max value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setMax(value);
		}
		else if (paramName == "colour")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> x >> y >> z >> a))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid colour value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setColour(Vector3(x, y, z), a);
		}
		else if (paramName == "colourChange")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> x >> y >> z >> a))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid colourChange value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setColourChange(Vector3(x, y, z), a);
		}
		else if (paramName == "width")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> value))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid width value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setWidth(value);
		}
		else if (paramName == "widthChange")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> value))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid widthChange value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}
			setWidthChange(value);
		}
		else if (paramName == "start")
		{
			ss = std::stringstream(trailParamsData[i][1].getValue());
			if (!(ss >> s))
			{
				LOG_ERROR("TRAIL MANAGER", "invalid start value \"%s\"", trailParamsData[i][1].getValue().c_str());
				continue;
			}

			if (s == "true")
				start();
			else if (s == "false")
				stop();
		}
	}
}

void Trail::newTrail(const std::string& bone)
{
	if (trail != nullptr) {
		gameObject->getScene()->getSceneManager()->getRootSceneNode()->detachObject(trail);
		gameObject->getScene()->getSceneManager()->destroyRibbonTrail(trail);
		trail = nullptr;
	}
	if (bbs != nullptr) {
		gameObject->getScene()->getSceneManager()->destroyBillboardSet(bbs);
		bbs = nullptr;
	}

	// Create billboard set
	bbs = gameObject->getScene()->getSceneManager()->createBillboardSet(gameObject->getName() + "BB");
	bbs->setDefaultDimensions(0.25, 0.25);
	bbs->setMaterialName("Billboard");
	bbs->createBillboard(0, 0, 0, Ogre::ColourValue::Black);

	// Create trail
	trail = gameObject->getScene()->getSceneManager()->createRibbonTrail(gameObject->getName() + "Trail");
	trail->setMaterialName("Trail");

	if (bone == "") // Node trail
	{
		trail->addNode(gameObject->node);
	}
	else // Bone trail
	{
		if (mesh != nullptr)
		{
			Ogre::TagPoint* tp = mesh->getMesh(mesh->getMeshId())->attachObjectToBone(bone, bbs, Ogre::Quaternion::IDENTITY,
				Ogre::Vector3(offset.x, offset.y, offset.z));
			trail->addNode(tp);
		}
		else
			LOG("TRAIL: mesh is nullptr\n");
	}

	gameObject->getScene()->getSceneManager()->getRootSceneNode()->attachObject(trail);
}

void Trail::start()
{
	if (trail != nullptr)
	{
		/*trail->(length);
		LOG("LENGTH: %d\n", length);*/
		trail->setVisible(true); // esto se puede mejorar!
	}
	else
		LOG("TRAIL: trying to start a NULL trail\n");
}

void Trail::stop()
{
	if (trail != nullptr)
	{
		//trail->setTrailLength(0);
		trail->setVisible(false); // esto se puede mejorar!
	}
	else
		LOG("TRAIL: trying to stop a NULL trail\n");
}

bool Trail::started()
{
	if (trail != nullptr)
		return /*trail->getTrailLength();*/trail->isVisible(); // esto se puede mejorar!
	else
		LOG("TRAIL: trying to stop a NULL trail\n");
}

void Trail::handleData(ComponentData* data)
{
	float length = 20; float max = 40; Vector3 colour = Vector3(1, 1, 1); float colourAlpha = 1.0;
	Vector3 colourChange = Vector3(0.5, 0.5, 0.5); float colourChangeAlpha = 0.5;
	float width = 0.5; float widthChange = 0.1;

	for (auto prop : data->getProperties()) {
		std::stringstream ss(prop.second);

		if (prop.first == "offset") {
			setVector3(offset);
		}
		else if (prop.first == "trail") {

			std::string type;
			if (ss >> type) {
				if (type == "node")
					newTrail("");
				else if (type == "bone")
				{
					std::string bone;
					ss >> bone;
					newTrail(bone);
				}
			}
			else {
				LOG("TRAIL: invalid data format. Property \"trail\"\n");
			}
		}
		else if (prop.first == "start") {
			if (prop.second == "true") {
				start();
			}
			else if (prop.second == "false") {
				stop();
			}
			else {
				LOG("TRAIL: invalid value \"%s\". Property \"start\"\n", prop.second.c_str());
			}
		}
		else if (prop.first == "length") {
			setFloat(length);
		}
		else if (prop.first == "max") {
			setFloat(max);
		}
		else if (prop.first == "colour") {
			setVector3(colour);
		}
		else if (prop.first == "alpha") {
			setFloat(colourAlpha);
		}
		else if (prop.first == "colourChange") {
			setVector3(colourChange);
		}
		else if (prop.first == "alphaChange") {
			setFloat(colourChangeAlpha);
		}
		else if (prop.first == "width") {
			setFloat(width);
		}
		else if (prop.first == "widthChange") {
			setFloat(widthChange);
		}
		else {
			LOG("TRAIL: invalid property name \"%s\"\n", prop.first.c_str());
		}
	}

	if (trail != nullptr)
	{
		setLength(length);
		setMax(max);
		setColour(colour, colourAlpha);
		setColourChange(colourChange, colourChangeAlpha);
		setWidth(width);
		setWidthChange(widthChange);
	}
}

void Trail::setMeshRenderer(MeshRenderer* mesh)
{
	this->mesh = mesh;
}

void Trail::setOffset(const Vector3& offset)
{
	this->offset = offset;
}

void Trail::setLength(float length)
{
	if (trail == nullptr) return;
	this->length = length;
	trail->setTrailLength(length);
}

void Trail::setMax(float max)
{
	if (trail == nullptr) return;
	trail->setMaxChainElements(max);
}

void Trail::setColour(const Vector3& colour, float colourAlpha)
{
	if (trail == nullptr) return;
	trail->setInitialColour(0, colour.x, colour.y, colour.z, colourAlpha);
}

void Trail::setColourChange(const Vector3& colourChange, float colourChangeAlpha)
{
	if (trail == nullptr) return;
	trail->setColourChange(0, colourChange.x, colourChange.y, colourChange.z, colourChangeAlpha);
}

void Trail::setWidth(float width)
{
	if (trail == nullptr) return;
	trail->setInitialWidth(0, width);
}

void Trail::setWidthChange(float widthChange)
{
	if (trail == nullptr) return;
	trail->setWidthChange(0, widthChange);
}
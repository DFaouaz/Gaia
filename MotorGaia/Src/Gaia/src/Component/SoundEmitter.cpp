#include "SoundEmitter.h"
#include "GameObject.h"


SoundEmitter::SoundEmitter(GameObject* gameObject) : GaiaComponent(gameObject)
{
    pos = SoundSystem::GetInstance()->vecToFMOD(gameObject->transform->getPosition());
    SoundSystem::GetInstance()->addEmitter(this);
    channel = nullptr;
    pitch = 1.0f;
    volume = 1.0f;
    paused = true;
}

SoundEmitter::~SoundEmitter()
{
}

void SoundEmitter::update()
{
    if (channel && !paused) {
        pos = SoundSystem::GetInstance()->vecToFMOD(gameObject->transform->getPosition());
        channel->set3DAttributes(&pos, &zero);
    }
}


void SoundEmitter::playSound(std::string soundName, bool reverb)
{
    if (channel) {
        channel->stop();
    }
    channel = SoundSystem::GetInstance()->playSound(soundName);
    channel->set3DAttributes(&pos, &zero);
    channel->setPitch(pitch);
    channel->setVolume(volume);
  
    if (!reverb){
        channel->setReverbProperties(0,0);
    }

    paused = false;
}

void SoundEmitter::playMusic(std::string soundName, bool reverb)
{
    bool paused;
    if (channel) {
        channel->stop();
    }
    channel = SoundSystem::GetInstance()->playMusic(soundName);
    channel->set3DAttributes(&pos, &zero);
    channel->setPitch(pitch);
    channel->setVolume(volume);
    if (!reverb) {
        channel->setReverbProperties(0, 0);
    }

    paused = false;
}

void SoundEmitter::pause()
{
    if (channel) {
        channel->getPaused(&paused);
        if (!paused) {
            channel->setPaused(true);
            paused = true;
        }
    }
}

void SoundEmitter::resume()
{
    if (channel) {
        channel->getPaused(&paused);
        if (paused) {
            channel->setPaused(false);
            paused = false;
        }
    }
}

void SoundEmitter::setVolume(float _volume)
{
    volume = _volume;
    if (channel) channel->setVolume(volume);
}

void SoundEmitter::setEmitterPitch(float _pitch)
{
    pitch = _pitch;
    if(channel)channel->setPitch(pitch);
}
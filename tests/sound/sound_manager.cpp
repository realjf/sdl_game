#include "sound_manager.h"

bool SoundManager::load(std::string fileName, std::string id, sound_type type) {
}

void SoundManager::playSound(std::string id, int loop) {
}

void SoundManager::playMusic(std::string id, int loop) {
}

SoundManager::SoundManager() {
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager() {
}

SoundManager::SoundManager(const SoundManager &) {
}

SoundManager &SoundManager::operator=(const SoundManager &) {
}

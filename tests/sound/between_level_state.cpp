#include "between_level_state.h"

const std::string BetweenLevelState::s_betweenLevelID = StateIDToString(StateID::BETWEEN_LEVEL);

void BetweenLevelState::update() {
}

void BetweenLevelState::render() {
}

bool BetweenLevelState::onEnter() {
    return true;
}

bool BetweenLevelState::onExit() {
    return true;
}

#ifndef _PLAYER_BULLET_H_
#define _PLAYER_BULLET_H_

#include "shooter_object.h"

class PlayerBullet : public ShooterObject {

public:
    PlayerBullet() : ShooterObject() {}

    virtual ~PlayerBullet() {}

    virtual std::string type() { return "PlayerBullet"; }
    virtual void load(std::unique_ptr<LoaderParams> const &pParmas, Vector2D heading) {
        ShooterObject::load(std::move(pParamas));
        m_heading = heading;
    }

    virtual void draw(RendererFlip flip = RendererFlip::FLIP_NONE) {
        ShooterObject::draw(flip);
    }

    virtual void collision() {
        m_bDead = true;
    }

    virtual void update() {
        m_velocity.setX(m_heading.getX());
        m_velocity.setY(m_heading.getY());

        ShooterObject::update();
    }

    virtual void clean() {
        ShooterObject::clean();
    }

private:
    Vector2D m_heading;
};

#endif /* _PLAYER_BULLET_H_ */

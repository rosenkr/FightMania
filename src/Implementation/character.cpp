#include "Implementation/character.h"
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Scene/sceneManager.h"
#include "Implementation/ground.h"
#include "Ichi/Graphics/sprite.h"
#include "Implementation/attack.h"
#include "Ichi/log.h"

#include <algorithm>

void Character::applyForce()
{
    // Applies gravity
    velocity += gravity;

    // Applies force to hitbox
    hitbox += velocity;

    checkGroundCollision();

    animation.get()->setX(hitbox.getX());
    animation.get()->setY(hitbox.getY());
}
bool cooldown = false;
void Character::handleInput()
{



    if (profile->canTakeAction(Profile::Action::UP))
    {
    }

    if (profile->canTakeAction(Profile::Action::UP))
    {
    }

    if (profile->canTakeAction(Profile::Action::RIGHT))
        velocity.setX(speed);
    else if (profile->canTakeAction(Profile::Action::LEFT))
        velocity.setX(-speed);
    else
        velocity.setX(0);

    if (grounded && profile->canTakeAction(Profile::Action::JUMP))
        velocity.setY(jumpVelocity);

    if (profile->canTakeAction(Profile::Action::LIGHT_ATTACK))
    {
    }

    if (!cooldown && profile->canTakeAction(Profile::Action::HEAVY_ATTACK))
    {
        ICHI_INFO("pressed K for heavy attack");
        auto it = attacks.find(AttackNames::FIREBALL);
        if (it != attacks.end()) {
            spawnAttack(it->second); 
        } else {
            ICHI_ERROR("Did not find attacktype for attackname (FIREBALL = 0)");
            SDL_Quit();
        }

       cooldown = true;
    }

    if (profile->canTakeAction(Profile::Action::BLOCK))
    {
    }
}

void Character::update()
{
    animation.get()->update();
    handleInput();
    applyForce();
}

void Character::checkGroundCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();
    grounded = false; // is not grounded untill proven otherwise
    for (auto &c : s->getComponents()) // for every component
    {
        if(auto g = dynamic_cast<Ground*>(c.get())){ // if component is Ground 
            if (!(g->getHitbox() == hitbox) && g->getHitbox().isOverlapping(hitbox + ichi::datatypes::Point(0, 1)))
                grounded = true;

            if (!(g->getHitbox() == hitbox) && g->getHitbox().isOverlapping(hitbox))
            {
                hitbox.setY(g->getHitbox().getY() - hitbox.getHeight());
                velocity.setY(0);
                grounded = true;
                return;
            }
        }
    }
}

void Character::draw() const
{
    animation.get()->draw();
}

// currently hardcoded for fireball, not general attack type
void Character::spawnAttack(AttackType at) const {

    ichi::datatypes::Point fireballDrawPt = drawPointAttack(at);
    ICHI_INFO("spawnAttack drawpoint: x: {}, y: {}", fireballDrawPt.X, fireballDrawPt.Y);
    
    ichi::datatypes::Hitbox fireballHitbox(fireballDrawPt, at.getWidth(), at.getHeight(), true);
    ICHI_INFO("spawnAttack hitbox: width: {}, height: {}", fireballHitbox.getWidth(), fireballHitbox.getHeight());

    std::shared_ptr<ichi::graphics::AnimatedSprite> fireballAnimation = std::make_shared<ichi::graphics::AnimatedSprite>(
    fireballHitbox, ichi::graphics::Sprite::Layer::UICOMPONENT, at.getPaths(), std::map<int, Uint32>{{0, 200}, {1, 200}, {2, 200}, {3, 200}}); // animation for attack
    ICHI_INFO("spawnAttack character direction x: {}, y: {} ", direction.getX(), direction.getY());
    std::shared_ptr<Attack> fbAttack = std::make_shared<Attack>(fireballHitbox, fireballAnimation, direction, 23.0, 1.0); // create attack

    ichi::scene::sceneManager::getActiveScene()->addComponent(fbAttack); // add attack to components
}

ichi::datatypes::Point Character::drawPointAttack(AttackType at) const{
    if(direction == ichi::datatypes::Vector2D{1,0}) // character facing right
        return ichi::datatypes::Point{hitbox.getX() + hitbox.getWidth() + 1, hitbox.getHeight() / 2};

    if(direction == ichi::datatypes::Vector2D(-1,0)) // character facing left
        return ichi::datatypes::Point{hitbox.getX() - (1 + at.getWidth()), hitbox.getHeight() / 2};

    return ichi::datatypes::Point{0, 0}; // temp default in case direction is neither left nor right
}
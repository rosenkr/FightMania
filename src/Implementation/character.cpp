#include "Implementation/character.h"
#include "Ichi/Core/component.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/log.h"
#include "Ichi/Scene/sceneManager.h"
#include "Implementation/ground.h"

#include <cstdlib>
using namespace ichi::input;

// Returns position, using Kinematic equation
float Character::calculateVerticalPositionKinematic(float dt, float v, float g, int y)
{
    return y + v * dt + (0.5f) * g * dt * dt;
}

void Character::applyGravity()
{

    Uint32 currentTime = SDL_GetTicks();
    float currentY = hitbox.getY(), newY, gravity = 22.0f, deltaTime;

    if (!grounded)
    { // if in the air
        if (jumpTime != 0)
        {                                                                     // if jumped
            deltaTime = static_cast<float>(currentTime - jumpTime) / 1000.0f; // time in seconds
            jumpVelocity += gravity * deltaTime;                              // velocity changes with time
            newY = calculateVerticalPositionKinematic(deltaTime, jumpVelocity, gravity, currentY);

            if (jumpVelocity >= 0)
            { // Peak hit at velocity = 0, transition to free-fall
                jumpTime = 0;
                jumpVelocity = -50.0f;
            }
        }
        else
        { // free fall
            if (fallTime == 0)
            {
                fallTime = currentTime;
            }
            deltaTime = static_cast<float>(currentTime - fallTime) / 1000.0f;
            newY = calculateVerticalPositionKinematic(deltaTime, 0, gravity, currentY); // 0 jump velocity, free fall
        }

        hitbox.setY(newY); // update both just in case
        animation.get()->setY(newY);

        if (checkGroundCollision())
        {
            jumpTime = 0;
            fallTime = 0;
            grounded = true;
            return;
        }
    }
    else
    {
        velocity.setY(0); // if grounded
    }
}

void Character::handleInput()
{
    bool left = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Left) || Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_LEFT) || ControllerHandler::getTotalLeftStickX() < 0;
    bool right = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Right) || Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_RIGHT) || ControllerHandler::getTotalLeftStickX() > 0;
    bool jump = Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_UP);

    if (jump && grounded)
    {
        jumpTime = SDL_GetTicks(); // will affect how gravity is applied
        grounded = false;
    }

    if (right)
    {
        animation.get()->setX(animation.get()->getX() + 1 * ms);
    }

    if (left)
    {
        animation.get()->setX(animation.get()->getX() - 1 * ms);
    }
}

void Character::update()
{
    animation.get()->update();
    handleInput();
    applyGravity();
}

// currently must handle both raw pointers and shared pointers
bool Character::checkGroundCollision()
{
    ichi::scene::Scene *s = ichi::scene::sceneManager::getActiveScene();

    for (auto &c : s->getComponents())
    {
        // Directly use shared_ptr to Component, no need for holds_alternative
        if (auto componentPtr = std::dynamic_pointer_cast<Ground>(c))
        {
            if (collidesWith(*componentPtr))
            {
                // Adjust Y position based on the ground's hitbox
                hitbox.setY(componentPtr->getHitbox().getY() - hitbox.getHeight());
                animation.get()->setY(componentPtr->getHitbox().getY() - animation.get()->getHeight());
                return true;
            }
        }
    }

    return false;
}

void Character::draw() const
{
    animation.get()->draw();
}

bool Character::collidesWith(const ichi::core::Component &other) const
{
    return other.getHitbox().getIsTangible() && hitbox.isOverlapping(other.getHitbox());
}

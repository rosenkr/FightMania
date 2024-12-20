#include "Ichi/Graphics/sprite.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/log.h"

namespace ichi::graphics
{

    Sprite::Sprite(datatypes::Hitbox &hb, Layer l, std::string s) : hitbox(hb), layer(l), path(s)
    {
        TextureManager::addTextureFor(*this, s);
    }

    void Sprite::draw() const
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), TextureManager::getTextureFor(*this), NULL, hitbox.getSDLRect());
    }

    const datatypes::Hitbox &Sprite::getHitbox() const
    {
        ICHI_DEBUG("Returning Hitbox with x: {}, y: {}", hitbox.getX(), hitbox.getY());
        return hitbox;
    }

    void Sprite::setX(int i)
    {
        hitbox.setX(i);
    }

    void Sprite::setY(int i)
    {
        hitbox.setY(i);
    }

} // namespace ichi::graphics

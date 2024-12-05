#include "Ichi/Graphics/sprite.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"

namespace ichi::graphics
{

    Sprite::Sprite(datatypes::Hitbox hb, Layer l, std::string s) : hitbox(hb), layer(l), path(s)
    {
        TextureManager::addTextureFor(*this, s);
    }

    void Sprite::draw() const
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), TextureManager::getTextureFor(*this), NULL, hitbox.getSDLRect());
    }

} // namespace ichi::graphics

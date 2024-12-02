#include "Ichi/Graphics/sprite.h"

// temp
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Graphics/textureManager.h"

namespace ichi::graphics
{

    Sprite::Sprite(core::Hitbox hb, Layer l, std::string s) : hitbox(hb), layer(l)
    {
        TextureManager::addTextureFor(*this, s);
    }

    void Sprite::draw()
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), TextureManager::getTextureFor(*this), NULL, hitbox.toSdlRect());
    }

} // namespace ichi::graphics

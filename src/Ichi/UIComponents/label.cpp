#include "Ichi/UIComponents/label.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

namespace ichi::uicomponents
{

    Label::Label(datatypes::Point location, const std::string &s, TTF_Font *f, SDL_Color c) : UIComponent(datatypes::Hitbox(location, 0, 0, false)), str(s), font(f), color(c)
    {
        updateText(s);
    }

    void Label::draw() const
    {
        auto texture = graphics::TextureManager::getTextTextureFor(str, font, color);
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hitbox.getSDLRect());
    }

    void Label::updateText(std::string text)
    {
        graphics::TextureManager::addTextTextureFor(str, font, color);

        auto texture = graphics::TextureManager::getTextTextureFor(str, font, color);

        int textWidth, textHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

        hitbox = datatypes::Hitbox(hitbox.getPos(), textWidth, textHeight, false);
    }

} // namespace ichi::uicomponents

#ifndef UICOMPONENT_H
#define UICOMPONENT_H    
#include "Ichi/Core/component.h"
namespace ichi::core {
    class UIComponent : public Component {
        public:
            // What sets UIComponent apart from Component is the idea of focus
            void setFocus(bool val) { focused = val; }
            bool isFocused() const { return focused; }

            // Redeclaring these from component to explicitly state that UIComponent is also abstract
            virtual void update() = 0;
            virtual void draw() const = 0;
            virtual void handleinput() {};

            UIComponent(const UIComponent&) = delete;
            UIComponent& operator=(const UIComponent&) = delete;
            virtual ~UIComponent() = default;
        protected:
        // UIComponent(): Component(Hitbox hb): hitbox(hb){};{}; // ?
        private:
            bool focused = 0;
    };
}
#endif
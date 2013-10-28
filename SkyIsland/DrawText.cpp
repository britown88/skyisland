#include <GLFW/glfw3.h>
#include "DrawText.h"
#include "IOCContainer.h"
#include "Text.h"

DrawText::DrawText(std::shared_ptr<TextString> text, Transform transform):
   m_text(std::move(text)), m_transform(transform)
{
}

void DrawText::draw()
{
   if(auto fe = IOC.resolve<FontEngine>())
   {
      auto& font = fe->getFont(*m_text->font);
         glPushMatrix();
            glColor4fv((float*)&m_text->color);
            glListBase(font.getDisplayList());

            applyGLTransformation(m_transform);
            glTranslatef(m_text->pos.x, m_text->pos.y, 0);


            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glCallLists(m_text->text.size(), GL_UNSIGNED_BYTE, m_text->text.c_str());

            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
         glPopMatrix();
   }
}
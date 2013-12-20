#include <GLFW/glfw3.h>
#include "DrawText.h"
#include "IOCContainer.h"
#include "Text.h"

DrawText::DrawText(std::shared_ptr<TextString> text, Transform transform):
   m_text(std::move(text)), m_transform(transform)
{
}

DrawText::DrawText(std::shared_ptr<TextString> text, TransformList transforms):
   m_text(std::move(text)), m_transformList(transforms)
{
}

void DrawText::draw()
{
   if(auto fe = IOC.resolve<FontEngine>())
   {
      auto& font = fe->getFont(*m_text->font);
         glPushMatrix();
            
            glListBase(font.getDisplayList());

            if(m_transformList)
               applyGLTransformation(m_transformList);
            else
               applyGLTransformation(m_transform);

            glTranslatef(m_text->pos.x, m_text->pos.y, 0);

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glPushMatrix();
            glTranslatef(0.0f, 2.0f, 2.0f);
            glColor4fv((float*)&(Colorf(m_text->color.a, 0, 0, 0)));
            glCallLists(m_text->text.size(), GL_UNSIGNED_BYTE, m_text->text.c_str());
            glPopMatrix();

            //glTranslatef(0.0f, -5.0f, 0.0f);
            glColor4fv((float*)&m_text->color);
            glCallLists(m_text->text.size(), GL_UNSIGNED_BYTE, m_text->text.c_str());

            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
         glPopMatrix();
   }
}
#pragma once

#include "IComponent.h"
#include "IRenderable.h"
#include <memory>

class GraphicsComponent : public IComponent
{
   std::shared_ptr<IRenderable> m_renderable;
public:
   GraphicsComponent(std::shared_ptr<IRenderable> renderable):m_renderable(std::move(renderable)){}

   const IRenderable &getRenderable() const {return *m_renderable;}

};
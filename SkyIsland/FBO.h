#pragma once

#include "Rect.h"
#include "Entity.h"
#include "Vertex.h"
#include "Transform.h"
#include <memory>

class FBO
{
   unsigned int m_fboHandle, m_texHandle;
   Rectf m_bounds;
   std::shared_ptr<Entity> m_entity;
   Transform m_transform;

public:
   FBO(){}
   FBO(Rectf bounds);
   ~FBO();

   Rectf getBounds(){return m_bounds;}

   unsigned int getGlHandle();
   std::shared_ptr<VertexList> getVertices();
   std::shared_ptr<std::vector<int>> getFaces();
   Transform getTransform();
   void updatePosition(Rectf &vpBounds);

   void bind();
};
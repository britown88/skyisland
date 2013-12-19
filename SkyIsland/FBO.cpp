#include <GL\glew.h>

#include "FBO.h"
#include "ComponentHelpers.h"
#include "MeshComponent.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"

FBO::FBO(Rectf bounds):m_bounds(Rectf(bounds))
{   
   glGenFramebuffers(1, &m_fboHandle);

   int pixelCount = m_bounds.width() * m_bounds.height();
   unsigned char *pixels = (unsigned char*)calloc(pixelCount * 16, sizeof(unsigned char));

   glGenTextures(1, &m_texHandle);
   glBindTexture(GL_TEXTURE_2D, m_texHandle);
   glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA32F, 
      m_bounds.width(), m_bounds.height(), 
      0, GL_RGBA, GL_FLOAT, pixels);

   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glBindTexture(GL_TEXTURE_2D, 0);

   free(pixels);

   m_entity = std::make_shared<Entity>();
   CompHelpers::addRectangleMeshComponent(*m_entity, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
   m_entity->addComponent<PositionComponent>(std::unique_ptr<PositionComponent>(new PositionComponent(Float2())));
   m_entity->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(m_bounds.width(), m_bounds.height()), Float2(0.0f, 0.0f)));
   m_transform = buildTransformation(*m_entity);

}

FBO::~FBO()
{
   glDeleteTextures(1, &m_texHandle);
   glDeleteFramebuffers(1, &m_fboHandle);
}

void FBO::updatePosition(Rectf &camBounds)
{
   m_entity->getComponent<PositionComponent>()->pos = Float2(camBounds.left, camBounds.top);
   m_transform = buildTransformation(*m_entity);
}

unsigned int FBO::getGlHandle()
{
   return m_texHandle;
}
std::shared_ptr<VertexList> FBO::getVertices()
{
   return m_entity->getComponent<MeshComponent>()->vertices;
}
std::shared_ptr<std::vector<int>> FBO::getFaces()
{
   return m_entity->getComponent<MeshComponent>()->faces;
}
Transform FBO::getTransform()
{
   return m_transform;
}

void FBO::bind()
{
   glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboHandle);
   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texHandle, 0);
   glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
}

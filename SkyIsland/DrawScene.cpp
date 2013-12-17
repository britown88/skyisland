#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "DrawScene.h"
#include "GraphicComponents.h"
#include "DrawTexture.h"

DrawScene::DrawScene(IViewport &vp, ICamera &camera):
   m_vpBounds(vp.getBounds()), m_camBounds(camera.getBounds())
{
   m_drawQueue.resize((int)RenderLayer::COUNT);

   m_scissor = false;

   for(auto &pass : camera.getFBOs())
   {
      auto dp = std::unique_ptr<DrawPass>(new DrawPass());
      dp->fboTexture = buildFboDrawObject(pass.second);
      dp->fbo = pass.second;

      m_passes.insert(std::make_pair(pass.first, std::move(dp)));
   }
     

}

DrawScene::DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds):
   m_vpBounds(vp.getBounds()), m_camBounds(camera.getBounds()), m_scissorBounds(scissorBounds)
{
   m_drawQueue.resize((int)RenderLayer::COUNT);

   m_scissor = true;
   for(auto &pass : camera.getFBOs())
   {
      auto dp = std::unique_ptr<DrawPass>(new DrawPass());
      dp->fboTexture = buildFboDrawObject(pass.second);
      dp->fbo = pass.second;

      m_passes.insert(std::make_pair(pass.first, std::move(dp)));
   }
}

std::unique_ptr<IDrawObject> DrawScene::buildFboDrawObject(std::shared_ptr<FBO> fbo)
{
   if(fbo)
   {   
      fbo->updatePosition(m_camBounds);
      auto drawObj = std::unique_ptr<IDrawObject>(
         new DrawTexture(fbo->getGlHandle(), fbo->getVertices(), fbo->getFaces(), fbo->getTransform()));

      dynamic_cast<DrawTexture*>(drawObj.get())->setBlendFunc(GL_DST_COLOR, GL_ZERO);

      return std::move(drawObj);
   }

   return std::unique_ptr<IDrawObject>();

}

void DrawScene::addObjectToPass(ICamera::Pass pass, RenderLayer layer, std::unique_ptr<IDrawObject> obj)
{
   if(m_passes.find(pass) != m_passes.end())
      m_passes[pass]->drawQueue[(int)layer].push_back(std::move(obj));
}

void DrawScene::addObject(RenderLayer layer, std::unique_ptr<IDrawObject> obj)
{
   m_drawQueue[(int)layer].push_back(std::move(obj));
}

void DrawScene::renderFBOObjectList(DrawPass &dp)
{
   dp.fbo->bind();
   glViewport(0, 0, dp.fbo->getBounds().width(), dp.fbo->getBounds().height());

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, m_camBounds.width(), m_camBounds.height(), 0, 1.0f, -1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();   

   glTranslatef(-m_camBounds.left, -m_camBounds.top, 0.0f);
   for(auto &layer : dp.drawQueue)
      for(auto &DO : layer)
         if(DO)DO->draw();

}

void DrawScene::renderObjectList(std::vector<DrawQueue> &queues)
{
   glViewport(m_vpBounds.left, m_vpBounds.top, m_vpBounds.right, m_vpBounds.bottom);
   if(m_scissor)
   {
      glScissor(m_scissorBounds.left, m_scissorBounds.top, m_scissorBounds.right, m_scissorBounds.bottom);
      glEnable(GL_SCISSOR_TEST);
   }
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, m_camBounds.width(), m_camBounds.height(), 0, 1.0f, -1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();   

   glTranslatef(-m_camBounds.left, -m_camBounds.top, 0.0f);
   for(auto &layer : queues)
      for(auto &DO : layer)
         if(DO)DO->draw();

   if(m_scissor)
      glDisable(GL_SCISSOR_TEST);

}

void DrawScene::draw()
{
   //draw passes
   for(auto &pass : m_passes)
      if(pass.second->fbo)
         renderFBOObjectList(*pass.second.get());

   ////draw main shit
   glBindFramebuffer(GL_FRAMEBUFFER, 0); 
   renderObjectList(m_drawQueue);

   //draw the passes
   if(m_scissor)
   {
      glScissor(m_scissorBounds.left, m_scissorBounds.top, m_scissorBounds.right, m_scissorBounds.bottom);
      glEnable(GL_SCISSOR_TEST);
   }

   for(auto &pass : m_passes)
      pass.second->fboTexture->draw();

   if(m_scissor)
      glDisable(GL_SCISSOR_TEST);
      

}

#include <GLFW/glfw3.h>

#include "Transform.h"

#include "Entity.h"

#include "RotationComponent.h"
#include "GraphicComponents.h"
#include "PositionComponent.h"

Transform buildTransformation(Entity &entity)
{
   Transform t;

   if(auto p = entity.getComponent<PositionComponent>())
   {
      t.offset = p->pos;
   }

   if(auto rot = entity.getComponent<RotationComponent>())
   {
      t.rotationAngle = rot->getAngle();
      t.rotationPoint = rot->getPoint();
   }

   if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
   {
      t.scale = gb->size;
      t.offset = Float2(t.offset.x - gb->size.x * gb->center.x, t.offset.y - gb->size.y * gb->center.y);
   }


   return t;
}

void applyGLTransformation(Transform t)
{
   //1. scale
   //2. Rotate
   //   A) Move to Origin (-rotpoint)
   //   B) Rotate
   //   C) translate back
   //3. Translate

   glTranslatef(t.offset.x, t.offset.y, 0.0f);
   glTranslatef(t.rotationPoint.x, t.rotationPoint.y, 0.0f);
   glRotatef(t.rotationAngle, 0.0f, 0.0f, 1.0f);
   glTranslatef(-t.rotationPoint.x, -t.rotationPoint.y, 0.0f);
   glScalef(t.scale.x, t.scale.y, 0.0f);
}
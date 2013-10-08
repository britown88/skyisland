#include <GLFW/glfw3.h>

#include "Transform.h"

#include "Entity.h"

#include "RotationComponent.h"

Transform buildTransformation(Entity &entity)
{
   Transform t;

   if(entity.hasComponent<RotationComponent>())
   {
      auto &rot = entity.getComponent<RotationComponent>();
      t.rotationAngle = rot.getAngle();
      t.rotationPoint = rot.getPoint();
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
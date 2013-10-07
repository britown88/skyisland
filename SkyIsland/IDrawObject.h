#pragma once

class IDrawObject
{
public:
   virtual ~IDrawObject(){}

   virtual void draw()=0;
};
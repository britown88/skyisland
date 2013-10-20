#pragma once

#include "Vector.h"
#include <string>
#include "IntrusiveLinkedList.h"
#include "StringTable.h"

class ITexture
{
public:
   IntrusiveListHook hook;

   virtual Int2 getSize() = 0;
   virtual int getBitsPerPixel() = 0;
   virtual unsigned int getGLHandle()=0;
   virtual InternString getFilePath()=0;

   virtual void acquire()=0;
   virtual void release()=0;

   virtual bool isLoaded()=0;
};

typedef IntrusiveList<ITexture, &ITexture::hook> TextureList;
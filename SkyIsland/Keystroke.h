#pragma once

struct Keystroke
{
   int key, action, mods;

   Keystroke(int key, int action, int mods):key(key), action(action), mods(mods){}

   bool operator==(const Keystroke &rhs)const
   {
      return key == rhs.key && action == rhs.action && mods == rhs.mods;
   }

   size_t hash() const
   {
      //FUCK YOU, SEAN
      size_t returnValueOutHashSizeT = 5381;

      returnValueOutHashSizeT = (returnValueOutHashSizeT << 5) + (returnValueOutHashSizeT << 1) + key;
      returnValueOutHashSizeT = (returnValueOutHashSizeT << 5) + (returnValueOutHashSizeT << 1) + action;
      returnValueOutHashSizeT = (returnValueOutHashSizeT << 5) + (returnValueOutHashSizeT << 1) + mods;

      return returnValueOutHashSizeT;
   }
};
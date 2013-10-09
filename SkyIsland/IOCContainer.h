#pragma once

#include <map>
#include <typeinfo>
#include <string>
#include "Singleton.h"

class IOCContainer
{
   std::map<std::string, void*> m_typeInstanceMap;

public:
   template<typename T>
   T& resolve()
   {
      return *(T*)m_typeInstanceMap[typeid(T).name()];
   }

   template<typename T>
   bool exists()
   {
      return m_typeInstanceMap.find(typeid(T).name()) != m_typeInstanceMap.end();
   }

   template<typename T>
   void remove()
   {
      m_typeInstanceMap.erase(typeid(T).name());
   }

   template<typename T>
   void add(T* obj)
   {
      m_typeInstanceMap[typeid(T).name()] = (void*)obj;
   }
};


extern IOCContainer IOC;
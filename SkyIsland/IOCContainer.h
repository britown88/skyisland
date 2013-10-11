#pragma once

#include <map>
#include <typeinfo>
#include <string>
#include <memory>

class IOCContainer
{
   std::map<std::string, std::shared_ptr<void>> m_typeInstanceMap;

public:
   template<typename T>
   T& resolve()
   {
      return *std::static_pointer_cast<T>(m_typeInstanceMap[typeid(T).name()]);
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
   void add(std::shared_ptr<T> obj)
   {
      m_typeInstanceMap[typeid(T).name()] = obj;
   }
};


extern IOCContainer IOC;
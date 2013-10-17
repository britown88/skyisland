#pragma once

#include <unordered_map>
#include <typeinfo>
#include <string>
#include <memory>

class IOCContainer
{
   std::unordered_map<int, std::shared_ptr<void>> m_typeInstanceMap;

public:
   template<typename T>
   std::shared_ptr<T> resolve()
   {
      if(!m_typeInstanceMap.empty() && m_typeInstanceMap.find(T::ID) != m_typeInstanceMap.end())
         return std::static_pointer_cast<T>(m_typeInstanceMap[T::ID]);
      else 
         return nullptr;
   }

   template<typename T>
   void remove()
   {
      m_typeInstanceMap.erase(T::ID);
   }

   template<typename T>
   void add(std::shared_ptr<T> obj)
   {
      m_typeInstanceMap[T::ID] = obj;
   }
};


extern IOCContainer IOC;
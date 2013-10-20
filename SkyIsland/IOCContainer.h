#pragma once

#include <unordered_map>
#include <typeinfo>
#include <string>
#include <memory>

#include <boost\optional.hpp>

class IOCContainer
{
   std::unordered_map<int, std::shared_ptr<void>> m_typeInstanceMap;

public:
   template<typename T>
   boost::optional<T&> resolve()
   {
      if(!m_typeInstanceMap.empty() && m_typeInstanceMap.find(T::ID) != m_typeInstanceMap.end())
         return *std::static_pointer_cast<T>(m_typeInstanceMap[T::ID]);
      else 
         return boost::none;
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
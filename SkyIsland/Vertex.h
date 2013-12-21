#pragma once

#include "Vector.h"
#include "Color.h"

#include <bitset>
#include <vector>

typedef int vint;//FUCK YOOOOOOUUUUUUU

enum class VertexComponent
{
   Position,
   Color,
   TextureCoordinate,
   COUNT
};

template<VertexComponent vc>
struct VertexComponentType;

template<>
struct VertexComponentType<VertexComponent::Position>
{
   typedef Float2 type;
};

template<>
struct VertexComponentType<VertexComponent::Color>
{
   typedef Colorf type;
};

template<>
struct VertexComponentType<VertexComponent::TextureCoordinate>
{
   typedef Float2 type;
};

inline size_t sizeOfComponent(VertexComponent vc)
{
   switch(vc)
   {
   case VertexComponent::Position:
      return sizeof(VertexComponentType<VertexComponent::Position>::type);
   case VertexComponent::Color:
      return sizeof(VertexComponentType<VertexComponent::Color>::type);
   case VertexComponent::TextureCoordinate:
      return sizeof(VertexComponentType<VertexComponent::TextureCoordinate>::type);
   }

   return 0;
}

typedef std::bitset<(size_t)VertexComponent::COUNT> VertexFlags;

//If you're reading this code comtime in the future I just want to remind 
//you that Sean is a fag and likes to suck a million cocks in space.
class VertexBuilder
{
   char *m_bytes;
   size_t *m_componentOffsets;
public:
   VertexBuilder(char *bytes, size_t *componentOffsets):m_bytes(bytes), m_componentOffsets(componentOffsets){}

   template<VertexComponent vc>
   VertexBuilder &with(typename VertexComponentType<vc>::type const &comp)
   {
      memcpy(m_bytes + m_componentOffsets[(int)vc], &comp, sizeof(comp));
      return *this;
   }
};

//TEN THOUSAND COCKS
class VertexIterator
{
   VertexFlags m_flags;
   size_t m_vertexSize;
   char *m_first, *m_last;
   size_t *m_offsets;

public:
   VertexIterator(VertexFlags flags, size_t vertexSize, char *first, char *last, size_t *offsets):
      m_flags(flags), m_vertexSize(vertexSize), m_first(first), m_last(last), m_offsets(offsets)
   {}

   bool hasMore()
   {
      return m_first != m_last;
   }
   
   void moveNext()
   {
      m_first += m_vertexSize;
   }

   template<VertexComponent vc>
   typename VertexComponentType<vc>::type *get()
   {
      return m_flags[(vint)vc] ? (VertexComponentType<vc>::type*)(m_first + m_offsets[(vint)vc]) : nullptr;
   }
};

class VertexList
{
   VertexFlags m_flags;
   size_t m_vertexSize;
   size_t m_componentOffset[VertexComponent::COUNT];

   std::vector<char> m_bytes;

public:
   VertexList(VertexFlags flags):m_flags(flags){build();}

   VertexList(const VertexList &rhs):
      m_flags(VertexFlags(rhs.m_flags)), m_vertexSize(rhs.m_vertexSize), 
      m_bytes(std::vector<char>(rhs.m_bytes))
   {
      for(int i = 0; i < (int)VertexComponent::COUNT; ++i)
         m_componentOffset[i] = rhs.m_componentOffset[i];
   }

   VertexList(VertexList && ref):
      m_flags(std::move(ref.m_flags)), m_vertexSize(ref.m_vertexSize), 
      m_bytes(std::move(ref.m_bytes))
   {
      for(int i = 0; i < (int)VertexComponent::COUNT; ++i)
         m_componentOffset[i] = ref.m_componentOffset[i];
   }

   void build()
   {
      m_vertexSize = 0;

      for(int i = 0; i < (int)VertexComponent::COUNT; ++i)
      {
         m_componentOffset[i] = m_vertexSize;

         if(m_flags[i])
            m_vertexSize += sizeOfComponent((VertexComponent)i);
      }
   }

   VertexIterator iterate()
   {
      return VertexIterator(m_flags, m_vertexSize, m_bytes.data(), m_bytes.data() + m_bytes.size(), m_componentOffset);
   }

   VertexBuilder addVertex()
   {
      //add bytes to end of vector for new shit
      m_bytes.resize(m_bytes.size() + m_vertexSize);

      VertexBuilder vb(m_bytes.data() + m_bytes.size() - m_vertexSize, m_componentOffset);
      return vb;
   }

   VertexIterator operator[](unsigned int i)
   {
      return VertexIterator(m_flags, m_vertexSize, m_bytes.data() + (i* m_vertexSize), m_bytes.data() + m_bytes.size(), m_componentOffset);
   }
};

class VertexListFactory
{
   VertexListFactory(){}//I DONT THINK YOU ARE COMPREHENDING JUST HOW MANY COCKS WE ARE TALKING HERE
   
   VertexFlags m_flags;

   friend VertexListFactory createVertexList();
public:

   VertexListFactory &with(VertexComponent vc)
   {
      m_flags[(vint)vc] = true;
      return *this;
   }

   VertexList build()
   {
      return VertexList(m_flags);
   }

};

inline VertexListFactory createVertexList()
{
   return VertexListFactory();
}

//createVertexList().with(VertexComponent::Position).build();

void drawGlVertices(VertexList &vl, std::vector<int> &faceList);
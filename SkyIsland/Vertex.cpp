#include "Vertex.h"

#include <GLFW/glfw3.h>

void drawGlVertices(VertexList &vl, std::vector<int> &faceList)
{
   glBegin(GL_TRIANGLES);
      for(int face : faceList)
      {
         auto v = vl[face];

         if(auto tc = v.get<VertexComponent::TextureCoordinate>())
            glTexCoord2fv((float*)tc);

         if(auto c = v.get<VertexComponent::Color>())
            glColor4fv((float*)c);

         if(auto pos = v.get<VertexComponent::Position>()) 
            glVertex2fv((float*)pos);
            
      }
   glEnd();
}
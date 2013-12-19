#include "TextureComponent.h"

#include "GLFW\glfw3.h"

TextureComponent::TextureComponent(InternString name):
   texture(name), size(Float2())
{
   blendS = GL_SRC_ALPHA;
   blendD = GL_ONE_MINUS_SRC_ALPHA;
}
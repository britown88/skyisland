#pragma once

#include "Color.h"
#include "StringTable.h"
#include <unordered_map>

class ColorFilter
{
public:
   InternString name;
   std::unordered_map<Color255, Color255, Color255Hash, Color255Comp> table;

   ColorFilter(InternString name):name(name){}
   ColorFilter(){}

};

class ColorFilterManager
{
public:
   static const int ID = 566953004;

   std::unordered_map<InternString, ColorFilter> filters;

};

void buildColorFilters();
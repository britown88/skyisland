#include "ColorFilter.h"
#include "IOCContainer.h"
#include "StringTable.h"

void buildColorFilters()
{
   auto &filters = IOC.resolve<ColorFilterManager>()->filters;
   auto st = IOC.resolve<StringTable>();

   ColorFilter redHair(st->get("redhair"));
   redHair.table.insert(std::make_pair(Color255(85, 85, 85), Color255(255, 85, 85)));
   redHair.table.insert(std::make_pair(Color255(145, 145, 145), Color255(255, 145, 145)));
   redHair.table.insert(std::make_pair(Color255(217, 217, 217), Color255(255, 217, 217)));
   redHair.table.insert(std::make_pair(Color255(242, 242, 242), Color255(255, 242, 242)));

   filters.insert(std::make_pair(st->get("redhair"), redHair));

   ColorFilter bluehair(st->get("bluehair"));
   bluehair.table.insert(std::make_pair(Color255(85, 85, 85), Color255(85, 85, 255)));
   bluehair.table.insert(std::make_pair(Color255(145, 145, 145), Color255(145, 145, 255)));
   bluehair.table.insert(std::make_pair(Color255(217, 217, 217), Color255(217, 217, 255)));
   bluehair.table.insert(std::make_pair(Color255(242, 242, 242), Color255(242, 242, 255)));

   filters.insert(std::make_pair(st->get("bluehair"), bluehair));


}
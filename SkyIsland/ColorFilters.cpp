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

   ColorFilter redclothes(st->get("redclothes"));
   redclothes.table.insert(std::make_pair(Color255(13, 47, 103), Color255(103, 47, 13)));
   redclothes.table.insert(std::make_pair(Color255(23, 82, 180), Color255(180, 82, 23)));
   redclothes.table.insert(std::make_pair(Color255(31, 113, 248), Color255(248, 113, 31)));

   filters.insert(std::make_pair(st->get("redclothes"), redclothes));

   ColorFilter greenclothes(st->get("greenclothes"));
   greenclothes.table.insert(std::make_pair(Color255(13, 47, 103), Color255(13, 103, 47)));
   greenclothes.table.insert(std::make_pair(Color255(23, 82, 180), Color255(23, 180, 82)));
   greenclothes.table.insert(std::make_pair(Color255(31, 113, 248), Color255(31, 248, 113)));

   filters.insert(std::make_pair(st->get("greenclothes"), greenclothes));


}
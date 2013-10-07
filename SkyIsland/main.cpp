#include "SkyApp.h"

int main(void)
{
   auto app = getSkyApp();

   app->start();

   while(true)
   {
      app->step();

      if(!app->isRunning())           
         break;            
   }  

   app->terminate(); 
}
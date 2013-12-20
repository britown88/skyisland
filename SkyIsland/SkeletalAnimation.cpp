#include "SkeletalAnimation.h"
#include "Interpolation.h"
#include "Trig.h"
#include <boost/algorithm/string.hpp>
#include "IOCContainer.h"
#include "StringTable.h"

SkeletalAnimation::SkeletalAnimation(float framesPerSecond):
   m_framesPerSecond(framesPerSecond), m_frameCount(0)
{
}


SkeletalFrame &SkeletalAnimation::addFrame(std::string partName, int frame)
{
   auto st = IOC.resolve<StringTable>();
   m_frameCount = std::max(m_frameCount, frame);

   SkeletalFrameObject *object = nullptr;
   for(auto &obj : m_frameObjs)
      if(obj.fullName == partName)
      {
         object = &obj;
         break;
      }

   if(!object)
   {
      std::vector<std::string> nameList;
      boost::split(nameList, partName, boost::is_any_of("/"));
      std::vector<InternString> internNameList;
      for(auto &name : nameList)
         internNameList.push_back(st->get(name.c_str()));

      m_frameObjs.push_back(SkeletalFrameObject(partName, std::move(internNameList)));
      object = &(m_frameObjs.back());
   }

   object->frames.push_back(SkeletalFrame(frame, Transform()));

   return object->frames.back();   

}

void SkeletalAnimation::updateEntity(float timeElapsed, Entity &entity)
{
   int frame = (int)(timeElapsed * m_framesPerSecond);

   if(frame > m_frameCount)
      if(m_loop)
         frame = frame % m_frameCount;
      else
         frame = m_frameCount;

   auto snc = entity.getComponent<SkeletalNodeComponent>();
   std::shared_ptr<SkeletalFrame> startFrame;
   if(!snc) return;

   for(auto &obj : m_frameObjs)
   {
      //find frameIndex
      int frameCount = obj.frames.size();
      for(int i = 0; i < frameCount - 1; ++i)
      {
         if(obj.frames[i].frame > frame || obj.frames[i].frame <= frame && obj.frames[i+1].frame > frame)
         {
            //determine if the object exists
            SNodeConnection *conn = nullptr;

            auto searchSnc = &(*snc);
            for(int i = 0; i < obj.name.size(); ++i)
            {
               if(searchSnc->connections.find(obj.name[i]) != searchSnc->connections.end())
               {
                  //name found
                  if(i == obj.name.size() - 1)
                  {
                     //set the right connection
                     conn = &searchSnc->connections[obj.name[i]];
                     break;
                  }
                  else
                  {
                     //reset searchsnc
                     if(auto newsnc = searchSnc->connections[obj.name[i]].entity->getComponent<SkeletalNodeComponent>())
                        searchSnc = &(*newsnc);
                     else 
                        break;
                  }
               }
               else
                  break;
            }

            //no connection was found by this name
            if(!conn)
               return;

            SkeletalFrame *frame1, *frame2;

            //first frame
            if(obj.frames[i].frame > frame)
            {
               if(!conn->startFrameSet)
               {
                  //set first frame to current frame transform
                  conn->startFrame = Transform(conn->transform);
                  conn->startFrameSet = true;
               }

               frame2 = &obj.frames[i];
               startFrame = std::make_shared<SkeletalFrame>(0, conn->startFrame);
               frame1 = startFrame.get();

            }
            else
            {
               frame1 = &obj.frames[i];
               frame2 = &obj.frames[i+1];
               conn->startFrameSet = false;
            }

            //now interpolate the data
            auto &t1 = frame1->transform;
            auto &t2 = frame2->transform;
            
            float delta = (float)(frame - frame1->frame) / (float)(frame2->frame - frame1->frame);
            auto t = Transform();

            //position
            t.offset = Float2(
               t1.offset.x + LinearInterpolate(t1.offset.x, t2.offset.x, delta),
               t1.offset.y + LinearInterpolate(t1.offset.y, t2.offset.y, delta));

            t.rotationAngle = t1.rotationAngle + LinearInterpolate(t1.rotationAngle, t2.rotationAngle, delta);

            if(frame1->layerSet)
               conn->layer = frame1->layer;

            //set the final transform
            conn->transform = t;

            break;
         }
      }

   }
}
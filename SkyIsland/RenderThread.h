#pragma once

#include "Renderer.h"
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

class RenderThread
{
   std::mutex m_mutex;
   std::thread m_thread;
   Renderer::SceneList m_queueFilling, m_queueCurrent;
   bool m_queueUpdated;
   std::atomic_bool m_isRunning;

   void _run();
public:

   RenderThread();

   void start();
   void stop();

   void resetQueue(Renderer::SceneList queue);

};
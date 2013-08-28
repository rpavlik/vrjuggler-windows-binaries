/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2010 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _VRJ_PF_INPUT_HANDLER_H_
#define _VRJ_PF_INPUT_HANDLER_H_

#include <vrj/Draw/Pf/Config.h>

#include <string>

#ifndef VPR_OS_Windows
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#endif

#include <Performer/pf.h>

#include <jccl/Config/ConfigElement.h>
#include <jccl/Config/ConfigElementPtr.h>

#ifdef VPR_OS_Windows
#  include <gadget/Devices/KeyboardMouseDevice/InputAreaWin32.h>
#else
#  include <gadget/Devices/KeyboardMouseDevice/InputAreaXWin.h>
#endif

#include <vrj/Display/Display.h>
#include <vrj/Util/Debug.h>


#ifdef VPR_OS_Windows
typedef struct _pfuWin32Event
{
  HWND hwnd;
  UINT uMsg;
  WPARAM wParam; // we should copy this and lParam
  LPARAM lParam;
  double time;
} pfuWin32Event;
#endif

namespace vrj
{

namespace pf
{

#ifdef VPR_OS_Windows
LRESULT CALLBACK eventCallback(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
#endif

/** \class vrj::pf::InputHandler InputHandler.h vrj/Draw/Pf/InputHandler.h
 *
 * Performer input handler.
 *
 * @note This class was renamed from vrj::PfInputHandler in VR Juggler 2.3.11.
 */
class InputHandler
#ifdef VPR_OS_Windows
   : public gadget::InputAreaWin32
#else
   : public gadget::InputAreaXWin
#endif
{
public:
   /**
    * Creates an adaptor which will route events from Performer into
    * platform-specific events.
    *
    * @param pipeWindow  Performer window to grab events from.
    * @param displayName The name of the display.
    */
   InputHandler(pfPipeWindow* pipeWindow, const std::string& displayName);

   /**
    * Configures the adaptor.
    *
    * @param e    ConfigElement that contains all configuration
    *             information to configure an InputArea.
    * @param disp VR Juggler display which contains size info.
    */
   void config(jccl::ConfigElementPtr e, vrj::DisplayPtr disp)
   {
      gadget::InputArea::config(e);
      int originX, originY, width, height;
      disp->getOriginAndSize(originX, originY, width, height);
      mWidth = (unsigned int)width;
      mHeight = (unsigned int)height;
   }

   void checkEvents();
#ifndef VPR_OS_Windows
   /**
    * Grab events from Performer window and sends them to
    * InputAreaXWin::handleEvent() or InputAreaWin32::handleEvent()
    *
    * @pre openConnection has been called.
    */
   void handleEvents();

   /**
    * Handles error output from X services
    * Traps X errors instead of killing the application
    */
   static int errorHandler( ::Display* display, XErrorEvent* e );

private:
   void openConnection();
#endif
   
private:
   std::string     mName;
   pfPipe*         mPipe;
   pfPipeWindow*   mPipeWindow;
};

}

}


#endif

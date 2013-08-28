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

#ifndef _PERF_PROBE_H_
#define _PERF_PROBE_H_

#include <deque>
#include <sstream>

#if defined(__APPLE__)
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

#include <vpr/Util/Interval.h>
#include <vrj/Draw/OpenGL/ContextData.h>
#include <Text.h>


class PerfProbe
{
public:
   PerfProbe();

public:
   /** Get the stream used for overlay text. */
   std::stringstream& getStream()
   { return mOverlayTextStream;  }

public:
   /** Method to be called once per frame.
    * Used to update data like frame rate.  Call from app::preFrame
    */
   void update();

   /** Draw the performance data.
    * Call from draw.
    */
   void draw();

protected:
   void drawOverlayText();

   void drawFrameRateGraph();

public:
   std::deque<float>    mFrameTimes;      /**< Used to track most recent set of frame times. */
   vpr::Interval        mLastUpdateTime;  /**< Time of the last update. */
   float                mFrameRate;       /**< Running inst average frame rate. */

   std::stringstream    mOverlayTextStream;  /**< Text to write out each frame. */
   std::string          mOverlayTextToDraw;
   vrj::opengl::ContextData<Text> mText;  /**< Context specific copy of text. */

   std::deque<float>    mFrameRateHistory;
   unsigned             mNumTrackedFrames;   /**< Number of frame rates to keep. */
   float                mMaxFrameRate;
};

#endif

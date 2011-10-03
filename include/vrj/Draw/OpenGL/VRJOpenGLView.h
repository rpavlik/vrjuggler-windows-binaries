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

#import <AppKit/NSOpenGLView.h>


namespace vrj
{

namespace opengl
{

class WindowCocoa;

}

}

/**
 * A custom Cocoa view class used for managing an OpenGL context. It must be
 * the content view for an NSWindow instance. This holds a pointer back to the
 * vrj::opengl::WindowCocoa object that keeps track of an NSWindow instance
 * for which this object is a view. This view will update the state of the
 * vrj:opengl::WindowCocoa object as appropriate, usually as a result of
 * resize events.
 *
 * @since 2.1.21
 *
 * @note This class was renamed from GlViewCocoa in VR Juggler 2.3.11.
 */
@interface VRJOpenGLView : NSOpenGLView
{
   vrj::opengl::WindowCocoa* mVrjWindow; /**< The window using this view. */

   /** @name Full Screen State */
   //@{
   /** Indicates whether this view is in a full screen window. */
   BOOL mFullScreen;

   /**
    * The Core Graphics display ID for the screen on which this view is
    * rendered.
    */
   CGDirectDisplayID mDisplayID;

#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
   CGDisplayModeRef mOrigDisplayMode;
#else
   NSDictionary* mOrigDisplayMode;
#endif
   //@}

   /**
    * Indicates whether this view should handle keyboard and mouse events.
    * If so, they are handed off to \c mVrjWindow (as subclass of
    * gadget::InputAreaCocoa).
    */
   BOOL mHandleInput;

   /**
    * Indicates whether the mouse cursor should be hidden whenever the mouse
    * is within the tracking rectnagle of this view.
    */
   BOOL mShouldHideCursor;

   /**
    * Tracking rectangle for mouse cursor hidding. If there is no need for
    * hiding the mouse cursor (based on the display window conofiguration),
    * then this will be 0.
    */
   NSTrackingRectTag mTrackingRect;
}

   /**
    * The designated initializer for this class. This creates a pixel format
    * object needed for the OpenGL context. If creation of the pixel format
    * object fails, then this method throws an NSException. Callers should
    * also test for a nil return value in case initialization through the
    * use of the NSOpenGLView initWithFrame:pixelFormat: initializer.
    *
    * @param frameFrect  The frame rectangle for this view. In general, this
    *                    should be identifical to the frame rectangle used for
    *                    the containing NSWindow.
    * @param window      The vrj::opengl::WindowCocoa instance to be
    *                    associated with this view.
    * @param screen      The screen on which this view will be used.
    * @param handleInput A Boolean flag indicating whether this view should
    *                    handle keyboard and mouse input events.
    *
    * @return self on successful initialization or nil on failure.
    *
    * @throw NSException is thrown if a pixel format object meeting the
    *        requirements of the vrj::Display instance of \p window.
    */
   -(id) initWithFrame:(NSRect) frameRect
              glWindow:(vrj::opengl::WindowCocoa*) window
                screen:(NSScreen*) screen
         inputHandling:(BOOL) handleInput;
@end

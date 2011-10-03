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

#ifndef _GADGET_KEYBOARD_MOUSE_DEVICE_H_
#define _GADGET_KEYBOARD_MOUSE_DEVICE_H_

#include <gadget/gadgetConfig.h>

#include <vpr/Sync/Mutex.h>

#include <gadget/Type/Input.h>
#include <gadget/Type/KeyboardMouse.h>
#include <gadget/Type/InputMixer.h>
#include <gadget/Type/KeyboardMouse/Event.h>

#include <jccl/Config/ConfigElementPtr.h>

#include <vpr/Util/Singleton.h>


namespace gadget
{

/** \class KeyboardMouseDevice KeyboardMouseDevice.h gadget/Devices/KeyboardMouseDevice/KeyboardMouseDevice.h
 *
 * Base class for keyboard/mouse input devices.
 */
class KeyboardMouseDevice : public InputMixer<Input,KeyboardMouse>
{
public:  // --- Internal helper class ----- //
   /**
    * Holds list of registered windows that may be used for keyboard/moues
    * Input.  This is used by KeyboardMouseDevice routines to find any windows
    * opened by other system components but that we still want to get input
    * from.
    */
   class KeyboardMouseDeviceRegistry
   {
   public:
      struct KeyboardMouseDeviceInfo
      {
         std::string    mSourceName;   /**< The KeyboardMouseDevice name. */
         KeyboardMouseDevice*   mKeyboardMouseDevice;   /**< The handle to the KeyboardMouseDevice. */
      };

   public:
      KeyboardMouseDeviceRegistry()
      {;}

      /** Add the given window to the registry.
       * @return true if window is added, false if matches existing window name.
       */
      bool addKeyboardMouseDevice(const std::string& name,
                                  KeyboardMouseDeviceInfo eventSourceInfo);

      /** Remove the window with the id of "name". */
      void removeKeyboardMouseDevice(const std::string& name);

      /** Get the window information. */
      bool getKeyboardMouseDevice(const std::string& name,
                                  KeyboardMouseDeviceInfo& eventSourceInfo);

   protected:
      typedef std::map<std::string, KeyboardMouseDeviceInfo> event_source_map_t;

      /**< Map Window name to the data needed for it. */
      event_source_map_t    mKeyboardMouseDeviceMap;

      vprSingletonHeader(KeyboardMouseDeviceRegistry);
   };

public:

   KeyboardMouseDevice();

   ~KeyboardMouseDevice();

   virtual bool config(jccl::ConfigElementPtr e);

   /** Start the windows sampling. */
   virtual bool startSampling()
   {
      return true;
   }

   /** Stop window sampling. */
   virtual bool stopSampling()
   {
      return true;
   }

   /** Dop nothing. */
   virtual bool sample()
   {
      // Do nothing
      return true;
   }

   /** Update the keys and event queue data structures with current data. */
   virtual void updateData();

   /** Return the element type associated with this device type. */
   static std::string getElementType();

   /** @name Property Accessors */
   //@{
   /**
    * Indicates whether mouse scroll events should be interpreted as button
    * press/release events (true) or as actual scroll events (false). The
    * former behavior is deprecated with the release of Gadgeteer 2.0. New
    * code should handle scrolling as scroll events.
    *
    * @return \c true is returned if scroll events from the native windowing
    *         system are to be handled as button press/release events when
    *         constructnig a gadget::MouseEvent object. \c false is returned
    *         if scroll events are to be handled as proper scroll events.
    *
    * @see gadget::MouseEvent
    *
    * @since 1.3.22
    */
   bool useButtonsForScrolling() const
   {
      return mUseButtonsForScrolling;
   }

   /**
    * Returns the button configured to be treated as a "scroll up" event.
    * This value is only valid if useButtonsForScrolling() returns true. If
    * useButtonsForScrolling() is false, then gadget::KEY_NONE is returned.
    *
    * @pre useButtonsForScrolling() returns true.
    *
    * @return The gadget::Keys value representing the value configured to be
    *         a "scroll up" event if useButtonsForScrolling() returns true.
    *         gadget::KEY_NONE is returned if said method returns false.
    *
    * @since 1.3.22
    */
   gadget::Keys getScrollUpButton() const
   {
      return mScrollUpButton;
   }

   /**
    * Returns the button configured to be treated as a "scroll down" event.
    * This value is only valid if useButtonsForScrolling() returns true. If
    * useButtonsForScrolling() is false, then gadget::KEY_NONE is returned.
    *
    * @pre useButtonsForScrolling() returns true.
    *
    * @return The gadget::Keys value representing the value configured to be
    *         a "scroll down" event if useButtonsForScrolling() returns true.
    *         gadget::KEY_NONE is returned if said method returns false.
    *
    * @since 1.3.22
    */
   gadget::Keys getScrollDownButton() const
   {
      return mScrollDownButton;
   }

   /**
    * Returns the button configured to be treated as a "scroll left" event.
    * This value is only valid if useButtonsForScrolling() returns true. If
    * useButtonsForScrolling() is false, then gadget::KEY_NONE is returned.
    *
    * @pre useButtonsForScrolling() returns true.
    *
    * @return The gadget::Keys value representing the value configured to be
    *         a "scroll left" event if useButtonsForScrolling() returns true.
    *         gadget::KEY_NONE is returned if said method returns false.
    *
    * @since 1.3.22
    */
   gadget::Keys getScrollLeftButton() const
   {
      return mScrollLeftButton;
   }

   /**
    * Returns the button configured to be treated as a "scroll right" event.
    * This value is only valid if useButtonsForScrolling() returns true. If
    * useButtonsForScrolling() is false, then gadget::KEY_NONE is returned.
    *
    * @pre useButtonsForScrolling() returns true.
    *
    * @return The gadget::Keys value representing the value configured to be
    *         a "scroll right" event if useButtonsForScrolling() returns true.
    *         gadget::KEY_NONE is returned if said method returns false.
    *
    * @since 1.3.22
    */
   gadget::Keys getScrollRightButton() const
   {
      return mScrollRightButton;
   }
   //@}

private:
   float        mMouseSensitivity;
   bool         mUseButtonsForScrolling;
   gadget::Keys mScrollUpButton;
   gadget::Keys mScrollDownButton;
   gadget::Keys mScrollLeftButton;
   gadget::Keys mScrollRightButton;

//XXX: Fix this!
public:
   vpr::Mutex   mKeysLock;   /**< Must hold this lock when accessing m_keys. */

   // NOTE: This driver does not use the normal triple buffering mechanism.
   // Instead, it just uses a modified double buffering system.

   /** @name Event window state holders */
   //@{
   /**
    * (0,*): The num key presses during an UpdateData (ie. How many keypress
    * events).
    */
   int mKeys[gadget::LAST_KEY];

   /**
    * (0,1): The real keyboard state, all events processed (ie. what is the
    * key now).
    */
   int mRealkeys[gadget::LAST_KEY];
   //@}
};


} // end namespace

#endif

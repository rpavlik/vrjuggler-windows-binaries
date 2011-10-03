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

#ifndef _GADGET_SIM_ANALOG_H
#define _GADGET_SIM_ANALOG_H
//#pragma once

#include <gadget/gadgetConfig.h>
#include <vector>

#include <jccl/Config/ConfigElementPtr.h>
#include <gadget/Type/InputBaseTypes.h>
#include <gadget/Type/Input.h>
#include <gadget/Type/Analog.h>
#include <gadget/Devices/Sim/SimInput.h>


namespace gadget
{

/** \class SimAnalog SimAnalog.h gadget/Devices/Sim/SimAnalog.h
 *
 * Simulated analog device.
 * Simulates an analog device from a keyboard device.
 * It allows any number of simulated analog devices to be created.
 *
 * This class should not be used directly by the user.
 */
class SimAnalog
   : public siminput_input_analog
{
public:
   SimAnalog();

   virtual ~SimAnalog();

   /**
    * Reads the minimum and maximum value configuration information for this
    * analog device.
    *
    * @param element The config element for an analog device.  It must derive
    *                from the base config element type 'analog'.
    */
   virtual bool config(jccl::ConfigElementPtr element);

   /** These functions don't do anything. */
   bool startSampling()
   {
      return true;
   }

   bool stopSampling()
   {
      return true;
   }

   bool sample()
   {
      return true;
   }

   /** Updates the data. */
   virtual void updateData();

   static std::string getElementType();

   virtual std::vector<KeyModPair> getUpKeys()
   {
      return mSimKeysUp;
   }

   virtual std::vector<KeyModPair> getDownKeys()
   {
      return mSimKeysDown;
   }

private:
   std::vector<AnalogData>    mAnaData;      /**< The analog data that we have */
   std::vector<KeyModPair>    mSimKeysUp;    /**< The keys to press for moving analog up */
   std::vector<KeyModPair>    mSimKeysDown;  /**< The keys to press for moving analog up */
   float                      mAnaStep;      /**< The analog step size */
   float                      mInitialValue; /**< The inital value for all inputs */
   bool                       mAutoReturn;   /**< Return to initial value when no key is pressed */
};

} // End of gadget namespace

#endif

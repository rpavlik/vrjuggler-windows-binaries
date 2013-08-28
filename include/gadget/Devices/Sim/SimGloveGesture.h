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

#ifndef _GADGET_SIM_GLOVE_GESTURE_H_
#define _GADGET_SIM_GLOVE_GESTURE_H_

#include <gadget/gadgetConfig.h>
#include <vector>
#include <gadget/Type/Input.h>
#include <gadget/Type/Digital.h>
#include <gadget/Type/GloveGesture.h>
#include <gadget/Type/Glove.h>
#include <gadget/Type/Gesture.h>
#include <gadget/Devices/Sim/SimInput.h>

namespace gadget
{

/** \class SimGloveGesture SimGloveGesture.h gadget/Devices/Sim/SimGloveGesture.h
 *
 * Simulated glove class.  This class simulates a gesture input device.
 * By default the glove is in gesture 0.
 */
class SimGloveGesture
   :  virtual public Input, public GloveGesture,  public Glove,  public Digital, public SimInput
{
public:
   /** Constructs a SimGloveGesture. */
   SimGloveGesture() {;}

   ~SimGloveGesture()
   {
      /* Do nothing. */ ;
   }

   virtual bool config(jccl::ConfigElementPtr element);

   /**
    * Get the current gesture.
    * @return id of current gesture.
    */
   virtual int getGesture() const;

   virtual const DigitalData getDigitalData(int devNum = 0);

   /**
    * Loads trained data for the gesture object.
    * Loads the file for trained data.
    */
   void loadTrainedFile(std::string fileName);

   bool startSampling() { return 1; }
   bool stopSampling() { return 1; }
   bool sample() { return 1; }

   /** Updates the device data. */
   void updateData ();

   static std::string getElementType();

   /*** These are not supported in sim ***/
   void saveTrainedFile(std::string fileName)
   {
      boost::ignore_unused_variable_warning(fileName);
   }

   void loadSamplesFile(std::string filename)
   {
      boost::ignore_unused_variable_warning(filename);
   }

   void saveSamplesFile(std::string filename)
   {
      boost::ignore_unused_variable_warning(filename);
   }

   void clearSamples(int gestureId = -1)
   {
      boost::ignore_unused_variable_warning(gestureId);
   }

   void addSample(int gestureId)
   {
      boost::ignore_unused_variable_warning(gestureId);
   }

   void train() { ; }

private:
   std::vector<KeyModPair> mSimKeys;    /**<  The keys to press for the gestures */
   int             mCurGesture;   /**< The current gesture id */
   DigitalData     mDigitalData;  /**< Result of table lookup of mCurGesture */
};

}

#endif

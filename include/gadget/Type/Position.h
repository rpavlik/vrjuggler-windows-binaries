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

/////////////////////////////////////////////////////////////////////////
//
// positional tracker base class
//
////////////////////////////////////////////////////////////////////////

#ifndef _GADGET_POSITION_H_
#define _GADGET_POSITION_H_

#include <gadget/gadgetConfig.h>

#include <typeinfo>
#include <vector>
#include <boost/noncopyable.hpp>

#include <gadget/Type/Input.h>
#include <gadget/Type/PositionData.h>
#include <gadget/Type/SampleBuffer.h>

#include <gmtl/Matrix.h>
#include <vpr/Util/Debug.h>
#include <vpr/IO/SerializableObject.h>
#include <gadget/Type/PositionPtr.h>


namespace gadget
{

class PositionFilter;
const unsigned short MSG_DATA_POS = 422;

/** \class Position Position.h gadget/Type/Position.h
 *
 * Position is the abstract base class from which devices with positional
 * (translation and/or rotation) data derive (through gadget::InputMixer).
 * This is in addition to gadget::Input.  gadget::Input provides pure virtual
 * function constraints in the following functions: startSampling(),
 * stopSampling(), sample(), and updateData().
 *
 * gadget::Position adds the function getPositionData() for retreiving the
 * received positional data.  This is similar to the additions made by
 * gadget::Analog and gadget::Digital.
 *
 * @see Input, InputMixer
 */
class GADGET_CLASS_API Position
   : public vpr::SerializableObject
   , boost::noncopyable
{
public:
   typedef gadget::SampleBuffer<PositionData> SampleBuffer_t;

protected:
   /** Constructor */
   Position();

public:
   /**
    * Creates a Position instance and returns it wrapped in a
    * PositionPtr object.
    *
    * @since 1.3.7
    */
   static PositionPtr create();

   /** Destructor */
   virtual ~Position();

   virtual bool config(jccl::ConfigElementPtr e);

   /** Get positional data. */
   const PositionData& getPositionData(int devNum = 0) const;

   /**
    * Helper method to add a collection of positional samples to the sample
    * buffers.  This MUST be called by all positional devices to add a new
    * sample.  The data samples passed in will then be modified by any local
    * filters.  The tracker transformations will occur in those filters, so
    * the data does not need to be transformed before being passed in.
    *
    * @post The given positional samples are added to the buffers, and the
    *       local filters are run on the new samples.
    *
    * @param posSample A vector of PositionData objects that represent the
    *                  newest samples taken.
    */
   void addPositionSample(std::vector< PositionData > posSample);

   /**
    * Swaps the positional data buffers.
    *
    * @post If the ready queue has values, then those values are copied from
    *       the ready queue to the stable queue.  If not, then stable queue
    *       is not changed.
    */
   void swapPositionBuffers()
   {
      mPosSamples.swapBuffers();
   }

   /**
    * Returns the Input type name used to map into the BaseTypeFactory. In a 
    * device driver, do not override this method unless the device driver is
    * also going to be implementing a new core Input device type.
    */
   virtual std::string getInputTypeName()
   {
      return std::string("Position");
   }

   /**
    * Serializes this object into the given object writer.
    *
    * @param writer The object writer to which this object will be serialized.
    *
    * @throw vpr::IOException is thrown if serialization fails.
    */
   virtual void writeObject(vpr::ObjectWriter* writer);

   /**
    * De-serializes this object.
    *
    * @param reader The object reader from which this object will be
    *               de-serialized.
    *
    * @throw vpr::IOException is thrown if de-serialization fails.
    */
   virtual void readObject(vpr::ObjectReader* reader);

   /**
    * Returns the current stable sample buffers for this device.
    */
   const SampleBuffer_t::buffer_t& getPositionDataBuffer() const
   {
      return mPosSamples.stableBuffer();
   }

protected:
   PositionData      mDefaultValue;   /**< Default positional value to return */

private:
   std::vector<PositionFilter*>  mPositionFilters;    /**< The active filters that are to be used */
   SampleBuffer_t                mPosSamples;         /**< Position samples */
};

} // End of gadget namespace

#endif

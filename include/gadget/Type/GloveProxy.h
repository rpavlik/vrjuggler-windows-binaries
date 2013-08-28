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
// Glove proxy class
//
////////////////////////////////////////////////////////////////////////

#ifndef _GADGET_GLOVE_PROXY_H_
#define _GADGET_GLOVE_PROXY_H_

#include <gadget/gadgetConfig.h>
#include <math.h>

#include <gadget/Type/Glove.h>
#include <gadget/Type/Proxy.h>
#include <gadget/Type/GloveProxyPtr.h>

namespace gadget
{

/** \class GloveProxy GloveProxy.h gadget/Type/GloveProxy.h
 *
 * Glove proxy class.
 */
class GADGET_CLASS_API GloveProxy : public TypedProxy<Glove>
{
protected:
   /**
    * Constructs the proxy to point to the given glove device and sub-unit
    * number.
    */
   GloveProxy(const std::string& deviceName = "UnknownGlove",
              const int unitNum = -1);

public:
   /**
    * Creates a GloveProxy instance and returns it wrapped in a
    * GloveProxyPtr object.
    *
    * @since 1.3.7
    */
   static GloveProxyPtr create(const std::string& deviceName = "UnknownGlove",
                               const int unitNum = -1);

   virtual ~GloveProxy();

   const gmtl::Vec3f getTipVector(const GloveData::GloveComponent component) 
      const
   {
      if(isStupefied())
      {
         return gmtl::Vec3f(0,0,0);
      }
      else
      {
         return mTypedDevice->getTipVector(component,mUnitNum);
      }
   }

   const gmtl::Matrix44f
   getTipTransform(const GloveData::GloveComponent component) const
   {
      if(isStupefied())
      {
         return gmtl::Matrix44f();
      }
      else
      {
         return mTypedDevice->getTipTransform(component,mUnitNum);
      }
   }
  
   const gmtl::Matrix44f
   getJointTransform(const GloveData::GloveComponent component,
                     const GloveData::GloveJoint joint)
      const
   {
      if(isStupefied())
      {
         return gmtl::Matrix44f();
      }
      else
      {
         return mTypedDevice->getJointTransform(component, joint, mUnitNum);
      }
   }

   const GloveData getData() const
   {
      if(isStupefied())
      {
         return GloveData();
      }
      else
      {
         return mTypedDevice->getGloveData(mUnitNum);
      }
   }

   /** Returns time of last update. */
   vpr::Interval getTimeStamp() const;

   /**
    * Returns a pointer to the device held by this proxy.
    *
    * @deprecated Use getTypedInputDevice() for forward compatibility with the
    *             next major release of Gadgeteer.
    */
   const GlovePtr getGlovePtr() const
   {
      if(isStupefied())
      {
         return GlovePtr();
      }
      else
      {
         return mTypedDevice;
      }
   }

   /** Returns the subUnit number that this proxy points to. */
   int getUnit() const
   {
      return mUnitNum;
   }

   bool isVisible() const
   {
      return mVisible;
   }

   static std::string getElementType();

   bool config(jccl::ConfigElementPtr element);

private:
   /** Should we be drawn on the screen? */
   bool mVisible;

   /** The sub-unit number to use in the device. */
   int mUnitNum;
};

} // End of gadget namespace

#endif

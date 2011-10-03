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

#ifndef _VRJ_PF_BASIC_SIMULATOR_H_
#define _VRJ_PF_BASIC_SIMULATOR_H_

#include <vrj/Draw/Pf/Config.h>

#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>

#include <jccl/Config/ConfigElementPtr.h>
#include <gadget/Type/PositionInterface.h>

#include <vrj/Draw/Pf/SimInterface.h>



namespace vrj
{

namespace pf
{

/** \class vrj::pf::BasicSimulator BasicSimulator.h vrj/Draw/Pf/BasicSimulator.h
 *
 * Interface for objects that wish to perform simulator function with an
 * OpenGL Performer application.
 *
 * @note This class was renamed from vrj::PfBasicSimulator in VR Juggler
 *       2.3.11.
 */
class BasicSimulator : public vrj::pf::SimInterface
{
public:   
   BasicSimulator();

   virtual ~BasicSimulator() {}

   /**
    * Configures the basic simulator config
    *
    * @pre element is a valid configuration element.
    * @post It should be configured
    */
   virtual bool config(jccl::ConfigElementPtr element);

   static std::string getElementType()
   {
      return std::string("default_simulator");
   }

   virtual void initialize(SimViewportPtr simVp)
   {
      mSimViewport = simVp;
   }

   /**
    * Sets the keyboard/mouse device the simulator can use to get input from
    * the user.
    */
   virtual void setKeyboardMouse(gadget::KeyboardMouseInterface kmInterface);

public:
   const gmtl::Matrix44f& getCameraPos()
   {
      return mCameraPos;
   }

   const gmtl::Matrix44f& getHeadPos()
   {
      return mHeadPos;
   }

   const gmtl::Matrix44f& getWandPos()
   {
      return mWandPos;
   }

   virtual void updateProjectionData(const float positionScale,
                                     ProjectionPtr leftProj,
                                     ProjectionPtr rightProj);

   /** Update internal simulator data. */
   void updateInternalData(float positionScale);

public:  // Sim Drawing parameters
/*
   bool shouldDrawProjections()
   {
      return mDrawProjections;
   }

   const gmtl::Vec3f& getSurfaceColor()
   {
      return mSurfaceColor;
   }
*/
   virtual void updateSimulatorSceneGraph();
   bool configPerformerAPI(jccl::ConfigElementPtr element);
   void initSimulatorGraph();

protected:
   SimViewportPtr mSimViewport;

   /** @name Drawing attributes */
   //@{
   bool           mDrawProjections;       /**< Should we draw projections */
   gmtl::Vec3f    mSurfaceColor;   /**< Color to draw surfaces */
   //@}

   gadget::PositionInterface mCamera; /**< Proxy interfaces to devices needed */
   gadget::PositionInterface mWand;

   gmtl::Matrix44f    mCameraPos;    /**< The data about the position of all this stuff */
   gmtl::Matrix44f    mHeadPos;
   gmtl::Matrix44f    mWandPos;
   
   pfScene*          mRootWithSim;     /**< The root with the simulator group & the sceneRoot */

   /** @name Simulator stuff */
   //@{
   pfGroup*          mSimTree;      /**< The simulator scene graph */
   pfDCS*            mHeadDCS;      /**< The DCS above the head */
   pfDCS*            mWandDCS;      /**< The DCS above the wand */
   std::string       mHeadModel;    /**< The head model file path */
   std::string       mWandModel;    /**< The wand model file path */
   //@}
};

}

}


#endif

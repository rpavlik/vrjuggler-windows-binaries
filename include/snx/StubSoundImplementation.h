/****************** <SNX heading BEGIN do not edit this line> *****************
 *
 * sonix
 *
 * Original Authors:
 *   Kevin Meinert, Carolina Cruz-Neira
 *
 ****************** <SNX heading END do not edit this line> ******************/

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

/* Generated by Together */

#ifndef SNXSTUBSOUNDIMPLEMENTATION_H
#define SNXSTUBSOUNDIMPLEMENTATION_H

#include <snx/snxConfig.h>

#include <string>
#include <boost/concept_check.hpp>
#include <gmtl/Math.h>
#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/VecOps.h>
#include <gmtl/Xforms.h>

#include "snx/SoundImplementation.h"
#include "snx/SoundInfo.h"
#include "snx/SoundAPIInfo.h"
#include "snx/Util/Debug.h"

namespace snx
{

/** \class StubSoundImplementation StubSoundImplementation.h snx/StubSoundImplementation.h
 *
 * Stub sound implementation.
 */
class StubSoundImplementation : public snx::SoundImplementation
{
public:
   /**
    * Constructor for the Stub sound implementation.
    */
   StubSoundImplementation();

   /**
    * Destructor for the Stub sound implementation.
    */
   virtual ~StubSoundImplementation();

   /**
     * Every implementation can return a new copy of itself.
     */
   virtual void clone( snx::ISoundImplementation* &newCopy )
   {
      StubSoundImplementation* temp = new StubSoundImplementation;

      // copy state, so that we return a true "clone"
      temp->copy( *this );

      newCopy = temp;
   }

   /**
    * Triggers a sound.
    *
    * @pre alias does not have to be associated with a loaded sound.
    * @post If alias is associated with a loaded sound, then the loaded sound
    *       is triggered.  If it isn't, then nothing happens.
    *
    * @param alias Alias of the sound to trigger, and number of times to play:
    *              -1 is repeat infinitely.
    */
   virtual void trigger(const std::string& alias, const int looping = 0)
   {
      snx::SoundImplementation::trigger( alias, looping );
      this->lookup( alias ).triggerOnNextBind = true;
      // do nothing
      //std::cout << "[snx]Stub::trigger (does nothing)\n"<<std::flush;
   }

   /**
    * Stops the sound.
    * @param alias Alias of the sound to be stopped.
    */
   virtual void stop( const std::string & alias )
   {
      snx::SoundImplementation::stop( alias );
      this->lookup( alias ).triggerOnNextBind = false;
      // do nothing
      //std::cout << "[snx]Stub::stop (does nothing)\n"<<std::flush;
   }

   /**
    * Set the sound's 3D position.
    */
   virtual void setPosition( const std::string& alias, float x, float y, float z )
   {
      snx::SoundImplementation::setPosition( alias, x, y, z );
   }

   /**
    * Gets sound's 3D position.
    *
    * @param alias A that has been associated with some sound data.
    * @param x     Storage for the X coordinate of the sound's position (in
    *              OpenGL coordinates).
    * @param y     Storage for the Y coordinate of the sound's position (in
    *              OpenGL coordinates).
    * @param z     Storage for the Z coordinate of the sound's position (in
    *              OpenGL coordinates).
    */
   virtual void getPosition( const std::string& alias, float& x, float& y, float& z )
   {
      snx::SoundImplementation::getPosition( alias, x, y, z );
   }

   /**
    * Sets the position of the listener.
    */
   virtual void setListenerPosition( const gmtl::Matrix44f& mat )
   {
      snx::SoundImplementation::setListenerPosition( mat );
   }

   /**
    * Gets the position of the listener.
    */
   virtual void getListenerPosition( gmtl::Matrix44f& mat )
   {
      snx::SoundImplementation::getListenerPosition( mat );
   }

   /**
    * Starts the sound API, creating any contexts or other configurations at
    * startup.  This function should be called before using the other
    * functions in the class.
    *
    * @post Sound API is ready to go.
    *
    * @return 0 if failed, 1 if success.
    */
   virtual int startAPI()
   {
       vpr::DebugOutputGuard output1(snxDBG, vprDBG_CONFIG_LVL, std::string("Stub::startAPI (does nothing)\n"), std::string("\n"));
       return 1;
   }

   /**
    * Kills the sound API, deallocating any sounds, etc.  This function could
    * be called any time.  The function could be called multiple times, so it
    * should be smart.
    *
    * @post Sound API is ready to go.
    */
   virtual void shutdownAPI()
   {
      vpr::DebugOutputGuard output2(snxDBG, vprDBG_CONFIG_LVL, std::string("Stub::shutdownAPI (does nothing)\n"), std::string("\n"));
   }

   /**
    * Queries whether the API has been started or not.
    *
    * @return true if API has been started, false otherwise.
    */
   virtual bool isStarted() const
   {
      return true;
   }

   /**
    * Configures/reconfigures the sound API global settings.
    */
   virtual void configure( const snx::SoundAPIInfo& sai )
   {
      // nothing to do, call the base impl...
      SoundImplementation::configure( sai );
   }

   /**
    * Configures/reconfigures a sound by associating an alias to sound data.
    * Later, this alias can be used to operate on this sound data.
    *
    * Configure: associate a name (alias) to the description if not already
    * done.
    * Reconfigure: change properties of the sound to the description provided.
    *
    * @pre Provide an alias and a SoundInfo which describes the sound.
    * @post Alias will point to loaded sound data.
    */
   virtual void configure( const std::string& alias, const snx::SoundInfo& description )
   {
      snx::SoundImplementation::configure( alias, description );
      // do nothing
   }

   /**
    * Remove a configured sound.  Any future reference to the alias will not
    * cause an error, but will not result in a rendered sound.
    */
   virtual void remove( const std::string& alias )
   {
      snx::SoundImplementation::remove( alias );
      // do nothing
   }

   /**
    * Clears all associations.  Any existing aliases will be stubbed.  Sounds
    * will be unbound.
    */
   virtual void clear()
   {
   }

   /**
    * Bind: load (or reload) all associated sounds.
    *
    * @post All sound associations are buffered by the sound API.
    */
   virtual void bindAll()
   {
   }

   /**
    * Unbind: unload/deallocate all associated sounds.
    *
    * @post All sound associations are unbuffered by the sound API.
    */
   virtual void unbindAll()
   {
   }

   /**
    * Loads/allocates the sound data this alias refers to the sound API.
    *
    * @post The sound API has the sound buffered.
    */
   virtual void bind( const std::string& alias )
   {
      boost::ignore_unused_variable_warning(alias);
   }

   /**
    * Unloads/deallocates the sound data this alias refers from the sound API.
    *
    * @post The sound API no longer has the sound buffered.
    */
   virtual void unbind( const std::string& alias )
   {
      boost::ignore_unused_variable_warning(alias);
   }

   /**
    * Call once per sound frame (doesn't have to be same as your graphics
    * frame).
    *
    * @param timeElapsed The time elapsed since the last sound frame.
    */
   virtual void step(const float timeElapsed)
   {
      snx::SoundImplementation::step( timeElapsed );
      // do nothing
   }

   /**
    * Invokes the global scope delete operator.  This is required for proper
    * releasing of memory in DLLs on Win32.
    */
   void operator delete(void* p)
   {
      ::operator delete(p);
   }

protected:
   /**
    * Deletes this object.  This is an implementation of the pure virtual
    * snx::ISoundImplementation::destroy() method.
    */
   virtual void destroy()
   {
      delete this;
   }

private:

   /** @link dependency */
   /*#  snx::SoundInfo lnkSoundInfo; */

   /** @link dependency */
   /*#  snx::SoundAPIInfo lnkSoundAPIInfo; */
};

} // end namespace

#endif //SNXSTUBSOUNDIMPLEMENTATION_H

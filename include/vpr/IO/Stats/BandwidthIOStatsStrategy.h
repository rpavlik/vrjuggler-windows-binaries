/****************** <VPR heading BEGIN do not edit this line> *****************
 *
 * VR Juggler Portable Runtime
 *
 * Original Authors:
 *   Allen Bierbaum, Patrick Hartling, Kevin Meinert, Carolina Cruz-Neira
 *
 ****************** <VPR heading END do not edit this line> ******************/

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

#ifndef VPR_BW_IOSTATS_H
#define VPR_BW_IOSTATS_H

#include <vpr/vprConfig.h>
#include <vpr/IO/Stats/BaseIOStatsStrategy.h>
#include <vpr/Util/SampleLimitedStatCollector.h>


namespace vpr
{

/** \class BandwidthIOStatsStrategy BandwidthIOStatsStrategy.h vpr/IO/Stats/BandwidthIOStatsStrategy.h
 *
 * Strategy for collecting bandwidth data about the block I/O device.
 * Holds all stats for Bandwidth collection.
 */
class VPR_CLASS_API BandwidthIOStatsStrategy //: public BaseIOStatsStrategy_i
{
public:
   BandwidthIOStatsStrategy();

   virtual ~BandwidthIOStatsStrategy();

   /** @name Strategy Interface */
   //@{
   /**
    * @pre The read operation must have already occured.
    */
   virtual void read_s(void* buffer, const vpr::Uint32 length,
                       vpr::Uint32& bytesRead, const vpr::Interval& timeout);

   /**
    * @pre The read operation must have already occured.
    */
   virtual void readn_s(void* buffer, const vpr::Uint32 length,
                        vpr::Uint32& bytesRead, const vpr::Interval& timeout);

   /**
    * @pre The write operation must have already occured.
    */
   virtual void write_s(const void* buffer, const vpr::Uint32 length,
                        vpr::Uint32& bytesWritten,
                        const vpr::Interval& timeout);
   //@}

   const vpr::SampleLimitedStatCollector<vpr::Uint32, true>& readStats() const
   {
      return mReadStats;
   }

   const vpr::SampleLimitedStatCollector<vpr::Uint32, true>& writeStats() const
   {
      return mWriteStats;
   }

private:
   vpr::SampleLimitedStatCollector<vpr::Uint32, true> mReadStats;
   vpr::SampleLimitedStatCollector<vpr::Uint32, true> mWriteStats;
};

} //namespace vpr


#endif //VPR_BWIOSTATS_H

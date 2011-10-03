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

#include <vpr/IO/SerializableObject.h>

namespace vrjTest
{
   
struct MyType
{
   int something;
   float otherStuff;
   char stupid;
   bool drawBool;
};
}

namespace vpr
{

/**
 * Serializes an object of type vrjTest::MyType into the given object writer.
 *
 * @param writer The object writer used for serializing the vrjTest::MyType
 *               object.
 *
 * @throw vpr::IOException is thrown if object serialization fails.
 */
template<>
inline void
vpr::SerializableObjectMixin<vrjTest::MyType>::writeObject(vpr::ObjectWriter* writer)
{ 
   writer->writeUint16(something);  
   writer->writeBool(drawBool);
}

/**
 * De-serializes an object of type vrjTest::MyType using the data in the
 * given object reader.
 *
 * @param reader The object reader used for de-serializing the vrjTest::MyType
 *               object.
 *
 * @throw vpr::IOException is thrown if object de-serialization fails.
 */
template<>
inline void
vpr::SerializableObjectMixin<vrjTest::MyType>::readObject(vpr::ObjectReader* reader)
{
   something = reader->readUint16();
   drawBool = reader->readBool();
}

}

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

#include <View/OpenSG/OpenSGGrabController.h>

#include <View/OpenSG/OpenSGView.h>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGeoPropPtrs.h>
#include <OpenSG/OSGSimpleGeometry.h>

#include <OpenSG/OSGDynamicVolume.h>
#include <OpenSG/OSGVector.h>

#include <DataSpace.h>
#include <Entity/DataSpaceEntity.h>
#include <View/OpenSG/OpenSGViewer.h>

#include <gmtl/Generate.h>
#include <gmtl/External/OpenSGConvert.h>
#include <gmtl/Output.h>
#include <gmtl/Vec.h>
#include <User/User.h>

#include <Util/Debug.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace
{
   void drawAxis(const float& len)
   {
      glPushMatrix();
         gmtl::Vec3f x_axis(len,0.0f,0.0f); gmtl::Vec3f y_axis(0.0f, len, 0.0f);
         gmtl::Vec3f z_axis(0.0f, 0.0f, len); gmtl::Vec3f origin(0.0f, 0.0f, 0.0f);
         glBegin(GL_LINES);
            glVertex3fv(origin.mData); glVertex3fv(x_axis.mData);
            glVertex3fv(origin.mData); glVertex3fv(y_axis.mData);
            glVertex3fv(origin.mData); glVertex3fv(z_axis.mData);
         glEnd();
      glPopMatrix();
   }
}

void OpenSGGrabController::init()
{
   GrabController::init();

   initSelectionGeom();          // Initialize the geometry node that we use for marking selection

#ifdef DEBUG_DRAW_VIEW_CONTROLLER
   // Setup drawing of debug geometry
   boost::function<void> gl_callback = boost::bind(&OpenSGGrabController::drawDebugGeom, this);
   Viewer* base_viewer = DataSpace::instance()->getViewer();
   OpenSGViewer* osg_viewer = dynamic_cast<OpenSGViewer*>(base_viewer);
   vprASSERT(osg_viewer != NULL);

   osg_viewer->addGlCallback(gl_callback);      // Add callback for drawing debug geometry
#endif
}

void OpenSGGrabController::preUpdate(Traverser* traverser)
{
   vprASSERT(mInitialized && "Update called before init. Not initialized");

   GrabController::preUpdate(traverser);     // Call parent to get state set correctly

   // Check for state change to visual rep
   if(mSelectStateChanged || (mRemoteState != mOldRemoteState))    // Only update the visual rep when the state changes
   {
      // First determine if highlighting should even be on
      if((NotSelected == mLocalSelectionState) && (UnSelected == mRemoteState))
      { 
         vprDEBUG(dspaceCNTRL, vprDBG_WARNING_LVL) << "Setting highlight state false: (NotSelected == mLocalSelectionState) || (UnSelected == mRemoteState)\n" << vprDEBUG_FLUSH;
         setHighlightState(false); 
      }
      else
      {  
         vprDEBUG(dspaceCNTRL, vprDBG_WARNING_LVL) << "Setting highlight state true: !((NotSelected == mLocalSelectionState) || (UnSelected == mRemoteState))\n" << vprDEBUG_FLUSH;
         setHighlightState(true); 
         
         float red(0.0f), green(0.0f), blue(0.0f);

         // Set red based on remote
         if(UnSelected == mRemoteState)
         { red = 0.0f; }
         else if(DoesIsect == mRemoteState)
         { red = 0.5f; }
         else if(HoldsLock == mRemoteState)
         { red = 1.0f; }

         if(IsSelected == mLocalSelectionState)
         {  blue = 1.0f; }
         else if(IsGrabbed == mLocalSelectionState)
         {  green = 0.5f; }
         else if(IsGrabbedAndLocked == mLocalSelectionState)
         {  green = 1.0f; }
      
         vprDEBUG(dspaceCNTRL, vprDBG_WARNING_LVL) << "Setting highlight color: [" << red << "," 
                                                   << green << "," << blue << "]\n" << vprDEBUG_FLUSH;
         setHighlightColor(red,green,blue);
      }

   }   

   if((mLocalSelectionState != NotSelected) || (mRemoteState != UnSelected))
   {
      //vprDEBUG(dspaceCNTRL, vprDBG_WARNING_LVL) << "Updating hightlight geometry.\n" << vprDEBUG_FLUSH;
      updateHighlightGeom();        // Update the geometry (only does this when selected)
   }
}

/** Check for intersection
* @returns true If the point is within the boundign volume
*                 of the associated view.
*/
bool OpenSGGrabController::intersect(gmtl::Matrix44f wandWorldPos)
{
   OpenSGViewPtr osg_view = boost::shared_dynamic_cast<OpenSGView>(getEntityView());
   vprASSERT(osg_view.get() != NULL);
   OSG::NodePtr osg_node = osg_view->getNode();     // Get the node to intersect against

   // XXX: The bounding volume returned from getWorldVolume is in the platform (real world)
   //      coordinate frame, so we need to transform wandWorldPos in that coordinate
   //      frame from the vw coordinate frame it starts in
   gmtl::Matrix44f plat_M_virt =  DataSpace::instance()->getUser()->getViewPlatform()->getTransform_platMvirt();
   gmtl::Matrix44f plat_M_wand = plat_M_virt * wandWorldPos;

   OSG::Matrix osg_wand_pos;
   gmtl::set(osg_wand_pos, plat_M_wand);
   OSG::Pnt3f osg_wand_pos_pnt(0.0f, 0.0f, 0.0f);
   osg_wand_pos.multFullMatrixPnt(osg_wand_pos_pnt);

   OSG::DynamicVolume bounding_volume;
   osg_node->getWorldVolume(bounding_volume);

   bool does_isect = bounding_volume.intersect(osg_wand_pos_pnt);

   // --- Debugging
   OSG::Matrix osg_wand_pos_vw;
   gmtl::set(osg_wand_pos_vw, wandWorldPos);
   updateWandRep(osg_wand_pos_vw);        // Update the wand pos rep

   OSG::Pnt3f min_pnt, max_pnt;
   bounding_volume.getBounds(min_pnt, max_pnt);

   gmtl::Vec3f wand_pos_pnt;
   wand_pos_pnt = gmtl::makeTrans<gmtl::Vec3f>(plat_M_wand);
   //std::cout << "Wand pos [plat]: " << wand_pos_pnt << std::endl;
   //std::cout << "Bounding vol (plat): \n" << std::flush;
   //bounding_volume.dump();

   return does_isect;
}


/** Set the current state of the selection */
void OpenSGGrabController::setHighlightState(bool newState)
{
   if(!mInitialized)
   {
      initSelectionGeom();
   }

   // If trying to switch to same state, just return
   if(mCurHightlightState == newState)
   {  return; }

   mCurHightlightState = newState;

   // Attach it to the
   //OpenSGViewPtr osg_view = boost::shared_dynamic_cast<OpenSGView>(getEntityView());

   // Parent on world root for now
   OpenSGViewPtr osg_view = boost::shared_dynamic_cast<OpenSGView>(DataSpace::instance()->getRoot()->getEntityView());
   vprASSERT(osg_view.get() != NULL);
   OSG::NodePtr osg_node = osg_view->getNode();     // Get the node to intersect against


   if(newState == true)    // Set to highlighted
   {
      vprASSERT(mHighlightNode->getParent() == OSG::NullFC);      // We should not have parent

      OSG::beginEditCP(osg_node);
         osg_node->addChild(mHighlightNode);
      OSG::endEditCP(osg_node);
   }
   else                    // Set not highlighted
   {
      if(mHighlightNode->getParent() != OSG::NullFC)
      {
         OSG::beginEditCP(osg_node);
            osg_node->subChild(mHighlightNode);
         OSG::endEditCP(osg_node);
      }
   }
}

/** Set the current state of the grabbed */
void OpenSGGrabController::setHighlightColor(float r, float g, float b)
{
   vprASSERT (mHighlightMaterial != OSG::NullFC);

   // Set color based on state
   OSG::beginEditCP(mHighlightMaterial);
      mHighlightMaterial->setDiffuse (OSG::Color3f(r,g,b));     
   OSG::endEditCP(mHighlightMaterial);
}


/*! Update the highlight for a moved object. Does not handle changing the
    object, this is done by highlightChanged().
 */
void OpenSGGrabController::updateHighlightGeom(void)
{
   //vprASSERT(mSelected);
   vprASSERT(mHighlightNode != OSG::NullFC);

   // Get osg node
   OpenSGViewPtr osg_view = boost::shared_dynamic_cast<OpenSGView>(getEntityView());
   vprASSERT(osg_view.get() != NULL);
   OSG::NodePtr osg_node = osg_view->getNode();     // Get the node to intersect against

    // calc the world bbox of the highlight object
    OSG::DynamicVolume vol;
    osg_node->getWorldVolume(vol);

    // We have to transform the volume back into virtual world coord system (instead of platform coord system)
    // because this bounding volume is drawn as a child of the root OSG node (which has the platform xform on it)
    gmtl::Matrix44f vw_M_plat =  DataSpace::instance()->getUser()->getViewPlatform()->getTransform_virtMplat();
    OSG::Matrix osg_vw_M_plat;
    gmtl::set(osg_vw_M_plat, vw_M_plat);

    vol.transform(osg_vw_M_plat);      // Transform back into virtual world

    OSG::Pnt3f min_pt,max_pt;
    vol.getBounds(min_pt, max_pt);

    OSG::beginEditCP(mHighlightPoints);
       mHighlightPoints->setValue(OSG::Pnt3f(min_pt[0], min_pt[1], min_pt[2]), 0);
       mHighlightPoints->setValue(OSG::Pnt3f(max_pt[0], min_pt[1], min_pt[2]), 1);
       mHighlightPoints->setValue(OSG::Pnt3f(min_pt[0], max_pt[1], min_pt[2]), 2);
       mHighlightPoints->setValue(OSG::Pnt3f(max_pt[0], max_pt[1], min_pt[2]), 3);
       mHighlightPoints->setValue(OSG::Pnt3f(min_pt[0], min_pt[1], max_pt[2]), 4);
       mHighlightPoints->setValue(OSG::Pnt3f(max_pt[0], min_pt[1], max_pt[2]), 5);
       mHighlightPoints->setValue(OSG::Pnt3f(min_pt[0], max_pt[1], max_pt[2]), 6);
       mHighlightPoints->setValue(OSG::Pnt3f(max_pt[0], max_pt[1], max_pt[2]), 7);
    OSG::endEditCP(mHighlightPoints);

    OSG::beginEditCP(mHighlightNode->getCore(), OSG::Geometry::PositionsFieldMask);
    OSG::endEditCP  (mHighlightNode->getCore(), OSG::Geometry::PositionsFieldMask);
}


/** Initialize the selection geometry */
void OpenSGGrabController::initSelectionGeom()
{
   vprASSERT(mInitialized == false && "Tried to initialize twice");
   vprDEBUG(dspaceCNTRL, vprDBG_CONFIG_LVL) << "OSGGrabController: Intializing selection geom, for entity: "
                           << getEntity()->getName() << std::endl << vprDEBUG_FLUSH;

   mInitialized = true;

   // init as needed
   if (mHighlightMaterial == OSG::NullFC)
   {
      mHighlightMaterial = OSG::SimpleMaterial::create();

      OSG::beginEditCP(mHighlightMaterial);
         mHighlightMaterial->setDiffuse (OSG::Color3f(0,1,0));
         mHighlightMaterial->setLit     (false);
      OSG::endEditCP(mHighlightMaterial);
   }
   if (mHighlightNode == OSG::NullFC)
   {
      OSG::GeoPTypesPtr type = OSG::GeoPTypesUI8::create();
      OSG::beginEditCP(type);
         type->addValue(GL_LINE_STRIP);
         type->addValue(GL_LINES);
      OSG::endEditCP(type);

      OSG::GeoPLengthsPtr lens = OSG::GeoPLengthsUI32::create();
      OSG::beginEditCP(lens);
         lens->addValue(10);
         lens->addValue(6);
      OSG::endEditCP(lens);

      OSG::GeoIndicesUI32Ptr index = OSG::GeoIndicesUI32::create();
      OSG::beginEditCP(index);
         // Line strip
         index->getFieldPtr()->addValue(0);
         index->getFieldPtr()->addValue(1);
         index->getFieldPtr()->addValue(3);
         index->getFieldPtr()->addValue(2);
         index->getFieldPtr()->addValue(0);
         index->getFieldPtr()->addValue(4);
         index->getFieldPtr()->addValue(5);
         index->getFieldPtr()->addValue(7);
         index->getFieldPtr()->addValue(6);
         index->getFieldPtr()->addValue(4);

         // Lines
         index->getFieldPtr()->addValue(1);
         index->getFieldPtr()->addValue(5);
         index->getFieldPtr()->addValue(2);
         index->getFieldPtr()->addValue(6);
         index->getFieldPtr()->addValue(3);
         index->getFieldPtr()->addValue(7);
      OSG::endEditCP(index);

      mHighlightPoints = OSG::GeoPositions3f::create();
      OSG::beginEditCP(mHighlightPoints);
         mHighlightPoints->addValue(OSG::Pnt3f(-1, -1, -1));
         mHighlightPoints->addValue(OSG::Pnt3f( 1, -1, -1));
         mHighlightPoints->addValue(OSG::Pnt3f(-1,  1, -1));
         mHighlightPoints->addValue(OSG::Pnt3f( 1,  1, -1));
         mHighlightPoints->addValue(OSG::Pnt3f(-1, -1,  1));
         mHighlightPoints->addValue(OSG::Pnt3f( 1, -1,  1));
         mHighlightPoints->addValue(OSG::Pnt3f(-1,  1,  1));
         mHighlightPoints->addValue(OSG::Pnt3f( 1,  1,  1));
      OSG::endEditCP(mHighlightPoints);

      OSG::GeometryPtr geo=OSG::Geometry::create();
      OSG::beginEditCP(geo);
         geo->setTypes     (type);
         geo->setLengths   (lens);
         geo->setIndices   (index);
         geo->setPositions (mHighlightPoints);
         geo->setMaterial  (mHighlightMaterial);
      OSG::endEditCP(geo);
      OSG::addRefCP(geo);

      mHighlightNode = OSG::Node::create();
      OSG::beginEditCP(mHighlightNode);
         mHighlightNode->setCore(geo);
      OSG::endEditCP(mHighlightNode);
      OSG::addRefCP(mHighlightNode);
   }

   initWandRep();
}

void OpenSGGrabController::initWandRep()
{
   // --- Initialize wand rep --- //
   // Create the geometyr
   OSG::NodePtr wand_rep_geode = OSG::Node::create();
   OSG::GeometryPtr wand_geo = OSG::makeSphereGeo(3,0.10f);

   OSG::beginEditCP(wand_rep_geode);
      wand_rep_geode->setCore(wand_geo);
   OSG::endEditCP(wand_rep_geode);

   // Create the transform node
   mWandRepTransNode = OSG::Node::create();
   mWandRepTrans = OSG::Transform::create();
   vprASSERT(mWandRepTrans != OSG::NullFC);

   OSG::beginEditCP(mWandRepTransNode);
      mWandRepTransNode->setCore(mWandRepTrans);
      mWandRepTransNode->addChild(wand_rep_geode);
   OSG::endEditCP(mWandRepTransNode);

   // Set material
   OSG::SimpleMaterialPtr geo_material = OSG::SimpleMaterial::create();

   OSG::beginEditCP(geo_material);
   {
      geo_material->setAmbient      (OSG::Color3f(0.2,0.2,0.2));
      geo_material->setDiffuse      (OSG::Color3f(0.8,0.1,0.6));
      geo_material->setEmission     (OSG::Color3f(0.0,0.0,0.0));
      geo_material->setSpecular     (OSG::Color3f(1.0,1.0,1.0));
      geo_material->setShininess    (10.0f);
      geo_material->setTransparency (0.0f);
      geo_material->setColorMaterial(GL_NONE);      // Turns off the object prim colors
   }
   OSG::endEditCP  (geo_material);

   // assign the material to the geometry
   OSG::beginEditCP(wand_geo, OSG::Geometry::MaterialFieldMask );
   {
      wand_geo->setMaterial(geo_material);
   }
   OSG::endEditCP  (wand_geo, OSG::Geometry::MaterialFieldMask );
}

void OpenSGGrabController::attachWandRep()
{
   // Attach wand rep to root (world) coord for debugging
   OpenSGViewPtr dataspace_view = boost::shared_dynamic_cast<OpenSGView>(DataSpace::instance()->getRoot()->getEntityView());
   vprASSERT(dataspace_view.get() != NULL);
   OSG::NodePtr dataspace_osg_node = dataspace_view->getNode();     // Get the node to intersect against

   OSG::beginEditCP(dataspace_osg_node);
      dataspace_osg_node->addChild(mWandRepTransNode);
   OSG::endEditCP(dataspace_osg_node);
}


/*! Update the highlight for a moved object. Does not handle changing the
 object, this is done by highlightChanged().
 */
void OpenSGGrabController::updateWandRep(OSG::Matrix osg_wand_pos)
{
   if(!mWandRepAttached)
   {
      mWandRepAttached = true;
      attachWandRep();
   }

   vprASSERT(mWandRepTrans != OSG::NullFC);

   OSG::beginEditCP(mWandRepTrans);
      mWandRepTrans->getMatrix().setValue(osg_wand_pos);
   OSG::endEditCP(mWandRepTrans);
}


void OpenSGGrabController::drawDebugGeom()
{
#ifdef DEBUG_DRAW_VIEW_CONTROLLER
   glPushMatrix();
      glColor3f(1.0f, 0.0f, 0.0f);
      glMultMatrixf( mDraw_xform_vm_M_o.getData());
      drawAxis(20.0f);
   glPopMatrix();

   glPushMatrix();
      glColor3f(0.0f, 1.0f, 0.0f);
      glMultMatrixf( mDraw_cur_xform_vm_M_o.getData());
      drawAxis(20.0f);
   glPopMatrix();

   glPushMatrix();
      glColor3f(0.0f, 0.0f, 1.0f);
      glMultMatrixf( mDraw_cur_xform_vm_M_n.getData());
      drawAxis(20.0f);
   glPopMatrix();

   glPushMatrix();
      glColor3f(0.0f, 1.0f, 1.0f);
      glMultMatrixf( mDraw_xform_vw_M_wand.getData());
      drawAxis(20.0f);
   glPopMatrix();

   glPushMatrix();
      glColor3f(1.0f, 0.0f, 1.0f);
      glMultMatrixf( mDraw_xform_vw_M_plat.getData());
      drawAxis(20.0f);
   glPopMatrix();
#endif
}




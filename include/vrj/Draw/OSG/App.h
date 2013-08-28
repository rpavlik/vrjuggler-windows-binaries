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

#ifndef _VRJ_OSG_APP_H_
#define _VRJ_OSG_APP_H_

#include <vrj/vrjConfig.h>

#include <vpr/Sync/Mutex.h>
#include <vpr/Sync/Guard.h>

#include <vrj/Draw/OpenGL/App.h>
#include <vrj/Draw/OpenGL/ContextData.h>
#include <vrj/Draw/OpenGL/Window.h>

#include <vrj/Display/CameraProjection.h>

#include <vrj/Kernel/Kernel.h>
#include <vrj/Kernel/User.h>

#include <osg/Version>
#include <osg/Vec3>
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/Group>
#include <osg/Camera>

#include <osgUtil/SceneView>
#include <osgUtil/UpdateVisitor>


namespace vrj
{

namespace osg
{

/** \class vrj::osg::App App.h vrj/Draw/OSG/App.h
 *
 * Encapsulates an Open Scene Graph (OSG) application.  This defines the base
 * class from which OSG-based application classes should be derived.  It makes
 * use of the OpenGL Draw Manager.
 *
 * @note This class was renamed from vrj::OsgApp in VR Juggler 2.3.11.
 *
 * @see vrj::opengl::App
 */
class App : public vrj::opengl::App
{
public:
   App(Kernel* kern = NULL)
      : vrj::opengl::App(kern)
      , mFrameNumber(0)
   {
      // Tell osg::Referenced to use thread-safe reference counting. We do
      // this here for all applications and all configurations though it is
      // only strictly necessary when VR Juggler is configured to use
      // multi-threaded rendering.
      ::osg::Referenced::setThreadSafeReferenceCounting(true);
   }

   virtual ~App()
   {
      ;
   }

   /**
    * Initializes the scene.
    * Called by init() to initialize the scene.
    */
   virtual void initScene() = 0;

   /**
    * Gets the root of the scene to render.
    * Called each frame to get the current scene to render.
    */
   virtual ::osg::Group* getScene() = 0;

   /**
    * Returns the options to be passed to osgUtil::SceneView::setDefaults()
    * for each scene view that is configured. This is called by the default
    * implementation of vrj::osg::App::configSceneView(). See
    * osgUtil::SceneView::Options for the available settings.
    *
    * @see configSceneView()
    *
    * @note The signatue of this method changed in VR Juggler 2.3.12.
    *       Instead of returning osgUtil::SceneView::Options, it now returns
    *       unsigned int.
    *
    * @since 2.3.0
    */
   virtual unsigned int getSceneViewDefaults()
   {
      return osgUtil::SceneView::STANDARD_SETTINGS;
   }

   /**
    * Configures newly created scene viewers.
    * This is called immediately after a new scene viewer is created for a
    * context.  This is the place to configure application background colors
    * and other viewer-specific information.  Below are some suggestions on
    * how to configure an osgUtil::SceneView instance with lighting.
    *
    * For an application configure with a sky light:
    *
    * \code
    * unsigned int MyApp::getSceneViewDefaults()
    * {
    *    return osgUtil::SceneView::SKY_LIGHT;
    * }
    * \endcode
    *
    * For an application configured with a headlight:
    *
    * \code
    * unsigned int MyApp::getSceneViewDefaults()
    * {
    *    return osgUtil::SceneView::HEADLIGHT;
    * }
    * \endcode
    *
    * For an application configure with a user-defined light, there are
    * several steps.
    *
    * \code
    * // First, declare two member variables in your subclass of vrj::osg::App
    * such as the following:
    * osg::ref_ptr<osg::Light> mLight0;
    * osg::ref_ptr<osg::LightSource> mLightSource0;
    *
    * // Then, in init() do something such as the following:
    * void MyApp::init()
    * {
    *    vrj::osg::App::init();
    *
    *    mLight0 = new osg::Light();
    *    mLight0->setLightNum(0);
    *    mLight0->setAmbient(osg::Vec4f(0.36862f, 0.36842f, 0.36842f, 1.0f));
    *    mLight0->setDiffuse(osg::Vec4f(0.88627f, 0.88500f, 0.88500f, 1.0f));
    *    mLight0->setSpecular(osg::Vec4f(0.49019f, 0.48872f, 0.48872f, 1.0f));
    *    mLight0->setPosition(osg::Vec4f(10000.0f, 10000.0f, 10000.0f, 0.0f));
    *    mLight0->setDirection(osg::Vec3f(-1.0f, -1.0f, -1.0f));
    *
    *    mLightSource0 = new osg::LightSource();
    *    mLightSource0->setLight(mLight0.get());
    *    mLightSource0->setLocalStateSetModes(osg::StateAttribute::ON);
    *
    *    // Now that we know we have a root node add the default light to the
    *    // scene.
    *    getScene()->addChild(mLightSource0.get());
    * }
    *
    * // Next, override vrj::osg::App::getSceneViewDefaults() to change the
    * // option passed to osgUtil::SceneView::setDefaults().
    * unsigned int MyApp::getSceneViewDefaults()
    * {
    *    return osgUtil::SceneView::NO_SCENEVIEW_LIGHT;
    * }
    *
    * // Finally, set up the osgUtil::SceneView instance to use this light.
    * void MyApp::configSceneView(osgUtil::SceneView* newSceneViewer)
    * {
    *    vrj::osg::App::configSceneView(newSceneViewer);
    *
    *    // add lights and turn on lighting
    *    newSceneViewer->getGlobalStateSet()->setAssociatedModes(
    *       mLight0.get(), osg::StateAttribute::ON
    *    );
    *    newSceneViewer->getGlobalStateSet()->setMode(GL_LIGHTING,
    *                                                 osg::StateAttribute::ON);
    * }
    * \endcode
    *
    * @post \p newSceneViewer is initialized.
    *
    * @see getSceneViewDefaults()
    */
   virtual void configSceneView(osgUtil::SceneView* newSceneViewer)
   {
      newSceneViewer->setDefaults(getSceneViewDefaults());

      // Set the timing information in the scene view. This has to be done
      // only once per osgUtil::SceneView instance and should be done before
      // calling osgUtil::SceneView::init().
      newSceneViewer->setFrameStamp(mFrameStamp.get());
      // The SceneView::init method calls into osg::isGLExtensionOrVersionSupported
      // which is unclear if this method is thread safe. Testing on various
      // hardware would indicate that it is not threadsafe.
      {
         vpr::Guard<vpr::Mutex> sv_guard(mSceneViewLock);
         newSceneViewer->init();
      }
      newSceneViewer->setClearColor(::osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));

      // Needed for stereo to work.
      newSceneViewer->setDrawBufferValue(GL_NONE);

      // Additional camera setup for OSG versions newer than 2.9.5.
#if OPENSCENEGRAPH_MAJOR_VERSION > 2    ||      \
    (OPENSCENEGRAPH_MAJOR_VERSION == 2  &&      \
     (OPENSCENEGRAPH_MINOR_VERSION > 9  ||      \
      OPENSCENEGRAPH_MINOR_VERSION == 9 &&      \
      OPENSCENEGRAPH_PATCH_VERSION > 5))
      newSceneViewer->getCamera()->setInheritanceMask( 
         newSceneViewer->getCamera()->getInheritanceMask() | 
         ::osg::CullSettings::DRAW_BUFFER
      );
#endif
   }

   /**
    * Function called after preFrame() and application-specific data
    * synchronization (in a cluster configuration) but before the start of a
    * new frame.
    *
    * If this method is overridden, it must be called as the last thing done
    * by the overriding version.  This calls update(), which is used to update
    * this application object's scene graph.
    *
    * @note Subclasses overriding this method \em must call this method
    *       implementation as the last step.
    *
    * @since 2.1.9
    */
   virtual void latePreFrame()
   {
      update();
   }

   /**
    * Function to set up and render the scene using OSG.  Override this
    * method with great care.  All the logic to handle multi-pipe rendering
    * and other VR Juggler features happens here.
    *
    * @pre OpenGL state has correct transformation and buffer selected.
    * @post The current scene has been drawn.
    */
   virtual void draw();

   /**
    * Application initialization function.
    * Execute any initialization needed before the graphics API is started.
    * If this method is overridden, it must be called by the overriding
    * version.  This calls initScene(), which is used to set up this
    * application object's scene graph.
    *
    * @note Derived classes MUST call base class version of this method.
    */
   virtual void init()
   {
      mUpdateVisitor = new osgUtil::UpdateVisitor();
      mFrameStamp    = new ::osg::FrameStamp();
      mUpdateVisitor->setFrameStamp(mFrameStamp.get());

      vrj::opengl::App::init();

      //Create the scene
      this->initScene();
   }

   /**
    * Function that is called immediately after a new context is created.
    * Use this function to create context-specific data structures such as
    * display lists and texture objects that are known to be required when
    * the context is created.
    *
    * @pre The OpenGL context has been set to the new context.
    * @post The application has completed context-specific initialization.
    */
   void contextInit();

   /**
    * Function that is called immediately before a context is closed.
    * Use the function to clean up any context-specific data structures.
    */
   virtual void contextClose()
   {
      ;
   }

   /**
    * Function that is called upon entry into the context before rendering.
    * This can be used to allocate context-specific data dynamically.
    *
    * @pre The OpenGL context has been set to the context for drawing.
    * @post The application object has executed any commands that need to be
    *       executed only once per context, per frame.
    *
    * @note This function can be used for things that need to happen
    *       every frame but only once per context.
    */
   virtual void contextPreDraw()
   {
      ;
   }

   /**
    * Function that is called once for each frame buffer of an OpenGL context.
    * This function is executed after contextInit() (if needed) but before
    * contextPreDraw().  It is called once per frame buffer (see note).
    *
    * @pre The OpenGL context has been set to the context for drawing.
    * @post The application object has executed any commands that need to be
    *        executed once per context, per buffer, per frame.
    *
    * @note This function is designed to be used when some task must be
    *       performed only once per frame buffer (i.e., once for the left
    *       buffer, once for the right buffer).  For example, the OpenGL clear
    *       color should be defined and glClear(GL_COLOR_BUFFER_BIT) should be
    *       called in this method.
    */
   virtual void bufferPreDraw()
   {
      ;
   }

   /**
    * Function that is called at the beginning of the drawing of each pipe.
    *
    * @pre The library is preparing to render all windows on a given pipe.
    * @post Any pre-pipe user calls have been done.
    *
    * @note Currently the OpenGL context is not set when this function is
    *       called.  This is a TEST function.  USE AT YOUR OWN RISK!!!
    */
   virtual void pipePreDraw()
   {
      ;
   }

protected:
   /**
    * Performs the update stage on the scene graph.  This function should be
    * called as the last thing that happens in latePreFrame(). If
    * latePreFrame() is not overridden, then this happens automatically.
    * Otherwise be sure to call vrj::osg::App::latePreFrame() as the last
    * thing in application object's override of latePreFrame().
    *
    * @pre The library is preparing to switch from the serial preDraw stages
    *      to the parallel draw stages.
    * @post The scene graph update stage is complete and it is ready for cull
    *       and draw to be called in parallel.
    *
    * @note This function also takes care of time-based features in the scene
    *       graph.
    * @note This method was made virtual in 2.3.20.
    *
    * @since 2.1.9
    */
   virtual void update()
   {
      ++mFrameNumber;

      // Update the frame stamp with information from this frame.
      mFrameStamp->setFrameNumber(mFrameNumber);

      const double head_time(
         mKernel->getUsers()[0]->getHeadPosProxy()->getTimeStamp().secd()
      );
      mFrameStamp->setReferenceTime(head_time);

      // This is available in OSG 1.9 and newer.
      // If OPENSCENEGRAPH_MAJOR_VERSION is defined, we know the version is
      // greater than or equal to 2.0.
#if defined(OPENSCENEGRAPH_MAJOR_VERSION) || \
    OSG_VERSION_MAJOR == 1 && OSG_VERSION_MINOR > 2 || OSG_VERSION_MAJOR >= 2
      mFrameStamp->setSimulationTime(head_time);
#endif

      // Set up the time and frame number so time-dependent things (animations,
      // particle system) function correctly.
      // XXX: This may not be necessary.
      mUpdateVisitor->setTraversalNumber(mFrameNumber);

      // Update the scene by traversing it with the the update visitor which
      // will call all node update callbacks and animations. This is
      // equivalent to calling osgUtil::SceneView::update() but does not
      // require access to the context-specific osgUtil::SceneView instance.
      getScene()->accept(*mUpdateVisitor);

      // NOTE: This comment was taken from osgUtil::SceneView::update():
      // Now force a recompute of the bounding volume while we are still in
      // the read/write app phase, this should prevent the need to recompute
      // the bounding volumes from within the cull traversal which may be
      // multi-threaded.
      getScene()->getBound();
   }

   /**
    * Returns a reference to the internal osg::FrameStamp object used by this
    * class.
    *
    * @since 2.3.20
    */
   ::osg::ref_ptr< ::osg::FrameStamp > getFrameStamp()
   {
      return mFrameStamp;
   }

   vrj::opengl::ContextData< ::osg::ref_ptr<osgUtil::SceneView> > sceneViewer;

private:
   ::osg::ref_ptr< ::osg::NodeVisitor > mUpdateVisitor;
   ::osg::ref_ptr< ::osg::FrameStamp >  mFrameStamp;

   int mFrameNumber;
   vpr::Mutex mSceneViewLock;
};

inline void App::contextInit()
{
   const unsigned int unique_context_id =
      vrj::opengl::DrawManager::instance()->getCurrentContext();

   // --- Create new context specific scene viewer -- //
   ::osg::ref_ptr<osgUtil::SceneView> new_sv(new osgUtil::SceneView);
   this->configSceneView(new_sv.get());            // Configure the new viewer
   new_sv->getState()->setContextID(unique_context_id);
   // Add the tree to the scene viewer and set properties
   {
      vpr::Guard<vpr::Mutex> sv_guard(mSceneViewLock);
      new_sv->setSceneData(getScene());
   }

   (*sceneViewer) = new_sv;
}

inline void App::draw()
{
   glClear(GL_DEPTH_BUFFER_BIT);

   // Users have reported problems with OpenGL reporting stack underflow
   // problems when the texture attribute bit is pushed here, so we push all
   // attributes *except* GL_TEXTURE_BIT.
   glPushAttrib(GL_ALL_ATTRIB_BITS & ~GL_TEXTURE_BIT);
   glPushAttrib(GL_TRANSFORM_BIT);
   glPushAttrib(GL_VIEWPORT_BIT);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();

   ::osg::ref_ptr<osgUtil::SceneView> sv;
   sv = (*sceneViewer);    // Get context specific scene viewer
   vprASSERT(sv.get() != NULL);

   // The OpenGL Draw Manager that we are rendering for.
   //Get the view matrix and the frustrum form the draw manager
   vrj::opengl::DrawManager* gl_manager =
      dynamic_cast<vrj::opengl::DrawManager*>(this->getDrawManager());
   vprASSERT(gl_manager != NULL);

   vrj::opengl::UserData* user_data = gl_manager->currentUserData();

   // Set the up the viewport (since OSG clears it out)
   float vp_ox, vp_oy, vp_sx, vp_sy;   // The float vrj sizes of the view ports
   int w_ox, w_oy, w_width, w_height;  // Origin and size of the window
   user_data->getViewport()->getOriginAndSize(vp_ox, vp_oy, vp_sx, vp_sy);
   user_data->getGlWindow()->getOriginSize(w_ox, w_oy, w_width, w_height);

   // compute unsigned versions of the viewport info (for passing to glViewport)
   const unsigned int ll_x =
      static_cast<unsigned int>(vp_ox * static_cast<float>(w_width));
   const unsigned int ll_y =
      static_cast<unsigned int>(vp_oy * static_cast<float>(w_height));
   const unsigned int x_size =
      static_cast<unsigned int>(vp_sx * static_cast<float>(w_width));
   const unsigned int y_size =
      static_cast<unsigned int>(vp_sy * static_cast<float>(w_height));

   //sv->setCalcNearFar(false);
   sv->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
   sv->setViewport(ll_x, ll_y, x_size, y_size);

   //Get the frustrum
   ProjectionPtr project = user_data->getProjection();
   Frustum frustum = project->getFrustum();
   sv->setProjectionMatrixAsFrustum(frustum[Frustum::VJ_LEFT],
                                    frustum[Frustum::VJ_RIGHT],
                                    frustum[Frustum::VJ_BOTTOM],
                                    frustum[Frustum::VJ_TOP],
                                    frustum[Frustum::VJ_NEAR],
                                    frustum[Frustum::VJ_FAR]);

   // Copy the view matrix
   sv->setViewMatrix(::osg::Matrix(project->getViewMatrix().mData));

   //Draw the scene
   // NOTE: It is not safe to call osgUtil::SceneView::update() here; it
   // should only be called by a single thread. The equivalent of calling
   // osgUtil::SceneView::update() is in vrj::osg::App::update().
   sv->cull();
   sv->draw();

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();

   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   glPopAttrib();
   glPopAttrib();
   glPopAttrib();
}

} // End of osg namespace

/**
 * Backwards compatibility type declaration for vrj::osg::App.
 *
 * @since 2.3.11
 *
 * @deprecated vrj::OsgApp has been deprecated in favor of vrj::osg::App.
 */
typedef vrj::osg::App OsgApp;

} // End of vrj namespace


#endif /* _VRJ_OSG_APP_H_ */

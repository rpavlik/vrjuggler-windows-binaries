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

/****************** <SNX heading BEGIN do not edit this line> *****************
 *
 * sonix
 *
 * Original Authors:
 *   Kevin Meinert
 *
 ****************** <SNX heading END do not edit this line> ******************/

// Kevin Meinert
// simple glut skeleton application: look for the !!!TODO!!!s, 
//  and fill in your code 
//                          there as needed
//

#if defined(WIN32) || defined(WIN64)
#  include <windows.h>  // make the app win32 friendly. :)
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <snx/sonix.h>    // interface
#include <snx/SoundHandle.h>
#include "StopWatch.h"

#include <iostream.h>
#include <stdlib.h>

// a place to store application data...
class AppWindow
{
public:
   static int width, height;
   static int mainWin_contextID;
};
int AppWindow::width = 0, AppWindow::height = 0;
int AppWindow::mainWin_contextID = -1;
std::string currentalias;

struct bokbok
{
   snx::SoundHandle sound;
};
std::map<int, bokbok> aliases;

StopWatch stopWatch;

int soundpos = 0;
float pitchbend = 1.0f;
float cutoff = 0.2f;
float volume = 1.0f;
bool pause_sound = false;
bool retriggerable = false;

// our sound object...
snx::SoundHandle kevinSound;

void drawGrid()
{
   glBegin( GL_LINES );
      for ( int x = -1000; x < 1000; ++x)
      {
         glVertex3f( -1000, 0, x );
         glVertex3f(  1000, 0, x );
         glVertex3f( x, 0, -1000 );
         glVertex3f( x, 0,  1000 );
      }
   glEnd();
}

//////////////////////////////////////////////////
// This is called on a glutPostRedisplay
//////////////////////////////////////////////////
static void OnRedisplay()
{ 
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
   
   
   // set up the projection matrix
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();                     
      gluPerspective( 80.0f, AppWindow::width / AppWindow::height, 0.01f, 1000.0f );
                           
   // initialize your matrix stack used for transforming your models
    glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

   // !!!TODO!!!: replace the following with your own opengl commands!
   glTranslatef( 0, -10, 0 );
   drawGrid();
   // !!!TODO!!!: ////////////////////////////////////////
   
   // swaps the front and back frame buffers.
   // hint: you've been drawing on the back, offscreen, buffer.  
   // This command then brings that framebuffer onscreen.
   glutSwapBuffers();
}

//////////////////////////////////////////////////
// This is called repeatedly, as fast as possible
//////////////////////////////////////////////////
#include "unistd.h"
static void OnIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != AppWindow::mainWin_contextID )
      glutSetWindow( AppWindow::mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
   
   snx::sonix::instance()->step( stopWatch.timeDelta() );
   stopWatch.pulse();
}

/////////////////////////////////////////////
// This is called on a Resize of the glut window
/////////////////////////////////////////////
static void OnReshape( int width, int height ) 
{
   // save these params in case your app needs them
   AppWindow::width = width;
   AppWindow::height = height;
   
   // set your viewport to the extents of the window
   glViewport( 0, 0, width, height );
   
   // let the app run idle, while resizing, 
   // glut does not do this for us automatically, so call OnIdle explicitly.
   OnIdle();
}

////////////////////////////////
// This is called on a Down Keypress        
////////////////////////////////
static void OnKeyboardDown( unsigned char k, int x, int y )
{ 
   switch (k)
   {
   // If user pressed 'q' or 'ESC', then exit the app.
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
   case 'q':
   case 27:
      exit( 0 );
      break;
   case '1':
   {
      snx::sonix::instance()->changeAPI( "Stub" );
      snx::SoundInfo si;
      si.filename = "sol.wav";
      si.ambient = false;
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );

      snx::sonix::instance()->changeAPI( "Audiere" );
   }
   break;
   case '2':
   {
      snx::sonix::instance()->changeAPI( "Stub" );
      snx::SoundInfo si;
      si.filename = "sep.wav";
      si.ambient = false;
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );

      snx::sonix::instance()->changeAPI( "Audiere" );
   }
   break;
   case '3':
   {
      snx::sonix::instance()->changeAPI( "Stub" );
      snx::SoundInfo si;
      si.filename = "attack.wav";
      si.ambient = false;
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );

      snx::sonix::instance()->changeAPI( "Subsynth" );
   }
   break;
   case '4':
   {
      snx::sonix::instance()->changeAPI( "Stub" );
   }
   break;
   
   case '0': aliases[0].sound.trigger(); break;
   case '9': aliases[9].sound.trigger(); break;
   case '8': aliases[8].sound.trigger(); break;
   case '7': aliases[7].sound.trigger(); break;
   
      case 'a':
   {
      snx::SoundInfo si;
      si.ambient = false;
      si.filename = "sol.wav";
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );
      std::cout<<"positional"<<std::endl;
   }
   break;
      case 'b':
   {
      snx::SoundInfo si;
      si.ambient = true;
      si.filename = "sep.wav";
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );
      kevinSound.setAmbient( true );
      std::cout<<"ambient"<<std::endl;
   }
   break;
      case 'c':
   {
      snx::SoundInfo si;
      si.ambient = false;
      si.filename = "suck.wav";
      si.datasource = snx::SoundInfo::FILESYSTEM;
      kevinSound.configure( si );
      std::cout<<"positional"<<std::endl;
   }
   break;
   case 't':
   {
      kevinSound.trigger();
   }
   break;
   case 'y':
   {
      kevinSound.trigger( -1 );
   }
   break;
   case 'p':
   {
      pause_sound = !pause_sound;
      if (pause_sound)
         kevinSound.pause();
      else
         kevinSound.unpause();
      std::cout << "paused " << kevinSound.isPaused() << std::endl;
   }
   break;
   case 's':
   {
      kevinSound.stop();
   }
   break;

   case ',':
   {
      soundpos -= 1;
      kevinSound.setPosition( soundpos, 0, 0 );
      std::cout<<"soundpos: "<<soundpos<<std::endl;
   }
   break;
   
   case 'r':
   {
      retriggerable = !retriggerable;
      kevinSound.setRetriggerable( retriggerable );
      std::cout<<"retriggerable: "<<kevinSound.isRetriggerable()<<std::endl;
   }
   break;

   case '.':
   {
      soundpos += 1;
      kevinSound.setPosition( soundpos, 0, 0 );
      std::cout<<"soundpos: "<<soundpos<<std::endl;
   }
   break;

   case '[':
   {
      pitchbend -= 0.1;
      kevinSound.setPitchBend( pitchbend );
      std::cout<<"pitchbend: "<<pitchbend<<std::endl;
   }
   break;

   case ']':
   {
      pitchbend += 0.1;
      kevinSound.setPitchBend( pitchbend );
      std::cout<<"pitchbend: "<<pitchbend<<std::endl;
   }
   break;
   
   
   case ';':
   {
      cutoff -= 0.01;
      kevinSound.setCutoff( cutoff );
      std::cout<<"Cutoff: "<<cutoff<<std::endl;
   }
   break;

   case '\'':
   {
      cutoff += 0.01;
      kevinSound.setCutoff( cutoff );
      std::cout<<"Cutoff: "<<cutoff<<std::endl;
   }
   break;
   
   case '-':
   {
      volume -= 0.1;
      kevinSound.setVolume( volume );
      std::cout<<"volume: "<<volume<<std::endl;
   }
   break;

   case '=':
   {
      volume += 0.1;
      kevinSound.setVolume( volume );
      std::cout<<"volume: "<<volume<<std::endl;
   }
   break;

   default:
      // do nothing if no key is pressed
      break;
   }
}
////////////////////////////////
// This is called on a Up Keypress        
////////////////////////////////
static void OnKeyboardUp( unsigned char k, int x, int y ) 
{
   switch (k)
   {
   case 'a':
      // !!!TODO!!!: add handler for when UP is released
      break;

   case 'z':
      // !!!TODO!!!: add handler for when DOWN is released
      break;
   
   default:
      // do nothing if no key is pressed
      break;
   }
}

////////////////////////////////
// This is called on a Down Keypress 
// of a "special" key such as the grey arrows.
////////////////////////////////
static void OnSpecialKeyboardDown(int k, int x, int y) 
{
   switch (k)
   {
   case GLUT_KEY_UP:
      // !!!TODO!!!: add handler for when UP is pressed
      break;
   case GLUT_KEY_DOWN:
      // !!!TODO!!!: add handler for when DOWN is pressed
      break;
   default:
      // do nothing if no special key pressed
      break;
   }
}

////////////////////////////////
// This is called on a Up Keypress        
////////////////////////////////
static void OnSpecialKeyboardUp( int k, int x, int y ) 
{
   switch (k)
   {
   case GLUT_KEY_UP:
      // !!!TODO!!!: add handler for when UP is released
      break;
   case GLUT_KEY_DOWN:
      // !!!TODO!!!: add handler for when DOWN is released
      break;
   default:
      // do nothing if no special key pressed
      break;
   }
}

////////////////////////////////
// This is called when mouse changes position
// x and y are the screen position 
// in your 2D window's coordinate frame
////////////////////////////////
static void OnMousePos( int x, int y ) 
{
   // !!!TODO!!!: do something based on mouse position
}

////////////////////////////////
// This is called when mouse clicks
////////////////////////////////
static void OnMouseClick( int a, int b, int c, int d )
{
   // !!!TODO!!!: Need mouse interaction?
   //             read the glut docs/manpage to find out how to query 
   //             which button was pressed...
   //             you may have to get this from the glut website 
   //             (use www.google.com to search for it)
}


// Initialize the application
// initialize the state of your app here if needed...
static void OnApplicationInit()
{
   // Don't put open GL code here, this func may be called at anytime
   // even before the API is initialized 
   // (like before a graphics context is obtained)
   
   aliases[0].sound.init( "sep" );
   aliases[9].sound.init( "sol" );
   aliases[8].sound.init( "attack" );
   aliases[7].sound.init( "drum" );
   
   snx::SoundInfo si;
   si.ambient = false;
   si.datasource = snx::SoundInfo::FILESYSTEM;
   si.filename = "sep.wav";
   aliases[0].sound.configure( si );
   si.filename = "sol.wav";
   aliases[9].sound.configure( si );
   si.filename = "attack.wav";
   aliases[8].sound.configure( si );
   si.filename = "drum44100.wav";
   aliases[7].sound.configure( si );
   
   kevinSound.init( "kevin" );
   stopWatch.pulse();
}


int main(int argc, char* argv[])
{
    // Initialize the application
    // initialize the state of your app here if needed...
    OnApplicationInit();
   
    // Set the window's initial size
    ::glutInitWindowSize( 640, 480 );
    ::glutInit( &argc, argv );
  
    // Set to double buffer to reduce flicker
    ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    // Set the window title
    AppWindow::mainWin_contextID = ::glutCreateWindow( "GLUT application" );
    
    cout<<"\n"<<flush;
    cout<<"sonix sample OpenGL+sound app - by kevin - kevn@vrjuggler.org\n"<<flush;
    cout<<"       usage:  t - trigger single shot sound\n"<<flush;
    cout<<"               y - trigger infinitly looping sound\n"<<flush;
    cout<<"               p - pause/unpause sound\n"<<flush;
    cout<<"               s - stop sound\n"<<flush;
    cout<<"               r - toggle isRetriggerable\n"<<flush;
    cout<<"               - - volume decrement\n"<<flush;
    cout<<"               = - volume increment\n"<<flush;
    cout<<"               [ - pitch decrement\n"<<flush;
    cout<<"               ] - pitch increment\n"<<flush;
    cout<<"               ; - lowpass filter cutoff decrement\n"<<flush;
    cout<<"               ' - lowpass filter cutoff increment\n"<<flush;
    cout<<"               , - move 3d sound source to the left\n"<<flush;
    cout<<"               . - move 3d sound source to the right\n"<<flush;
    cout<<"               1 - Change subsystem to OpenAL\n"<<flush;
    cout<<"               2 - Change subsystem to AudioWorks\n"<<flush;
    cout<<"               3 - Change subsystem to Subsynth\n"<<flush;
    cout<<"               4 - Change subsystem to None\n"<<flush;
    cout<<"               a - configure sound object to sol.wav\n"<<flush;
    cout<<"               b - configure sound object to drumsolo.wav\n"<<flush;
    cout<<"               c - configure sound object to suck.wav\n"<<flush;
    cout<<"               7 - trigger drum44100.wav\n"<<flush;
    cout<<"               8 - trigger attack.wav\n"<<flush;
    cout<<"               9 - trigger sol.wav\n"<<flush;
    cout<<"               0 - trigger sep.wav\n"<<flush;
    cout<<"\n"<<flush;
    
   // display callbacks.
   ::glutReshapeFunc( OnReshape );
   ::glutIdleFunc( OnIdle );
   ::glutDisplayFunc( OnRedisplay );

   // tell glut to not call the keyboard callback repeatedly 
   // when holding down a key. (uses edge triggering, like the mouse)
   ::glutIgnoreKeyRepeat( 1 );

   // keyboard callback functions.
   ::glutKeyboardFunc( OnKeyboardDown );
   ::glutKeyboardUpFunc( OnKeyboardUp );
   ::glutSpecialFunc( OnSpecialKeyboardDown );
   ::glutSpecialUpFunc( OnSpecialKeyboardUp );

   // mouse callback functions...
   ::glutMouseFunc( OnMouseClick );
   ::glutMotionFunc( OnMousePos );
   ::glutPassiveMotionFunc( OnMousePos );

    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    ::glutMainLoop();
    
    return 1;
}


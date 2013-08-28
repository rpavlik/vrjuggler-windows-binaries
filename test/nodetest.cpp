#include <assert.h>
#include <iostream>
#include <string>
#include <cppdom/cppdom.h>

bool configureInput( const std::string& filename )
{
   cppdom::ContextPtr ctx( new cppdom::Context );
   cppdom::Document doc( ctx );

   // load a xml document from a file
   try
   {
      doc.loadFile( filename );
   }
   catch (cppdom::Error e)
   {
      std::cerr << "Error: " << e.getString() << std::endl;
      if (e.getInfo().size())
      {
         std::cerr << "File: " << e.getInfo() << std::endl;
      }
      if (e.getError() != cppdom::xml_filename_invalid &&
          e.getError() != cppdom::xml_file_access)
      {
/*
         e.show_error( ctx );
         e.show_line( ctx, filename );
*/
         std::cout << "Error: (need to impl the show functions)" << std::endl;
      }
      return false;
   }

   std::cerr << "successfully loaded " << filename << std::endl;

   cppdom::NodeList nl = doc.getChild( "gameinput" )->getChildren();
   cppdom::NodeListIterator it = nl.begin();
   while (it != nl.end())
   {
      std::cerr << "in name: " << (*it)->getName() << std::endl;
      try
      {
         cppdom::Attributes& attr = (*it)->attrib();
         std::cout << "attr: " << attr.get( "action" ) << "\n" << std::flush;
         std::cout << "attr: " << attr.get( "device" ) << "\n" << std::flush;
         std::cout << "attr: " << attr.get( "input" ) << "\n" << std::flush;

         cppdom::Node* parent = (*it)->getParent();
         assert(parent != NULL && parent->getName() == std::string("gameinput"));
      }
      catch (cppdom::Error e)
      {
         std::cerr << "Error: " << e.getString() << std::endl;
         it++;
         continue;
      }
      it++;
   }

   return true;
}

/** Main function */
int main()
{
   // Just call single function to load and process input file
   configureInput( "game.xml" );
   return 1;
}

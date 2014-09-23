#ifndef OPTION_REPOSITORY_H
#define OPTION_REPOSITORY_H

#include <string>
#include <sstream>
#include <cppdom/cppdom.h>


namespace cppdom
{

/**
 * Extension class for managing configuration options.
 * Allow an xml configuration file to be loaded and provides a simplified
 * API for accessing contained options.
 * It acts as a hierarchical map of indices to correlated string values.
 * The options system loads XML configuration files and takes full option
 * specifications as strings of the form:  option/option/.../attrib
 */
class CPPDOM_CLASS OptionRepository
{
public:
   /** Constructor.
    * @param rootTagName   The name of the element that is the base for all options elements.
    */
   OptionRepository(std::string rootTagName="options");

   /** Template method to get option value and convert to known type.
    * @example  int value = opts.getValue<int>("group/mine/option");
    * @param option  Option identifier of same form as for getOptionString.
    * @return  If option does not exist, throws error.
    * @note Requires a stream operation of type T
    */
   template<class T>
   T getValue(std::string option, const T defaultVal = T())
   {
      T t = defaultVal;
      std::string str_val = getOptionString(option);
      if(!str_val.empty())
      {
         std::istringstream iss(str_val);
         iss >> t;
      }
      return t;
   }

#if defined(_MSC_VER) && _MSC_VER == 1300
   template<>
   std::string getValue<std::string>(std::string option,
                                     const std::string defaultValue)
   {
      std::string str_val = getOptionString(option);
      return str_val;
   }
#endif

   /**
    * Set mData to the string value of val
    * @note Requires a stream operation of type T
    */
   template<class T>
   void setValue(std::string option, const T& val)
   {
      std::ostringstream oss;
      oss << val;
      std::string str_val = oss.str();
      setOptionString(option, str_val);
   }


   /** Called to check if option exists.
    */
   bool hasOption(std::string option);

   /** Called to get string value of option.
    * @param  option    Option identifier of the form group/group/.../option.
    * @return Empty string if option not found, otherwise the string value of the option.
    * @note   The naming convention corresponds to XML element.element.attrib.
    */
   std::string getOptionString(std::string option);

   /** Set the value of an option.
    * @param option     The option to set the value for.
    * @param value      The value to set option to.
    */
   void setOptionString(std::string option, std::string value);

   /** Return the xml node for the root of the options tree. */
   NodePtr optionsNode()
   { return mOptionRoot; }

   /** Loads a set of options from the given file.
    * @param filename   Name of an XML file of options.  root node must have tag "terra_options"
    */
   void loadOptionsFile(std::string filename);

   /** Save a set of options to the given file.
    * @param filename   Name of the file to save the XML options.
    */
   void saveOptionsFile(std::string filename);

protected:
   /** Helper method to split the option string to the elt path and the attrib name. */
   void splitOptionPath(const std::string& option, std::string& option_path, std::string& attrib_name);

protected:
   cppdom::DocumentPtr  mDocRoot;         /** Root of the document we are holding. */
   cppdom::NodePtr      mOptionRoot;      /** Root of options tree. */
   std::string          mOptionRootTag;   /** The tag for the root options element. default: options. */
};

#if ! defined(_MSC_VER) || _MSC_VER > 1300
template<>
inline std::string OptionRepository::getValue<std::string>(std::string option, const std::string defaultValue)
{
   std::string str_val = getOptionString(option);
   return str_val;
}
#endif

}

#endif //OPTIONS_H

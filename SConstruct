#!python
try:
   import wing.wingdbstub;       # stuff for debugging
   print "Loaded wingdb stub for debugging..."
except:
   pass

import os, string, sys, re, glob, copy, types
import os.path
sys.path.insert(0, os.path.join('deps', 'scons-addons', 'src'))

import SCons.Environment
import SCons
import SConsAddons.Util
import SConsAddons.Options as sca_opts
import SConsAddons.Variants as sca_variants
import SConsAddons.Builders
import SConsAddons.Options.CppUnit
import SConsAddons.Options.Boost
from SConsAddons.EnvironmentBuilder import EnvironmentBuilder

# Aliases
GetPlatform = SConsAddons.Util.GetPlatform
Export('GetPlatform')
pj = os.path.join

#------------------------------------------------------------------------------
# Main build setup
#------------------------------------------------------------------------------
EnsureSConsVersion(2,0)
#SourceSignatures('MD5')
#SourceSignatures('timestamp')
SConsignFile('.sconsign.'+GetPlatform())

# Figure out what version of CppDom we're using
CPPDOM_VERSION = SConsAddons.Util.GetVersionFromHeader('CPPDOM', 'cppdom/version.h')
cppdom_version_str = '%i.%i.%i' % CPPDOM_VERSION
Export('CPPDOM_VERSION')
print 'Building CppDom Version: %s' % cppdom_version_str

platform = GetPlatform()
unspecified_prefix = "use-instlinks"
buildDir = "build." + platform      
option_filename = "config.cache." + platform

temp_env = dict(ENV = os.environ)
if GetPlatform() == "win32":
   if ARGUMENTS.has_key("MSVC_VERSION"):
      temp_env["MSVC_VERSION"] = ARGUMENTS["MSVC_VERSION"]

   if ARGUMENTS.has_key("MSVS_ARCH"):
      temp_env["MSVS_ARCH"] = ARGUMENTS["MSVS_ARCH"]
      temp_env["TARGET_ARCH"] = ARGUMENTS["MSVS_ARCH"]

   temp_env["MSVS"] = {"VERSION" : temp_env["MSVC_VERSION"]}

temp_env["CONFIGUREDIR"] = '.sconf_temp_'+platform
temp_env["CONFIGURELOG"] = 'sconf.log_'+platform

# Create variant helper and builder
variant_helper = sca_variants.VariantsHelper()
base_bldr = EnvironmentBuilder()

# --------------- #
# --- OPTIONS --- #
# --------------- #
opts = sca_opts.Options(files = [option_filename, 'options.custom'],
                                   args= ARGUMENTS)

cppunit_options = SConsAddons.Options.CppUnit.CppUnit("cppunit", "1.9.10", required=0)
boost_options = SConsAddons.Options.Boost.Boost("boost","1.31.0",required=0)
opts.AddOption(sca_opts.SeparatorOption("\nPackage Options"))
opts.AddOption( cppunit_options )
opts.AddOption( boost_options )

base_bldr.addOptions(opts)
variant_helper.addOptions(opts)
common_env = base_bldr.buildEnvironment(None,None,**temp_env)
SConsAddons.Builders.registerSubstBuilder(common_env)

opts.AddOption(sca_opts.SeparatorOption("\nOther settings"))
opts.Add('prefix', 'Installation prefix', unspecified_prefix)
opts.Add('build_test', 'Build the test programs', 'yes')
opts.Add(sca_opts.BoolOption('versioning', 
                             'If no then build only libraries and headers without versioning', True))
#if common_env.has_key("MSVS"):
#   opts.Add('MSVS_VERSION', 'Set to specific version of MSVS to use. %s'%str(common_env['MSVS']['VERSIONS']), 
#            common_env['MSVS']['VERSION'])

opts.Process(common_env)

help_text = """--- CppDom Build system ---
%s
Targets:
   install - Install this puppy
      ex: 'scons install prefix=$HOME/software' to install in your account
   Type 'scons' to just build it
 
"""%(opts.GenerateHelpText(common_env),)

#help_text = opts.GenerateHelpText(common_env) + help_text

# --- MAIN BUILD STEPS ---- #
# If we are running the build
if not SConsAddons.Util.hasHelpFlag():
   try:                                   # Try to save the options if possible
      opts.Save(option_filename, common_env)
   except LookupError, le:
      pass
   
   # -- Common builder settings
   variant_helper.readOptions(common_env)
   base_bldr.readOptions(common_env)
   base_bldr.enableWarnings()   
  
   # Apply any common package options
   # Update environment for boost options
   if boost_options.isAvailable():
      boost_options.apply(common_env)    
     
   # If defaulting to instlinks prefix:
   #  - Use symlinks
   #  - Manually set the used prefix to the instlinks of the build dir
   if common_env['prefix'] == unspecified_prefix:
      if hasattr(os,'symlink'):
         common_env['INSTALL'] = SConsAddons.Util.symlinkInstallFunc
      common_env['prefix'] = pj( Dir('.').get_abspath(), buildDir, 'instlinks')
   
   # --- Setup installation paths --- #
   base_inst_paths = {}
   base_inst_paths['base'] = os.path.abspath(common_env['prefix'])
   base_inst_paths['lib'] = pj(base_inst_paths['base'], 'lib')
   base_inst_paths['flagpoll'] = pj(base_inst_paths['lib'], 'flagpoll')
   base_inst_paths['bin'] = pj(base_inst_paths['base'], 'bin')
   base_inst_paths['flagpollPrefix'] = pj('${fp_file_cwd}' ,'..' ,'..')
   include_dir = pj(base_inst_paths['base'], 'include')
   base_inst_paths['includePrefix'] = pj( base_inst_paths['flagpollPrefix'], 'include')

   if GetPlatform() == "win32":
      base_inst_paths["include_path_flag"] = "/I"
      base_inst_paths["lib_path_flag"]     = "/LIBPATH:"
   else:
      base_inst_paths["include_path_flag"] = "-I"
      base_inst_paths["lib_path_flag"]     = "-L"

   if common_env['versioning']:
      version_suffix = "-%s_%s_%s" % CPPDOM_VERSION

      # We do not use a versioned header directory on Windows.
      if not sys.platform.startswith('win'):
         include_dir = pj(base_inst_paths['base'], 'include', 
                          "cppdom-%s.%s.%s" % CPPDOM_VERSION)
      base_inst_paths['includePrefix'] = pj(  base_inst_paths['includePrefix'], 
                                              "cppdom-%s.%s.%s" % CPPDOM_VERSION )
   else:
      version_suffix = ''

   base_inst_paths['include'] = include_dir
   print "using prefix: ", base_inst_paths['base']         
      
   print "types: ",    variant_helper.variants["type"] 
   print "libtypes: ", variant_helper.variants["libtype"] 
   print "archs: ",    variant_helper.variants["arch"] 

   sub_dirs = ['cppdom']
   if common_env['build_test'] == 'yes':
      sub_dirs.append('test')

   # ---- FOR EACH VARIANT ----- #   
   for combo in variant_helper.iterate(locals(), base_bldr, common_env):
      #build_env = base_bldr.applyToEnvironment(common_env.Copy(), variant=combo,options=opts)  
      print "   Processing combo: ", ", ".join(['%s:%s'%(i[0],i[1]) for i in combo.iteritems()])

      inst_paths = copy.copy(base_inst_paths)
      inst_paths['libPrefix'] = pj(inst_paths['flagpollPrefix'], 'lib')
      if "x64" == combo["arch"]:
         inst_paths['lib'] = inst_paths['lib'] + '64'
         inst_paths['libPrefix'] = inst_paths['libPrefix'] + '64'
      if "debug" == combo["type"]:
         inst_paths["lib"] = pj(inst_paths["lib"],"debug")
         inst_paths['libPrefix'] = pj(inst_paths['libPrefix'],'debug')

      if GetPlatform() == 'win32':
         inst_paths["libPrefix"] = '"%s"' % inst_paths["libPrefix"]
         inst_paths["includePrefix"] = '"%s"' % inst_paths["includePrefix"]

      cppdom_shared_libname = 'cppdom' + shared_lib_suffix + version_suffix
      cppdom_static_libname = 'cppdom' + static_lib_suffix + version_suffix
      
      # set a library name to use when linking test applications
      if "shared" in combo["libtype"]:
         cppdom_app_libname = cppdom_shared_libname
      elif "static" in combo["libtype"]:
         cppdom_app_libname = cppdom_static_libname
      
      Export('build_env','inst_paths','opts', 'variant_pass','combo',
             'cppunit_options', 'boost_options', 
             'cppdom_shared_libname','cppdom_static_libname', 'cppdom_app_libname')
      
      # Process subdirectories
      full_build_dir = pj(buildDir,combo_dir)      
      for d in sub_dirs:
         SConscript(pj(d,'SConscript'), variant_dir=pj(full_build_dir, d), duplicate=0)

      # Build up the provides vars for the .fpc files
      inst_paths['flagpoll'] = pj(inst_paths['lib'],'flagpoll')
      provides = "cppdom"
      # XXX: provides data
      #if combo["type"] != "optimized":
      #   provides += "_%s"%combo["type"]

      arch = "noarch"
      if "ia32" == combo["arch"]:
         arch = "i386"
      elif "x64" == combo["arch"]:
         arch = "x86_64"      
      elif "ppc" == combo["arch"]:
         arch = "ppc"
      elif "ppc" == combo["arch"]:
         arch = "ppc64"
      elif "universal" == combo["arch"]:
         arch = "universal"

      cppdom_cxxflags = ''
      cppdom_libs = "-l%s" % cppdom_shared_libname

      # Use automatic linking on Windows.
      if GetPlatform() == 'win32':
         cppdom_libs     = ''
         cppdom_cxxflags = '/DCPPDOM_AUTO_LINK'

         if "debug" in combo["type"] or "debugrt" in combo["type"]:
            cppdom_cxxflags += ' /DCPPDOM_DEBUG'
         if "shared" in combo["libtype"]:
            cppdom_cxxflags += ' /DCPPDOM_DYN_LINK'

      # - Define a builder for the cppdom.fpc file
      # ------------------ Build -config and .pc files ----------------- #
      # Build up substitution map
      submap = {
         '@provides@'                  : provides,
         '@prefix@'                    : inst_paths['flagpollPrefix'],
         '@exec_prefix@'               : '${prefix}',
         '@cppdom_cxxflags@'           : cppdom_cxxflags,
         '@include_path_flag@'         : inst_paths['include_path_flag'],
         '@includedir@'                : inst_paths['includePrefix'],
         '@cppdom_extra_cxxflags@'     : '',
         '@cppdom_extra_include_dirs@' : '',
         '@cppdom_libs@'               : cppdom_libs,
         '@lib_path_flag@'             : inst_paths['lib_path_flag'],
         '@libdir@'                    : inst_paths['libPrefix'],
         '@arch@'                      : arch,
         '@version@'                   : cppdom_version_str
      }

      # Setup the builder for cppdom.fpc
      # XXX: This generates multiple cppdom*.fpc files instead of putting all
      # the variation of debug/optimized/debugrt and static/shared into one
      # architecture-specific file!
      name_parts = ['cppdom',cppdom_version_str,arch]
      if combo["type"] != "optimized":
         name_parts.append(combo["type"])
      if GetPlatform() == 'win32':
         name_parts.append(combo["libtype"])
      pc_filename = "-".join(name_parts) + ".fpc"
      cppdom_pc   = build_env.SubstBuilder(pj(inst_paths['flagpoll'],
                                              pc_filename),
                                           'cppdom.fpc.in', submap = submap)
      build_env.AddPostAction(cppdom_pc, Chmod('$TARGET', 0644))
      build_env.Depends(cppdom_pc, 'cppdom/version.h')
   
   common_env.Install(inst_paths['bin'],'cppdom-config')
   common_env.Alias('install', inst_paths['base'])

   # Close up with aliases and defaults   
   Default('.')

Help(help_text)

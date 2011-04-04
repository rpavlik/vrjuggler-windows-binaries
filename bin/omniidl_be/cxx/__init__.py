# -*- python -*-
#                           Package   : omniidl
# __init__.py               Created on: 1999/11/3
#			    Author    : David Scott (djs)
#
#    Copyright (C) 2002-2008 Apasphere Ltd
#    Copyright (C) 1999 AT&T Laboratories Cambridge
#
#  This file is part of omniidl.
#
#  omniidl is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
#  02111-1307, USA.
#
# Description:
#
#   Entrypoint to the C++ backend

# $Id: __init__.py,v 1.23.2.9 2009/05/06 16:15:53 dgrisby Exp $
# $Log: __init__.py,v $
# Revision 1.23.2.9  2009/05/06 16:15:53  dgrisby
# Update lots of copyright notices.
#
# Revision 1.23.2.8  2008/12/03 10:53:58  dgrisby
# Tweaks leading to Python 3 support; other minor clean-ups.
#
# Revision 1.23.2.7  2007/09/11 12:01:20  dgrisby
# Do not mask exceptions in the C++ backend.
#
# Revision 1.23.2.6  2007/05/11 09:52:28  dgrisby
# New -Wbguard_prefix option. Thanks Austin Bingham.
#
# Revision 1.23.2.5  2005/11/18 18:23:06  dgrisby
# New -Wbimpl_mapping option.
#
# Revision 1.23.2.4  2005/09/05 17:22:09  dgrisby
# Reference counted local call shortcut.
#
# Revision 1.23.2.3  2005/01/06 23:09:47  dgrisby
# Big merge from omni4_0_develop.
#
# Revision 1.23.2.2  2003/10/23 11:25:54  dgrisby
# More valuetype support.
#
# Revision 1.23.2.1  2003/03/23 21:02:43  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.20.2.7  2002/09/03 09:32:57  dgrisby
# C++ back-end bails out if asked to compile more than one file.
#
# Revision 1.20.2.6  2002/03/11 12:23:45  dpg1
# -Wbe option for example code suffix.
#
# Revision 1.20.2.5  2002/02/20 13:37:18  dpg1
# C++ back-end old signatures option did not work.
#
# Revision 1.20.2.4  2001/11/08 16:33:50  dpg1
# Local servant POA shortcut policy.
#
# Revision 1.20.2.3  2001/06/08 17:12:11  dpg1
# Merge all the bug fixes from omni3_develop.
#
# Revision 1.20.2.2  2000/10/12 15:37:45  sll
# Updated from omni3_1_develop.
#
# Revision 1.21.2.4  2000/09/14 16:03:00  djs
# Remodularised C++ descriptor name generator
# Bug in listing all inherited interfaces if one is a forward
# repoID munging function now handles #pragma ID in bootstrap.idl
# Naming environments generating code now copes with new IDL AST types
# Modified type utility functions
# Minor tidying
#
# Revision 1.21.2.3  2000/08/21 11:34:31  djs
# Lots of omniidl/C++ backend changes
#
# Revision 1.21.2.2  2000/08/07 17:48:14  dpg1
# Merge from omni3_develop again.
#
# Revision 1.18.2.8  2000/07/18 15:34:17  djs
# Added -Wbvirtual_objref option to make attribute and operation _objref
# methods virtual
#
# Revision 1.18.2.7  2000/06/26 16:23:09  djs
# Added new backend arguments.
# Better error handling when encountering unsupported IDL (eg valuetypes)
# Refactoring of configuration state mechanism.
#
# Revision 1.18.2.6  2000/05/31 15:11:11  dpg1
# C++ back-end properly handles Windows paths.
#
# Revision 1.18.2.5  2000/05/24 17:16:34  dpg1
# Minor omniidl usage message fix.
#
# Revision 1.18.2.4  2000/05/04 14:34:50  djs
# Added new flag splice-modules which causes all continuations to be output
# as one lump. Default is now to output them in pieces following the IDL.
#
# Revision 1.18.2.3  2000/04/26 18:22:12  djs
# Rewrote type mapping code (now in types.py)
# Rewrote identifier handling code (now in id.py)
#
# Revision 1.18.2.2  2000/02/18 23:01:19  djs
# Updated example implementation code generating module
#
# Revision 1.18.2.1  2000/02/14 18:34:57  dpg1
# New omniidl merged in.
#
# Revision 1.18  2000/01/13 11:45:47  djs
# Added option to customise C++ reserved word name escaping
#
# Revision 1.17  2000/01/13 10:52:04  djs
# Rewritten argument handling
# Added options to specify the header and stubs file prefix, mirroring omniidl3
#
# Revision 1.16  2000/01/12 19:54:47  djs
# Added option to generate old CORBA 2.1 signatures for skeletons
#
# Revision 1.15  2000/01/12 17:48:27  djs
# Added option to create BOA compatible skeletons (same as -BBOA in omniidl3)
#
# Revision 1.14  2000/01/11 14:12:41  djs
# Updated commandline option help to include Fragment generation
#
# Revision 1.13  2000/01/11 11:35:36  djs
# Added support for fragment generation (-F) mode
#
# Revision 1.12  2000/01/10 15:39:34  djs
# Better name and scope handling.
#
# Revision 1.11  1999/12/24 18:20:12  djs
# Builds list of IDL files #included by walking the AST and examining the
# file() of each Decl node.
#
# Revision 1.10  1999/12/09 20:41:24  djs
# Now runs typecode and any generator
#
# Revision 1.9  1999/12/01 17:05:13  djs
# Backend now supports command line arguments
#
# Revision 1.8  1999/11/29 19:26:59  djs
# Code tidied and moved around. Some redundant code eliminated.
#
# Revision 1.7  1999/11/17 20:37:09  djs
# General util functions
#
# Revision 1.6  1999/11/15 19:10:54  djs
# Added module for utility functions specific to generating skeletons
# Union skeletons working
#
# Revision 1.5  1999/11/12 17:17:45  djs
# Creates output files rather than using stdout
# Utility functions useful for skeleton generation added
#
# Revision 1.4  1999/11/08 19:28:56  djs
# Rewrite of sequence template code
# Fixed lots of typedef problems
#
# Revision 1.3  1999/11/04 19:05:01  djs
# Finished moving code from tmp_omniidl. Regression tests ok.
#
# Revision 1.2  1999/11/03 17:35:06  djs
# Brought more of the old tmp_omniidl code into the new tree
#
# Revision 1.1  1999/11/03 11:09:49  djs
# General module renaming
#

# From http://www-i3.informatik.rwth-aachen.de/funny/babbage.html:
# ...
# C. A. R. Hoare, in his 1980 ACM Turing Award lecture, told of two
# ways of constructing a software design: "One way is to make it so
# simple that there are obviously no deficiencies and the other way
# is to make it so complicated that there are no obvious deficiencies." 
#

## Import Output generation functions ###################################
## 
from omniidl_be.cxx import header, skel, dynskel, impl

## Utility functions
from omniidl_be.cxx import id, config, ast, output, support, descriptor

import re, sys, os.path

cpp_args = ["-D__OMNIIDL_CXX__"]
usage_string = """\
  -Wbh=<suffix>     Specify suffix for generated header files
  -Wbs=<suffix>     Specify suffix for generated stub files
  -Wbd=<suffix>     Specify suffix for generated dynamic files
  -Wba              Generate code for TypeCodes and Any
  -Wbtp             Generate 'tie' implementation skeletons
  -Wbtf             Generate flattened 'tie' implementation skeletons
  -Wbsplice-modules Splice together multiply opened modules into one 
  -Wbexample        Generate example implementation code
  -WbF              Generate code fragments (for experts only)
  -WbBOA            Generate BOA compatible skeletons
  -Wbold            Generate old CORBA 2.1 signatures for skeletons
  -Wbold_prefix     Map C++ reserved words with prefix _ instead of _cxx_
  -Wbinline         Generate code for #included files inline with the main file
  -Wbkeep_inc_path  Preserve IDL #include path in header #includes
  -Wbuse_quotes     Use quotes in #includes: "foo" rather than <foo>
  -Wbdll_includes   Extra support for #included IDL in DLLs
  -Wbguard_prefix   Prefix for include guards in generated headers
  -Wbvirtual_objref Use virtual functions in object references
  -Wbimpl_mapping   Use 'impl' mapping for object reference methods"""

# Encountering an unknown AST node will cause an AttributeError exception
# to be thrown in one of the visitors. Store a list of those not-supported
# so we can produce a friendly error message later.
AST_unsupported_nodes = [ "Native" ]

def process_args(args):
    for arg in args:
        if arg == "a":
            config.state['Typecode']          = 1
        elif arg == "tp":
            config.state['Normal Tie']        = 1
        elif arg == "tf":
            config.state['Flattened Tie']     = 1
        elif arg == "splice-modules":
            config.state['Splice Modules']    = 1
        elif arg == "example":
            config.state['Example Code']      = 1
        elif arg == "F":
            config.state['Fragment']          = 1
        elif arg == "BOA":
            config.state['BOA Skeletons']     = 1
        elif arg == "old":
            config.state['Old Signatures']    = 1
        elif arg == "old_prefix":
            config.state['Reserved Prefix']   = "_"
        elif arg == "keep_inc_path":
            config.state['Keep Include Path'] = 1
        elif arg == "use_quotes":
            config.state['Use Quotes']        = 1
        elif arg == "virtual_objref":
            config.state['Virtual Objref Methods'] = 1
        elif arg == "impl_mapping":
            config.state['Impl Mapping'] = 1
        elif arg == "debug":
            config.state['Debug']             = 1
        elif arg[:2] == "h=":
            config.state['HH Suffix']         = arg[2:]
        elif arg[:2] == "s=":
            config.state['SK Suffix']         = arg[2:]
        elif arg[:2] == "d=":
            config.state['DYNSK Suffix']      = arg[2:]
        elif arg[:2] == "e=":
            config.state['IMPL Suffix']       = arg[2:]
        elif arg == "inline":
            config.state['Inline Includes']   = 1
        elif arg == "shortcut":
            config.state['Shortcut']          = 1
        elif arg[:9] == "shortcut=":
            if arg[9:] == "refcount":
                config.state['Shortcut']      = 2
            elif arg[9:] == "simple":
                config.state['Shortcut']      = 1
            else:
                util.fatalError('Unknown shortcut option "%s"' % arg[9:])
        elif arg == "dll_includes":
            config.state['DLLIncludes']       = 1
        elif arg[:len('guard_prefix=')] == "guard_prefix=":
            config.state['GuardPrefix']       = arg[len('guard_prefix='):]
        else:
            util.fatalError("Argument \"" + str(arg) + "\" is unknown")

run_before = 0

def run(tree, args):
    """Entrypoint to the C++ backend"""

    global run_before

    if run_before:
        util.fatalError("Sorry, the C++ backend cannot process more "
                        "than one IDL file at a time.")
    run_before = 1

    dirname, filename = os.path.split(tree.file())
    basename,ext      = os.path.splitext(filename)
    config.state['Basename']  = basename
    config.state['Directory'] = dirname

    process_args(args)

    try:
        # Check the input tree only contains stuff we understand
        support.checkIDL(tree)

        # initialise the handy ast module
        ast.__init__(tree)

        # Initialise the descriptor generating code
        descriptor.__init__(tree)

        # Build the map of AST nodes to Environments
        tree.accept(id.WalkTree())

        # AMI code hooks into existing infrastructure (ie doesn't need to
        # be driven explicitly here)
        #if config.state['AMI']:
        #    tree = ami.__init__(tree)
        #    tree.accept(id.WalkTree())
        # Not ported yet.
        
        header.run(tree)
        
        skel.run(tree)
        
        # if we're generating code for Typecodes and Any then
        # we need to create the DynSK.cc file
        if config.state['Typecode']:
            dynskel.run(tree)

        if config.state['Example Code']:
            impl.run(tree)

    except AttributeError, e:
        name = e.args[0]
        unsupported_visitors = map(lambda x:"visit" + x,
                                   AST_unsupported_nodes[:])
        if name in unsupported_visitors:
            # delete all possibly partial output files
            for file in output.listAllCreatedFiles():
                os.unlink(file)

            util.unsupportedIDL()
            
        raise

    except SystemExit, e:
        # fatalError function throws SystemExit exception
        # delete all possibly partial output files
        for file in output.listAllCreatedFiles():
            os.unlink(file)
        
        raise

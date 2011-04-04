# -*- python -*-
#                           Package   : omniidl
# forward.py                Created on: 1999/12/1
#			    Author    : David Scott (djs)
#
#    Copyright (C) 2003-2004 Apasphere Ltd
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
#   Produce ancillary forward declarations for the header file

# $Id: forward.py,v 1.10.2.5 2009/05/06 16:15:46 dgrisby Exp $
# $Log: forward.py,v $
# Revision 1.10.2.5  2009/05/06 16:15:46  dgrisby
# Update lots of copyright notices.
#
# Revision 1.10.2.4  2004/07/23 10:29:59  dgrisby
# Completely new, much simpler Any implementation.
#
# Revision 1.10.2.3  2003/11/06 11:56:56  dgrisby
# Yet more valuetype. Plain valuetype and abstract valuetype are now working.
#
# Revision 1.10.2.2  2003/10/23 11:25:55  dgrisby
# More valuetype support.
#
# Revision 1.10.2.1  2003/03/23 21:02:37  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.8.2.5  2001/10/29 17:42:40  dpg1
# Support forward-declared structs/unions, ORB::create_recursive_tc().
#
# Revision 1.8.2.4  2001/06/08 17:12:17  dpg1
# Merge all the bug fixes from omni3_develop.
#
# Revision 1.8.2.3  2001/03/26 11:11:55  dpg1
# Python clean-ups. Output routine optimised.
#
# Revision 1.8.2.2  2000/10/12 15:37:51  sll
# Updated from omni3_1_develop.
#
# Revision 1.9.2.1  2000/08/21 11:35:17  djs
# Lots of tidying
#
# Revision 1.9  2000/07/13 15:26:00  dpg1
# Merge from omni3_develop for 3.0 release.
#
# Revision 1.6.2.4  2000/06/26 16:23:59  djs
# Better handling of #include'd files (via new commandline options)
# Refactoring of configuration state mechanism.
#
# Revision 1.6.2.3  2000/06/05 13:03:56  djs
# Removed union member name clash (x & pd_x, pd__default, pd__d)
# Removed name clash when a sequence is called "pd_seq"
# Nested union within union fix
# Actually generates BOA non-flattened tie templates
#
# Revision 1.6.2.2  2000/04/26 18:22:29  djs
# Rewrote type mapping code (now in types.py)
# Rewrote identifier handling code (now in id.py)
#
# Revision 1.6.2.1  2000/02/14 18:34:55  dpg1
# New omniidl merged in.
#
# Revision 1.6  2000/01/19 11:23:28  djs
# Moved most C++ code to template file
#
# Revision 1.5  2000/01/17 17:02:14  djs
# Constructed types in typedef fix
#
# Revision 1.4  2000/01/13 15:56:39  djs
# Factored out private identifier prefix rather than hard coding it all through
# the code.
#
# Revision 1.3  2000/01/07 20:31:28  djs
# Regression tests in CVSROOT/testsuite now pass for
#   * no backend arguments
#   * tie templates
#   * flattened tie templates
#   * TypeCode and Any generation
#
# Revision 1.2  1999/12/24 18:14:30  djs
# Fixed handling of #include'd .idl files
#
# Revision 1.1  1999/12/01 17:01:46  djs
# New module to create necessary forward declarations in the header
#

"""Produce ancillary forward declarations for the header file"""

from omniidl import idlast, idltype, idlutil
from omniidl_be.cxx import config, id, ast
from omniidl_be.cxx.header import template

import forward
self = forward

def __init__(stream):
    forward.stream = stream
    return forward

# Control arrives here
#
def visitAST(node):
    for n in node.declarations():
        if ast.shouldGenerateCodeForDecl(n):
            n.accept(self)

def visitModule(node):
    # again check what happens here wrt reopening modules spanning
    # multiple files
    for n in node.definitions():
        n.accept(self)


def visitStruct(node):
    for n in node.members():
        n.accept(self)

def visitStructForward(node):
    pass

def visitUnion(node):
    for n in node.cases():
        if n.constrType():
            n.caseType().decl().accept(self)
            
def visitUnionForward(node):
    pass

def visitInterface(node):
    for n in node.declarations():
        n.accept(self)



def visitException(node):
    for n in node.members():
        n.accept(self)
        
def visitMember(node):
    if node.constrType():
        node.memberType().decl().accept(self)

def visitEnum(node):
    pass


def visitTypedef(node):
    if node.constrType():
        node.aliasType().decl().accept(self)
    
        
def visitForward(node):
    pass
def visitConst(node):
    pass
def visitDeclarator(node):
    pass

def visitValueForward(node):
    pass
def visitValue(node):
    pass
def visitValueAbs(node):
    pass
def visitValueBox(node):
    pass

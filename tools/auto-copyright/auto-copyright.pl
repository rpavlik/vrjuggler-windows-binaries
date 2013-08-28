#!/usr/bin/perl

#
# Copyright (c) 2000 Patrick L. Hartling (original author)
# contributors:
#  - Kevin Meinert (command line args, external config data, working dir)
#  - Ben Scott (emacs and vi modeline support)
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The names of its contributors may not be used to endorse or promote
#    products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
# NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#       $Id$
#

use File::Basename;
use Getopt::Std;

# Do this to include the path to the script in @INC.
my $path;

BEGIN {
    $path = (fileparse("$0"))[1];
}

use lib($path.".");
use RecurseDir;

# get opts:
getopts('d:m:t:c:e:ha');

my $modeline_file = "$opt_m";
my $tags_file = "$opt_t";
my $copyright_file = "$opt_c";
my @extensions = split( /,/, "$opt_e" );
my $working_dir = "$opt_d" || ".";



if ( $opt_h )
{
   helpText();
   exit 1;
}

# execute the tags file, putting it's vars into scope.
if($tags_file)
{
   unless ($return = do $tags_file)
   {
       helpText();
       warn "couldn't parse $tags_file: $@"         if $@;
       warn "couldn't do $tags_file: $!"            unless defined $return;
       warn "couldn't run $tags_file"               unless $return;
   }
}

# execute the modeline file, putting it's vars into scope
if ($modeline_file)
{
   unless ($return = do $modeline_file)
   {
       helpText();
       warn "couldn't parse $modeline_file: $@"     if $@;
       warn "couldn't do $modeline_file: $!"        unless defined $return;
       warn "couldn't run $modeline_file"           unless $return;
       exit 1;
   }
}
if (!open(TAGSFILE, "$tags_file"))
{
   helpText();
   print "ERROR: Must specify a valid tags file. i.e. -t tags.pl\n";
   exit 1;
}
close(TAGSFILE);


$RecurseDir::print_cur_dir = 1;
$RecurseDir::pass_rec_func_cur_file = 1;

if (!open(COPYRIGHT, "$copyright_file"))
{
   helpText();
   print "ERROR: Must specify a valid copyright file. i.e. -c copyright_header_include.txt\n";
   exit 1;
}
my(@copyright) = <COPYRIGHT>;
close(COPYRIGHT);


recurseDir( $working_dir );

exit 0;

sub helpText()
{
    print "\n\n";
    print "auto-copyright - by patrick hartling and kevin meinert\n";
    print "\n";
    print "Example Usage: \n";
    print "       $0 -c copyrightheader.txt -t tagsfile.pl -e h,cpp -a\n";
    print "             add or replace header to all files in current dir\n";
    print "\n";
    print "       $0 -c copyrightheader.txt -t tagsfile.pl -e h,cpp\n";
    print "             replace headers (no add) to all files in current dir\n";
    print "\n";
    print "       $0 -h\n";
    print "             gives this text\n";
    print "\n";
    print "Options:\n";
    print "       -d <working dir> name of dir to start recursive processing\n";
    print "       -e <ext1,ext2,..,extn> file extensions to process\n";
    print "       -m <modelinefile> name of the file with the modeline header\n";
    print "       -c <(c) header> name of file with copyright text\n";
    print "       -t <tags.pl> name of perl script which defines 4\n";
    print "                    variables as input to this script\n";
    print "       -a causes the header to be added if old header is not found\n";
    print "\n\n";
}

sub makeRegexSafe( $$ )
{
   my $string = shift;
   my $regex_safe_string = shift;

   $$regex_safe_string = $string;
   $$regex_safe_string =~ s/\./\\./gs;
   $$regex_safe_string =~ s/\*/\\*/gs;
   $$regex_safe_string =~ s/\$/\\\$/gs;
   $$regex_safe_string =~ s/\+/\\+/gs;
   $$regex_safe_string =~ s/\?/\\?/gs;
   $$regex_safe_string =~ s/\@/\\\@/gs;
}


sub recurseFunc {
   my $filename = shift;

   return unless checkName("$filename");

   if ( ! open(INPUT, "$filename") )
   {
      warn "WARNING: Could not open $filename: $!\n";
   }

   else
   {
      if ( ! open(OUTPUT, "> $filename.new") )
      {
         warn "WARNING: Could not create new file: $!\n";
      }

      else
      {
         # gather every copyright together
         my $all_copyrights;
         foreach(@copyright)
         {
            $all_copyrights .= $_;
         }

         # gather each line of the source file into one string so we can do a subst across multiple lines.
         my $file_contents;
         while(<INPUT>)
         {
            $file_contents .= $_;
         }

         # check for emacs modeline
         if ( $file_contents =~ m!^(/\*|//) *-\*- Mode:.*-\*-( *\*/)?! )
         {
            print "Replacing emacs modeline in $filename ...\n";
            print OUTPUT "$1 -*- Mode: $emacs_modeline -*-$2\n";
            $file_contents =~ s!(/\*|//) *-\*- Mode:.*-\*-( *\*/)?\r?\n!!;
         }
         elsif ($opt_a)
         {
            print "Adding emacs modeline to $filename ...\n";
            print OUTPUT "/* -*- Mode: $emacs_modeline -*- */\n";
         }
         else
         {
            print "$filename: No previous emacs modeline, no replace.\n";
         }

         # check for vim modeline
         if ( $file_contents =~ m!(/\*|//) *vim:.*( *\*/)?! )
         {
            print "Replacing vim modeline in $filename ...\n";
            print OUTPUT "$1 vim:$vim_modeline$2\n";
            $file_contents =~ s!(/\*|//) *vim:.*( *\*/)?\r?\n!!;
         }
         elsif ($opt_a)
         {
            print "Adding vim modeline to $filename ...\n";
            print OUTPUT "// vim:$vim_modeline\n";
         }
         else
         {
            print "$filename: No previous vim modeline, no replace.\n";
         }

         my $copyrights_plus_delimiters = "$newbegintag\n$all_copyrights$newendtag\n";

         # convert tags for use in a regex
         $begintag_regex_safe = $begintag;
         $endtag_regex_safe = $endtag;
         makeRegexSafe( $begintag, \$begintag_regex_safe );
         makeRegexSafe( $endtag, \$endtag_regex_safe );

         if ( $file_contents =~ s/($begintag_regex_safe*.*?$endtag_regex_safe[\r]?[\n]?)/$copyrights_plus_delimiters/s ) # not global, only first one...
         {
             print "Replacing the copyright in $filename ...\n";

             #print "old:\n";
             #print $1;

             #print "new:\n";
             #print $copyrights_plus_delimiters;
         }

         elsif ($opt_a)
         {
            print "Adding copyright to $filename ...\n";
            print OUTPUT "$copyrights_plus_delimiters";
         }

         else
         {
            print "$filename: No previous copyright, no replace.\n";
         }

         # put the new file_contents to the output file.
         print OUTPUT $file_contents;

         close(OUTPUT) or warn "WARNING: Could not save changes: $!\n";

         unlink("$filename");
         rename("$filename.new", "$filename");
      }

      close(INPUT);
   }
}

sub checkName ($) {
   my $filename = shift;

   foreach (@extensions)
   {
      return 1 if $filename =~ /\.$_$/;
   }
   return 0;
}

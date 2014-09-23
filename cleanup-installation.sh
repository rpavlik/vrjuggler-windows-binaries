#!/bin/sh
cd $(dirname $0)
find . -name '*.exp' -o -name "vc9.pdb" -exec rm {} \;

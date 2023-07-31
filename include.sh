#!/usr/bin/env bash

## GETS THE CURRENT MODULE ROOT DIRECTORY
MOD_DRUIDBUFF_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_DRUIDBUFF_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_DRUIDBUFF_ROOT"/conf/conf.sh" ]; then
    source $MOD_DRUIDBUFF_ROOT"/conf/conf.sh"
fi
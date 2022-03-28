#!/bin/bash

PATH=$1
PROJ=$2

if [ -z "$PROJ" ]
then
    PROJ="lfc"
fi

echo > include/$PROJ/$PATH.h
echo > src/$PROJ/$PATH.c

#!/bin/bash

# make shure your user is in the uucp group!

avrdude -p t24 -P /dev/ttyACM0 -c stk500v2 -U flash:w:main.hex:a

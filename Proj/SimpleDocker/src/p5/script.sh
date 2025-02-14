#!/bin/bash

gcc -o serv serv.c -lfcgi
spawn-fcgi -p 8080 ./serv
nginx -g "daemon off;"
/bin/bash
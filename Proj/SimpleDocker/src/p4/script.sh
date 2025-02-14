#!/bin/bash

gcc -o serv serv.c -lcfgi
spawn-fcgi -p 8080 ./serv

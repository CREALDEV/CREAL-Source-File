#!/usr/bin/perl


use strict;
use warning; 
use FCGI; 

# FAST CGI BELOW

while (FCGI::accept >= 0) 
{

  printf("Hello!!");  //this is nice right here


}



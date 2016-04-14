#!/usr/bin/perl
use CGI;
my $q = new CGI;
use IO::File;
#get the file name from URL ex. http://<server_IP>/cgi-bin/download.cgi?a=testing.txt
my $file= $q->param(''); 



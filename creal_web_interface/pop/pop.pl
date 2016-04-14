#!/usr/bin/perl

use strict; 
use warnings; 

#~ use FCGI;
#~ use CGI; #NEED THIS FOR PARAM FUNCTIONS
#~ #use JSON; #REGULAR JSON
#~ #use JSON::XS; #XS JSON
#~ use JSON::SL; #SL JSON ~ SUPPOSEDLY FASTER

my $staticCommand0 = "simBinary.bin"; #this is the main binary string
my $selectionVariable = "sel.txt"; #this is the main binary string
my $timeNumber = 3600; # this is the default number we want to work on right here 
my $timeMultiplier = 3600; # this is the default number we want to work on right here 

my $somethingHere; 
my $commandVariable = ""; #this is where the command will be for this stuff





#~ `$commandVariable`; #execute on the bash shell... err korn shell

#~ open(SEL,">",$selectionVariable) or die "could not open the file!"; #if die then its really bad..


#~ print SEL "this"; #I think this will be good right here 


my $count = 0;
#~ my $q = CGI->new; #this is using CGI again
#~ my $json = JSON::SL->new();
#~ my $jpath = "/^/partial";
#~ $json->set_jsonpointer( [$jpath] );

#~ ##The json stuff right here

my $headerAndStarBody = qq(
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Sim</title>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta name="generator" content="Geany 1.26" />
	
	<style>
	
	</style> 
	
</head>
<body>
);



my $bodyEnd = qq(
</body>
</html>
); 

		#~ $q->param("d");

        print("Content-type: text/html\r\n\r\n");
        #~ print "Content-Type:application/x-downloadn";  
        print($headerAndStarBody);
        print("CREAL Simulator <br>\n");
        		
		
        
		print "Content-Disposition:attachment;filename=dw.txt";  
        
     
        
        print($bodyEnd);

#~ my $variable = param('hello'); #I don't know if this works right here 


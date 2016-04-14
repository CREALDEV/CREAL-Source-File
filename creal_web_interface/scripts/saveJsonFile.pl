#!/usr/bin/perl
#This script is used to download json from the server

#created by Randy White 

use strict; 
use warnings; 
my $count = 0;
my $q = CGI->new; #this is using CGI again
my $json = JSON::SL->new();
my $jpath = "/^/partial";
$json->set_jsonpointer( [$jpath] );
my $fileToBeDownloaded = "sharedMem/jsonFile.json"; #this is where the temporary file system should be 
my $paramString = ""; 
use CGI ':standard';  #I think this is what I want to use right here
my @jsonString; #this is the main array to store the json shit from javascript 



		#~ @jsonString = 	$q->param("jsonData");
		
		#~ if(@jsonString)
		#~ {
			#~ open(JSON, ">$fileToBeDownloaded"); 
			
		#~ for(my $i = 0, i < @jsonString, i++)
		#~ {
			#~ print JSON $jsonString[i] . "\n"; #appends file to string..
		#~ } 
			
		#~ close(JSON);

		
		print "Content-Type:application/x-downloadn";  
        
		print "Content-Disposition:attachment;filename=dw.txt";  
        
        

#~ }

	#~ else
	#~ {
	 
	 
	 #~ #this means that there was an error right here 
		
	 
	 #~ }

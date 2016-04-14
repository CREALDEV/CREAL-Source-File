#!/usr/bin/perl
use CGI;
my $q = new CGI;
use IO::File;
#get the file name from URL ex. http://<server_IP>/cgi-bin/download.cgi?a=testing.txt
#~ my $file= $q->param('a'); 


# somewhere earlier in the code I define my filename ...



my $postVariable = $q->param('saveJsonData');

	
	

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

		 my $bool = 0; 
        print("Content-type: text/html\r\n\r\n");
        

        #~ print "Content-Type:application/x-downloadn";  
        print($headerAndStarBody);
        
        open(ERROR, "</tmp/err.txt");
        
      	while(<ERROR>)
			{
					print $_ . "<br>\n"; 
			}
			
	
		print "YOOO !!!";
        close(ERROR);






print($bodyEnd);

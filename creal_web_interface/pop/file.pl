#!/usr/bin/perl
use CGI;
my $q = new CGI;
use IO::File;
#get the file name from URL ex. http://<server_IP>/cgi-bin/download.cgi?a=testing.txt
#~ my $file= $q->param('a'); 


# somewhere earlier in the code I define my filename ...



my $postVariable = $q->param('saveJsonData');

if (!($postVariable eq "NULL"))
{
	
	

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


        print("Content-type: text/html\r\n\r\n");
        #~ print "Content-Type:application/x-downloadn";  
        print($headerAndStarBody);
        #~ print("CREAL Simulator <br>\n");
        #~ open FILE , "/var/www/html/dw.txt" or die "SORRY";
        open(JSON, ">/var/www/html/saveFiles/crealFile.json");
        #~ my $fh = IO::File->new(">/var/www/html/saveFiles/teessst.txt");
        print JSON $postVariable. "\n"; 
        #~ print $fh "jjjjj\n"; 
        close(JSON);
        #~ close($fh);
		
		
		#~ print $yuu . "\n"; 
		print "<a href= '/saveFiles/crealFile.json' download='crealFile.json' id = 'downloader' >";
        print qq(<script>
				var downloadLinkClicker = document.getElementById('downloader');
				downloadLinkClicker.click(); 
				</script>
        ); 
        
		#~ print "Content-Disposition:attachment;filename=dw.txt";  
        
     
        
        print($bodyEnd);


}
else
{
					print("Content-type: text/html\r\n\r\n");
	                print("No data has been passed \n");

}

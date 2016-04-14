
#!/usr/bin/perl
use CGI;
my $q = new CGI;
use IO::File;
#get the file name from URL ex. http://<server_IP>/cgi-bin/download.cgi?a=testing.txt
#~ my $file= $q->param('a'); 


# somewhere earlier in the code I define my filename ...



my $getRunSimData = $q->param('runSimData');

	
	if ($getRunSimData)
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
	
<script>

</script> 

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
		
		print qq|
		
		<header>
		RUN SIM
		</header>
	
<br>
<br>
		<span id="errorPage" style="">
		<iframe name="errorFrame" id="errorFrame" src="checkErrors.pl" width="468" height="300"></iframe>
		</span>	

		<span id="simPage" style="display: none;">
		</span>	

		<span id="graphPage" style="display: none;">
		</span>	
<br>
<br>
<script>window.onload = function(){setInterval(function(){
    parent.frames['errorFrame'].location.href = "checkErrors.pl";
},4000);}
	</script>|;





print($bodyEnd);
}

else
{
	
				print("Content-type: text/html\r\n\r\n");
	            print("No data has been passed \n");

}

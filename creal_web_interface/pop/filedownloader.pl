if ($ID eq '') {  

print "Content-type: text/htmlnn";  

print "You must specify a file to download.";  

} else {



#####



open(DLFILE, "<$files_location/$ID") || Error('open', 'file');  

@fileholder = <DLFILE>;  

close (DLFILE) || Error ('close', 'file');

####



print "Content-Type:application/x-downloadn";   

print "Content-Disposition:attachment;filename=$IDnn";  

print @fileholder  

}



#!/usr/bin/perl -wT  

  

use CGI ':standard';  

use CGI::Carp qw(fatalsToBrowser);   

  

my $files_location;   

my $ID;   

my @fileholder;  

  

$files_location = "/usr50/home/webdata/photos";  

  

$ID = param('ID');  

  

if ($ID eq '') {   

print "Content-type: text/htmlnn";   

print "You must specify a file to download.";   

} else {  

  

open(DLFILE, "<$files_location/$ID") || Error('open', 'file');   

@fileholder = <DLFILE>;   

close (DLFILE) || Error ('close', 'file');   

  

open (LOG, ">>/usr50/home/webdata/public_html/test.log") || Error('open', 'file');  

print LOG "$IDn";  

close (LOG);  

  

print "Content-Type:application/x-downloadn";   

print "Content-Disposition:attachment;filename=$IDnn";  

print @fileholder  

}


<html><head>  

<title>Download Page</title>  

</head>  

<body>  

<form action="/cgi-bin/script.cgi">  

<p>  

  <select size="1" name="ID">  

  <option value="0001.jpg">File One  

  </option>  

  <option value="file.zip">File Two  

  </option>  

</p>  

  </select>  

<input type="submit" value="Submit" name="B1">  

</form>  

</body>  

</html>


###copy file to web accessible area and send a download link

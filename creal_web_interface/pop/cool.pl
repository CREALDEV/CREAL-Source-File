use CGI;
my $html= new CGI;
#get the file name from URL ex. http://<server_IP>/cgi-bin/download.cgi?a=testing.txt
my $file= $html->param('a'); 
# $file is nothing but testing.txt
my $filepath= "/var/www/html/dw.txt";

print ("Content-Type:application/x-download\n");
print "Content-Disposition: attachment; filename=$file\n\n";

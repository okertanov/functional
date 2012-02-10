#!/usr/bin/perl -w

use strict;
use warnings;
use utf8;

use LWP;
use URI;
use Date::Format;

use DBI;

use XML::XPath;
use XML::XPath::XMLParser;

use Net::Twitter::Lite;

sub trim($);

binmode STDOUT, ":utf8";

my $url = "http://www.seb.lv/en/private/services/currency/rates/curency/";
my $regexp = qr(tyle="padding-top: 10px;" valign="top">.*<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\">(.*?)<\/table>);

my $ua = LWP::UserAgent->new;
$ua->agent('Mozilla/5.0');

my $response = $ua->get( $url );
die "Can't get $url -- ", $response->status_line unless $response->is_success;
die "Expecting HTML, not ", $response->content_type unless $response->content_type eq 'text/html';

###temporary file op
#open(FILE, "testpage.html") or die("Unable to open file");
#undef $/;
#my $content = <FILE>;
#close(FILE);
###

my $content = $response->content;

### xml compat fixes
$content =~ s/\x0D//g;
$content =~ s/\x0A//g;
if ( $content =~ /$regexp/g )
{
    $content ="<root>".$1."</root>";
}
else
{
    die "Table not found.";
}
###

my $parser = XML::XPath::XMLParser->new(xml => $content);
my $root_node = $parser->parse;
my $xp = XML::XPath->new(context => $root_node);

my $nodeset = $xp->find('/*/tr/td[(@class="odd" or @class="even") and (contains(.,"EUR") or contains(.,"SEK") or contains(.,"USD") or contains(.,"GBP"))]'); 

my %dataHash = ();

foreach my $node ($nodeset->get_nodelist)
{
    my $currNode = trim($xp->getNodeText($node));
    $currNode =~ s/\(.*\)//;
    $currNode = trim($currNode);
    #print($currNode, "\n");

    my @dataArray = ();

    my $sibling = $xp->find('following-sibling::*', $node);

    foreach my $snode ($sibling->get_nodelist)
    {
        my $urlnode = $xp->find('img/@src', $snode);
        if ( $urlnode )
        {
            my $urlText  = trim($xp->getNodeText($urlnode));
            $urlText =~ s/^.*\///; $urlText =~ s/\..*$//; $urlText =~ s/\d+//g;
            $urlText =~ s/up/^/; $urlText =~ s/down/v/; $urlText =~ s/right/>/;
            push(@dataArray, $urlText);
            #print("\t", $urlText, "\n");
        }
        else
        {
            my $nodeText = trim($xp->getNodeText($snode));
            push(@dataArray, $nodeText);
            #print("\t", $nodeText, "\n");
        }
    }

    $dataHash{$currNode} = \@dataArray;
}

### Format
my @lt = localtime(time);
my $currDateTime = strftime("%d %b %Y %R LVL: ", @lt);
my $postStr = "$currDateTime ";
foreach my $curr (keys %dataHash)
{
    my $lineStr = "";
    my $e0 = ${$dataHash{$curr}}[0];
    my $e1 = ${$dataHash{$curr}}[1];
    my $e2 = ${$dataHash{$curr}}[2];
    my $s0 = ${$dataHash{$curr}}[3];

    $lineStr = sprintf("%s %s %.4f/%.4f/%.4f  ", $curr, $s0, $e0, $e1, $e2);
    $postStr = $postStr.$lineStr;
}

print "$postStr \n";

### Twitt it
#my $twit = Net::Twitter::Lite->new( username=>"twilats", password=>"Mkdir12345",
#                                    clientname=>"robot", clientver=>"1.0",
#                                    clienturl=>"http://twilats.espectrale.com/");
#my $result = $twit->update($postStr);

### Store into MySQL
my $sql_values = "STR_TO_DATE(\"$currDateTime\",\"%d %b %Y %T\"),".
                 "$dataHash{EUR}[0], $dataHash{EUR}[1], $dataHash{EUR}[2], ".
                 "$dataHash{SEK}[0], $dataHash{SEK}[1], $dataHash{SEK}[2], ".
                 "$dataHash{USD}[0], $dataHash{USD}[1], $dataHash{USD}[2], ".
                 "$dataHash{GBP}[0], $dataHash{GBP}[1], $dataHash{GBP}[2]";

my $dbh = DBI->connect('DBI:mysql:twilats', 'twilats', 'SecurePassword') || die "Could not connect to database: $DBI::errstr";
$dbh->do("insert into rates (date, eur1, eur2, eur3, sek1, sek2, sek3, usd1, usd2, usd3, gbp1, gbp2, gbp3) values ($sql_values)") ||
                die "Could not execute SQL. Error: $DBI::errstr";
$dbh->disconnect();

### Functions
sub trim($)
{
    my $string = shift;
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}


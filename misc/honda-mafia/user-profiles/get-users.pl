#!/usr/bin/perl -w

use strict;
use LWP;
use URI;
use IO::File;
use XML::Writer(DATA_MODE => 'true', DATA_INDENT => 2);
use Text::Iconv;

my $regexp = qr(
\s*<td class="td1" align="center"><span class="gen">&nbsp;(.*)&nbsp;</span></td>.*
\s*<td class="td1" align="center"><a href="(.*)" class="nav">(.*)</a></td>.*
\s*<td class="td1" align="center" valign="middle"><span class="gen">(.*)</span></td>);

my $regexp_a = qr(<td class="td1" height="150" valign="top" align="center"><img src="(.*)" alt="" border="0" /><br />);

my $out_file_name = "users.html";
my $out_page_title = "Site Users Map";

my $m_base = "http://honda.org.ua/";
my $m_url = "http://honda.org.ua/forum/memberlist.php";
my $m_enum_url = "http://honda.org.ua/forum/memberlist.php?mode=joined&order=ASC&start=";
#my @m_interval = (57..57);
my @m_interval = (0..170);

my $ua = LWP::UserAgent->new;
$ua->agent('Mozilla/5.0');

my $cv = Text::Iconv->new("cp1251", "utf-8");

my $xml_output = new IO::File(">$out_file_name");
my $wr = new XML::Writer( OUTPUT => $xml_output );

$wr->xmlDecl( 'UTF-8' );
$wr->doctype( 'html' );
$wr->comment( "$out_page_title" );
$wr->startTag( 'html' );

    $wr->startTag( 'head' );
        $wr->startTag( 'link', 'rel'=>'icon', 'href'=>'/favicon.ico', 'type'=>'image/x-icon' );
        $wr->endTag(); #link-icon
        $wr->startTag( 'link', 'rel'=>'stylesheet', 'media'=>'screen', 'href'=>'style.css', 'type'=>'text/css' );
        $wr->endTag(); #link-style

        $wr->startTag( 'title' );
            $wr->characters( "$out_page_title" );
        $wr->endTag(); #title
    $wr->endTag(); #head

    $wr->startTag( 'body' );
        &process();
    $wr->endTag(); #body
$wr->endTag(); #html

sub process
{
    $wr->startTag( 'div', 'name' => 'users' );

    foreach my $page (@m_interval)
    {
        my $pref = $page * 40;
        my $url = $m_enum_url.$pref;
        print "\nProcessing page $page from $url\n";

        my $response = $ua->get( $url );
        die "Can't get $url -- ", $response->status_line unless $response->is_success;
        die "Expecting HTML, not ", $response->content_type unless $response->content_type eq 'text/html';

        my $content = $response->content;
        chomp $content;
        my $un_content = $cv->convert($content);

        my @ma =$un_content =~ /$regexp/g;
        my $matches_count = @ma;

        print "Done with page $page. Matches: $matches_count\n";

        for (my $i = 0; $i < $matches_count;)
        {
            my ($id, $profile, $name, $place) = ($ma[$i++], URI->new_abs( $ma[$i++], $response->base ), $ma[$i++], $ma[$i++]);

            print "Getting profile for $id - $name from $profile\n";

            my $response_p = $ua->get( $profile );
            die "Can't get $url -- ", $response_p->status_line unless $response_p->is_success;

            my $content_p = $response_p->content;
            chomp $content_p;

            if( $content_p =~ /$regexp_a/ )
            {
                my $img_a = URI->new_abs($1, $response_p->base);
                $wr->startTag( 'a', 'href' => "$profile" );
                    $wr->startTag( 'img', 'src'=>"$img_a", 'alt'=>"$name", 'title'=>"$name", 'border'=>'0');
                    $wr->endTag(); #img-src
                $wr->endTag(); #a-href
            }

            print "Done\n";
        }
    }

    $wr->endTag(); #div-users
}


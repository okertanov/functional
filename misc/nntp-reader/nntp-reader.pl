#!/usr/bin/perl -w

use utf8;
use strict;
use warnings;
use Net::NNTP;
use MIME::Words qw(:all);
use Text::Iconv;

use Encode;
require Encode::Detect;

###################################################################
my $server = "news.ntu-kpi.kiev.ua";
my $group  = "kyivstar.test";
my $g_from_rx = q/.*(Xyz)|(Qazw)|(Lola)|(Lala)|(<nospam@spam.com>)|(xyz@xyz.ru)|(xyz@zzz.net).*/;
my $g_host_rx = "10.20.35.11";

###################################################################
my $new_msg_string = <<MSG;
    ...
    ...
    ...
MSG

###################################################################
binmode STDOUT, ":utf8";

###################################################################
my $converter = Text::Iconv->new("UTF-8","KOI8-R//IGNORE");
Text::Iconv->raise_error(0);
my $new_msg_koi8_string = $converter->convert($new_msg_string);

###################################################################
#create a nntp object
my $nntp = Net::NNTP->new($server) or die "Can't connect to $server";

my $prev_last_art = 0;

while (1)
{
    my ($arts_count, $first_art, $last_art, $grp_name) =
        $nntp->group($group) or warn "Can't select the group $group";
    print localtime().": Received from $grp_name: $arts_count. First: $first_art, Last: $last_art \n";

    if ($prev_last_art == 0)
    {
        $prev_last_art = $last_art;
    }

    my $art = $prev_last_art;

    while ($art <= $last_art)
    {
        my $hdr_ref = $nntp->head($art);
        if ( !$hdr_ref )
        {
            warn "Can't get head($art)! Server says: ".$nntp->message."\n";
            $art++; #skip errorous
            last;
        }

        my @hdr_arr = @{$hdr_ref};

        #normalize header
        my @hdr_norm_arr = ();
        my $real_subj = "";
        my $index = 0;
        my $msindex = 0;
        my $msfound = 0;
        foreach (@hdr_arr)
        {
            my $item = $_;
            if ( $item =~ /^Subject: .*$/ )
            {
                chomp $item;
                $real_subj = $item;
                $msindex = $index;
            }
            if ( $item =~ /^\s=.*$/ )
            {
                chomp $item;
                $real_subj .= $item;
                splice @hdr_arr, $index, 1;
                $msfound = 1;
            }
            $index++;
        }

        if ( $msfound )
        {
            $hdr_arr[$msindex] = $real_subj;
        }

        #parse header
        my %hdr_map = map /^(\S[^:]+):\s(.*)$/g, @hdr_arr;

        my $decoded_from = decode_mimewords($hdr_map{'From'});
        my $decoded_subj = decode_mimewords($hdr_map{'Subject'});

        my $utf_from = decode("Detect", $decoded_from);
        my $utf_subj = decode("Detect", $decoded_subj);

        my $msg_id = $hdr_map{'Message-ID'} || "";
        my $msg_refs = $hdr_map{'References'} || "";

        my $is_autogen =  $hdr_map{'X-Auto-Generated'} || 'no';
        my $posting_host = $hdr_map{'NNTP-Posting-Host'} || '';

        if ( ($utf_from =~ /$g_from_rx/ || $posting_host eq $g_host_rx) && $is_autogen ne 'yes' )
        {
            print "---------------------------------"."\n";
            print "Article: $art \n";
            print "Posting Date: $hdr_map{'Date'} \n";
            print "NNTP Posting Date: $hdr_map{'NNTP-Posting-Date'} \n";
            print "From: ".($utf_from)." \n";
            print "Subject: ".($utf_subj)." \n";
            print "---------------------------------"."\n";

            #my @body_arr = @{$nntp->body($art)};
            #my $body_str = join("", @body_arr);
            #my $utf_body_str = decode("Detect", $body_str);
            #print $utf_body_str;

            #post reply
            my @new_body_arr = split('/$/', $new_msg_koi8_string);

            #modify header
            #$hdr_map{'References'} = "$msg_id $msg_refs";
            $hdr_map{'References'} = "$msg_id";
            $hdr_map{'In-Reply-To'} = $msg_id;
            $hdr_map{'Lines'} = scalar @new_body_arr;
            $hdr_map{'Message-ID'} = "";
            $hdr_map{'Xref'} = "";
            $hdr_map{'NNTP-Posting-Host'} = "";
            $hdr_map{'NNTP-Posting-Date'} = "";
            $hdr_map{'X-Trace'} = "";
            $hdr_map{'X-Complaints-To'} = "";
            $hdr_map{'X-Auto-Generated'} = "yes";

            #enforce koi8-r encoding
            $hdr_map{'Content-Type'} = 'text/plain; charset=KOI8-R; format=flowed';
            $hdr_map{'Content-Transfer-Encoding'} = '8bit';

            my @post_hdr_arr = ();
            for my $key ( keys %hdr_map )
            {
                my $value = $hdr_map{$key};
                if ( length($value) )
                {
                    push @post_hdr_arr, "$key: $value\n";
                }
            }
            push @post_hdr_arr, "\n";

            my @post_complete = (@post_hdr_arr, @new_body_arr);

            if ( $nntp->postok() )
            {
                if (1) #$nntp->post(@post_complete)
                {
                    print "Message has been posted OK.\n"
                }
                else
                {
                    warn "Can't post a message! Server says: ".$nntp->message."\n";
                }
            }
            else
            {
                warn "Posting is disabled!\n";
            }
        }
        else
        {
            print "--------------------\n";
            print "Article: $art       \n";
            print "From:    $utf_from  \n";
            print "Subject: $utf_subj. \n";
            print "--------------------\n";
        }

        $art++;
    }

    $prev_last_art = $art;

    print "Waiting...\n";
    sleep(60);
}

$nntp->quit;

1;

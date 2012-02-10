#!/usr/bin/perl -w

sub traverse_dir($);
sub parse_content($);
sub process_file($);

#	Имя	Откуда	Зарегистрирован	Последний визит	День Рождения	Возраст	Сообщения	Карма
#
#	  <td class="td1" align="center"><span class="gen">&nbsp;1&nbsp;</span></td>
#	  <td class="td1" align="center"><a href="/forum/user/mazy" class="nav">mazy</a></td>
#	  <td class="td1" align="center" valign="middle"><span class="gen">котоубежище</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gensmall">14.07.2004</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gensmall">07.11.2008</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gensmall">не указан</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gensmall">-</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gen">6301</span></td>
#	  <td class="td1" align="center" valign="middle"><span class="gen">30</span></td>

#	  <td class="td1" align="center"><span class="gen">&nbsp;132&nbsp;<img src="templates/Pixelated/images/icon_rcard.gif" border=0 alt="Пользователь забанен by Мыш on &nbsp;26.03.2008"></span></td>


$user_info_regexp = '\s*<td class="td1" align="center"><span class="gen">&nbsp;(\d+)&nbsp;.*</span></td>\s*
\s*<td class="td1" align="center"><a href=".*" class="nav">(.*)</a></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gen">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gensmall">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gensmall">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gensmall">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gensmall">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gen">(.*)</span></td>\s*
\s*<td class="td1" align="center" valign="middle"><span class="gen">(.*)</span></td>\s*';

sub parse_content($)
{
    local ($content) = @_;

    my @re_matches;

    if ( @re_matches = $content =~ m/$user_info_regexp/g )
    {
        my $matches_size = scalar @re_matches;

        if ( $matches_size != 0 )
        {
            my $records_count = $matches_size;
            my $current_count = 0;

            while ( $current_count < $records_count )
            {
                #Obtain
                my ($u_id, $u_nick, $u_from, $u_registered, $u_visit, $u_birthday, $u_age, $u_messages, $u_karma) =
                   (   $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++],
                       $re_matches[$current_count++]  );

                #Normalize
                $u_from =~ s/&nbsp;/-/;
                $u_birthday =~ s/не указан/-/;

                #Output
                print("$u_nick | $u_from | $u_registered | $u_visit | $u_birthday | $u_age | $u_messages | $u_karma\n");
            }
        }
    }
    else
    {
        die("\nFAILED!\n");
    }
}

#	<th class="td3" colspan="3" nowrap="nowrap">Профиль пользователя mazy</th>
#...
#		  <td valign="top" nowrap="nowrap" align="right"><span class="gen">Автомобиль:</span></td>
#		  <td> <b><span class="gen"><FONT COLOR=#CC0000>СR-V RD8 / Civic FD1</FONT></span></b></td>

$user_profile_regexp = '\s*<th class="td3" colspan="3" nowrap="nowrap">Профиль пользователя (.*)</th>\s*.*\s*<td valign="top" nowrap="nowrap" align="right"><span class="gen">Автомобиль:</span></td>\s*<td> <b><span class="gen"><FONT COLOR=#CC0000>(.*)</FONT></span></b></td>\s*';

sub parse_content_user($)
{
    local ($content) = @_;

    #Pre-normalize
    $content =~ s/$//g;
    $content =~ s/\x0A//g;
    $content =~ s/\x0D//g;

    my @re_matches;

    if ( @re_matches = $content =~ m/$user_profile_regexp/ )
    {
        print ("$1 | $2\n");
    }
    else
    {
        die("\nFAILED!\n");
    }
}

sub process_file($)
{
    local ($fullpath) = @_;

    open F, "< $fullpath" or die "Can't open $fullpath : $!";
    my @file_data = <F>;
    close F;

    my $file_string = join("", @file_data);

    #print(">>> Processing: $fullpath\n");
    &parse_content($file_string);
}

sub process_user_file($)
{
    local ($fullpath) = @_;

    open F, "< $fullpath" or die "Can't open $fullpath : $!";
    my @file_data = <F>;
    close F;

    my $file_string = join("", @file_data);

    #print(">>> Processing: $fullpath\n");
    &parse_content_user($file_string);
}

sub traverse_dir($)
{

    local ($path) = @_;
    local (@dir, $entry, $fullpath);

    opendir (DIR, $path);
    @dir = readdir(DIR);  # get list of current directory
    closedir (DIR);

    foreach $entry (sort @dir)
    {
        if ($entry eq '.' or $entry eq '..')
        {
            next;
        }

        $fullpath = "$path\\$entry";

        if (-d $fullpath)
        {
            traverse_dir($fullpath);  # recursive directory listing
        }
        else
        {
            if ( $fullpath =~ m/memberlist-(\d+).html/)
            {
                &process_file($fullpath);
            }
            #else
            #if ( $fullpath =~ m/user-(\d+).html/)
            #{
            #    &process_user_file($fullpath);
            #}
        }
    }
}

$startpath = shift;
$startpath = '.' unless $startpath;

&traverse_dir($startpath);

1;

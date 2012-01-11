#!perl -w

use strict;
use Encode qw/encode decode/; 

my @latexArray = ();
my ($g_Section, $g_SubSection, $g_Question, $g_Answer) = 
	("default", "default", "default", "default", 0, 0);

my ($g_CountTopic, $g_CountTotal) = (0, 0);

my ($paramfilein, $paramfileout, $paramfiletemplate);
$paramfilein = $ARGV[0];
$paramfileout = $ARGV[1];
$paramfiletemplate = $ARGV[2];
#@ARGV || die "Ussage: \n\tscript.pl filein fileout filetemplate\n";

print "\n$paramfilein, $paramfileout, $paramfiletemplate\n";

sub propagateVariable($$)
{
	my($level, $value) = @_;
	if($level eq 0)
	{
		$g_Section = $value;
	}
	elsif($level eq 1)
	{
		$g_SubSection = $value;
	}
	elsif($level eq 2)
	{
		$g_Question = $value;
	}
	elsif($level eq 3)
	{
		$g_Answer = $value;
	}
	else
	{
		#exception
		die;
	}
}

sub initializeParser($)
{
	my $fname = $_[0];
	my @p = ();
	open(LF, "<$fname") or die ">>>ERROR: can't open file $fname\n";
	print "Start Loading...\n";
	while(<LF>)
	{
		my $line = $_;
		chomp $line;
		push @p, ($line);
		print "."
	}
	close(LF);
	print "Loading was done\n";
	return @p;
}

sub parseSections($$$$$)
{
	my ($iter, $sectname, $limitto, $cb, $level) = @_;
	for (;$iter<=$#latexArray; $iter++)
	{
		my $item = $latexArray[$iter];
		if($item =~ /\\$limitto/)
		{
			return 0;			
		}
		if ($item =~ /\\$sectname/)
		{
			my $section = $latexArray[$iter++];
			#FIXME!!! Basic beauty here
			chomp $section;
			$section =~ s/\\$sectname//i; 	#removes section name
			$section =~ s/^\{(.*)\}$/$1/;

			#EXCEPTION: go deeper to check for the verbatim section
			my $verb = "";
			if($latexArray[$iter] eq "\\begin{verbatim}")
			{
				my $liter = $iter+1;
				do
				{
					$verb = $verb.$latexArray[$liter++]."&#10;";
				}
				until($latexArray[$liter] eq "\\end{verbatim}");
			}
			if ($verb)
			{
				$verb = "&#10;"."<B>".$verb."</B>";
			}
			
			#callback invocation
			&$cb($level, $section.$verb);

			#return current position back
			return $iter;
		}
	}
	return 0;
}

my $cbDumpSection = sub
{
	my($level, $section) = @_;
	&propagateVariable($level, $section);
	print " " x (($level)*4), $section, "\n";
};

sub initStreams($$)
{
	my($from, $to) = @_;
	open(SRC, "< $from") or die "Couldn't open $from for reading: $!\n";
	open(DST, "> $to")   or die "Couldn't open $to for writing: $!\n";
	binmode(SRC, ':utf8');
	binmode(DST, ':utf8' );
	return(*SRC, *DST);
}

sub deInitStreams($$)
{
	my($hfrom, $hto) = @_;
	close($hfrom) or die "Couldn't close $hfrom: $!\n";
	close($hto)   or die "Couldn't close $hto: $!\n";
}

sub writeHeader($$)
{
	my($hfrom, $hto) = @_;
	while(<$hfrom>)
	{
		print $hto $_;
		last if($_ =~ /<!-- BOI -->/);
	}
}

sub writeFooter($$)
{
	my($hfrom, $hto) = @_;
	my $allow = 0;
	while(<$hfrom>)
	{
		$allow = 1 if($_ =~ /<!-- EOI -->/);
		print $hto $_ if ($allow);
	}
}

#   <Row ss:AutoFitHeight="0" ss:Height="102">
#    <Cell ss:StyleID="s21"><Data ss:Type="String">C++</Data></Cell>
#    <Cell ss:StyleID="s25"/>
#    <Cell ss:Index="6" ss:StyleID="s26"><ss:Data ss:Type="String"
#      xmlns="http://www.w3.org/TR/REC-html40">How to get <B>char*</B><Font> pointer from an existing </Font><B>std::string</B><Font>? For example having string </Font><B>str</B><Font>?</Font></ss:Data></Cell>
#    <Cell ss:StyleID="s27"><ss:Data ss:Type="String"
#      xmlns="http://www.w3.org/TR/REC-html40">1. <B>char* ptr = str.c_str();</B><Font>&#10;2.</Font><B> char* ptr = str.get_string();</B><Font>&#10;3. </Font><B>char* ptr = str.to_string();</B><Font>&#10;4. </Font><B>char* ptr = str.CString();</B><Font>&#10;5. </Font><B>char* ptr;&#10; str.GetCString(ptr);</B><Font>&#10;6. </Font><B>char* ptr;&#10;str.bufferize(ptr);</B></ss:Data></Cell>
#    <Cell ss:StyleID="s28"><Data ss:Type="Number">1</Data></Cell>
#    <Cell><Data ss:Type="String">Oleg Kertanov</Data></Cell>
#    <Cell><Data ss:Type="String">SINGLE</Data></Cell>
#   </Row>
my $rowTemplate = <<EOT;
   <Row ss:AutoFitHeight="1">
    <Cell ss:StyleID="s21"><Data ss:Type="String">C++ Standard Template Library</Data></Cell>
    <Cell ss:StyleID="s21"><Data ss:Type="String">!C0</Data></Cell>
    <Cell ss:StyleID="s25"><Data ss:Type="String">!C1</Data></Cell>
    <Cell ss:Index="6" ss:StyleID="s26"><ss:Data ss:Type="String"
      xmlns="http://www.w3.org/TR/REC-html40"><pre>!C2</pre></ss:Data></Cell>
    <Cell ss:StyleID="s27"><ss:Data ss:Type="String"
      xmlns="http://www.w3.org/TR/REC-html40"><pre>!C3</pre></ss:Data></Cell>
    <Cell ss:StyleID="s28"><Data ss:Type="String">!C4</Data></Cell>
    <Cell><Data ss:Type="String">Oleg Kertanov</Data></Cell>
    <Cell><Data ss:Type="String">!C5</Data></Cell>
   </Row>
EOT

my $groupTemplate = <<EOG;
EOG

my $totalTemplate = <<EOG;
<Row>
    <Cell ss:StyleID="s21"><Data ss:Type="String">C++ Standard Template Library</Data></Cell>
    <Cell ss:StyleID="s29"><Data ss:Type="String">TOTAL STL</Data></Cell>
    <Cell ss:StyleID="s29" ss:Index="4"><Data ss:Type="Number">!C0</Data></Cell>
    <Cell ss:Index="6" ss:StyleID="s25"/>
    <Cell ss:StyleID="s27"/>
    <Cell ss:StyleID="s24"/>
   </Row>
EOG

sub writeItemEntry($$$$$)
{
	my($fh, $r0, $r1, $r2, $r3) = @_;
	my($r4, $r5) = ("", "");
	my $currentRecord = $rowTemplate;

	#underscores
	$r1 =~ s/\\_/_/gi;
	$r2 =~ s/\\_/_/gi;
	$r3 =~ s/\\_/_/gi;
	
	#linebreaks
	$r1 =~ s/\\\\/\n/gi;
	$r2 =~ s/\\\\/\n/gi;
	$r3 =~ s/\\\\/\n/gi;

	#amps
	$r1 =~ s/\\{0,1}&(?!#)/&amp;/gi;
	$r2 =~ s/\\{0,1}&(?!#)/&amp;/gi;
	$r3 =~ s/\\{0,1}&(?!#)/&amp;/gi;

	#diezeses
	$r1 =~ s/\\#/#/gi;
	$r2 =~ s/\\#/#/gi;
	$r3 =~ s/\\#/#/gi;
	
	#<>
	$r1 =~ s/</&lt;/gi;
	$r1 =~ s/>/&gt;/gi;
	$r1 =~ s/\\llll/&lt;/gi;
	$r1 =~ s/\\rrrr/&gt;/gi;
	
	$r2 =~ s/<(?!(b|\/b)>)/&lt;/gi;
	$r2 =~ s/(!<(b|\/b))>/&gt;/gi;
	$r2 =~ s/\\llll/&lt;/gi;
	$r2 =~ s/\\rrrr/&gt;/gi;
	
	$r3 =~ s/</&lt;/gi;
	$r3 =~ s/>/&gt;/gi;
	$r3 =~ s/\\llll/&lt;/gi;
	$r3 =~ s/\\rrrr/&gt;/gi;
	
	#Type and correct answers
	if($r3 =~ m/\s*\w+\.\s*\[\\(rad|rax)\]/)
	{
		$r5 = 'SINGLE';
		$r3 =~ m/\s*(\w+)\.\s*\[\\rax\]/;
		$r4 = $1;
	}
	elsif($r3 =~ m/\s*\d+\.\s*\[\\(chk|chx)\]/)
	{
		$r5 = 'MULTIPLE';
		while($r3 =~ m/\s*(\d+)\.\s*\[\\chx\]/g)
		{
			if ($r4 eq '')
			{
				$r4 = $1;
			}
			else
			{
				$r4 = $r4.", ".$1;
			}
		}
	}
	elsif($r3 =~ m/\s*\w+\.\s*\[\\(edt)\]/)
	{
		$r5 = 'EDIT';
		$r3 =~ m/\\framebox\[3in\]\{(.*)\}/;
		$r4 = $1;
		$r3 = ''; #empty it for edit type
	}
	$r3 =~ s/\[\\rad\]|\[\\rax\]|\[\\chk\]|\[\\chx\]|\[\\edt\]//gi; 	#rad/rax/chk/chx/edt
	
	$currentRecord =~ s/!C0/$r0/; #Section
	$currentRecord =~ s/!C1/$r1/; #SubSection
	$currentRecord =~ s/!C2/$r2/; #Question
	$currentRecord =~ s/!C3/$r3/; #Answer
	$currentRecord =~ s/!C4/$r4/; #Correct
	$currentRecord =~ s/!C5/$r5/; #Type
	print $fh $currentRecord;
}

sub writeGroupEntry($$$$$)
{
	my($fh, $sect, $subsect, $num) = @_;
	#empty on additiaonal
	my $currentRecord = $groupTemplate;

	#$currentRecord =~ s/!C0/$r0/; #Section
	#$currentRecord =~ s/!C1/$r1/; #SubSection
	#$currentRecord =~ s/!C2/$r2/; #Number of the questions in the group
	#print $fh $currentRecord;
}

sub writeTotalEntry($$)
{
	my($fh, $num) = @_;
	#empty on additiaonal
	my $currentRecord = $totalTemplate;

	$currentRecord =~ s/!C0/$num/; #num of questions
	print $fh $currentRecord;
}

sub writeEntry($$$$$)
{
	my($fh, $r0, $r1, $r2, $r3) = @_;
	if (not defined $r1 or $r1 eq "")
	{
		&writeTotalEntry($fh, $r0);		
	}
	elsif(($r2 eq "") or ($r3 eq ""))
	{
		&writeGroupEntry($fh, $r0, $r1);
	}
	else
	{
		&writeItemEntry($fh, $r0, $r1, $r2, $r3);
	}
}

my($HSRC, $HDST) = initStreams("$paramfiletemplate", "$paramfileout");
&writeHeader($HSRC, $HDST);
@latexArray = initializeParser("$paramfilein");
my $isect = 0;
while(  $isect = parseSections($isect, "section", "end{document}", $cbDumpSection, 0) )
{
	my $isect2 = $isect;
	while(  $isect2 = parseSections($isect2, "subsection", "section", $cbDumpSection, 1) )
	{
		$g_CountTopic = 0;
		my $isect3 = $isect2;
		while(  $isect3 = parseSections($isect3, "textbf", "subsection", $cbDumpSection, 2) )
		{
			#increment globals
			$g_CountTotal++;
			$g_CountTopic++;
			#locals
			my $isect4 = $isect3;
			my $qCounter = 0;
			my $aAnswer = ""; #accumulate answers to put in a single cell
			while( $isect4 = parseSections($isect4, "item", "textbf", $cbDumpSection, 3) )
			{
				$qCounter++;
				$aAnswer = $aAnswer."$qCounter. ".$g_Answer."&#10;";
			}
			&writeEntry($HDST, $g_Section, $g_SubSection, $g_Question, $aAnswer);
		}
	}
}
&writeEntry($HDST, $g_CountTotal);
&writeFooter($HSRC, $HDST);
&deInitStreams($HSRC, $HDST);
#Finalize
print "\nStatistic: $g_CountTotal\n";

#here we are going to implement new features.
#Just for the CVS training.



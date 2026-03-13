# A fun scripty gubbins to convert a shader SPDL from using
# the old Phenomenon section to the new MetaShader section.

# I'm sure that there is a more pretty way of coding this.

use strict;
use warnings qw( all );
use File::Basename;

sub convertShaderSPDL
{
	my( $filePathIn, $filePathOut ) = @_;
	
	open( my $spdlFileIn, $filePathIn ) || die "Cannot open $filePathIn for input: $!\n";
	open( my $spdlFileOut, ">$filePathOut" ) || die "Cannot open $filePathOut for output: $!\n";
	
	print "Converting " . basename( $filePathIn ) . " ";
	
	my $rtTest = 0;
	my $rtDLL = '';
	my $rtSymbol = '';
	
	my $phen = 0;
	my $phenText = '';
	my $spacing = '';
	
	my @rePhenoTree;
	my %reOptions;
	my $reUsage = '';
	my $reName = '';
	
	while( my $line = <$spdlFileIn> )
	{
		# Test for realtime shader. It should have an output type of rtrendercontext.
		$rtTest = 2 if( $line =~ /^\s*[Tt]ype\s*=\s*[Rr][Tt][Rr]ender[Cc]ontext/ && $rtTest == 1 );
		$rtTest = 1 if( $line =~ /^\s*[Pp]arameter.*output/ );
		$rtTest = -1 if( $line =~ /^\s*[Pp]arameter.*input/ && $rtTest == 1 );
		if( $line =~ /^\s*[Pp]arameter\s+("\S+")\s+input/ && ( $rtTest == 2 || $rtTest == 3 ) )
		{
			$rtDLL = $1 if( $rtTest == 2  );
			$rtSymbol = $1 if( $rtTest == 3  );
			$rtTest++;
		}
		
		# Test for phenomenon
		$phen = 1 if( $line =~ /^(\s*)[Pp]henomenon\s+\"(.+)\"\s*(\{?)\s*$/ );
		
		if( !$phen )
		{
			print $spdlFileOut $line;
			next;
		}
		
		if( $phen == 1 )
		{
			$spacing = $1;
			
			print $spdlFileOut $spacing . "MetaShader \"$2\"\n";
			print $spdlFileOut $spacing . "{\n";
			
			$phen = ($3 ne '' )?3:2;
			next;
		}
		
		if( $phen == 2 && $line =~ /^\s*\{\s*$/ )
		{
			$phen = 3;
			next;
		}
		
		if( $phen == 3 || $phen == 4 )
		{
			$line =~ s/^\s*//;
			$line =~ s/\s*$//;
			
			( $reUsage = $1, $phen = 3, next ) 							if( $line =~ /^[Uu]se\s*=\s*(.*);$/ );
			( $reName = $1, $phen = 3, next ) 							if( $line =~ /^[Nn]ame\s*=\s*(.*);$/ );
			( $reOptions{ 'scanline' } = lc($1), $phen = 3, next ) 			if( $line =~ /^[Ss]canline\s*=\s*(.*);$/ );
			( $reOptions{ 'trace' } = lc($1), $phen = 3, next ) 			if( $line =~ /^[Tt]race\s*=\s*(.*);$/ );
			( $reOptions{ 'shadow' } = "\"segment\"", $phen = 3, next )	if( $line =~ /^[Ss]hadow\s*=\s*[Ss]egment\s*;$/ );
			( $reOptions{ 'shadow' } = "\"sort\"", $phen = 3, next )	if( $line =~ /^[Ss]hadow\s*=\s*[Ss]ort\s*;$/ );
			( $reOptions{ 'shadow' } = $1, $phen = 3, next ) 			if( $line =~ /^[Ss]hadow\s*=\s*(.*);$/ );
			( $reOptions{ 'shadow' } = $1, $phen = 3, next ) 			if( $line =~ /^[Ss]hadow\s*=\s*(.*);$/ );
			( $reOptions{ 'face' } = "\"$1\"", $phen = 3, next ) 		if( $line =~ /^[Ff]ace\s*=\s*(.*);$/ );
			( $reOptions{ 'autovolume' } = lc( $1 ), $phen = 3, next ) 		if( $line =~ /^[Ss]mart\s+[Vv]olume\s*=\s*(.*);$/ );
			( $reOptions{ 'framebuffers' } = lc( $1 ), $phen = 3, next ) 		if( $line =~ /^[Oo]utput\s+[Oo]ptions\s*=\s*(.*);$/ );
			( $reOptions{ 'version' } = $1, $phen = 3, next ) 			if( $line =~ /^[Vv]ersion\s*=\s*(.*);$/ );
			if( $line =~ /^[Dd]erivative\s*=\s*(\d+)\s+(\d+);$/ )
			{ 
				$reOptions{ 'derivative1' } = "on" if( $1 != 0 );
				$reOptions{ 'derivative2' } = "on" if( $2 != 0 );
				$phen = 3; 
				next;
			}
			
			( push( @rePhenoTree, "Connection" . $1 ), $phen = 4, next ) if( $line =~ /^[Cc]onnection(.*)$/ );
			( push( @rePhenoTree, "Node" . $1 ), $phen = 4, next ) if( $line =~ /^[Nn]ode(.*)$/ );
			
			# Copy any empty line spillage if we're in pheno tree collection mode
			( push( @rePhenoTree, $line ), next ) 			if( $line =~ /^#/ );
			( push( @rePhenoTree, '' ), next ) 			if( $line eq '' );
			
			
			if( $line =~ /^\s*\}\s*$/ )
			{
				# Transform and spit out usage types
				print $spdlFileOut $spacing . "\tName = $reName;\n" if( $reName ne '' );
				print $spdlFileOut $spacing . "\tType = $reUsage;\n" if( $reUsage ne '' );
				
				if( $rtSymbol ne '' && $rtDLL ne '' )
				{
					print "as realtime shader.\n";
					print $spdlFileOut $spacing . "\tRenderer \"realtime\"\n";
					print $spdlFileOut $spacing . "\t{\n";
					print $spdlFileOut $spacing . "\t\tName = $rtSymbol;\n";
					print $spdlFileOut $spacing . "\t\tFileName = $rtDLL;\n";
					print $spdlFileOut $spacing . "\t}\n";
				}
				else
				{
					print "as mental ray shader.\n";
					print $spdlFileOut $spacing . "\tRenderer \"mental ray\"\n";
					print $spdlFileOut $spacing . "\t{\n";
					print $spdlFileOut $spacing . "\t\tName = $reName;\n" if( $reName ne '' );
					
					# Spit out options
					if( keys %reOptions != 0 )
					{
						print $spdlFileOut $spacing ."\t\tOptions\n";
						print $spdlFileOut $spacing ."\t\t{\n";
						
						foreach my $key (sort( keys %reOptions ) )
						{
							print $spdlFileOut $spacing ."\t\t\t\"$key\" = " . $reOptions{$key} . ";\n";
						}
						print $spdlFileOut $spacing ."\t\t}\n";
					}
					
					# Spit out pheno tree
					if( @rePhenoTree != 0 )
					{
						print $spdlFileOut $spacing ."\t\tBeginText\n";
						
						foreach $phen ( @rePhenoTree )
						{
							print $spdlFileOut $spacing ."\t\t$phen\n";
						}
						
						print $spdlFileOut $spacing . "\t\tEndText\n";
					}
					
					print $spdlFileOut $spacing . "\t}\n";
				}
				print $spdlFileOut $spacing . "}\n";
				$phen = 0;
			}
		}
		
	}
	close( $spdlFileIn );
	close( $spdlFileOut );
}

die "Usage: ".basename( $0 ). " <spdl file in> <spld file out>" if( @ARGV != 2 );

&convertShaderSPDL( $ARGV[ 0 ], $ARGV[ 1 ] );

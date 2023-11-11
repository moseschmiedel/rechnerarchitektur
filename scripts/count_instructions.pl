#!/usr/bin/env perl

use v5.36;
use warnings;

my @algorithms = ( 'sobel-sequential', 'sobel-parallel' );

my $algo_regex;
for my $algo (@algorithms) {
    $algo_regex .= "|$algo-g";
    $algo_regex .= "|$algo-O1";
    $algo_regex .= "|$algo-O2";
    $algo_regex .= "|$algo-O3";
}
my @foo = split '', $algo_regex;
shift @foo;
$algo_regex = join '', @foo;
$algo_regex = "^($algo_regex)\$";

my $binary_dir_path = $ARGV[0];

say "searching for algorithm binaries in: $binary_dir_path/";

opendir my $binary_dir, $binary_dir_path or die "Cannot open directory: $!";
my @binary_dir_content = readdir $binary_dir;
closedir $binary_dir;

for my $file_name (@binary_dir_content) {
    if ( $file_name =~ m/$algo_regex/ ) {
        say "found: $file_name";

        my %instr_counts;

        my @obj_lines =
          qx{objdump --disassemble=sobel -Matt $binary_dir_path/$file_name};
        for my $line (@obj_lines) {
            if ( $line =~ m/^ \s .* $/x ) {
                $line =~ s/^.+\t.+\t+([a-z]+)?\s+.*$/$1/p;
                chomp($line);
                if ( $line =~ m/^ [a-z]+ $/x ) {
                    if ( !$instr_counts{$line} ) {
                        $instr_counts{$line} = 1;
                    }
                    else {
                        $instr_counts{$line}++;
                    }
                }
            }
        }

        open( my $fh, '>', "$binary_dir_path/$file_name.csv" )
          or die "Could not open file '$binary_dir_path/$file_name.csv'";
        for my $instr ( keys %instr_counts ) {
            print $fh $instr . ',' . $instr_counts{$instr} . "\n";
        }
        close $fh;
    }
}

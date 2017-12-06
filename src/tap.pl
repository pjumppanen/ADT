#!/usr/bin/perl
# Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
# ORGANISATION (CSIRO), Australia.
# All rights reserved.
#
# This file is part of ADT.  The full ADT copyright notice, including
# terms governing use, modification, and redistribution, is contained in
# the file COPYING. COPYING can be found at the root of the source code
# distribution tree;
use strict;
use Getopt::Std;
use LWP::UserAgent;
use HTTP::Cookies;
use HTML::Form;
use HTML::Strip;
use Archive::Zip;

sub help_info
{
    print "Usage: tap.pl -s {source file} -f {function name} [-o {output vars}] [-i {input vars}] -m {mode}\n";
    print "\n";
    print "[] denotes optional parameters.\n";
    print "{} denotes user supplied parameters.\n\n";
    print "-h                     display help.\n";
    print "-f {function name}     specifies the function to differentiate.\n";
    print "-s {source file}       specifies file containing the source to be\n";
    print "                       differentiated.\n";
    print "-o {output vars}       specifies dependent output variables to\n";
    print "                       provide differentials for.\n";
    print "-i {input vars}        specifies independent input variables to\n";
    print "                       provide differentiate wrt.\n";
    print "-m {mode}              specifies mode of differentiation.\n";
    print "\n";
    print "{mode} can be one of:\n\n";
    print "t     tangent (forward) mode.\n";
    print "mt    multidirectional tangent mode.\n";
    print "a     adjoint (reverse) mode.\n";
    print "ma    multiobjective adjoint mode.\n\n";

    exit();
}

print "\nTapenade On-line Forwarder\n\n";

my %mode_map = ("t"  => "buttondiffforward",
                "mt" => "buttondiffforwardvectorial",
                "a"  => "buttondiffbackward",
                "ma" => "buttondiffbackwardvectorial");
my %mode_suffix_map = ("t"  => "_d",
                       "mt" => "_dv",
                       "a"  => "_b",
                       "ma" => "_bv");
my $source;
my $head;
my $click;
my $mode;
my $depoutputvars  = "";
my $indepinputvars = "";

our($opt_h, $opt_s, $opt_f, $opt_o, $opt_i, $opt_m);
getopts("hs:f:o:i:m:");

if (defined($opt_h))
{
  help_info();
}

if (defined($opt_s))
{
  my $filename = $opt_s;

  if (open(FILE, $filename) == 0)
  {
    print("ERROR: Couldn't open file: $filename\n\n");
    help_info();
  }

  $source = join("", <FILE>);
  close FILE;

} else
{
  print("ERROR: no source file specified. Use -s {source file}\n\n");
  help_info();
}

if (defined($opt_f))
{
  $head = $opt_f;
} else
{
  print("ERROR: no function to differentiate give. Use -f {function name}\n\n");
  help_info();
}

if (defined($opt_o))
{
  $depoutputvars = $opt_o;
}

if (defined($opt_i))
{
  $indepinputvars = $opt_i;
}

if (defined($opt_m))
{
  $mode = $opt_m;

  if ($mode_map{$mode})
  {
    $click = $mode_map{$mode};

  } else
  {
    print("ERROR: unknown mode in -m {mode}.\n\n");
    help_info();
  }

} else
{
  print("ERROR: no mode specified. Use -m {mode}.\n\n");
  help_info();
}

print "Differentiating $head\n";
print "Dependent output variables: $depoutputvars\n";
print "Independent input variables: $indepinputvars\n\n";

my $cookie_jar = HTTP::Cookies->new;
my $ua         = LWP::UserAgent->new;

$ua->cookie_jar($cookie_jar);
$ua->requests_redirectable(['GET', 'HEAD', 'POST']);
$ua->max_redirect(5);
$ua->agent("Mozilla/5.0 (Windows NT 6.1)");
#$ua->add_handler("request_send",  sub { print shift->headers()->as_string; return });
#$ua->add_handler("response_done", sub { print shift->headers()->as_string; return });
#$ua->add_handler("response_redirect", sub { print shift->headers()->as_string; return });

# open a Tapenade paste.jsp form
my $request    = HTTP::Request->new(GET => 'http://www-tapenade.inria.fr:8080/tapenade/paste.jsp');
my $resp       = $ua->request($request);

if ($resp->is_success)
{
  my @forms = HTML::Form->parse($resp);
  my @inputs = $forms[0]->inputs;
  my %expected_inputs = ("choice"                      => "text",
                         "filetype"                    => "fortran95",
                         "source"                      => $source,
                         "head"                        => $head,
                         "depoutputvars"               => $depoutputvars,
                         "indepinputvars"              => $indepinputvars,
                         "buttondiffforward"           => "Tangent Mode",
                         "buttondiffforwardvectorial"  => "Multidirectional Tangent Mode",
                         "buttondiffbackward"          => "Adjoint Mode",
                         "buttondiffbackwardvectorial" => "Multiobjective Adjoint Mode",
                         "Tapenade-Log"                => "");

  # Check the form conforms to the structure we expect and set values of fields in the form
  foreach my $input (@inputs)
  {
    if (defined($expected_inputs{$input->name}))
    {
      my $value = $expected_inputs{$input->name};

      $input->value($value);

    } else
    {
      print("WARNING:Tapenade forwarder out of date. Can't find '".$input->name."'. Update tap.pl script.\n");
    }

    $input->value($expected_inputs{$input->name});
  }

  # Click the appropriate differentiation button
  my $ad_request = $forms[0]->click($click);
  my $ad_resp    = $ua->request($ad_request);

  if ($ad_resp->is_success)
  {
    # Open the frames in the Tapenade result response
    my $src_graph_request  = HTTP::Request->new(GET => 'http://www-tapenade.inria.fr:8080/tapenade/sourceCallGraph.jsp');
    my $diff_graph_request = HTTP::Request->new(GET => 'http://www-tapenade.inria.fr:8080/tapenade/diffCallGraph.jsp');
    my $msg_request        = HTTP::Request->new(GET => 'http://www-tapenade.inria.fr:8080/tapenade/msg.jsp');
    my $src_graph_resp     = $ua->request($src_graph_request);
    my $diff_graph_resp    = $ua->request($diff_graph_request);
    my $msg_resp           = $ua->request($msg_request);

    if ($diff_graph_resp->is_success)
    {
      # Click on the download button to download the corresponding files
      my @diff_forms       = HTML::Form->parse($diff_graph_resp);
      my $download_request = $diff_forms[0]->click("Download");
      my $download_resp    = $ua->request($download_request);

      if ($download_resp->is_success)
      {
        my $default_all = "default".$mode_suffix_map{$mode}."-all.f95";

        # Save the downloaded zip file
        open(OUTFILE, ">ad_files.zip") or die "ERROR: cannot open ad_files.zip for writing\n";
        binmode(OUTFILE);
        print OUTFILE $download_resp->content;
        close(OUTFILE);

        my $zip = Archive::Zip->new();

        $zip->read("ad_files.zip");
        $zip->extractMemberWithoutPaths($default_all);
        unlink("ad_files.zip");
      }
    }

    if ($msg_resp->is_success)
    {
      my $hs = HTML::Strip->new();

      $hs->set_emit_spaces(0);
      print $hs->parse($msg_resp->content);
      $hs->eof;
    }
  } else
  {
    print $ad_resp->status_line;
  }

} else
{
  print $resp->status_line;
}

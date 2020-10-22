#!/bin/sh

# The .body source files contain documentation for executables.
# This files have the synopsis and the options section empty.
# The synopsis and the options documentation are generated automatically
# using the EST native sgml generated documentation options.
# The xsl transformations convert the sgml output from the EST executables
# into markdown format, parseable by doxygen.
#
# Simple usage: 
# ./create_dox.sh \
#    "../../bin/ch_wave" \
#    ./ch_wave_man.dox.body
#
# A ch_wave_manual.dox will be generated in current directory
# (has to be run from speech_tools/doc/man/ directory)
#
# Custom xsltproc binary:
#
# ./create_dox.sh \
#    /path/to/ch_wave \
#    /path/to/ch_wave_man.dox.body \
#    . \
#    . \
#    /usr/bin/xsltproc \
#    /usr/bin/awk
#
# Out of tree usage:
# /tmp/speech_tools/doc/man/create_dox.sh \
#    /path/to/ch_wave \
#    /path/to/ch_wave_man.dox.body \
#    /tmp/speech_tools/doc/man/ \
#    /tmp/builddir/ \
#    /usr/bin/xsltproc \
#    /usr/bin/awk
full_program="$1"
doc_body="$2"
doc_man_dir="${3:-$PWD}"
out_dir="${4:-$PWD}"
XSLTPROC="${5:-xsltproc}"
AWK="${6:-awk}"

program=`basename $full_program`
doc_out="${out_dir}/${program}_man.dox"

# Generate
$full_program -sgml_synopsis | "${XSLTPROC}" "${doc_man_dir}/convert-synopsis.xslt" - > "${program}_synopsis.txt" || exit 1
$full_program -sgml_options | "${XSLTPROC}" "${doc_man_dir}/convert-options.xslt" - > "${program}_options.txt" || exit 1

${AWK} 'BEGIN {
        while ((getline line < ARGV[1]) > 0) {file1 = file1 nl line; nl = "\n"}; 
        close (ARGV[1]); nl = "";
        while ((getline line < ARGV[2]) > 0) {file2 = file2 nl line; nl = "\n"};
        close (ARGV[2]);
        ARGV[1] = ""; ARGV[2] = "" }
      { gsub("@SYNOPSIS@", file1); 
        gsub("@OPTIONS@", file2); 
        print }' "${program}_synopsis.txt" "${program}_options.txt" "${doc_body}" > "${doc_out}" || exit 1

rm "${program}_synopsis.txt" "${program}_options.txt" || exit 1

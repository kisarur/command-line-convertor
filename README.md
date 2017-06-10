# command-line-convertor
This is a complete command line conversion tool which converts numbers from a given format to another given format used in computers.
This program doesn't use any library function other than fprintf from stdio.

The tool takes command line arguments as shown below.

       ./clc -<input format> -<output format> <input>
      
Input/output format can be one of the followings.

      B - A 32-bit or 64-bit representation
      H - An 8-digit or 16-digit hexadecimal representation
      I - Integer (32-bit)
      F - Single precision floating point number
      D - Double precision floating point number

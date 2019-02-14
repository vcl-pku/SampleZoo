/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int argc, char **argv)
{
    Samples::AutoTest();
    return 0;
}

/*
TODO:

 * make documentation for uniform random tests
  * and LDS (sobol only right now, maybe add more?)
  * and best candidate blue noise (should we have other blue noise multiple amounts? like 0 at high sample count? and a high multiplier value?)

* make some autogenerated test results file
 * And have an analysis md that goes along with it?
 * Do they combine together? Maybe analysis.rsw.md combines with results.md to make analysis.md?
* For text things (like discrepancy) make a .Lua file to store the data in individual files.
 * For test results, have a Lua file that generates results.md
 * Have a "begin" / "item" / "end" function call.
 * Item can show individual results but also store a table for sorting, like for discrepancy.
 * For numberline, only really need the item function.
* Autotest should probably just be a test in itself
 * also maybe have some way to run the auto tests... maybe a macro list?

* make some better tests that actually show things:
 * discrepancy as a graph with number of samples
 * integration error over time vs specific functions

* clean this up below & figure out what is needed to open this up to letting people submit 1d sample sequences!
 * purpose of samples and test documentation?
 * automated testing setup / comparisong testing?

 ? how does testing a progressive sequence differ from non progressive?
 * show a graph of discrepancy over sample count, to see how it changes.
 * somehow need to note that it's progressive - in documenation, and also in code?
 * for now, it's not treated as progressive or noted as progressive.

* some kind of autogen for test & sample documentation?
 * like for samples, maybe if the .md doesn't exist, create it with links to all the files generated by tests?
 * or, a person can make sections of info and it somehow gets dropped into a template with string replacement from a dictionary lookup for specific markup?

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up




Documentation WIP:

Guidelines overall:
* samples are in [0,1)^N in general and similar. If you have a good reason to diverge from that, you can.
* Code should ideally be copy / paste-able for easy drop in use. modular / standalone to be low effort to take & use.
* Prefer readability over efficiency. STL is fine.
* Comments are good
* snake case file names
* upper camel case function names, name space names
* The purpose of sample specific documentation is two fold...
 1) Make programmers (non mathematicians) able to understand how it works.
 2) Show how it works, as well as any choices or trade offs there may be.
 * NOTE: comparison vs other sequences is usually out of scope of a sample submission, and should be made into a special test type, which you can link to.

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1)
* make a subfolder in src/samples/_1d/.  The subfolder name is snake case.
 * add your code (multiple cpps and headers are allowed)
 * make an info.lua
* run premake and it will make a .h file that is named the same as the subfolder that exposes the functions you listed in your info.lua file.
 * it will also update the header files to include this header file.
* The namespace is named off of "code name" in the .lua file.  It should be the same as the subfolder name but upper camel case instead of snake case.
! TODO: talk about documentation md file.

*/
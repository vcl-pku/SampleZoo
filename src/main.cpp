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

// TODO: temp! make this automatic, and run the autotest like you did before for samples.
#include "tests\_1d\numberline\autotest.h"

int main(int argc, char **argv)
{
    // TODO: make a root function in tests or something, that runs all the auto tests?
    Tests::_1d::Numberline::AutoTest();

    return 0;
}

/*
TODO:

* maybe have the toc link into the output folder files? have that be where the combined documentation file goes?

* clean up the hand written pages.
 * maybe put the header (and namespace if you want it) there automatically.

* put 2 scandirs at the top of each file so you only have to get the sample and test types once.
 * actually no, can't. need to scan for subsamble and subtest types

* next: get other tests working and making their results.md files
 * then, do the sample for samples having results.md
 * then, combine the hand written md file from tests and samples with results.md to make the actual .md that the TOC links to.
 * at that point, it'll be pretty close to ready to open up


* Generate numberline results page next. Fuse it with hand written numberline text.
 * Make a results.md for tests and for samples both (in output maybe?)
 * Combine with a handwritten .md for each, into whatever file name is actually linked to from the toc.

* link to blue noise paper about mitchell's best candidate:
 * "Spectrally Optimal Sampling for Distribution Ray Tracing" by Don P. Mitchell 1991
 * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.556.445&rep=rep1&type=pdf

* name test results as "<test>_<sampleCount>.png" or "<test>.png" since it's already scoped by sample type / sample family.

* put tests and samples both under _1d.  same with output.  fix documentation links.

* do these for LDS, and also link to from LDS
 * https://twitter.com/TechSparx/status/1096394113635753984?s=03
 * http://extremelearning.com.au/going-beyond-golden-ratio/

* integration test: include y=x^3

* maybe move to upper camel case instead of snake case.  Then can use folder names directly more often and can use function names in file names.

* after fixing up testing, delete "output" folder and see how things regenerate
 * also fix up documentation

* figure out the right sample counts for each test

? what is the goal of testing?
 1) have some things to show on the sample page (semi automatic - gather all test results for this sample type and mix it with supplied explanation / analysis)
 2) show results of tests on a tests page (semi automatic - gather all test results for this test type and mix it with supplied explanation / analysis)
 3) be able to have pages that compare aspects of sampling and talk about them (manual - manually gather whatever images you want and supply with whatever text you want)

 * make sampleFunctions etc const in test function signatures

 * make progressive sample functions not reset if they want more samples!

 * the tests should operate on a single set of samples, yes.
  * have the auto test loop through the sample functions and counts.
  ! but wait... sometimes we want single results, sometimes grouped...
   * it's ok, you can decide per test now.
   * you also can easily move the "single sample set" work to an internal function

* make all the existing tests work again!

 * make sure all tests have a AutoTestSampleCounts, and remove code that makes it ok to be missing

 * Histogram test. Check white noise at large sample counts! Maybe 10, 100, 1000, etc

* make tests have autotest.h files which run through all sample types in the same family, at the specified number of samples.

* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!

* make sure mitchell's best candidate is using torroidal distance between points.

* Golden ratio: link to generating unique colors with GR

* have each test autogen a results page.
 * loop through each sample in the same family (passed as an array of function pointers)
 * have custom code to do whatever needs to be done?
 * might have "per sample" code, and might have "overall" code.  This is for eg graphing multiple things together



 * don't need sample autotest.h files.

* could cache expensive to calculate sequences, and check that in.

* finish turning autotest into just calling the 1d standard test!
 * might need to pass function pointer to Standard() so it can generate the number of samples it needs exactly?
 * i guess progressive sequence functions just add more if they need to, while the others clear it and start over

* do integration tests
 * add more!
 * make it graph them!

 * make documentation for Sobol in LDS sample type
  * and integration test
  * and standard test

? is blue noise less predictable than white? do tests to find out!

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
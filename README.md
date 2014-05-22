filestat
========

filestat is my learning effort for application development in ANSI C

Some important learning points are:

1. A refresher on writing code in ANSI C language.
2. Setting up a coding environment with Sublime Text 2.
3. Played with different build tools for C like QBS, premake, cmake, etc. Currently I have chosen to use cbuild.
4. Played with some static analysis tools like Splint, CppCheck, OCLint, RSM. RSM is a rule based static code analyser which allows writing custom rules. But RSM doesn't do memory leak checking. In this respect OCLint appears very interesting though it is still in development stage. However I couldn't find a binary of OCLint current version for 32bit Ubuntu and building in my laptop failed.
5. Played with different unit testing frameworks for C and currently using CuTest for unit testing.
6. Code coverage for unit testing has been calculated using gcov/lcov tool.

Some TODOs

1. Implement check for memory leaks at the time of running unit tests.
2. 50% of the code is not unit testable due to bad design. A redesign of the code keeping unit testability in mind.
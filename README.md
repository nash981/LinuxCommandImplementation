# LinuxCommandImplementation
<!-- # NOTE: Work in progress -->

## Description

Implementation of following linux commands from scratch in C:
- cut
- grep

This program runs on a terminal, with detailed instructions given below. 

## Requirements

- GCC compiler
- UNIX based terminal

## Usage
**scut (simplified version of Cut)**
- Run `make clean` to remove all existing compiled files
- Run `make` to compile latest version of the scut executable. 
- To run the executable, we have to give it input stream to cut from. It can be done by piping the output of some commands like cat, ls,etc.
- Command format: `[Piping input] | scut [feature] [range]
 - **feature**: 
  - **-l**: columns for the cut selections are on a per-character basis
  - **-w**: the cut selection columns will be separated by any whitespace (spaces or tabs) 
  - **-c**: cut selection columns will be separated by commas
 - **range**:
  - **1,3,4**: Comma separated input implies individual colums
  - **3-8**: Hyphen seperated input implies range between the two numbers. 
  - This program supports mix of comma seperated input and hyphen separated input as long as they are in ascending order and not overlapping

<!-- **sgrep (simplifed version of Grep command)**
- Run `make clean` to remove all existing compiled files
- Run `make` to compile latest version of the scut executable. 
- To run the executable, we have to give it input stream to cut from. It can be done by piping the output of some commands like cat, ls,etc.
- Command format: `[Piping input] | scut [feature] [range]
 - **feature**: 
  - **-l**: columns for the cut selections are on a per-character basis
  - **-w**: the cut selection columns will be separated by any whitespace (spaces or tabs) 
  - **-c**: cut selection columns will be separated by commas
 - **range**:
  - **1,3,4**: Comma separated input implies individual colums
  - **3-8**: Hyphen seperated input implies range between the two numbers. 
  - This program supports mix of comma seperated input and hyphen separated input as long as they are in ascending order and not overlapping
 -->


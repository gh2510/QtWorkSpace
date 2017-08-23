#!/bin/bash
find . -maxdepth 1 -type f -name "*.h" | xargs indent -kr -npro -nip -nlp -i4 -ts4 -sob -l200 -ss -bl -br -bli 0
find . -maxdepth 1 -type f -name "*.c" | xargs indent -kr -npro -nip -nlp -i4 -ts4 -sob -l200 -ss -bl -br -bli 0
find . -maxdepth 1 -type f -name "*.cpp" | xargs indent -kr -npro -nip -nlp -i4 -ts4 -sob -l200 -ss -bl -br -bli 0
find . -maxdepth 1 -type f -name "*~" | xargs rm

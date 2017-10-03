cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Accept.cpp
        Accept.h
        Determinize.cpp
        Determinize.h
        Equivalence.cpp
        Equivalence.h
        ExpressionRationnelle.cpp
        ExpressionRationnelle.h
        FA_main.cpp
        FA_tools.cpp
        FA_tools.h
        FA_types.h
        lex.yy.cpp
        location.hh
        Minimize.cpp
        Minimize.h
        parser.hpp
        parser.tab.cpp
        parser.tab.hpp
        parser_defs.hpp
        position.hh
        stack.hh
        ToGraph.cpp
        ToGraph.h)

add_executable(src ${SOURCE_FILES})
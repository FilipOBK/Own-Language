cmake_minimum_required(VERSION 3.27.4)

project(OwnLanguage)

add_library(Context Context.cpp)
add_library(Errors Errors.cpp)
add_library(Interpreter Interpreter.cpp)
add_library(Lexer Lexer.cpp)
add_library(Parser Parser.cpp)
add_library(Position Position.cpp)
add_library(RuntimeResult RuntimeResult.cpp)
add_library(SymbolTable SymbolTable.cpp)
add_library(Token Token.cpp)
add_library(Values Values.cpp)


add_executable(a shell.cpp)
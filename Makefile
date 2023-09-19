output: Context.o Errors.o Interpreter.o Lexer.o Nodes.o Parser.o Position.o RuntimeResult.o shell.o SymbolTable.o Token.o Values.o
	g++ *.o -o a.exe

target: dependencies
	action
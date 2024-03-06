CC := g++
ASM := AsmMatrixMult
STD := MatrixMult
RM := rm

app.exe: mainMatrix.o $(ASM).o $(STD).o
	@$(CC) $^ -o $@
	-./app.exe
	@$(RM) $^

%.o: %.cpp
	@$(CC) -c $^
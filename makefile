all: compila executa

compila: main.o EliminacaoGauss.o FatoracaoLU.o
	gcc main.o EliminacaoGauss.o FatoracaoLU.o -o prog

main.o: main.c
	gcc -c main.c

EliminacaoGauss.o: EliminacaoGauss.c
	gcc -c EliminacaoGauss.c

FatoracaoLU.o: FatoracaoLU.c
	gcc -c FatoracaoLU.c

executa:
	./prog.exe arquivo.txt

clean:
	del main.o EliminacaoGauss.o FatoracaoLU.o prog
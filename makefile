all: compila executa

compila: main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o GaussSeidel.o
	gcc main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o GaussSeidel.o -o prog

main.o: main.c
	gcc -c main.c

EliminacaoGauss.o: EliminacaoGauss.c
	gcc -c EliminacaoGauss.c

FatoracaoLU.o: FatoracaoLU.c
	gcc -c FatoracaoLU.c

GaussJacobi.o: GaussJacobi.c
	gcc -c GaussJacobi.c

GaussSeidel.o: GaussSeidel.c
	gcc -c GaussSeidel.c
	
executa:
	./prog.exe arquivo.txt

clean:
	del main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o GaussSeidel.o prog.exe
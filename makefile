all: compila executa

compila: main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o
	gcc main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o -o prog

main.o: main.c
	gcc -c main.c

EliminacaoGauss.o: EliminacaoGauss.c
	gcc -c EliminacaoGauss.c

FatoracaoLU.o: FatoracaoLU.c
	gcc -c FatoracaoLU.c

GaussJacobi.o: GaussJacobi.c
	gcc -c GaussJacobi.c

executa:
	./prog.exe arquivo.txt

clean:
	del main.o EliminacaoGauss.o FatoracaoLU.o GaussJacobi.o prog
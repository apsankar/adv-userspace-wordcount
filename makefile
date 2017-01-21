all: combiner

combiner: mapper.c reducer.c combiner.c
	gcc mapper.c -o mapper
	gcc reducer.c -o reducer
	gcc combiner.c -o combiner

clean:
	rm mapper reducer combiner
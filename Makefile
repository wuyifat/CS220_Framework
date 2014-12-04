
SRC=$(filter-out %main.cc, Source/*)
OBJ=claim.o edge.o map.o twobit.o netlist.o node.o path.o pathsegment.o lee.o threebit.o problem_object.o segmentgroup.o 

vpath %.cc Source/

all: $(OBJ) main.cc
	g++ -o grid_router $^ Utilities/JSON_parser/json_parser.so 

test: all
	./grid_test
	
%.o: %.cc
	g++ -c $^

cleanup:
	rm -f *.o

clean: cleanup
	rm -f grid_test


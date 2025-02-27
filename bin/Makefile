all: count

count: count.cpp
	g++ count.cpp -o count

clean:
	rm count

test: count_test.cpp
	g++ count_test.cpp -o count_test
	./count_test
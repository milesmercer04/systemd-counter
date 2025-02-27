build:
	g++ bin/count.cpp -o bin/count

test:
	g++ -o count_test -DUNIT_TEST bin/count.cpp bin/count_test.cpp -lgtest -lgtest_main -pthread
	./count_test

clean: build
	rm bin/count

run: build
	bin/count

build-deb:

lint-deb:
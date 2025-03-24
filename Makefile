build:
	g++ bin/count.cpp -o bin/count

test:
	g++ -o bin/count_test -DUNIT_TEST bin/count.cpp bin/count_test.cpp -lgtest -lgtest_main -pthread
	bin/count_test

clean:
	rm -f bin/count
	rm -f bin/count_test
	rm -rf build
	rm -f counter-v2.0.0.deb

run: build
	bin/count

build-deb: build
	rm -rf build
	mkdir -p build build/bin build/etc build/DEBIAN
	cp bin/count build/bin/
	strip build/bin/count
	echo "NAME=Miles" > build/etc/count.conf
	echo "/etc/count.conf" > build/DEBIAN/conffiles
	cp conf/* build/DEBIAN/
	chmod 755 build/DEBIAN/postinst build/DEBIAN/prerm build/DEBIAN/postrm
	dpkg-deb --root-owner-group --build build
	mv build.deb counter-v2.0.0.deb

lint-deb: build-deb
	lintian counter-v2.0.0.deb

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
	-docker rmi counter:latest
	docker system prune -f
	rm -rf /tmp/count/

run: build
	bin/count

build-deb: build test
	rm -rf build
	mkdir -p build build/bin build/etc build/DEBIAN build/lib/systemd/system
	cp bin/count build/bin/
	strip build/bin/count
	echo "NAME=Miles" > build/etc/count.conf
	echo "/etc/count.conf" > build/DEBIAN/conffiles
	cp counter.service build/lib/systemd/system/
	cp conf/* build/DEBIAN/
	chmod 755 build/DEBIAN/postinst build/DEBIAN/prerm build/DEBIAN/postrm
	dpkg-deb --root-owner-group --build build
	mv build.deb counter-v2.0.0.deb

lint-deb:
	-lintian counter-v2.0.0.deb

docker-image:
	docker build -t counter:latest .

docker-run: docker-image
	[ -d /tmp/count ] || mkdir -p /tmp/count/
	chmod 1777 /tmp/count/
	docker run --rm -it --mount type=bind,source=/tmp/count,dst=/tmp/count counter:latest

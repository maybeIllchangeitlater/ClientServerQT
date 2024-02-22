all: clean build

build: build_server build_client

build_server: clean_server
	mkdir build_server && cd build_server && cmake ../server

build_client: clean_client
	mkdir build_client && cd build_client && cmake ../client

serv: build_server
	cd build_server && make server && ./server

cli: build_client
	cd build_client && make client && open -a client.app

clean_server:
	rm -rf build_server

clean_client:
	rm -rf build_client 

clean: clean_server clean_client
	rm -rf html

doxygen:
	doxygen Doxyfile
	open html/index.html

.PHONY: build build_server build_client serv cli clean_server clean_client clean doxygen

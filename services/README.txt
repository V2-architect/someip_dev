# SOME/IP Service directory structure

{SERVICE_NAME}/
	|-- CMakeLists.txt
	|-- build.sh
	|-- gen_code.sh
	|-- build
	|   |-- CMakeCache.txt
	|   |-- CMakeFiles
	|   |-- Makefile
	|   |-- {SERVICE_NAME}_client
	|   |-- {SERVICE_NAME}_client_udp
	|   |-- {SERVICE_NAME}_server
	|   |-- {SERVICE_NAME}_server_udp
	|   |-- client_tcp.json.in
	|   |-- client_udp.json.in
	|   |-- cmake_install.cmake
	|   |-- run_client.sh
	|   |-- run_routingd.sh
	|   |-- run_server.sh
	|   |-- server_tcp.json.in
	|   `-- server_udp.json.in
	|-- conf
	|   |-- client_tcp.json.in
	|   |-- client_udp.json.in
	|   |-- server_tcp.json.in
	|   `-- server_udp.json.in
	|-- fidl
	|   |-- {SERVICE_NAME}.fdepl
	|   |-- {SERVICE_NAME}.fidl
	|   |-- {SERVICE_NAME}_tcp.fdepl
	|   `-- {SERVICE_NAME}_udp.fdepl
	|-- src
	|   |-- {SERVICE_NAME}_client.cpp
	|   |-- {SERVICE_NAME}_server.cpp
	|   |-- {SERVICE_NAME}_server_stubimpl.cpp
	|   `-- {SERVICE_NAME}_server_stubimpl.hpp
	`-- src-gen
		`-- v1


# CMakeList.txt requires ..
- DEPS_PATH: /home/jhshin/work/dependencies
- LIB_PATH: /home/jhshin/work/lib_gits


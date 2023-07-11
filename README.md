
# Virtual filesystem server

* [Project Description](#Project-Description)
* [Usage](#usage)

## Project Description
The task is to program a simple HTTP server with support for different content generators.
The tool will implement:
- Providing content of the following kind:
- Static content (a specific file).
- Listing of directory content (if enabled in the settings).
- Running a script (e.g. sh, c, c++, ...).
- Sending a signal to exit the server.
- Non-existent page.
The server will allow:
- Retrieving static files using the GET method.
- Saving static files using the POST method.
The tool will be configurable from a file:
- Network parameters (IP address, port, and more).
- Restrictions on working with specific directories (configuration includes mapping individual directories to addresses).
- Logging of traffic to the log.
- Definition of extensions for scripting.
- Address (or method) for shutting down the server.

## Usage
compile: Compiles the project.
```console
$ make compile
```
run: Compiles and runs the project.
```console
$ make run
```
doc: Generates Doxygen documentation.
```console
$ make doc
```
clean: Cleans object files, executables, and generated documentation.
```console
$ make clean
```
clean_server_files: Cleans server files.
```console
$ make clean_server_files
```
tests: Compiles the test files.
```console
$ make tests
```
run_tests: Runs the compiled tests.
```console
$ make run_tests
```
all: The default target. It compiles, generates documentation, and runs tests.
```console
$ make all
```
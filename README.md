# EECS 348 Class Project

[![C/C++ CI](https://github.com/kmdeskin/EECS348-Class-Project/actions/workflows/compiles.yml/badge.svg)](https://github.com/kmdeskin/EECS348-Class-Project/actions/workflows/compiles.yml)

## Setting up the project

This is a repository for our class project done for EECS348 Software Engineering I at KU for the Fall 2023 semester.

The app is currently hosted at http://137.184.123.158:3000/

To build the project for yourself, run the associated build script for the operating system you are using.

If you are using Windows, run `./windows-build.sh`.

If you are using macOS, run `./macos-build.sh`.

If you are using Linux, run `./linux-build.sh`.

The expected output should look something like:
```
$ ./linux-build.sh

Building configurations...
Running action 'gmake'...
Done (80ms).
```

If you are using Windows, a `.sln` file should be outputted. Open this file using Visual Studio and build it from there.

If you are using Linux or macOS, now, to compile the project, run `make`. The expected output is:
```
$ make

==== Building Calculator (debug) ====
==== Building Website (debug) ====
```

Next, change to the directory for the website by running `cd www`. 

In this directory, now run `./Website`.

Open your browser of choice and navigate to the following IP address: `127.0.0.1:3000`.

You should now see the web calculator application on the screen of your device.

## Testing the project

There is a Python script to run a suite of test cases in the `tests/` folder. Running this will require the `requests` library, and if running the project from your own machine, you will need to change the `WEB_URL` constant in the script to the URL of your machine or the server you are running the project on.

Navigate to the `tests/` directory and run
```
$ python3 tests.py
```
to run the automated tests on the test cases in `test_cases.csv`.


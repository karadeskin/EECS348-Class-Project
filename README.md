# EECS 348 Class Project

[![C/C++ CI](https://github.com/kmdeskin/EECS348-Class-Project/actions/workflows/compiles.yml/badge.svg)](https://github.com/kmdeskin/EECS348-Class-Project/actions/workflows/compiles.yml)

This is a repository for our class project done for EECS348 Software Engineering I at KU for the Fall 2023 semester.

The app is currently hosted at http://137.184.123.158:3000/

To build the project for yourself, run the associated build script for the operating system you are using.

For example, using macOS, run `./macos-build.sh`, where the expected output is:
```
$ ./macos-build.sh

Building configurations...
Running action 'gmake'...
Done (80ms).
```

Now, to compile the project, run `make`. The expected output is:
```
$ make

==== Building sqlite (debug) ====
==== Building Calculator (debug) ====
==== Building Website (debug) ====
```

Next, change to the directory for the website by running `cd www`. 

In this directory, now run `./Website`.

Open your browser of choice and navigate to the following IP address: `127.0.0.1:3000`.

You should now see the web calculator application on the screen of your device.




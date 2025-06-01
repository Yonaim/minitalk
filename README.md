# minitalk

![screenshot](/screenshot.png)

`minitalk` is a personal implementation of a simple client-server communication program using UNIX signals. The server listens for signals sent from a client process and reconstructs messages transmitted bit-by-bit through these signals.

## Project Purpose

- Understand inter-process communication (IPC) through UNIX signals (`SIGUSR1`, `SIGUSR2`).
- Practice bitwise operations and message encoding/decoding.
- Gain experience in handling signals and managing process synchronization.

## How It Works

- The **client** sends a message character by character, encoding each bit as a signal:
  - `SIGUSR1` for binary `0`
  - `SIGUSR2` for binary `1`

- The **server** receives these signals, decodes them bit by bit, and reconstructs the original message.

## Installation and Compilation

Clone the repository and compile using the provided Makefile:

```bash
git clone https://github.com/Yonaim/minitalk.git
cd minitalk
make
```

This will generate two executables:
- `server`
- `client`

## Usage

First, run the server:

```bash
./server
```

The server will display its PID, which you'll need for the client.

Then, in another terminal, run the client with the server PID and your message:

```bash
./client [server_pid] "Your message"
```

## Example

Terminal 1 (Server):

```bash
$ ./server
Server PID: 12345
```

Terminal 2 (Client):

```bash
$ ./client 12345 "Hello, minitalk!"
```

Server Output:

```
Received message: Hello, minitalk!
```

## Signals Used

| Signal    | Binary |
|-----------|--------|
| `SIGUSR1` | `0`    |
| `SIGUSR2` | `1`    |

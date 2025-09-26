# Minitalk

A tiny client/server IPC exercise using UNIX signals. The client encodes a message bit by bit and the server rebuilds and prints it.

![Signal flow](./minitalk-signal-flow.avif)

## How it works
- Client converts each character to 8 bits and sends them MSB→LSB.
- SIGUSR1 represents bit 1, SIGUSR2 represents bit 0.
- A short usleep (~40µs) between bits gives the server time to handle signals.
- Server assembles bits into bytes and writes characters as they complete.
- Bonus: the server can acknowledge each received bit; the client prints what was acknowledged. Using sigaction allows passing sender info.

## Build
On a standard Linux toolchain:

- Mandatory
  - gcc -Wall -Wextra -Werror server.c -o server
  - gcc -Wall -Wextra -Werror client.c -o client
- Bonus
  - gcc -Wall -Wextra -Werror server_bonus.c -o server_bonus
  - gcc -Wall -Wextra -Werror client_bonus.c -o client_bonus

## Usage
1) Start the server and note its PID:
   - ./server
2) Send a message from the client:
   - ./client <PID> "your message"

Bonus version:
- ./server_bonus
- ./client_bonus <PID> "your message"  (shows per‑bit acknowledgements)

## Repo layout
- server.c / client.c — mandatory
- server_bonus.c / client_bonus.c — bonus
- server/ and client/ — project sources or headers as needed

## Notes
- Timing between signals matters; too little delay can drop bits depending on host load.
- Wide characters can be sent if client and server agree on the byte stream sent.
- This project was inspired by community write‑ups and prior 42 work on signal‑based IPC.

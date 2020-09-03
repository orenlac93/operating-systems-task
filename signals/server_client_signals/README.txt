
how to compile:
	type (make), the makefile will create 2 executable files (server , client)

how to run:
	1. first run the server by typing: ./server
	2. run the client with 3 parameters(server_pid , signal_number , number_of_signals)
	   by typing: ./client <server_pid> <signal_number> <number_of_signals>
	   
	signal_numbers: 2(SIGINT) 10(SIGUSR1)

example:
	./client 116 2 1000              
	(the client send to the server(pid 116) 1000 SIGINT signals)

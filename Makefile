all:
	g++ -Wall main.cpp biggest-divisible-conglomerate.cpp -o bdc

run:
	./bdc

try: all run
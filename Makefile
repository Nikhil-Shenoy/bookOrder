true: true.c
	clear
	gcc -o true true.c -lpthread
	./true
	rm true 
mod: mod.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	clear
	gcc -o mod mod.c extract.c order.h person.h person.c order.c dbList.h dbList.c -lpthread
	./mod database.txt orders.txt categories.txt
	rm mod 
dmod: mod.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	clear
	gcc -g mod.c extract.c order.h person.c person.h order.c dbList.h dbList.c -lpthread
	gdb a.out
	rm a.out

orderList: order.h orderList.h orderList.c order.c
	clear
	gcc -o listTest listTest.c order.h orderList.h orderList.c order.c
	./listTest
	rm listTest
debug: order.h orderList.h orderList.c order.c
	clear
	gcc -g listTest.c order.h orderList.h orderList.c order.c
	gdb a.out

dbList: person.h dbList.h dbList.c person.c dbTest.c order.h order.c orderList.h orderList.c
	clear
	gcc -o dbTest dbTest.c person.h dbList.h dbList.c person.c order.h order.c orderList.h orderList.c

	./listTest
	rm listTest

test: test.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	clear
	gcc -o test test.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	./test database.txt orders.txt
	rm test
dtest: test.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	clear
	gcc -g  test.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	gdb a.out

Rmod: Rmod.c extract.c order.h person.c person.h order.c dbList.h dbList.c
	clear
	gcc -o Rmod Rmod.c extract.c order.h person.h person.c order.c dbList.h dbList.c -lpthread
	./Rmod database.txt orders.txt categories.txt
	rm Rmod 


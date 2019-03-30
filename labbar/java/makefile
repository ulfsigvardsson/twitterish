run: Simulator.class
	java Simulator 1 2 3 4

debug:
	jdb Simulation

Simulator.class: Simulator.java Simulation.class
	javac Simulator.java

Simulation.class: Simulation.java Store.class
	javac Simulation.java

Store.class: Store.java Register.class
	javac Store.java

Register.class: Register.java Queue.class
	javac Register.java

Queue.class: Queue.java Customer.class
	javac Queue.java

Customer.class: Customer.java
	javac Customer.java

test: TestFile.class
	java -cp .:/usr/share/java/junit4.jar TestFile

TestFile.class: TestFile.java TestCustomer.class
	javac -cp .:/usr/share/java/junit4.jar TestFile.java

TestCustomer.class: TestCustomer.java Customer.class
	javac -cp .:/usr/share/java/junit4.jar TestCustomer.java

clean:
	rm -f *~
	rm -f ´#
	rm -f *.class

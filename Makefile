all:
	javac ./source/*.java -d ./bin

client: all
	java -cp ./bin/ Twitterish localhost 8082

server: all
	java -cp ./bin/ Server 8082

clean:
	rm -f  ./bin/*.class
	rm -f ./source/*#
	rm -f ./source/*~

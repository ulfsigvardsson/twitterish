# Twitterish - A Terrible Chat Application

Are You tired of Messenger, Snapchat and Twitter with all their distracting colours and fanciness? Then Twitterish is the social media app for You! 

Clone the repo `git clone https://github.com/ulfsigvardsson/twitterish` and run `make all`, then `make server` and in a seperate terminal window, `make client`. Then, have a friend do the same but modify the makefile like so 

```client: all
java -cp ./bin/ Twitterish <ip> 8082
``` 

where <ip> is the IP address of the machine running the server.
  
As user control is the keyword for Twitterish, the chat feed is not being updated in realtime. To refresh the feed, enter `U` to see what has been going on. Add friends, comment on posts or ignore the meanies with the corresponding commands at the bottom of the screen.

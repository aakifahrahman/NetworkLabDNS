DESIGN OF CLIENT CODE OF DNS :

  1. Client socket is setup using socket() system call with datagram sockets.
  2. Server address and port is setup in a structure.
  3. User is asked to enter a command of the form 'nslookup abc.com'.
  4. The domain name abc.com is extracted from the command and is sent to the server using the
     structure setup using sendto() system call using datagram sockets.
  5. The IP adress sent from server is obtained usinf recvfrom() system call.
  6. If an IP adress is not recieved from server, error message is displayed.

DESIGN OF SERVER CODE OF DNS :

  1. Server socket is setup using socket() system call with datagram sockets.
  2. The socket is bound using the bind() system call to an IP adress and port number.
  3. The socket recieves host name from cleint using recvfrom() system call.
  4. The file containg the host name to IP adress mappings is opened, and each line is checked
     for the host name recieved from client.
  5. If a match is found, the corresponding IP adress is sent back to client using sendto() system
     call.
  6. If no match is found after searching the file, an error message is send back.


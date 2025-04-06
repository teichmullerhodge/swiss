const net = require('net');

const server = net.createServer((socket) => {
  socket.on('data', (data) => {
    const req = data.toString();
    
    let body;
    if (req.startsWith('GET /user')) {
      body = '{"Name": "Matheus", "Age": 25, "Favorite language": "C"}\n';
    } else if (req.startsWith('GET /status')) {
      body = '{"Status": true, "Uptime": 0.0}\n';
    } else {
      body = 'Not Found\n';
      const res = `HTTP/1.1 404 Not Found\r\nContent-Length: ${body.length}\r\nContent-Type: text/plain\r\n\r\n${body}`;
      socket.write(res);
      socket.end();
      return;
    }

    const res = `HTTP/1.1 200 OK\r\nContent-Length: ${body.length}\r\nContent-Type: application/json\r\n\r\n${body}`;
    socket.write(res);
    socket.end();
  });

  socket.on('error', (err) => {
    console.error('Socket error:', err);
  });
});

server.listen(9001, () => {
  console.log('Raw TCP Node server listening on http://localhost:9001');
});

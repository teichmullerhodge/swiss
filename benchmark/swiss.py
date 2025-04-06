import socket
from threading import Thread

HOST = 'localhost'
PORT = 9002

def handle_client(conn):
    request = conn.recv(4096).decode()

    if request.startswith("GET /user"):
        body = '{"Name": "Matheus", "Age": 25, "Favorite language": "C"}\n'
    elif request.startswith("GET /status"):
        body = '{"Status": true, "Uptime": 0.0}\n'
    else:
        body = "Not Found\n"
        response = f"HTTP/1.1 404 Not Found\r\nContent-Length: {len(body)}\r\nContent-Type: text/plain\r\n\r\n{body}"
        conn.sendall(response.encode())
        conn.close()
        return

    response = f"HTTP/1.1 200 OK\r\nContent-Length: {len(body)}\r\nContent-Type: application/json\r\n\r\n{body}"
    conn.sendall(response.encode())
    conn.close()

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(100)
    print(f"Servidor Python rodando em http://{HOST}:{PORT}")

    while True:
        conn, _ = server.accept()
        Thread(target=handle_client, args=(conn,)).start()

if __name__ == "__main__":
    start_server()

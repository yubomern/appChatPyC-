import socket
import threading

HOST = "0.0.0.0"
PORT = 5000


def handle_client(client_socket, address):
    print(f"[+] Client connecté : {address}")

    try:
        while True:
            data = client_socket.recv(4096)

            if not data:
                break

            message = data.decode("utf-8")
            print(f"[{address}] {message}")

            response = f"Server received: {message}"
            client_socket.sendall(response.encode("utf-8"))

    except ConnectionError:
        print(f"[!] Connexion perdue : {address}")

    finally:
        client_socket.close()
        print(f"[-] Client déconnecté : {address}")


def main():
    server_socket = socket.socket(
        socket.AF_INET,
        socket.SOCK_STREAM
    )

    # Permet de redémarrer rapidement le serveur
    server_socket.setsockopt(
        socket.SOL_SOCKET,
        socket.SO_REUSEADDR,
        1
    )

    server_socket.bind((HOST, PORT))
    server_socket.listen(10)

    print("==========================")
    print("      PYTHON SERVER")
    print("==========================")
    print(f"Listening on port {PORT}...")
    print()

    try:
        while True:
            client_socket, address = server_socket.accept()

            thread = threading.Thread(
                target=handle_client,
                args=(client_socket, address),
                daemon=True
            )

            thread.start()

            print(
                f"[INFO] Threads actifs : "
                f"{threading.active_count() - 1}"
            )

    except KeyboardInterrupt:
        print("\n[SERVER] Arrêt du serveur...")

    finally:
        server_socket.close()


if __name__ == "__main__":
    main()
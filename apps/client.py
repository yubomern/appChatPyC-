import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8081


def main():
    client = socket.socket(
        socket.AF_INET,
        socket.SOCK_STREAM
    )

    try:
        print(f"Connexion à {SERVER_IP}:{SERVER_PORT}...")

        client.connect((SERVER_IP, SERVER_PORT))

        print("Connecté au serveur.")
        print("Tape 'exit' pour quitter.\n")

        while True:
            message = input("Client > ")

            if message.lower() == "exit":
                break

            if not message:
                continue

            client.sendall(message.encode("utf-8"))

            response = client.recv(4096)

            if not response:
                print("Serveur déconnecté.")
                break

            print("Server >", response.decode("utf-8"))

    except ConnectionRefusedError:
        print("Impossible de se connecter au serveur.")

    except ConnectionError as e:
        print("Erreur réseau :", e)

    finally:
        client.close()
        print("Client fermé.")


if __name__ == "__main__":
    main()
import socket

HOST = '127.0.0.1'
PORT = 50000 # temos que conectar na mesma porta

# Criando o Socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # SOCK_STRAM indica que estamos utilizando TCP

# Solicitar a conexão do socket no servidor
s.connect((HOST, PORT))

# Para enviar dados
s.sendall(str.encode("Cliente e Servidor com Python"))

# O servidor vai retornar os dados
dados = s.recv(1024)

print(f'A mensagem foi retornada pelo servidor: {dados.decode()}')


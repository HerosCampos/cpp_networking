import socket

HOST = "localhost"
PORT = 50000

# Parâmetro Método         IPV4            TCP
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT)) # BIND para vincular HOST e PORTA
s.listen()
print('Aguardando conexão...')

conexao, endereco = s.accept()
print('Conectado em: ', endereco)
while True:
    dados = conexao.recv(1024)
    if not dados:
        print('Fechando a conexao!')
        conexao.close()
        break
    conexao.sendall(dados)


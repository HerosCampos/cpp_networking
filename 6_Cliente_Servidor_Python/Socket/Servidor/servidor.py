import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('localhost', 7777))
s.listen()

conexao, endereco = s.accept()

arquivo_nome = conexao.recv(1024).decode()

with open(arquivo_nome, 'rb') as file:
    for dados in file.readlines():
        conexao.send(dados)
    
    print('Arquivo enviado!')


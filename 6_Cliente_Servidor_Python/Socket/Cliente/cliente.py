import socket

cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

cliente.connect(('localhost', 7777))
print('Conectado!\n')

arquivo_nome = input('Digite o nome do arquivo que deseja receber: ')

cliente.send(arquivo_nome.encode())

with open(arquivo_nome, 'wb') as file:
    while 1:
        dados = cliente.recv(1000000)
        if not dados:
            break
        file.write(dados)

print(f'{arquivo_nome} recebido!\n')

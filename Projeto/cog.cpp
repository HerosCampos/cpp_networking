#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/asio/steady_timer.hpp>
#include <fstream>
#include <pthread.h>
#include <chrono>


std::vector<char> vBuffer(200);


void coletor_de_dados(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            std::cout << "\n\nRead: " << length << " bytes\n\n";
            
            std::string prefix = "cog";
            std::string extension = ".txt";
            
            std::ofstream file("rede.txt", std::ios::app);
            for(int i = 0; i < length; i++)
            {
                std::cout << vBuffer[i];

                file << vBuffer[i];
            }
            coletor_de_dados(socket);
        }
    );
}


int main()
{
    try
    {
        // Criando um contexto - de acordo com a documentação o io_context fornece funcionalidades como socket, acceptor...
        boost::asio::io_context context;


        // boost::asio::steady_timer timer{context, std::chrono::seconds{2}};
        // timer.async_wait([](const boost::system::error_code &ec) {
        //     std::cout << "2 segundos: " << ec.message() << std::endl;});


        // Give some fake tasks to asio so the context doesnt finish
        boost::asio::io_context::work idleWork(context);

        // Start context
        std::thread thrContext = std::thread([&]() {context.run();});

        // Criando um Endpoint do tipo TCP, ou seja, é determinado por um endereço de IP e uma porta do lugar que queremos conectar
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34"), 80);

        // Criando um socket 
        boost::asio::ip::tcp::socket socket(context);

        // Solicitando o socket para conectar com o endpoint
        socket.connect(endpoint);

        // Ao connectar o servidor estará esperando uma requisição HTTP (HTTP Request)
        if(socket.is_open())
        {
            coletor_de_dados(socket);

            std::string sRequest =
                "GET /index.html HTTP/1.1\r\n"
                "Host: example.com\r\n"
                "Connection: close\r\n\r\n";

            socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()));

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(200ms);
        }
    }
    catch(const boost::system::system_error& err)
    {
        std::cerr << "CODIGO ERRO: " << err.code() << ".\nMensagem: " << err.what() << std::endl;
    }   
}

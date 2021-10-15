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

            for(int i = 0; i < length; i++)
            {
                std::ofstream file((prefix + "_" + std::to_string(i) + extension), std::ios_base::out);
                for(int c = 0; c < length; c++)
                {
                    std::cout << vBuffer[c];

                    file << vBuffer[c];
                }
                
            }
            coletor_de_dados(socket);
        }
    );
}


int main()
{
    boost::system::error_code ec;

    // Criando um contexto - de acordo com a documentação o io_context fornece funcionalidades como socket, acceptor...
    boost::asio::io_context context;

    // Give some fake tasks to asio so the context doesnt finish
    boost::asio::io_context::work idleWork(context);

    // Start context
    std::thread thrContext = std::thread([&]() {context.run();});

    // Criando um Endpoint do tipo TCP, ou seja, é determinado por um endereço de IP e uma porta do lugar que queremos conectar
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);

    // Criando um socket 
    boost::asio::ip::tcp::socket socket(context);
    // Solicitando o socket para conectar com o endpoint
    socket.connect(endpoint, ec);

    if(!ec)
    {
        std::cout << "Conectado!" << std::endl;
    }
    else
    {
        std::cout << "Falha ao conectar ao endereço: " << ec.message() << std::endl;
    }

    // Ao connectar o servidor estará esperando uma requisição HTTP (HTTP Request)
    if(socket.is_open())
    {
        coletor_de_dados(socket);

        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        context.stop();
        if(thrContext.joinable()) thrContext.join();
        

        // socket.wait(socket.wait_read);

        //  using namespace std::chrono_literals;
        //  std::this_thread::sleep_for(200ms);

        // size_t bytes = socket.available();
        // std::cout << "Tamanho em Bytes: " << bytes << std::endl;

        // if(bytes > 0)
        // {
        //     std::vector<char> vBuffer(bytes);
        //     socket.read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()), ec);

        //     for(auto c: vBuffer)
        //     {
        //         std::cout << c;
        //     }
        // }

    }
}

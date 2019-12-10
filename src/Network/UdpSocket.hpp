/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** UdpSocket
*/

#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_

#include <iostream>
#include <QNetworkInterface>
#include <QString>
#include <QObject>
#include <QUdpSocket>

#define MAX_DATAGRAM_SIZE (3832)

namespace babel {
    class Core;
    class CallThread;
    namespace network {
    class UdpSocket : public QObject {
            Q_OBJECT
        public:
            explicit UdpSocket(const int &port, const std::string &target_ip, const int &target_port, babel::Core *parent = 0);
            explicit UdpSocket(const int &port, babel::CallThread *parent = 0);
            ~UdpSocket();
            

        signals:
            
        public slots:
            void readyRead();

        public:
            void write(const char *buffer, const unsigned int &size) const;
            void read(char *buffer);          
            void setTarget(std::string target, const int &port);

        private:

            QUdpSocket *_socket;
            QHostAddress _address;
            qint16 _port;
    };
    }
}

#endif /* !UdpSocket_HPP_ */

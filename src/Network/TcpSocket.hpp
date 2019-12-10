/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** TcpSocket
*/

#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDebug>

namespace babel {
    class Core;
    namespace network {
        class TcpSocket : public QObject {
            Q_OBJECT
        public:
            explicit TcpSocket(std::string target_ip, int target_port, bool isSocketServer, babel::Core *parent);
            explicit TcpSocket(QTcpSocket *socket, babel::Core *parent);
            
        signals:
            
        public slots:
            void connected();
            void disconnected();
            void bytesWritten(qint64 bytes);

        public:
            void read(char *buffer, int size);
            void connectToHost(std::string ip);
            void write(const char *buffer, const unsigned int size) const;
            std::string getPeerAddress();
            void close();

        private:
            QTcpSocket *_socket;
        };
    }
}
#endif // MYTCPSOCKET_H
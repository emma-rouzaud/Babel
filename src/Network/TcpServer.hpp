/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** TcpServer
*/

#ifndef TCPSERVER_H
    #define TCPSERVER_H

    #include <QObject>
    #include <QTcpSocket>
    #include <QTcpServer>
    #include <QDebug>

    namespace babel {
        class Core;
        namespace network {
            class  TcpServer : public QObject {
                Q_OBJECT
            public:
                explicit TcpServer(babel::Core *parent = 0);
                
            signals:
                
            public slots:
                QTcpSocket *getNewConnection();
                
            public:
                void startListening();
                void stopListening();

            private:
                QTcpServer *_server;
            };
        }
    }
#endif // MYTCPSERVER_H
/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** CallThread
*/

#ifndef CALLTHREAD_HPP_
    #define CALLTHREAD_HPP_
    #include <QThread>
    #include "UdpSocket.hpp"
    #include "Audio.hpp"


    namespace babel {
        class CallThread : public QThread {
            Q_OBJECT
        public:
            explicit CallThread();

        signals:

        public slots:
            void readyRead();

        public:
            void run() override;
            void endCall();
            void setTarget(const std::string &target);
            void setSocket(network::UdpSocket *socket);

        private:
            network::UdpSocket *_socket;
            Audio _audioManager;
            bool _isCallEnded = false;
        };
    }

#endif // MYTHREAD_HPP_


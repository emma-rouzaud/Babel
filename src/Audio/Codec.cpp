/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Codec
*/

#include "Codec.hpp"
#include <stdexcept>

babel::Codec::Codec()
{
    _encoder = opus_encoder_create(SAMPLE_RATE, NUM_CHANNELS, APPLICATION, &_error);
    if (_error != OPUS_OK)
        throw std::runtime_error("error");
    _error = opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(BITRATE));
    if (_error != OPUS_OK)
        throw std::runtime_error("error");
    _decoder = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &_error);
    if (_error != OPUS_OK)
        throw std::runtime_error("error");
}

babel::Codec::~Codec()
{
    opus_decoder_destroy(_decoder);
    opus_encoder_destroy(_encoder);
}

int     babel::Codec::encode(unsigned char * cbits, char * dataInput)
{
    return (opus_encode(_encoder, reinterpret_cast<opus_int16 *>(dataInput), FRAME_SIZE, cbits, MAX_PACKET_SIZE));
}

int     babel::Codec::decode(unsigned char * cbits, char * dataOutput, int nbBytes)
{
    return (opus_decode(_decoder, cbits, nbBytes, reinterpret_cast<opus_int16 *>(dataOutput), MAX_FRAME_SIZE, 0));
}

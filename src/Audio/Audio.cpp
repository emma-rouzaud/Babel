/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Audio
*/

#include "Audio.hpp"
#include <stdexcept>
#include <iostream>

babel::Audio::Audio()
{
    _input = new Stream;
    _output = new Stream;

    _error = Pa_Initialize();
    if (_error != paNoError)
        throw std::runtime_error("error");
    
    _input->stream = _output->stream = nullptr;
    _input->params.channelCount = _output->params.channelCount = NUM_CHANNELS;
    _input->params.sampleFormat = _output->params.sampleFormat = PA_SAMPLE_TYPE;
    _input->params.hostApiSpecificStreamInfo = _output->params.hostApiSpecificStreamInfo = nullptr;

    _input->params.device = Pa_GetDefaultInputDevice();
    _output->params.device = Pa_GetDefaultOutputDevice();
    _input->info = Pa_GetDeviceInfo(_input->params.device);
    _output->info = Pa_GetDeviceInfo(_output->params.device);
    _input->params.suggestedLatency = _input->info->defaultHighInputLatency;
    _output->params.suggestedLatency = _output->info->defaultHighOutputLatency;

}

babel::Audio::~Audio()
{
    _error = Pa_Terminate();
}

void    babel::Audio::init(void)
{
    _error = Pa_OpenStream(
        &_input->stream,
        &_input->params,
        nullptr,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        nullptr,
        nullptr
    );
    if (_error != paNoError)
        throw std::runtime_error("error");
    _error = Pa_OpenStream(
        &_output->stream,
        nullptr,
        &_output->params,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        nullptr,
        nullptr
    );
    if (_error != paNoError)
        throw std::runtime_error("error");
    _error = Pa_StartStream(_input->stream);
    if (_error != paNoError)
        throw std::runtime_error("error");
    _error = Pa_StartStream(_output->stream);
    if (_error != paNoError)
        throw std::runtime_error("error");
}

void    babel::Audio::close(void)
{
    _error = Pa_StopStream(_input->stream);
    if (_error != paNoError)
        throw std::runtime_error("error");
    _error = Pa_StopStream(_output->stream);
    if (_error != paNoError)
        throw std::runtime_error("error");
}

int    babel::Audio::read(char *buffer)
{
    char            dataInput[FRAME_SIZE * NUM_CHANNELS * 2] = {0};
    unsigned char * cbits = (unsigned char *)(buffer + 4);
    int *           nbBytes = (int *)buffer;

    _error = Pa_ReadStream(_input->stream, dataInput, FRAMES_PER_BUFFER);
    if (_error != paNoError)
        throw std::runtime_error("error");
    *nbBytes = _codec.encode(cbits, dataInput);
    return (*nbBytes + 4);
}

void    babel::Audio::write(char * buffer)
{
    char            dataOutput[MAX_FRAME_SIZE * NUM_CHANNELS * 2] = {0};
    unsigned char * cbits = (unsigned char *)(buffer + 4);
    int *           nbBytes = (int *)buffer;

    _codec.decode(cbits, dataOutput, *nbBytes);
    _error = Pa_WriteStream(_output->stream, dataOutput, FRAMES_PER_BUFFER);
}
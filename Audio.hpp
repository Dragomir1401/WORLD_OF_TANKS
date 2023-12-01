#pragma once

#include "windows.h"
#include <iostream>
#include <string>

class Audio
{
public:
    Audio(
        std::string const& audioPath,
        uint32_t deviceIndex = 0
    );
    ~Audio();
    void Play();
    void Stop();
    void Pause();
    void Kill();
    bool IsPlaying();

private:
    void Close();
    void Error(MCIERROR error);
    std::string CreateAudioOpenCommand(const std::string& audioPath);
    void CreateCommands();
    std::string audioPath_;
    uint32_t deviceIndex_;
    std::string playCommand_;
    std::string stopCommand_;
    std::string closeCommand_;
    std::string pauseCommand_;
    std::string statusCommand_;
};
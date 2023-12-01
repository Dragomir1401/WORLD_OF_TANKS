#include "Audio.hpp"

Audio::Audio(
    std::string const& audioPath,
    uint32_t deviceIndex
) :
    audioPath_(audioPath),
    deviceIndex_(deviceIndex)
{
    CreateCommands();
}


void Audio::CreateCommands()
{
	// Create command as play + wave + deviceIndex
	playCommand_ += "play wave";
	playCommand_ += std::to_string(deviceIndex_);

    // Create command as stop + wave + deviceIndex
    stopCommand_ += "stop wave";
    stopCommand_ += std::to_string(deviceIndex_);

    // Create command as close + wave + deviceIndex
    closeCommand_ += "close wave";
    closeCommand_ += std::to_string(deviceIndex_);

    // Create command as pause + wave + deviceIndex
    pauseCommand_ += "pause wave";
    pauseCommand_ += std::to_string(deviceIndex_);

    // Create command as status + wave + deviceIndex
    statusCommand_ += "status wave";
    statusCommand_ += std::to_string(deviceIndex_);
}


Audio::~Audio()
{
    Stop();
    Close();
}

void Audio::Play()
{
    if (!IsPlaying())
    {
        Kill();
    }

    MCIERROR error;

    // Send the command
    error = mciSendString(CreateAudioOpenCommand(audioPath_).c_str(), NULL, 0, NULL);
    if (error)
    {
        Error(error);
    }

    // Send the command to play the wave
    mciSendString(playCommand_.c_str(), NULL, 0, NULL);
    if (error)
    {
        Error(error);
    }
}

void Audio::Stop()
{
    // Stop the sound
    MCIERROR error;
    error = mciSendString(stopCommand_.c_str(), NULL, 0, NULL);
    if (error)
    {
        Error(error);
    }
}

void Audio::Close()
{
    MCIERROR error;
    error = mciSendString(closeCommand_.c_str(), NULL, 0, NULL);
    if (error)
    {
        Error(error);
    }
}

void Audio::Pause()
{
    MCIERROR error;
    error = mciSendString(pauseCommand_.c_str(), NULL, 0, NULL);
    if (error)
    {
        Error(error);
    }
}

void Audio::Kill()
{
    Stop();
    Close();
}

void Audio::Error(MCIERROR error)
{
    char errorMessage[256];
    mciGetErrorString(error, errorMessage, sizeof(errorMessage));
    //std::string prefixedErrorMessage = "[Audio] " + std::string(errorMessage);
    //std::cout << prefixedErrorMessage << std::endl;
}

bool Audio::IsPlaying()
{
    MCIERROR error;
    char buffer[128];

    // Command to check if the sound is still playing
    error = mciSendString(statusCommand_.c_str(), buffer, sizeof(buffer), 0);
    if (error)
    {
        Error(error);
    }
    else
    {
        if (!strncmp(buffer, "stopped", 7))
        {
            return false;
        }
    }
    return true;
}

std::string Audio::CreateAudioOpenCommand(const std::string& audioPath) {
    // Calculate the available space for the audio path, considering the command format
    constexpr size_t commandOverhead = sizeof("open \"\" type waveaudio alias wave ") - 1;
    constexpr size_t maxPathLength = 150 - commandOverhead;

    if (audioPath.length() > maxPathLength)
    {
        char errorMessage[256];
        snprintf(errorMessage, sizeof(errorMessage), "Audio path is too long: %s", audioPath.c_str());
        std::cout << errorMessage << std::endl;
    }

    char audioCommand[150];
    std::snprintf(audioCommand, sizeof(audioCommand), "open \"%s\" type waveaudio alias wave%s", audioPath.c_str(), std::to_string(deviceIndex_).c_str());
    return std::string(audioCommand);
}

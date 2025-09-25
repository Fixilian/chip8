#include "SdlBuzzer.h"

#include "base/Log.h"

namespace chip8 {


SdlBuzzer::SdlBuzzer()
    : audio_stream_(nullptr),
      audio_samples_(512),
      current_sine_sample_(0)
{}


bool SdlBuzzer::init() {
  SDL_AudioSpec spec;
  spec.channels = 1;
  spec.format = SDL_AUDIO_F32;
  spec.freq = 8000;

  audio_stream_ = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
  if (!audio_stream_) {
    Log::error("Couldn't create audio stream: {}", SDL_GetError());
    return false;
  }

  // SDL_OpenAudioDeviceStream starts the device paused. You have to tell it to start!
  SDL_ResumeAudioStreamDevice(audio_stream_);
  return true;
}


void SdlBuzzer::buzz()  {
  // 8000 float samples per second. Half of that
  const int minimum_audio = static_cast<int>((8000 * sizeof(float)) / 2);  
  if (SDL_GetAudioStreamQueued(audio_stream_) < minimum_audio) {
    // generate a 440Hz pure tone
    int len = static_cast<int>(audio_samples_.size());
    for (int i = 0; i < len; i += 1) {
      const int freq = 440;
      const float phase = current_sine_sample_ * freq / 8000.0f;
      audio_samples_[i] = SDL_sinf(phase * 2 * SDL_PI_F);
      current_sine_sample_ += 1;
    }

    // wrapping around to avoid floating-point errors
    current_sine_sample_ %= 8000;

    // feed the new data to the stream
    // It will queue at the end, and trickle out as the hardware needs more data
    SDL_PutAudioStreamData(audio_stream_, audio_samples_.data(), len);
  }
}


} // namespace chip8

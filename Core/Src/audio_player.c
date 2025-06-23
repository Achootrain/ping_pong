#include "audio_player.h"

extern I2S_HandleTypeDef hi2s3;

static volatile uint8_t isPlaying = 0;

void AudioPlayer_PlayPing(void)
{
    if (!isPlaying)
    {
        isPlaying = 1;
        HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t *)pingSound, pingSoundSize / 2);
    }
}

uint8_t AudioPlayer_IsPlaying(void)
{
    return isPlaying;
}

// Callback khi DMA truyền xong
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->Instance == SPI3)
    {
        isPlaying = 0;
    }
}

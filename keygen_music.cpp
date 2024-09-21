#include <stdio.h>
#include "pico/binary_info.h"
#include "pico/rand.h"
#include "pico/stdlib.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "m4p/m4p.h"
#include "pico_audio_i2s/include/pico/audio_i2s.h"
#include <math.h>

#include "tunes/crack.h"
#include "tunes/unreal.h"
#include "tunes/ghidapop.h"

static const unsigned int channels = 2;
static const unsigned int rate = 44100;
static const size_t buffer_size = 6000;

void set_binary_info() {
	// I2S
  	bi_decl(bi_1pin_with_name(26, "I2S BIT_CLK"))
  	bi_decl(bi_1pin_with_name(27, "I2S LR_CLK / W_CLK"))
  	bi_decl(bi_1pin_with_name(28, "I2S DATA	OUT"))
}

int main()
{
    stdio_init_all();
	set_binary_info();

	// load random song
	int songIndex = get_rand_32() % 3;
	switch (songIndex)
	{
		case 0:
			m4p_LoadFromData((uint8_t*)unreeeal_superhero_3_xm, unreeeal_superhero_3_xm_len, rate, buffer_size);
			break;
		case 1:
			m4p_LoadFromData((uint8_t*)ghidapop_xm, ghidapop_xm_len, rate, buffer_size);
			break;
		case 2:
			m4p_LoadFromData((uint8_t*)crack_xm, crack_xm_len, rate, buffer_size);
			break;
		default:
			m4p_LoadFromData((uint8_t*)crack_xm, crack_xm_len, rate, buffer_size);
			break;
	}

	m4p_PlaySong();


	audio_format_t format = {
		.sample_freq = rate,
		.format = AUDIO_BUFFER_FORMAT_PCM_S16,
		.channel_count = channels
	};

	audio_i2s_config_t config = {
		.data_pin = 28,
    	.clock_pin_base = 26,
    	.dma_channel = 0,
    	.pio_sm = 0
	};

	audio_buffer_format_t buffer_format = {
		.format = &format,
		.sample_stride = sizeof(int16_t) * channels
	};
	audio_buffer_pool_t *producer = audio_new_producer_pool(&buffer_format, 4, buffer_size);

	const struct audio_format *output_format = audio_i2s_setup(&format, &config);
	if (!output_format) {
        panic("PicoAudio: Unable to open audio device.\n");
    }

	audio_i2s_connect(producer);
	audio_i2s_set_enabled(true);

	uint32_t samplesGathered = 0;
	while (true)
	{
		printf("Generating samples\n");
		
		audio_buffer_t *ab = get_free_audio_buffer(producer, true);

		int16_t *buffer = (int16_t *) ab->buffer->bytes;
		m4p_GenerateSamples(buffer, buffer_size / sizeof(int16_t));
		ab->sample_count = buffer_size / sizeof(int16_t);
		queue_full_audio_buffer(producer, ab);

		samplesGathered += buffer_size;
		printf("Samples gathered: %d\n", samplesGathered);
	}

    return 0;
}

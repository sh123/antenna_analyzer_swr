#ifndef MAIN_H
#define MAIN_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <si5351.h>
#include <Rotary.h>
#include <SimpleTimer.h>
#include "Wire.h"

// 25 / 27 MHz crystals
#define XTAL_CUSTOM_FREQ   27000000

#define BANDS_CNT          14

// analog read pins
#define PIN_SWR_FWD        0
#define PIN_SWR_RFL        1

// rotary encoder pins
#define PIN_ROTARY_CLK     11
#define PIN_ROTARY_DATA    12
#define PIN_ROTARY_BTN     13

// screen pins
#define PIN_PCD_CLK        7
#define PIN_PCD_DIN        6
#define PIN_PCD_DC         5
#define PIN_PCD_CS         4
#define PIN_PCD_RST        3

#define SWR_MAX            32
#define SWR_LIST_SIZE      84
#define SWR_SCREEN_HEIGHT  48
#define SWR_SCREEN_CHAR    8
#define SWR_GRAPH_HEIGHT   (SWR_SCREEN_HEIGHT - SWR_SCREEN_CHAR)
#define SWR_GRAPH_CROP     6

#define FREQ_STEP_INC      2500000ULL
#define FREQ_STEP_MAX      100000000ULL
#define FREQ_MAX           20000000000ULL
#define FREQ_DELAY_MS      5

#define TO_KHZ(freq)       (freq / (1000ULL * SI5351_FREQ_MULT))
#define VALID_RANGE(freq)  (freq < FREQ_MAX && !(freq > 14810000000ULL && freq < 15000000000ULL))

enum MAIN_SCREEN_STATE {
  S_MAIN_SCREEN = 0,
  S_GRAPH_MANUAL,
  S_GRAPH_AUTOMATIC,
  S_SETTINGS
};

void generator_initialize();
void generator_set_frequency(uint64_t freq);

void swr_list_clear();
void swr_list_shift_right();
void swr_list_shift_left();
void swr_list_store_center(double swr);
void swr_list_draw();
void swr_list_sweep_and_fill();
void swr_list_grid_draw();

unsigned int swr_screen_normalize(double swr);
void swr_update_minimum_swr(double swr, long freq_khz);
double swr_read();
double swr_calculate(int fwd, int rfl);

void band_select_next();
void band_select(int index);
void band_rotate_frequency(int dir);
void band_rotate_step(int dir);

void screen_select_next();

void process_rotary();
void process_rotary_button();
void process_display_swr();

#endif // MAIN_H
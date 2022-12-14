#include "sdcard.h"
#include "main.h"

#include <Arduino.h>
#include <SD.h>
#include <FS.h>

sdcard sdcard::instance;

bool sdcard::pre_begin()
{
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SDMMC_CLK, SDMMC_D0, SDMMC_CMD);

    return mount();
}

void sdcard::begin()
{
}

bool sdcard::mount()
{
    if (!SD.begin(SD_CS))
    {
        log_e("Failed to initialize SD Card");
        return false;
    }

    const auto card_type = SD.cardType();
    if (card_type == CARD_NONE)
    {
        log_e("No SD card");
        return false;
    }
    else
    {
        log_i("SD card type :%d", card_type);
        log_i("SD Card Size: %llu MB", SD.cardSize() / (1024 * 1024));
    }

    return true;
}

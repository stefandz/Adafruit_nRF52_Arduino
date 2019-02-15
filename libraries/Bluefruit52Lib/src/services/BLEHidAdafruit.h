/**************************************************************************/
/*!
    @file     BLEHidAdafruit.h
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2018, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#ifndef BLEHIDADAFRUIT_H_
#define BLEHIDADAFRUIT_H_

#include "bluefruit_common.h"

#include "BLECharacteristic.h"
#include "BLEHidGeneric.h"
#include "BLEService.h"


class BLEHidAdafruit : public BLEHidGeneric
{
  public:
    /*--------- Callback Signatures ----------*/
    typedef void (*kbd_led_cb_t)  (uint8_t leds_bitmap);

    BLEHidAdafruit(void);

    virtual err_t begin(void);

    // Keyboard
    bool keyboardReport(hid_keyboard_report_t* report);
    bool keyboardReport(uint8_t modifier, uint8_t keycode[6]);
    bool keyboardReport(uint8_t modifier, uint8_t keycode0, uint8_t keycode1=0, uint8_t keycode2=0, uint8_t keycode3=0, uint8_t keycode4=0, uint8_t keycode5=0);

    void setKeyboardLedCallback(kbd_led_cb_t fp);

    bool keyPress(char ch);
    bool keyRelease(void);
    bool keySequence(const char* str, int interal=5);

    // Consumer Media Keys
    bool consumerReport(uint16_t usage_code);
    bool consumerKeyPress(uint16_t usage_code);
    bool consumerKeyRelease(void);

    // Mouse
    bool mouseReport(hid_mouse_report_t* report);
    bool mouseReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel=0, int8_t pan=0);

    bool mouseButtonPress(uint8_t buttons);
    bool mouseButtonRelease(void);

    bool mouseMove(int8_t x, int8_t y);
    bool mouseScroll(int8_t scroll);
    bool mousePan(int8_t pan);

  protected:
    uint8_t _mse_buttons;
    kbd_led_cb_t _kbd_led_cb;

    friend void blehid_ada_keyboard_output_cb(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len, uint16_t offset);
};

#endif /* BLEHIDADAFRUIT_H_ */

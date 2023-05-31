# RP2040 learning projects

## How to use
Install the Raspberry Pi Pico C/C++ SDK by following their official documentation and/or any online help you may find. God help you if it doesn't "just work".

After this, make sure you have the PICO\_SDK\_PATH set to the absolute path of your Pico SDK.

Then you git clone this repo, possibly into your pico directory you have.

Copy the known to be working (On my system[TM]) ./tutorial directory, remove the contents of the build directory inside of your copy of the ./tutorial directory. 

Stand inside of your copy of the ./tutorial directory and run "code .". Allow vscode to choose which build system you use, which is arm_none_eabi or whatever. 

Build your project once. And then code away.

(if using picoprobe (also my system verified YMMV)
To upload your shit you run the command [openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -s tcl -c "adapter speed 5000" -c "program ./build/blink.elf verify reset exit"], then run the same command but without everything past and including [-c] to start a server onto which you can debug.

Congrats, you're done.

## About the projects

### PWMTest
This test is my first blinky essencially. Its a simple and crude program to softly blink the on board LED of the Pico. I also started trying my hand at IRQ handling, but that has its own project.

### IRQTest
Interrupts. The PWM functionality has an IRQ trigger for when the counter wraps to 0, which I use to control the brightness of the pwm. Basically ripped from the Pico Examples. Then I hooked up a button to the pico, using a GPIO pullup, and an edge triggered IRQ, with some crude software debouncing worked in. REMEMBER: Use a resistor between button and GND!!! Don't short your shit, shorty.

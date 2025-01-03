# CYD Crypto Ticker

Just a small project to display current and historic crypto prices on a **C**heap **Y**ellow **D**isplay.
Since it worked nicely as a desktop station, also added a weather display and current time.
The variant I'm working with is a JC2432W328C, but it should be usable on other variants with minimal changes.

https://github.com/user-attachments/assets/5a5a0f53-603e-4157-b374-5f24e80d367c

(Video not 100% representative, didn't manage to run an emulator with Arduino libraries, so this was just recorded on figma)

## Inspiration

Some inspiration (and Binance API code) taken from [https://github.com/nishad2m8/BTC-Ticker](https://github.com/nishad2m8/BTC-Ticker), be sure to check it out.

## Case
![Screenshot_20250103_121223](https://github.com/user-attachments/assets/deb33430-7cb8-426e-a9d8-ab88f5330d6b)

The case is a slight remix from [https://www.printables.com/model/645166-esp32-28inch-touch-ips-cyd-lcd-screen-case](https://www.printables.com/model/645166-esp32-28inch-touch-ips-cyd-lcd-screen-case/files), to adjust to my variant of the CYD, and integrate the stand directly in the back of the case.


## Improvements I might work on

- Loading screen
- Having one screen alive at a time, instead of all loaded at boot time
- Clean code (first time using c++ and lvgl so it's super messy) 
- Better settings screen (scrolling screen in view so the keyboard isn't in the way)

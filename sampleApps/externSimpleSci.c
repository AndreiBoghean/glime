#include "compat.h"

/*
the gravitational constant (G) = 6.67259*10^-11
the speed of light (c) = 2,99792458x10^8
the avogadro constant (Na) = 6.0221367*10^23
the gas constant (R) = 8.314510
the boltzmann constant (k) = 1.380658*10^-23
the stefan-boltzmann constant = 5.67051*10^-8

secondary to that, you also sometimes an order of magnitude reference: https://www.techtarget.com/rms/onlineimages/order_of_magnitude_with_powers_of_10-f.png
0.000000001 = 10^-9
0.000001 = 10^-6
0.001 = 10^-3
0.01 = 10^-2
0.1 = 10^-1
*/

void show_slide1()
{
    clear_screen();
	place_label("0.000000001 = 10^-9", 120, 10);
	place_label("0.000001 = 10^-6   ", 120, 40);
	place_label("0.001 = 10^-3      ", 120, 60);
	place_label("0.01 = 10^-2       ", 120, 80);
	place_label("0.1 = 10^-1        ", 120, 100);
}

void show_slide2()
{
    clear_screen();
	place_label("G = 6.67259*10^-11", 120, 10);
	place_label("c = 2,99792458x10^8", 120, 40);
	place_label("Na = 6.0221367*10^23", 120, 60);
	place_label("R = 8.314510", 120, 80);
	place_label("k = 1.380658*10^-23", 120, 100);
	place_label("stefan-boltzmann constant = 5.67051*10^-8  ", 120, 120);
}

int swipeHandler(enum globalTouchEvent e)
{
	if (e == globalTouchEvent::SwipeDown)
	{ show_slide1(); return 1; }
	else if (e == globalTouchEvent::SwipeUp)
	{ show_slide2(); return 1; }

	return 0;
}

int extern_main()
{
	set_colours(0xFFFFFF, 0x000000);
	show_slide1();
	register_global_eventListener(swipeHandler);
	return 0;
}


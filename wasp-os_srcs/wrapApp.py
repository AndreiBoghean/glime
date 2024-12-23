# SPDX-License-Identifier: MY-LICENSE
# Copyright (C) YEAR(S), AUTHOR

import wasp
import gateway


def rgb888_to_rgb565(red8, green8, blue8):
    # Convert 8-bit red to 5-bit red.
    red5 = round(red8 / 255 * 31)
    # Convert 8-bit green to 6-bit green.
    green6 = round(green8 / 255 * 63)
    # Convert 8-bit blue to 5-bit blue.
    blue5 = round(blue8 / 255 * 31)

    # Shift the red value to the left by 11 bits.
    red5_shifted = red5 << 11
    # Shift the green value to the left by 5 bits.
    green6_shifted = green6 << 5

    # Combine the red, green, and blue values.
    rgb565 = red5_shifted | green6_shifted | blue5

    return rgb565

def delegate(*_args):
    operation = _args[0]
    args = _args[1:]
    print("delag called for", operation, "with args: '" + str(args) + "'")

    if operation == "show_int":
        wasp.watch.drawable.string("Sh:" + str(args[0]), 0, 108, width=240)
    elif operation == "set_colours":
        parsed_fg = rgb888_to_rgb565(args[0] >> 8*2, (args[0] >> 8) & 0xFF, args[0] & 0xFF)
        parsed_bg = rgb888_to_rgb565(args[1] >> 8*2, (args[1] >> 8) & 0xFF, args[1] & 0xFF)
        wasp.watch.drawable.set_color(parsed_fg, parsed_bg)
    elif operation == "place_label":
        wasp.watch.drawable.string(str(args[0]), args[1], args[2])
    elif operation == "set_brightness":
        wasp.system.brightness = args[0]+1
    elif operation == "clear_screen":
        wasp.watch.drawable.fill()

class WrapApp():
    """A hello world application for wasp-os."""
    NAME = "Wrap"

    def __init__(self):
        pass

    def foreground(self):
        self._draw()
        wasp.system.request_event(wasp.EventMask.TOUCH | wasp.EventMask.SWIPE_LEFTRIGHT)

    def _draw(self):
        draw = wasp.watch.drawable
        draw.fill()
        # test(draw)
        # test2(draw)

        # external.exern_main_handler(lambda : draw.string("Hello, world!", 0, 108, width=240) )
        # gateway.handle_main(draw.string)
        gateway.handle_main(delegate)

    
    def touch(self, event):
        print("we've been touched")
        wasp.watch.drawable.string(gateway.touch_handler(0), 0, 108)

        
    def swipe(self, event):
        print("we've been swiped")
        # get an ID representation for the tocuh event, which we pass to our function,
        # which converts it to a C enum and then gives it to the user-provided event listener.
        wasp.watch.drawable.string(gateway.touch_handler({wasp.EventType.LEFT: 3, wasp.EventType.RIGHT: 4}.get(event[0], -1)), 0, 108)

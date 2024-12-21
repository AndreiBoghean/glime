# SPDX-License-Identifier: MY-LICENSE
# Copyright (C) YEAR(S), AUTHOR

import wasp
import gateway

# def delegate(operation, args):
def delegate(*_args):
    operation = _args[0]
    args = _args[1:]
    print("delag called for", operation, "with args: '" + str(args) + "'")

    if operation == "show_int":
        wasp.watch.drawable.string("Sh:" + str(args[0]), 0, 108, width=240)
    else:
        wasp.watch.drawable.string("no Sh", 0, 108, width=240)

class WrapApp():
    """A hello world application for wasp-os."""
    NAME = "Wrap"

    def __init__(self):
        pass

    def foreground(self):
        self._draw()

    def _draw(self):
        draw = wasp.watch.drawable
        draw.fill()
        # test(draw)
        # test2(draw)

        # external.exern_main_handler(lambda : draw.string("Hello, world!", 0, 108, width=240) )
        # gateway.handle_main(draw.string)
        gateway.handle_main(delegate)

        

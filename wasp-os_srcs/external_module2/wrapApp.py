# SPDX-License-Identifier: MY-LICENSE
# Copyright (C) YEAR(S), AUTHOR

import wasp

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

        # external.exern_main_handler(lambda : draw.string("Hello, world!", 0, 108, width=240) )
        exern_main_handler(lambda x: draw.string("Hello, world!, " + x, 0, 108, width=240) )

        

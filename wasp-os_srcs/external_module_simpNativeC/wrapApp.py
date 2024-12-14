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

        draw.string("num" + get_num(), 0, 108, width=240)

        

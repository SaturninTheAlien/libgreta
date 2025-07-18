#!/usr/bin/env python3

import py_greta as pk2

def PigTest():
    sprite = pk2.load_json_sprite("dino.spr2")

    for i in range(0, len(sprite.ai)):
        print("{} -> {}".format(i, sprite.ai[i]))

    print(sprite.ammo1)
    print(sprite.ammo2)
    print(sprite.bonus)
    print(sprite.transformation)
    print(sprite.attack1_offset)
    print(sprite.attack2_offset)

if __name__ == "__main__":
    PigTest()
    
#!/usr/bin/python3

import json


# python3 json-to-c.py | pbc
f = open("layout.json")
data = f.read()
f.close()
layout = json.loads(data)

for i, layer in enumerate(layout["layers"]):
    l = str(layer)
    l = l.replace("'", "")
    l = l.replace("[", "LAYOUT(")
    l = l.replace("]", ")")
    print("    [_LAYER{}] = {},".format(i,l))

#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author: 8023
# @Date:   2016-04-20 15:23:14
# @Last Modified by:   8023
# @Last Modified time: 2016-04-20 21:36:05
import os
import binascii

regulation = {};
path = './unprocessed/'

with open('regulation.ini', 'r') as file:
    for line in file.readlines():
        line = line.strip()
        line = line.split(' ')
        regulation[line[0]] = line[1]

for filename in os.listdir(path):
    with open(path + filename, 'rb') as file:
        data = file.read(3)
        data = binascii.b2a_hex(data)
        data = data.decode('utf-8')
        data = data.upper()
        file.close()
        if data in regulation:
            newname = filename.split('.')
            newname[-1] = regulation[data]
            newname = list(map(lambda x: '.' + x, newname))
            newname[0] = newname[0][1:]
            newname = ''.join(newname)
            os.rename(path + filename, path + newname)




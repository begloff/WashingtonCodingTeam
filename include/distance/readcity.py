#!/usr/bin/env python3

import requests
import re

origin = "South+Bend,+IN"
destin = "Elkhart,+IN"


out = open('input.txt','w')
first = open('origin.txt')

for line1 in first:

    origin = line1.replace(" ","+")
    second = open('destin.txt')

    for line2 in second:
        destin = line2.replace(" ","+")

        URL = f"https://www.travelmath.com/drive-distance/from/{origin}/to/{destin}"

        if(origin != destin):
            obj = requests.get(URL)
            search = re.findall(r'The total driving distance .* miles</strong>', str(obj.content))

            miles = re.findall(r'[0-9].*[0-9]',search[0])
            miles = int( miles[0].replace(',','') )
            out.write(f"{line1.split(',')[0]},{line2.split(',')[0]},{miles}\n")

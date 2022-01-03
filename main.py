import random

import argparse
parser = argparse.ArgumentParser( 
    description='MPLAB CLI for automating PIC build processeses') 
parser.add_argument("-p", 
   "--produce", 
    help="Build main project", action="store_true")
args = parser.parse_args()
if args.produce:
    n = random.randint(0, 30)    
    print(n)
  # Kod för att producera ny enhet mot Azure

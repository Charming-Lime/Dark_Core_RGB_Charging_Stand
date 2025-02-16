# Corsair Dark Core RGB Pro SE Wireless Charging Stand 
A RGB wireless charging stand for the Corsair Dark Core RGB Pro SE.

Designed to be printed with a single manual filament swap for the diffuser ring. 

Printed in Polymaker PolyTerra charcoal matte PLA and SUNLU transparent PLA. 
# Materials
Links are for example purposes and should be generic if you can find the right physical size.

## Required 
* Generic Wireless charger PCB, there are many listings on amazon and aliexpress with the same dimentions that will work (https://www.amazon.com/dp/B0BTHXKM91?ref=ppx_yo2ov_dt_b_fed_asin_title](https://www.amazon.com/dp/B073W7P5T8?ref=ppx_yo2ov_dt_b_fed_asin_title))
* RP2040-zero (https://www.amazon.com/RP2040-Zero-High-Performance-Microcontroller-Castellated-Applications/dp/B09KZPCNPL?th=1)
* USB C Fast Charge Decoy Trigger PCB set at 5V (https://www.amazon.com/dp/B0BTHXKM91?ref=ppx_yo2ov_dt_b_fed_asin_title)
* 5v WS2821 RGB strip light (https://www.amazon.com/dp/B0CFTP3S41?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* Wire, heatshrink, soldering equipment
* 4x m3x16 self taping screws
* Stick on rubber feet (https://www.amazon.com/dp/B0BLN4TCPT?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_3)

Most of the compenents should be generic enough that they the exact item matters, but i have included exactly what i used anyway. Room is tight and most components are sized to fit snuggly.

## Optional
* 10k and 20k resistor for voltage divider.
  *  Required if you want the LED on the stand to pulse when the mouse is charging.
 
# Directions
## Printing
The charging stand is printed in 3 pices, stand, base, and cover, i used 0.16 layer height 
Print orentaion should be as imported into the slicer, upright. The base and diffuser get imported and sliced togeather, with a pause and filament swap at ~11.50mm.
Print with suports on for the holder and base. Set your suport settings so the only part with supports is the cutout and screw holes. You *may* be able to get away without it depending on how good your printer is at bridging.

 ### Base
The part where the magic happons.
Tranparent filament works the best for the diffuser, but a white filament should work. 
Import both the base and the diffuser and slice them togeather. Insert a pause command or a filament swap at 11.50mm. Be sure to thourghly purge and clean your nozzle. If your slicer suports it change the settings for the diffuser to be no infill, 2 perimeters, and 0.2 layer height, but feel free to exparament. You are trying to strike a ballence between seeing the individual LEDs and letting light though. This 
will give you the most even difusing.

 ##Wireing
Wire the PCBs togeather as shown in the schmatic.You will need to locate the 5V and GND pins on the charing circut board as well as the charging sense pin. In my case it was high (5v) when not charging and dropped while charging. The charging sense circuit is defonetly a hack, but it works. I have included a anotated photo of which pin drops down from 5v when charging, but it should be verified with a multimeter before soldering. Keep extra wirelength to a minamum as space is tight. Be mindfull of wire guages as well, the charging curcuit can pull 2A and the LEDs can draw another 1A. You will need to cut the 
wireless charging pad wires and likly legthen them before attaching the PCB and resoldering it. I used hot glue to mount all of the PCBs and add insolation. 

 ![alt text]( https://raw.githubusercontent.com/rab1515/darkcorestand/refs/heads/main/photos/714dquSzSGL._AC_SL1500_.jpg?token=GHSAT0AAAAAAC4LVSNIVHFKJ3MZPGIQR55SZ5P5YPQ)
 ![alt text](  https://raw.githubusercontent.com/rab1515/darkcorestand/refs/heads/main/photos/Screenshot_20250214_202349.png?token=GHSAT0AAAAAAC4LVSNILKCDSAWEAOU6WILEZ5P5Z6Q)
 

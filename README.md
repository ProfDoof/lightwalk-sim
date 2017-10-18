# Lightwalk simulator

## Purpose

This code serves as a simulator for effects that run on lightwalk in the Quad.  Use it to test out your code before deploying.

## Requirements

SDL2. For example:
- Download the .dmg from  ```https://libsdl.org/download-2.0.php```
- Drag "SDL2.framework" into /Library/Frameworks

## Running the simulator

- Place your Shimmer.cpp in /lib. 
- Edit lightwalk-sim.cpp and include lib/Shimmer.cpp, then in the loop that builds nodes:

```
 for (int ee = 0; ee < SIM_NODES; ee++)
    {
        // Bubbles *e = new Bubbles(ee, 0, 200, 0,200);
        // Shimmer *e = new Shimmer(ee, 0, rgb_r, rgb_g, rgb_b, speed);
        // AcidRain *e = new AcidRain(ee, 0, rgb_r, rgb_g, rgb_b, speed);
        // RainbowRain *e = new RainbowRain(ee, 0);
        // SplishSplash e = new SplishSplash(0, rgb_r, rgb_g, rgb_b, ee * 30, speed);

        Shimmer *e = new Shimmer(ee, 0, rgb_r, rgb_g, rgb_b);

        nodes[ee] = new Node(ee, (ee * 10), e, 0, lengths);
        // nodes[ee] = new Node(ee, (ee * 10), e, 37, lengths);
    }
```

Now compile for your platform.
Mac OS X seems happy with:
```
clang++ -std=c++11 -stdlib=libc++ -o m -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -framework Cocoa lightwalk-sim.cpp
```

*Note: If you are on Mac OS X High Sierra, and/or are getting the following error:*
```
ld: framework not found SDL2
```
*Try running the following compile statement instead:*
```
clang++ -std=c++11 -stdlib=libc++ -o m -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -framework Cocoa lightwalk-sim.cpp
```

Run lightwalk-sim
```
./m
./m --time 30  (gives you 30 seconds to observe things or click around on interactive effects)
./m --speed 10  (some of the effects take a velocity from 1 - 10)
./m -r 0 -g 250 -b 0  (some effects take a color, so you can send in RGB values)
./m --pizza (leaning tower of... get it... leaning...)
```

## Notes

Two kinds of effects, Standard and Interactive.

## Standard Effects

- WaveUp
- WaveDown
- WaveSide
- Breathe
- Starfield
- RainbowRain
- AcidRain
- Shimmer (Cole Spears)
- Smokescreen (Cole Spears)

## Interactive Effects

- Bubbles
- Tug Of War (Cole Spears)
- Power


When you left-click more than once on a node, the effect is added again so you can have several bubbles
running at the same place.  Looks messed-up.  
Right-click to remove effects at that node, like the person stepped away.

## Next Steps

- [ ] Load effects via command line option instead of uncomment.

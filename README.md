# Lightwalk simulator

## Purpose

This code serves as a simulator for effects that run on lightwalk in the Quad.  Use it to test out your code before deploying.

## Requirements

SDL2. For example:

```
brew install sdl2
```

## Running the simulator

- Place your RainbowRain.cpp in /lib. 
- Edit lightwalk-sim.cpp and include lib/RainbowRain.cpp, then in the loop that builds nodes:

```
    for (int ee = 0; ee < SIM_NODES; ee++)
    {
        // Bubbles e = new Bubbles(ee, 0, 230, 0, 0)
        // AcidRain e = new AcidRain(ee, 0, 255, 0, 0, 3);
        // RainbowRain e = new RainbowRain(ee, 0);
        // SplishSplash e = new SplishSplash(0, 0, 200, 0, ee * 30, 3);

        RainbowRain *e = new RainbowRain(ee, 0);
        nodes[ee] = new Node(ee, (ee * 45), e, 0, lengths);
        // nodes[ee] = new Node(ee, (ee * 45), e, 37, lengths);
    }
```

Now compile for your platform.
Mac OS X seems happy with:
```
clang++ -std=c++11 -stdlib=libc++ -o m -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -framework Cocoa lightwalk-sim.cpp
```


Run lightwalk-sim
```
./m
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

## Interactive Effects

- Bubbles

When you left-click more than once on a node, the effect is added again so you can have several bubbles
running at the same place.  Looks messed-up.  
Right-click to remove effects at that node, like the person stepped away.

## Next Steps

- [ ] Load effects via command line option instead of uncomment.
- [x] reed lengths random - not all exactly 37 pixels. Use the lengths[] array.
- [x] have reeds that aren't all straight up and down so they're more realistic visually.
- [x] Simulate all 35 nodes. (14 fit ok on this old Mac Book Pro).
- [x] Interactive effects.  Left-mouse-click for "here" and Right-mouse-click for "gone".
- [x] Use real time instead of fake integer debug time.

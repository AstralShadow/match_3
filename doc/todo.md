# Add blocked flag to some tiles
These are tiles that won't be moveable by the player.


# Mark tiles for destruction and count score once
Current algorithm is a bit heavier than it should be.

I might need to add a flag to mark the tile as "being removed",
if i haven't added one yet.


# Constantly drain the score bars
Execute different events when they fill up or get empty.


# Use VSync
Provides constant framerate and limits system resource usage.



# Ignore skipped frames when not on focus (optimization)
That's not really prioritized. Might as well not do it, because:
 * As a desktop game, VSync should limit system usage enough.
 * Browsers increase the delay between frames when not focused.


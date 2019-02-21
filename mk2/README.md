# README

Say you have a plane paved with hexagons.  
How you want to have a path through it, a [space-filling curve][space filling].  
It has to start somewhere and stop somewhere.  
And you want it to draw hexagons.  
Even more, you want it to preserve [locality][locality hashing].  
And maybe a few aesthetic choices.

## Development overview

I use C++17.  
I use `std::pair` quite a bit (defined in `<utility>`).

I might use `time_filling.l.hpp` one day.

### Things to prove

* Why an itinerary always exists (cf. `get_itinerary`)
* Why rounding to convert a Hexagon to a size higher works with
  the normal distance and not the HexPoint specific distance (cf. `hexagon`)

### Files

* `utils.hpp`: Currently only defines `cr <>`
* `point`: Defines Point, Coord, and HexPoint and their operations
* `hexagon`: Defines Hexagon (et al.) which is the main data structure
  Also defines Node.
* `hexagon_ops`: Functions which operate on hexagons
* `itinerary`: Defines Itinerary and Endpoints, which are used for the path
* `rng`: Implements the (header) global RNG
* `time_filling`: General logic

[space filling]: https://en.wikipedia.org/wiki/Space-filling_curve
[locality hashing]: https://en.wikipedia.org/wiki/Locality-sensitive_hashing#Locality-preserving_hashing

# What is Blue Noise?

Blue noise are numbers that are randomized, but roughly evenly spaced, like the below.
![MakeNumberline_BestCandidate.png](../output/_1d/samples/blue_noise/MakeNumberline_BestCandidate.png)  

This is in contrast to regular old random numbers (white noise), which can clump together and leave empty holes.
![UniformRandom](../output/_1d/samples/uniform_random/MakeNumberline_UniformRandom.png)  

For a non graphics oriented explanation of why that's useful, check this out: https://blog.demofox.org/2018/01/30/what-the-heck-is-blue-noise/

It's called blue noise because if you do a DFT to look at the frequency content, it's missing (or has attenuated) low frequencies.

![BestCandidate](../output/_1d/samples/blue_noise/DFT_BestCandidate.png)  

For graphics, blue noise has some interesting properties:
* pro - gives the least aliasing
* pro - very easy on the eyes and looks a lot better than other noise patterns with the same amount of error
* pro - has good coverage over the sampling space, so has good starting error
* pro - it leaves high frequency noise, which is more easily removed with a less powerful low pass filter (aka blur) compared to other noise patterns
* pro - the error pattern it leaves is roughly evenly spaced.  It is as though error diffusion has happened, even though you don't have to explicitly do error diffusion (great for real time graphics)
* con - integrates at the same rate as white noise (slowly), even though it starts at a lower error.
* con - can be computationally expensive to generate

All this means that in general, if you can only afford a low sample count, and your result isn't going to converge all the way, you are best off using blue noise so that the remaining error is most pleasing to the eye and least noticeable.

If you have the benefit of a higher sample count, and your result is going to be allowed to fully converge, other sampling strategies are probably more appropriate.

Since I'm a real time graphics person, blue noise is very much my friend.  It allows me to get nice looking results with a very low sample count.

It's amazing what blue noise can accomplish at low sample counts, when doing apples to apples comparisons against other sampling strategies - most strikingly of all, compared to white noise which really hurts to look at in comparison.

When there are concrete examples in Sample Zoo to show I'll put them here (when the dithering section is done, or if any shadows or AO type tests show up).  In the meantime, here's a blog post that shows some examples: https://blog.demofox.org/2017/10/31/animating-noise-for-integration-over-time/

Blue noise sample points tend to tile well, even if they weren't designed to tile.  Their lack of low frequency content makes it so there are no larger structures to catch your eye.

Many things in our world - natural and man made - are distributed in a blue noise pattern.  This includes the photoreceptors in your eyes, as well as foam in a tempurpedic matress (something which is unique to their process of making matresses, and patented).  "Randomized but roughly evenly spaced" turns out to be a really common requirement of things, and in fact, if you have something in a game that doesn't feel random enough ("hey, i just fought one of those guys! This isn't random at all!"), the real randomness you might be looking for is blue noise, which doesn't repeat in the same way white noise does.  Despite this, it's still randomized and unpredictable.

Beyond graphics, I've heard of game designers using blue noise for things like loot drops or boss encountered.  White noise has too much clumping and repeating.  Blue noise gives you something different every time and so feels more random.  In that context, blue noise is a bit like a shuffle.

## Links:

Blue noise links from Mikkel Gjoel (https://twitter.com/pixelmager) of INSIDE fame  
https://gist.github.com/pixelmager/5d25fa32987273b9608a2d2c6cc74bfa  
https://blog.demofox.org/2018/01/30/what-the-heck-is-blue-noise/ - What the heck is blue noise?  
https://blog.demofox.org/2018/08/07/tiled-blue-noise/ - Tiled blue noise  
https://blog.demofox.org/2018/08/12/not-all-blue-noise-is-created-equal/ - Not All Blue Noise is Created Equal  
https://www.princeton.edu/news/2014/02/24/eye-chicken-new-state-matter-comes-view - In the eye of a chicken, a new state of matter comes into view  
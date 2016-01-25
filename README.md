<snippet>
  <content>
# Multithreaded Mandelbrot Generation
  Mandelbrot fractal set generated and timed with a single thread up to eight threads. The Mandelbrot set is split up split up evenly 
  by rows between all the threads. Average time is found after the set is generated fives times for each set of threads.
  Standard deviation is found after the average is calculated. Speed up and efficiency is calculted for each set generated with
  more than 1 thread, the speed up and efficiency is the time improvement of using multiple threads vs a single thread.
## Usage
This was written as a homework assignment for CS 3100: Operating Systems and Concurrency



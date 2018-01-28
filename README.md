# Taxi Simulation using one process

This is a C program that simulates a taxi call terminal, similar to this [project of mine](https://github.com/vostertag/taxi-simulation-multi-process), except we are only using one process here.

## Index

[1. How to use](#how-to-us)  
[2. What does it do](#what-does-it-do)  
[3. Create new demands](#create-new-demands)  

## How to use

Go to the "src" folder with a terminal and execute the make command:

```
make
```

To run the code, use this command, with N being the number of taxis you would like to have (I advise using 2 to 4):

```
.\output N
```

## What does it do

Once you ran the code with N taxis, the program will read the demands stored in the "demandes.dat" file, put them in a queue and then the taxis will take the calls. The results are displayed in the terminal, telling us which taxi took which call and whether or not the client had to wait... 

![Alt Text](https://image.ibb.co/fJKkOb/Screenshot_from_2018_01_28_16_05_28.jpg)

## Create new demands

The demands are read in the "src/data/demandes.dat" file:

![Alt Text](https://image.ibb.co/heVEzG/demandes.jpg)

Each demand must be written like this:  
Number of seconds until next client  
Client Name ;Number of seconds it will take to take this call

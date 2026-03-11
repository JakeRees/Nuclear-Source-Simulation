#Nuclear Source Simulation
Includes a source class and detector class, through which simple nuclear decay simulations can be ran. An example test simulation is included in simulation.cpp, with input from a config file.

##Development Timeline

###Disclosure of Delegation to Generative AI:

The authors declare the use of generative AI in the research and writing process. According to the GAIDeT taxonomy (2025), the following tasks were delegated to GAI tools under full human supervision:

- Creation of algorithms for data analysis

The GAI tool used was: Claude Sonnet 4.6.
Responsibility for the final manuscript lies entirely with the authors.
GAI tools are not listed as authors and do not bear responsibility for the final outcomes.
Declaration submitted by: Jake Rees

Additional note: I used GAI to aid in the creation of the days_from_epoch function in the source class. Formally for help with creating an algorithm which works for any year and accounts for all calendar peculiarities. The code was written by me, the algorithm was generated.

###Description of development

**Note: Sources given in slide includes Co-92, which isn't a real isotope of Cobalt, so I changed this to Co-60, a real isotope used in nuclear physics.**

First created a skeleton source and detector class. I then, using the help of claude, created an algorithm to calculate the age in seconds of a given source. I then filled in the getters and setters for both classes, and improved the get_activity method to calculate the activity at a given time using the inverse exponential formula and the half life.

I added input validation to the setter methods for source, and used the methods in the class constructor to avoid duplicating the validation code. The random count function added to the detector class was originally a calculated using a square distribution around the mean value, generating a random number of counts over a given time. I changed this to use a Poisson distribution to better model real nuclear physics. I overloaded this function, so that if no time is given it defaults to a time period of 1 second.

The config file used was a simple text file with space separators for each value and an identifier to determine source from detector. To read this file I added a function to the main cpp file, which also validates input from the config file to ensure it is as expected. Initially had trouble with creating sources with the same ids, but found this was because every line of the config file it read it created and destroyed a local copy of a source object. This meant it removed the id from the set of used_ids within the destructor each time, causing the used_ids set to always be empty. This was fixed by bypassing creating a local copy using vector.emplace_back() instead of vector.push_back().

##How to use config file

Values in each line are separated either by a space " " or a comma ","
Lines in the config file are identified by the type identifier string located in the first column:
SOURCE - creates a source object with values: ID Activity HalfLife AquiryDate Name
DETECTOR - creates a detector object with values: Name
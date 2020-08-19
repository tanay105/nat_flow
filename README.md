[![Build Status](https://travis-ci.com/tanay105/nat_flow.svg?branch=master)](https://travis-ci.com/tanay105/nat_flow)

# nat_flow
Search for flows from corresponding NAT mappings

The current implementation uses a hash map data structure to search for flow data among the corresponding NAT mappings given to us.

Time complexity for current implementation:
Since the map in C++ has an internal implementation using balanced binary search tree. The Time complexity of insertion is O(log(n)) where n is the number of NAT mappings. For an insertion (plus some time for rebalancing) and the time complexity of search is O(log(n)) as well. This will be consistent no matter what how much data we fill in the map.

Design ideas for optimisation:

1. One implementaiton could be by using Trie data structure:

The time complexity of search and insert in that case would be O(n*(average_tuple_length)), where n is the number of NAT mappings. We store the value of a tuple to mapping to other tuple in the end node of the trie data structure.

2. One other way in which we could save space is by using a compact Trie data structure.

Currently this repository does not have any unit testing code for the project, because of the one hour time contraint.

If given more time, I would add a Makefile and unit test code to test the main coding logic in nat_flow.cpp file.

Also, the code does not handle any errorneous tuple present in both NAT and flow files. Thus, error handling is one of the next improvement I would want to focus on. This would improve the reliablility of the code in the parsing and the searching logic.

One of the interesting coding/desgin logic that I would want to point to is about the use of a map data structure on pairs of strings, i.e. the map data structure would map a key which is actually a pair of ip and port to a corresponding value, which is a pair of ip and port (both of these ip and port are strings when stored).

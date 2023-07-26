# Travelling-Salesman

The Traveling Salesman Problem (TSP) is a well known optimization problem in the field of computer science. It is a well-known NP-hard problem, which means that as the number of cities (points) increases, the complexity grows exponentially. The objective of the TSP is to find the shortest possible route that allows a traveling salesman to visit each city exactly once and return to the starting city.

The problem can be described as follows:
    Given a set of cities and the distances between each pair of cities, the task is to find a tour that visits all cities exactly once and has the minimum total distance.
    The tour must form a closed loop, meaning the salesman returns to the city from which he started.
    The salesman is not required to visit all cities in a specific order; he just needs to find the optimal sequence that minimizes the total distance traveled.

The Travelling Salesman is yet somewhat similar to a Hamiltonian Circuit. There are multiple ways to solve this problem which includes Naive Method, Brunch and Bound, Dynamic Programming, Approxmation Method etc. This Algorithm solves this problem using Dynamic Programming in a time complexity of 2n*n^2 which makes this solution better than the Naive and Brunch and Bound Method. 

This solution to solve this problem is quite common and can be found on multiple website and videos (including geeksforgeeks, tutorialspoint, programiz)but a major flaw that i have found in the online solutions is that it only work for complete graphs. Considering a graph that is not completely connected meaning there exists a vertice that contains an edge to other vertices but not all the vertices.
In such a case I have found the online solutions to fail giving wrong answer including all the that i researched on. SO I have developed this solution; most part of this solution is  Basic File Handling but the real magic happens in the recursive function and uses a Dynamic Approach to solve this problem.
    
<img width="863" alt="Travelling" src="https://github.com/umairkhalidx/Travelling-Salesman/assets/109782978/74b3ccf8-25e7-43dc-aefc-7b790ed3b355">

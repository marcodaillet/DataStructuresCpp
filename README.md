# Ft_containers

The goal here was to re-implement four containers of the Standard Template Library in C++: Vector, Stack, Map, and Set.  
I also implemented an iterators system for each of them (except stack even if we can use it because stack inherits from the vector class), and all C++ tools listed below.  
• Iterators_traits : the characteristics of iterators.  
• Reverse_iterator : an iterator starting at the end.  
• Enable_if : a tool allowin the exection of a segment of code depending on the boolean return value passed as parameter.  
• Is_integral : returns true if type passed is integral.  
• Lexicographical_compare : compare a range of iterators.  
• std::pair : the standard pair class used in map.  
  
You can make and then make diff to compare my containers outputs with the stl containers outputs.  
  
For the Map and Set, I had to implement a red-black binary tree, which I think was the more interesting part of this project because of how performing this tree is in comparion of others way of storing data (OlogN time complexity).  
Exemple of a Red-Black tree :  
  
Red-black_tree_example svg  :
  
![Red-black_tree_example svg](https://user-images.githubusercontent.com/55747965/155562232-1a459469-5381-4256-a69e-8b5884768362.png)  
  
Specs of a Red-Black tree :  
• Every node in T is either red or black.  
• The root node of T is black.  
• Every NULL node is black.  
• If a node is red, both of its children are black.  
• Every path from a root node to a NULL node has the same number of black nodes.  
  
Respecting those rules are quite the challenge when you try to insert or erase elements, but overall, with documentations, it is pretty straigthforward.  

Sources :  
  https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/  
  https://www.cplusplus.com/

Here is a gif of the testing part with my containers on the left column and the stl's on the right (spoiler its the same):  
  
![Containers](https://user-images.githubusercontent.com/55747965/155561838-6d04d53b-a2ba-4c3b-b86b-ead94e47b074.gif)


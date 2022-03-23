/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 *
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 *
 * Date: 2021-02
 */

#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;
#include "Direction.hpp"
using ariel::Direction;

#include <string>
#include <algorithm>
using namespace std;

Notebook notebook1;
Notebook notebook2;
Notebook notebook3;

TEST_CASE("notebook 1")
{
	// Test Case 1 --> notebook 1;
	notebook1.write(0,0,0,Direction::Horizontal,"abc");
	notebook1.write(0,0,0,Direction::Vertical,"abc");
	
	CHECK(notebook1.read(0,0,0,Direction::Horizontal,3) == "abc");
	CHECK(notebook1.read(0,0,0,Direction::Vertical,3) == "abc");
	CHECK(notebook1.read(0,0,0,Direction::Horizontal,3) != "ABC");
	CHECK(notebook1.read(0,1,0,Direction::Horizontal,1) == "b");
	CHECK(notebook1.read(0,2,0,Direction::Horizontal,1) == "c");
	
	notebook1.erase(0,0,0,Direction::Horizontal,1);
	notebook1.erase(0,0,2,Direction::Horizontal,1);

	CHECK( notebook1.read(0,0,0,Direction::Horizontal,3) == "~b~");
	CHECK(notebook1.read(0,0,0,Direction::Vertical,3)=="~bc");
	CHECK(notebook1.read(0,0,0,Direction::Horizontal,3) != "abc");	

	notebook1.erase(0,0,0,Direction::Horizontal,3);
	notebook1.erase(0,0,0,Direction::Vertical,3);

	CHECK(notebook1.read(0,0,0,Direction::Horizontal,3) == "~~~");
	CHECK(notebook1.read(0,0,0,Direction::Vertical,3) == "~~~");

}
TEST_CASE("notebook 2")
{
	// Test Case 2 --> notebook 2;
	notebook2.write(300,5,0,Direction::Horizontal,"Memories have to be our most painful blessing - Kanye West");
	notebook2.write(300,6,0,Direction::Horizontal,"No matter where life takes me. Find me with a smile - Mac Miller");
	notebook2.write(300,7,0,Direction::Horizontal,"Life’s a b****, but god forbid that b**** divorce me - Nas");
	notebook2.write(300,8,0,Direction::Horizontal,"You’ve got enemies? Good, that means you actually stood up for something - Eminem");
	notebook2.write(300,9,0,Direction::Horizontal,"Chuba chuba chuba chuba chuba chuba chubby - Eminem");
	notebook2.write(300,10,0,Direction::Horizontal,"If you stop at general math, you’re only going to make general math money - Snoop Dogg");
	
	CHECK_FALSE(notebook2.read(299,5,0,Direction::Horizontal,59) != "Memories have to be our most painful blessing - Kanye West");
	CHECK_FALSE(notebook2.read(300,5,0,Direction::Horizontal,30) != "Memories have to be our most painful blessing - Kanye West");
	CHECK(notebook2.read(300,5,0,Direction::Horizontal,59) == "Memories have to be our most painful blessing - Kanye West");
	CHECK(notebook2.read(300,5,0,Direction::Vertical,6) == "MNLYCI");
	CHECK(notebook2.read(300,5,10,Direction::Vertical,6) == "h btuo");
	CHECK(notebook2.read(300,6,55,Direction::Horizontal,6) == "Mac Miller"); 
	CHECK(notebook2.read(300,10,79,Direction::Horizontal,6) == "Snoop Dogg");
	
	notebook2.erase(300,10,79,Direction::Vertical,6); // Deleting 'Snoop Dogg' ->"~~~~~~~~~~".
	notebook2.erase(300,7,0,Direction::Horizontal,58); // Delete all seq, all left is Nas.
	notebook2.erase(300,6,56,Direction::Horizontal,1); // "M~c Miller"
	notebook2.erase(300,6,65,Direction::Horizontal,1); // "M~c M~ller"
	notebook2.erase(300,6,68,Direction::Horizontal,1); // "M~c M~ll~r"

	CHECK(notebook2.read(300,10,79,Direction::Vertical,6) == "~~~~~~~~~~");
	CHECK(notebook2.read(300,7,0,Direction::Vertical,61) == "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Nas");
	CHECK(notebook2.read(300,6,55,Direction::Vertical,6) == "M~c M~ll~r"); 

}

TEST_CASE("Bad input")
{
	// Test Case 3 --> notebook 3;

	// Check write for bad input  --> string size = 89, strating write at 20 --> total length is too big (109 > 100).
	CHECK_THROWS(notebook3.write(300,10,20,Direction::Horizontal,"If you stop at general math, you’re only going to make general math money - Snoop Dogg"));
	CHECK_THROWS(notebook3.write(300,9,0,Direction::Horizontal,"Chuba chuba chuba chuba chuba chuba chubby I don't have any lines to go right here So, chubba-Teletubby - Eminem"));


	// Check write for bad input  --> '~'
	CHECK_THROWS(notebook3.write(172,10,20,Direction::Vertical,"Snoop ~~~ Dogg ~~~ "));


	// Check read for bad input  page/ row/ column.
	notebook3.write(0,0,0,Direction::Horizontal,"abc");
	notebook3.write(0,0,0,Direction::Vertical,"abc");
	
	CHECK_THROWS(notebook3.read(-1,0,0,Direction::Horizontal,3));
	CHECK_THROWS(notebook3.read(0,-1,0,Direction::Horizontal,3));
	CHECK_THROWS(notebook3.read(0,0,-1,Direction::Horizontal,3));
	CHECK_THROWS(notebook3.read(0,0,150,Direction::Horizontal,3));
	CHECK_THROWS(notebook3.write(300,9,0,Direction::Horizontal,"Chuba chuba chuba chuba chuba chuba chubby I don't have any lines to go right here So, chubba-Teletubby - Eminem"););
	
}



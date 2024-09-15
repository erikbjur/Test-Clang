#include <algorithm>
#include <format>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Entity.h"

#include <utility>
#include <ranges>
#include <chrono>

int main()
{
  unsigned int nextID = 0;
  const unsigned int NUMBER_OF_OBJECTS = 1000000;

  std::cout << "Enter the index of the object you want to find later (0 - 1000000):\n";
  
  unsigned int ELEMENT_INDEX_TO_FIND = 0;
  std::cin >> ELEMENT_INDEX_TO_FIND;

      std::cout << "Creating the map..." << std::endl;

  // Create a new unordered map
  std::unordered_map<unsigned int, std::unique_ptr<MyApp::Entity>> DataStorage_unordered_map;

  auto start_time = std::chrono::high_resolution_clock::now();
  for( int i = 0; i < NUMBER_OF_OBJECTS; ++i ) {
    // Create a unique pointer of an Entity object
    std::unique_ptr<MyApp::Entity> myEntity = std::make_unique<MyApp::Entity>();
    myEntity->Name = std::format( "Entity #{}", i );
    myEntity->ObjectID = nextID;
    nextID++;

    // Move new entity into map
    DataStorage_unordered_map.try_emplace( myEntity->ObjectID, std::move( myEntity ) );
  }
  auto end_time = std::chrono::high_resolution_clock::now();

  // Calculate the time it took in milliseconds
  std::chrono::duration<double, std::milli> time_in_ms = end_time - start_time;

  // Print the time it took
  std::cout << "It took " << time_in_ms << " ms to load the unordered_map\n";

  // Print the count of objects added to the DataStorage
  std::cout << "The total number of objects in the unordered_map is " << DataStorage_unordered_map.size() << std::endl;

  // Now lets find an object in the unordered_map
  start_time = std::chrono::high_resolution_clock::now();
  const auto& it = DataStorage_unordered_map.find( ELEMENT_INDEX_TO_FIND );
  end_time = std::chrono::high_resolution_clock::now();
  time_in_ms = end_time - start_time;
  const auto& [key, object] = *it;
  std::cout << "It took " << time_in_ms << " ms to find " << object->Name << " using unorderd_map::find()\n";

  // Now clearing out the datastorage
  std::cout << "Done... Now deleting all the elements" << std::endl;
  start_time = std::chrono::high_resolution_clock::now();
  DataStorage_unordered_map.clear();
  end_time = std::chrono::high_resolution_clock::now();
  std::cout << "Done deleting elements!" << std::endl;
  time_in_ms = end_time - start_time;
  std::cout << "It took " << time_in_ms << " ms to delete the unordered_map\n";
  std::cout << "There are now " << DataStorage_unordered_map.size() << " elements in the unordered_map." << std::endl;

  // Now try it with a vector
  // Create a new vector
  std::cout << "Starting tests with vector...\n";
  nextID = 0; // Reset the index to zero
  std::vector<std::unique_ptr<MyApp::Entity>> DataStorage_vector;

  start_time = std::chrono::high_resolution_clock::now();
  for( int i = 0; i < NUMBER_OF_OBJECTS; ++i ) {
    // Create a unique pointer of an entity object
    std::unique_ptr<MyApp::Entity> myEntity = std::make_unique<MyApp::Entity>();
    myEntity->Name = std::format( "Entity #{}", i );
    myEntity->ObjectID = nextID;
    nextID++;

    // Move new entity into map
    DataStorage_vector.push_back( std::move( myEntity ) );
  }
  end_time = std::chrono::high_resolution_clock::now();
  time_in_ms = end_time - start_time;
  std::cout << "It took " << time_in_ms << " ms to load the vector\n";

  // Print the count of objects added to the DataStorage
  std::cout << "The total number of objects in the vector is " << DataStorage_vector.size() << std::endl;

  // Now lets find an object in the vector
  start_time = std::chrono::high_resolution_clock::now();
  // Use ranges to find if an element with the target int value exists
  auto iterator = std::ranges::find_if( DataStorage_vector, [ELEMENT_INDEX_TO_FIND]( const auto& obj ) {
    return obj->ObjectID == ELEMENT_INDEX_TO_FIND;
  } );
  end_time = std::chrono::high_resolution_clock::now();
  time_in_ms = end_time - start_time;

  if( iterator != DataStorage_vector.end() ) {
    const auto& object_from_vector = *iterator;
    std::cout << "It took " << time_in_ms << " ms using ranges::find_if() to find " << object_from_vector->Name
              << std::endl;
  } else {
    std::cout << "Element with object id " << ELEMENT_INDEX_TO_FIND << " not found." << std::endl;
  }

  // Use std::find_if to find if an element with the target int value exists
  start_time = std::chrono::high_resolution_clock::now();
  iterator =
      std::find_if( DataStorage_vector.begin(), DataStorage_vector.end(),
                    [ELEMENT_INDEX_TO_FIND]( const auto& obj ) { return obj->ObjectID == ELEMENT_INDEX_TO_FIND; } );
  end_time = std::chrono::high_resolution_clock::now();
  time_in_ms = end_time - start_time;

  if( iterator != DataStorage_vector.end() ) {
    const auto& object_from_vector = *iterator;
    std::cout << "It took " << time_in_ms << " ms using std::find_if() to find " << object_from_vector->Name
              << std::endl;
  } else {
    std::cout << "Element with object id " << ELEMENT_INDEX_TO_FIND << " not found." << std::endl;
  }

  // Now clearing out the datastorage
  std::cout << "Done... Now deleting all the elements" << std::endl;
  start_time = std::chrono::high_resolution_clock::now();
  DataStorage_vector.clear();
  end_time = std::chrono::high_resolution_clock::now();
  time_in_ms = end_time - start_time;
  std::cout << "Done deleting elements!" << std::endl;
  std::cout << "It took " << time_in_ms << " ms to delete the vector\n";
  std::cout << "There are now " << DataStorage_vector.size() << " elements in the vector." << std::endl;

  return 0;
}
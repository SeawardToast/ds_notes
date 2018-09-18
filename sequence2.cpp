#include "sequence2.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
 // TYPEDEFS and MEMBER CONSTANTS
        

sequence::sequence(sequence::size_type initial_capacity){
	data = new value_type[initial_capacity];
	capacity = initial_capacity;
	used = 0;
	current_index = 0;
}

sequence::sequence(const sequence& source){
	if(this != &source) {
		data = new value_type [source.capacity];
		std::copy(source.data, source.data+source.used, data);
		capacity = source.capacity;
		used = source.used;
		
			current_index = source.current_index;
	
	}
}

sequence::~sequence( ){
		delete [] data;
}


// MODIFICATION MEMBER FUNCTIONS
void sequence::resize(size_type new_capacity){
	//this function is meant to allocate data for a bag during an insert or attach function
	value_type *larger_array;

	if(new_capacity == capacity)
		return; // not neccesary to allocate any more memory
  
    if(new_capacity < used)
		new_capacity = used; //cannot allocate less than we are using
    
    larger_array = new value_type[new_capacity];
    std::copy(data, data+used, larger_array);
    delete [] data; //no need for old block of memory, delete it
    data = larger_array; //data needs to point to new memory block now, point data to the new memory block
	capacity = new_capacity; //set capacity to new capacity
}

void sequence::start( ){
	current_index = 0;
}

void sequence::advance( ){
	if(is_item())
	current_index++;
}

void sequence::insert(const value_type& entry){
        if( size() == capacity ) 
			resize(used+1);
		if(!is_item()) 
			current_index = 0;
		for(size_type i = used; i>current_index; --i)
			data[i] = data[i-1];
		data[current_index] = entry;
		++used;
}

void sequence::attach(const value_type& entry){
		if( size() == capacity )
			resize(used+1);
		if(!is_item()) 
			current_index = used-1;
		++current_index;
		for(size_type i = used; i>current_index;--i)
			data[i] = data[i-1];
		data[current_index] = entry;
		++used;
}

void sequence::remove_current( ){
	    assert(is_item());
        for(int i = current_index; i < used-1; ++i)
            data[i] = data[i+1];
        used--;
}
        
void sequence::operator =(const sequence& source){
	
	if(this == &source) return;
	value_type *new_data = new value_type [source.capacity];
	std::copy(source.data, source.data+source.used, new_data);
	delete [] data;
	data = new_data;
	used = source.used;
	capacity = source.capacity;
		current_index = source.current_index;
	
}
        // CONSTANT MEMBER FUNCTIONS
sequence::size_type sequence::size( ) const{
	return used;	
}
        
bool sequence::is_item( ) const{
	return (current_index < used);
}
        
sequence::value_type sequence::current( ) const{
	return data[current_index];
}

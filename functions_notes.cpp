

/*
Whenever a function is called, the program passes through the following stages. 

	Pre call

	prologue

	function

	epilogue

	post call
*/

//The easiest thing to implement is to spill every register, and then restore every register as well. 
	//REMEMBER to spill the return address as well. 
	//jal - jump and link - mips command to do function calls. 

//The Frame pointer moves with function calls, but it doesn't move during the lifetime of the function. Or it's as if it didn't move. 

//The frame pointer points into the middle of the activation record. 
	//Everything below the frame pointer is the precall 
	//Everything above the frame pointer is the prologue. 
	
	//Function parameters should be positive offsets from the frame pointer. 
		//That offset information should be put in two places
			//The global symbol table for the function call, so that the caller knows where to put things
			//The local symbol table of the function, so that the function knows where to find its parameters. 











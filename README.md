# Branch Predictors

This project measures the effectiveness of several branch direction predictors on a number of 
traces of conditional branch instructions. Each line in the trace contains the following 
information for each branch: the program counter (expressed as a word address), the actual 
outcome of the branch, and the target of the branch.
	
# Here are the branch predictors that are implemented
## Always taken and Alway not taken
	These functions calculate branch predictions based on a simple rule:
	readtaken counts a branch as taken (T) and increments a counter when 
	the "behavior" field in the trace file is "T." readnottaken counts a branch 
	as not taken (NT) and increments a counter when the "behavior" field in the 
	trace file is "NT."
	
## Bimodal Predictions with a single bit of history
	This function implements a bimodal predictor with various table sizes (e.g., 
	16, 32, 128, 256, 512, 1024, 2048 entries). It uses a table of counters 
	(initialized to true) and a hash function to index the table based on the address. 
	For each branch in the trace file, it checks whether the prediction in the table matches 
	the actual behavior. If they match, it increments the correct predictions counter. 
	If not, it updates the table.

## Bimodal Predictor with 2 bit saturating counters
	This function implements a two-bit predictor with various table sizes. It uses 
	a table of two-bit saturating counters for each table entry. For each branch in 
	the trace file, it checks the counter's value in the table based on the address and 
	updates the counter according to the actual behavior (taken or not taken).
	It also keeps track of correct predictions based on the counter's state.
	
## Gshare Predictor
	This function implements a gshare predictor with different global history register 
	(GHR) sizes (ranging from 2^3 to 2^11). It uses a table of two-bit saturating 
	counters and combines the global history register with the address to index the 
	table. For each branch in the trace file, it updates the GHR and uses it to index the 
	table and it checks whether the prediction in the table matches the actual behavior and 
	increments the correct predictions counter accordingly.
	
## Tournament Predictor
	This function combines the bimodal and gshare predictors to create a tournament
	predictor. It maintains separate tables for bimodal and gshare predictors as 
	well as a selector table. For each branch in the trace file, it makes predictions 
	using both predictors and then uses the selector table to choose which prediction to use. 
	It tracks correct predictions based on the selected prediction.
	
## Branch Target Buffer
	This function implements a branch target buffer (btb) predictor with 512 entries. It 
	uses a table to store target addresses for taken branches. For each branch in 
	the trace file, it checks the BTB for the predicted target address based on the branch's
	address. It compares the predicted target with the actual target and increments the 
	correct predictions counter if they match.

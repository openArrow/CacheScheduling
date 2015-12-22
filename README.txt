The Code reades the trace.lis format file
The format of trace file is as follows: Every line in every file has four fields
1. First field: starting block
2. Second field: number of blocks (each block is 512 bytes)
3. Third field: ignore
4. Fourth field: request number (starts at 0)


The code for LRU and ARC are in the respective folder
Each folder contains script.sh file to compile and Run  the program
Follow the following steps to compile code:
1.Move to folder LRU or ARC
2.change mode of script.sh to executable using command:sudo chmod +x script.sh
3.run the script file giving it two command line parameters
first parameter:size of cache
second parameter:file path
Example:./script.sh 1024 ./P3.lis

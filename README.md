# encryption_using_ga
This contains a Genetic Algorithm based Encryption of a file.The file is read in blocks of 32 and the process of crossover and mutation is applied to the blocks and there is a key generated for each block which is the key to decrypt that block.Now after the encryption process is over the overall strength of the present encryption is compared to the encryption in the previous iteration and the stronger one prevails.This way after getting the stronger encryption we write the file and the corresponding keys to the keys file.
We have also applied huffmann coding to reduce the size of the file and remove redundancy.
The folder compress contains a shell script which runs the programs sequentially.

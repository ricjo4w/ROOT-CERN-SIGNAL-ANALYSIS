******************************************************************************************
                                     Instructions
******************************************************************************************

Programs included:
	- machRun.C
	- machEval.C
	- Grapher.C
	- multiRun.C
	- fitMass.C(on Gat6 server)
	
USE:
	1.) Open multiRun.C in a text editor
	2.) Set the name and location of the signal tree
	3.) Set the name, location, and branch name of the real-data tree
	4.) Choose a method (For list of avaliable methods, look in the method array)
	5.) Choose a number of nodes in each layer (I find 15, 10 works best for me, but yours may very)
	6.) Add a call to the fitMass.C program with the specified root files following with identifiers(I do not have the fitMass files, but I believe I left them in a finished state on the server. The input method is simple to follow at the top input variables.)
	6.) Run multiRun.C